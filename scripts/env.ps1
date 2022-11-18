Set-Variable -Name GAME_DIR            -Value "C:\Program Files (x86)\Steam\steamapps\common\Desperados Wanted Dead or Alive"
Set-Variable -Name NUM_CPU_CORES       -Value "16"

# ------------------------------------------------------------------------------

Set-Variable -Name PROJECT_DIR         -Value "$(Join-Path "$PSScriptRoot" ".." -Resolve)"

# ------------------------------------------------------------------------------

Set-Variable -Name BUILD_DIR           -Value "$PROJECT_DIR\.build"
Set-Variable -Name SRC_DIR             -Value "$PROJECT_DIR"

Set-Variable -Name INSTALL_DIR_DEBUG   -Value "$PROJECT_DIR\.install"
Set-Variable -Name INSTALL_DIR_RELEASE -Value "$GAME_DIR\tools"

# ------------------------------------------------------------------------------

if (-not (Test-Path -Path "$GAME_DIR" -PathType Container))
{
    Write-Output "WARNING: The GAME_DIR variable is set to '$GAME_DIR' which does not exist"
}
