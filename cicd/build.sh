#!/bin/bash
set -e
echo "Starting build process..."
sudo make
sudo make install
echo "Build completed successfully"
