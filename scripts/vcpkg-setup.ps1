Set-Variable -Name VCPKG_DIR -Value "$(Join-Path "$PSScriptRoot" "..\extern\vcpkg" -Resolve)"

& "$VCPKG_DIR\bootstrap-vcpkg.bat"
& "$VCPKG_DIR\vcpkg.exe" install bzip2:x64-windows
