#!/bin/bash

set -e

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$PROJECT_DIR/build/Release"
EXECUTABLE="$BUILD_DIR/main"
BUNDLE_DIR="$PROJECT_DIR/particle-view-bundle"

if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: Executable not found at $EXECUTABLE"
    exit 1
fi

echo "Creating bundle directory..."
rm -rf "$BUNDLE_DIR"
mkdir -p "$BUNDLE_DIR/lib"

echo "Copying executable..."
cp "$EXECUTABLE" "$BUNDLE_DIR/particle-view"

echo "Finding Qt dependencies..."

# Function to copy library and its dependencies recursively
copy_library() {
    local lib_path="$1"
    local lib_name=$(basename "$lib_path")
    
    # Skip if already copied
    if [ -f "$BUNDLE_DIR/lib/$lib_name" ]; then
        return
    fi
    
    # Skip system libraries
    if [[ "$lib_path" == /lib/* ]] || [[ "$lib_path" == /usr/lib/* ]] || [[ "$lib_path" == /lib64/* ]]; then
        return
    fi
    
    # Copy the library
    echo "Copying $lib_name..."
    cp "$lib_path" "$BUNDLE_DIR/lib/"
    
    # Find dependencies of this library
    ldd "$lib_path" 2>/dev/null | grep "=>" | awk '{print $3}' | while read dep; do
        if [ -f "$dep" ] && [[ "$dep" == *Qt* ]]; then
            copy_library "$dep"
        fi
    done
}

# Find Qt libraries used by the executable
ldd "$EXECUTABLE" | grep "=>" | awk '{print $3}' | while read lib; do
    if [ -f "$lib" ] && [[ "$lib" == *Qt* ]]; then
        copy_library "$lib"
    fi
done

# Create a launch script that sets LD_LIBRARY_PATH
echo "Creating launch script..."
cat > "$BUNDLE_DIR/run-particle-view.sh" << 'EOF'
#!/bin/bash
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export LD_LIBRARY_PATH="$SCRIPT_DIR/lib:$LD_LIBRARY_PATH"
exec "$SCRIPT_DIR/particle-view" "$@"
EOF

chmod +x "$BUNDLE_DIR/run-particle-view.sh"

echo "Bundle created successfully in $BUNDLE_DIR"
echo "Contents:"
ls -la "$BUNDLE_DIR"
echo "Libraries:"
ls -la "$BUNDLE_DIR/lib"

# Create tarball for artifact
echo "Creating tarball..."
cd "$PROJECT_DIR"
tar -czf particle-view-bundle.tar.gz -C particle-view-bundle .

echo "Bundle tarball created: particle-view-bundle.tar.gz"