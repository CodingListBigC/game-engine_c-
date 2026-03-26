#!/bin/bash

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
