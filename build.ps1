# Parse command-line arguments
param (
    [string]$Config = "Release"  # Default value if not provided
)

# Determine build type and build directory
$BUILD_TYPE = $Config
$BUILD_DIR = "build-release"

# Function to display usage information
function Usage
{
    Write-Host "ERROR in arguments. Please use one of the following:"
    Write-Host "$0 [-c <Debug|Release|RelWithDebInfo> for the configuration you want for the binary]"
    exit 1
}

# Set build directory based on the provided configuration
switch ($BUILD_TYPE)
{
    "Debug" {
        $BUILD_DIR = "build-debug"
    }
    "RelWithDebInfo" {
        $BUILD_DIR = "build-relwithdebinfo"
    }
    "Release" {
        $BUILD_DIR = "build-release"
    }
    default {
        Write-Host "Invalid build type: $BUILD_TYPE"
        Usage
    }
}

# Create build directory if it doesn't exist
if (-Not (Test-Path -Path $BUILD_DIR))
{
    New-Item -ItemType Directory -Path $BUILD_DIR | Out-Null
}

# Change to the build directory
Set-Location -Path $BUILD_DIR

# Install dependencies if in Debug mode
if ($BUILD_TYPE -eq "Debug")
{
    & conan install .. --output-folder=_deps --build=missing -s build_type=Debug
}

# Run CMake to configure the project
& cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -Wno-dev ..

# Build the project
& cmake --build . --config $BUILD_TYPE
