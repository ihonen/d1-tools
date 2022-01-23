#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

// -----------------------------------------------------------------------------

enum class LogLevel
{
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Fatal,
};

LogLevel verbosityToLogLevel(
    unsigned verbosity
);

unsigned logLevelToVerbosity(
    LogLevel level
);

// -----------------------------------------------------------------------------

class LogBuffer : public std::stringbuf
{
public:

    LogBuffer(
        const std::filesystem::path& logFilePath,
        bool stdoutEnabled,
        LogLevel thresholdLevel
    );

    ~LogBuffer(
    ) override;

    void setFile(
        const std::filesystem::path& logFile
    );

    void setStdoutEnabled(
        bool stdoutEnabled
    );

    void setActiveLevel(
        LogLevel level
    );
    
    void setThresholdLevel(
        LogLevel level
    );

    int sync(
    ) override;

private:

    std::filesystem::path m_logFilePath;

    std::ofstream m_logFile;
    bool m_stdoutEnabled;

    LogLevel m_activeLevel;
    LogLevel m_thresholdLevel;
};

// -----------------------------------------------------------------------------

class Log : private std::ostream
{
public:

    static Log& get(
    );

    static void setThresholdLevel(
        LogLevel level
    );
    
    static void setFile(
        const std::filesystem::path& logFile
    );

    static void setStdoutEnabled(
        bool stdoutEnabled
    );

    static std::ostream& trace(
    );

    static std::ostream& debug(
    );

    static std::ostream& info(
    );

    static std::ostream& warning(
    );

    static std::ostream& error(
    );

    static std::ostream& fatal(
    );

private:

    Log(
        const std::filesystem::path& logFile = "",
        bool stdoutEnabled = true,
        LogLevel thresholdLevel = LogLevel::Trace
    );

    ~Log(
    ) override;

    static void setActiveLevel(
        LogLevel level
    );

private:

    LogBuffer m_buffer;
};
