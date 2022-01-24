#include "common/log.hh"

// -----------------------------------------------------------------------------

namespace
{
    constexpr const char* TracePrefix   = "TRACE:   ";
    constexpr const char* DebugPrefix   = "DEBUG:   ";
    constexpr const char* InfoPrefix    = "INFO:    ";
    constexpr const char* WarningPrefix = "WARNING: ";
    constexpr const char* ErrorPrefix   = "ERROR:   ";
    constexpr const char* FatalPrefix   = "FATAL:   ";
}

// -----------------------------------------------------------------------------

LogLevel verbosityToLogLevel(
    unsigned verbosity
)
{
    switch (verbosity)
    {
    case 0: return LogLevel::Fatal;
    case 1: return LogLevel::Error;
    case 2: return LogLevel::Warning;
    case 3: return LogLevel::Info;
    case 4: return LogLevel::Debug;
    case 5: return LogLevel::Trace;
    }

    return LogLevel::Trace;
}

unsigned logLevelToVerbosity(
    LogLevel level
)
{
    switch (level)
    {
    case LogLevel::Fatal:   return 0;
    case LogLevel::Error:   return 1;
    case LogLevel::Warning: return 2;
    case LogLevel::Info:    return 3;
    case LogLevel::Debug:   return 4;
    case LogLevel::Trace:   return 5;
    }

    return 5;
}

// -----------------------------------------------------------------------------

LogBuffer::LogBuffer(
    const std::filesystem::path& logFilePath,
    bool stdoutEnabled,
    LogLevel thresholdLevel
)
    : m_logFilePath(logFilePath)
    , m_logFile(logFilePath)
    , m_stdoutEnabled(stdoutEnabled)
    , m_thresholdLevel(thresholdLevel)
    , m_activeLevel(LogLevel::Trace)
{
}

LogBuffer::~LogBuffer(
)
{
    std::cout << std::flush;
    m_logFile << std::flush;
}

void LogBuffer::setFile(
    const std::filesystem::path& logFile
)
{
    m_logFile = std::ofstream(logFile);
}

void LogBuffer::setStdoutEnabled(
    bool stdoutEnabled
)
{
    m_stdoutEnabled = stdoutEnabled;
}

void LogBuffer::setActiveLevel(
    LogLevel level
)
{
    m_activeLevel = level;
}

void LogBuffer::setThresholdLevel(
    LogLevel level
)
{
    m_thresholdLevel = level;
}

int LogBuffer::sync(
)
{
    if (str().empty())
    {
        return 0;
    }

    bool printSuccess = true;
    if (m_stdoutEnabled && m_activeLevel >= m_thresholdLevel)
    {
        switch (m_activeLevel)
        {
        case LogLevel::Trace:
        case LogLevel::Debug:
        case LogLevel::Info:
        case LogLevel::Warning:
            std::cout << str() << std::flush;
            printSuccess = static_cast<bool>(std::cout);
            break;
        case LogLevel::Error:
        case LogLevel::Fatal:
            std::cerr << str() << std::flush;
            printSuccess = static_cast<bool>(std::cerr);
            break;
        }
    }

    bool fileSuccess = true;
    if (!m_logFilePath.empty())
    {
        m_logFile << str() << std::flush;
        fileSuccess = static_cast<bool>(m_logFile);
    }

    str("");

    return printSuccess && fileSuccess ? 0 : -1;
};

// -----------------------------------------------------------------------------

Log& Log::get(
)
{
    static Log instance;
    return instance;
}

void Log::setActiveLevel(
    LogLevel level
)
{
    get().m_buffer.setActiveLevel(level);
}

void Log::setThresholdLevel(
    LogLevel level
)
{
    get().m_buffer.setThresholdLevel(level);
}

void Log::setFile(
    const std::filesystem::path& logFile
)
{
    get().m_buffer.setFile(logFile);
}

void Log::setStdoutEnabled(
    bool stdoutEnabled
)
{
    get().m_buffer.setStdoutEnabled(stdoutEnabled);
}

std::ostream& Log::trace(
)
{
    get() << TracePrefix;
    setActiveLevel(LogLevel::Trace);
    return get();
}

std::ostream& Log::debug(
)
{
    get() << DebugPrefix;
    setActiveLevel(LogLevel::Debug);
    return get();
}

std::ostream& Log::info(
)
{
    get() << InfoPrefix;
    setActiveLevel(LogLevel::Info);
    return get();
}

std::ostream& Log::warning(
)
{
    get() << WarningPrefix;
    setActiveLevel(LogLevel::Warning);
    return get();
}

std::ostream& Log::error(
)
{
    get() << ErrorPrefix;
    setActiveLevel(LogLevel::Error);
    return get();
}

std::ostream& Log::fatal(
)
{
    get() << FatalPrefix;
    setActiveLevel(LogLevel::Fatal);
    return get();
}

// -----------------------------------------------------------------------------

Log::Log(
    const std::filesystem::path& logFile,
    bool stdoutEnabled,
    LogLevel thresholdLevel
)
    : std::ostream(&m_buffer)
    , m_buffer(logFile, stdoutEnabled, thresholdLevel)
{
}

Log::~Log(
)
{
    flush();
}
