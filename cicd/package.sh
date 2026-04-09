#!/bin/bash
set -e
VERSION="1.0"
PACKAGE_NAME="programm"
echo "Creating .deb package..."
mkdir -p build/
dpkg-buildpackage -us -uc
echo "Package $PACKAGE_NAME-$VERSION.deb created successfully"
