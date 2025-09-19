# Base image
FROM ubuntu:22.04

# Set non-interactive mode for apt
ENV DEBIAN_FRONTEND=noninteractive

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    python3-pip \
    git \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Install Conan globally
RUN pip3 install conan

# Create working directory
WORKDIR /app

# Copy project files into the container
COPY . .

# Optional: configure Conan remotes or profiles
RUN conan profile detect --force

# Install dependencies
RUN conan install . --build=missing -c tools.system.package_manager:mode=install

# Build makefile
RUN cmake --preset conan-release

# Build targets
RUN cmake --build build/Release

# Project built succesfully
RUN echo "✅ Particle View built succesfully"
