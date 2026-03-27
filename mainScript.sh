#!/bin/bash

# 1. Get the absolute path to the directory where THIS script lives
PROJECT_ROOT="$(cd "$(dirname "$0")" && pwd)"

# 2. Change the working directory to that root
cd "$PROJECT_ROOT" || exit
>>>>>>> 2edadbf (15:(feat): make running scripts better)
# If $1 is empty, choice becomes 1
choice=${1:-1}

case $choice in
  1)
    echo "Starting Build (Default)..."
		./scripts/run.sh
    ;;
    
  2)
    echo "Remaking CMake Config"
		./scripts/remakeRun.sh
    ;;

  3)
    echo "Cleaning build directory..."
		./scripts/cleanRun.sh
    ;;

  *)
    echo "Error: '$choice' is not a valid option."
    echo "Usage: ./mainScript.sh [1|2|3]"
    exit 1
    ;;
esac
