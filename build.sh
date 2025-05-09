#!/usr/bin/env bash

# Color variables for stylized output
NC='\033[0m' # No color
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
CYAN='\033[0;36m'

# Functions for formatted output with colors
function print_header() {
    echo -e "${CYAN}=======================================================${NC}"
    echo -e "${CYAN}$1${NC}"
    echo -e "${CYAN}=======================================================${NC}"
}

function print_info() {
    echo -e "${BLUE}[ ] $1${NC}"
}

function print_success() {
    echo -e "${GREEN}[+] $1${NC}"
}

function print_warning() {
    echo -e "${YELLOW}[?] $1${NC}"
}

function print_error() {
    echo -e "${RED}[!] $1${NC}"
}

print_header "DOMKRAT3D Build Script"

# Path for build directory
BUILD_DIR="build"

# Function to configure the project with CMake
function configure_build() {
    local build_type="$1"
    print_header "Configuring project ($build_type build)"

    # Remove previous build directory if exists
    if [ -d "$BUILD_DIR" ]; then
        print_warning "Removing existing build folder: $BUILD_DIR"
        rm -rf "$BUILD_DIR"
    fi

    # Create build directory
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"

    # Set the generator type based on build type
    if [ "$build_type" == "MultiConfig" ]; then
        # For multi-configuration generators (e.g., Visual Studio)
        print_info "Generating for multi-configuration generator (e.g., Visual Studio)"
        cmake -S .. -B . || { print_error "Configuration failed"; exit 1; }
    else
        # For single-configuration generators (e.g., Makefiles)
        print_info "Generating for single-configuration generator (Unix Makefiles)"
        cmake -S .. -B . -D CMAKE_BUILD_TYPE=Release || { print_error "Configuration failed"; exit 1; }
    fi

    cd ..
    print_success "Configuration completed!"
}

# Function to build the project
function build_project() {
    local build_type="$1"
    print_header "Building project ($build_type build)"
    if [ ! -d "$BUILD_DIR" ]; then
        print_error "Build folder ($BUILD_DIR) not found! Please configure first."
        exit 1
    fi

    cd "$BUILD_DIR"

    # Build with or without multi-configuration support
    if [ "$build_type" == "MultiConfig" ]; then
        cmake --build . --config Release || { print_error "Build failed"; exit 1; }
    else
        cmake . -Ddomkrat3d_DEVELOPER_MODE=ON || { print_error "Build failed"; exit 1; }
    fi

    cd ..
    print_success "Build finished successfully!"
}

# Function to run tests
function run_tests() {
    local build_type="$1"
    local test_dir="$BUILD_DIR/test"

    # If test directory does not exist, build tests first
    if [ ! -d "$test_dir" ]; then
        print_warning "Test directory ($test_dir) not found. Building tests..."
        build_tests "$build_type"
    fi

    echo -e "${CYAN}[+] Running tests...${NC}\n"
    # Assuming tests are run via ctest in the test directory
    (cd "$test_dir" && cmake --build . && ./domkrat3d_test)
    if [ $? -eq 0 ]; then
        print_success "\nAll tests passed successfully!"
    else
        print_error "\nSome tests failed!"
    fi
}

# Function to build tests
function build_tests() {
    local build_type="$1"
    print_header "Building tests"
    # Assuming tests are part of the main project and can be built via make target
    cd "$BUILD_DIR"
    if [ "$build_type" == "MultiConfig" ]; then
        cmake . -Ddomkrat3d_DEVELOPER_MODE=ON --config Release || { print_error "Failed to build tests"; exit 1; }
    else
        cmake . -Ddomkrat3d_DEVELOPER_MODE=ON || { print_error "Failed to build tests"; exit 1; }
    fi
    cd ..
    print_success "Tests built successfully!"

}

# Usage instructions
function usage() {
    echo -e "${YELLOW}Usage:${NC} $0 [command] [option]"
    echo -e "Commands:"
    echo -e "  configure [single|multi]  — Configure the project (single / multi configuration)"
    echo -e "  build [single|multi]      — Build the project"
    echo -e "  test [single|multi]       — Run tests"
    echo -e "  install [single|multi]    — Install the project"
    echo -e "  all [single|multi]        — Run all steps: configure, build, test"
    echo -e ""
    echo -e "Example: ${YELLOW}$0 all single${NC} — fully build and test in single configuration mode"
}

# Main script execution
if [ $# -lt 1 ]; then
    usage
    exit 1
fi

COMMAND=$1
OPTION=${2:-single}  # Default is 'single' if not provided

case "$COMMAND" in
    configure)
        if [ "$OPTION" == "multi" ]; then
            configure_build "MultiConfig"
        else
            configure_build "SingleConfig"
        fi
        ;;
    build)
        if [ "$OPTION" == "multi" ]; then
            build_project "MultiConfig"
        else
            build_project "SingleConfig"
        fi
        ;;
    test)
        if [ "$OPTION" == "multi" ]; then
            run_tests "MultiConfig"
        else
            run_tests "SingleConfig"
        fi
        ;;
    install)
        echo -e "${BLUE}[+] Installing the project...${NC}"
        cd "$BUILD_DIR"
        if [ "$OPTION" == "multi" ]; then
            cmake --install . --config Release
        else
            cmake --install .
        fi
        cd ..
        print_success "Installation complete!"
        ;;
    all)
        if [ "$OPTION" == "multi" ]; then
            configure_build "MultiConfig"
            build_project "MultiConfig"
            run_tests "MultiConfig"
        else
            configure_build "SingleConfig"
            build_project "SingleConfig"
            run_tests "SingleConfig"
        fi
        ;;
    *)
        usage
        exit 1
        ;;
esac

# End of script
