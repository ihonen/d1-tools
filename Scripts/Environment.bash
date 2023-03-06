GAME_DIR="$HOME/.steam/debian-installation/steamapps/common/Desperados Wanted Dead or Alive"
NUM_CPU_CORES="$(nproc)"

# ------------------------------------------------------------------------------

PROJECT_DIR="$(dirname $BASH_SOURCE)/.."

# ------------------------------------------------------------------------------

BUILD_DIR="$PROJECT_DIR/.build"
SRC_DIR="$PROJECT_DIR"

INSTALL_DIR_DEBUG="$PROJECT_DIR/.install/debug"
INSTALL_DIR_RELEASE="$PROJECT_DIR/.install/release"

# ------------------------------------------------------------------------------

if [ ! -d "$GAME_DIR" ]; then
    echo "WARNING: The GAME_DIR variable is set to '$GAME_DIR' which does not exist"
fi
