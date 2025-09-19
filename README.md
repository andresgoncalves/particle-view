# Particle View

```sh
# Install dependencies
conan install . --build=missing -c tools.system.package_manager:mode=install

# Build makefile
cmake --preset conan-release

# Build targets
cmake --build build/Release

# Run main target
./build/Release/main
```
