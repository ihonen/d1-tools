. "$PSScriptRoot\env.ps1"

# ------------------------------------------------------------------------------

function Configure
{
    cmake -B "$BUILD_DIR" -S "$SRC_DIR"
}

function Build-Debug
{
    Configure
    cmake --build "$BUILD_DIR" --config "Debug" --parallel "$NUM_CPU_CORES"
}

function Build-Release
{
    Configure
    cmake --build "$BUILD_DIR" --config "Release" --parallel "$NUM_CPU_CORES"
}

function Install-Debug
{
    Build-Debug
    cmake --install "$BUILD_DIR" --config "Debug" --prefix "$INSTALL_DIR_DEBUG"
}

function Install-Release
{
    Build-Release
    cmake --install "$BUILD_DIR" --config "Release" --prefix "$INSTALL_DIR_RELEASE"
}

function Uninstall-Debug
{
    Remove-Item -Recurse "$INSTALL_DIR_DEBUG"
}

function Uninstall-Release
{
    Remove-Item -Recurse "$INSTALL_DIR_RELEASE"
}

function Clean
{
    Remove-Item -Recurse "$BUILD_DIR"
}
