#!/usr/bin/env bash

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR/.."

echo "Generating Doxygen documentation..."
doxygen Doxyfile

echo "Documentation generated in ./doxygen/html/"
echo "Open ./doxygen/html/index.html in a browser to view."
