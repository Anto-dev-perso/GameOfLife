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

function Invoke-Process {
    param (
        [string]$Executable,    # The command to run
        [string]$Arguments,     # Arguments to pass to the command
        [int]$Timeout = 30000   # Timeout in milliseconds (default: 60 seconds)
    )

    Write-Host "Running: $Executable $Arguments"

    # Start the process and wait for it to complete
    $process = Start-Process -FilePath $Executable -ArgumentList $Arguments -NoNewWindow -PassThru -Wait

    # Wait for the process to exit, with a timeout
    if (-not $process.WaitForExit($Timeout)) {
        $process.Kill()
        throw "Process '$Executable' timed out after $($Timeout / 1000) seconds."
    }

    # Check the exit code
    if ($process.ExitCode -ne 0) {
        throw "Process '$Executable' failed with exit code $($process.ExitCode)."
    }

    Write-Host "Process '$Executable' completed successfully."
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

# TODO install Qt from command line
#  See articles:
#  - https://www.reddit.com/r/QtFramework/comments/sih353/installing_qt62_via_terminal_in_windows/
#  - https://doc.qt.io/qtinstallerframework/ifw-use-cases-cli.html
#  - https://github.com/miurahr/aqtinstall

Invoke-Expression "conan install .. --output-folder=_deps --build=missing -s build_type=$BUILD_TYPE -s compiler.cppstd=17"

# Run CMake to configure the project (with Start-Process otherwise BUILD_TYPE value is not used)
Invoke-Expression "cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -Wno-dev .."

# Example with CMake (build step)
Invoke-Expression "cmake --build . --config $BUILD_TYPE"