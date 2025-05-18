#!/usr/bin/env bash

# Color codes for formatted output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
RESET='\033[0m'
BOLD='\033[1m'
UNDERLINE='\033[4m'

# Default flags
LOGFILE=".report_log.txt"
RUN_TESTS=true
RUN_LOG=true

# Function to display help
function display_help() {
    echo -e "${BOLD}${CYAN}Usage: $0 [OPTIONS]${RESET}"
    echo -e "${BOLD}${CYAN}Options:${RESET}"
    echo -e "  --help         Display this help message"
    echo -e "  --no-tests     Skip running tests for vkcube and glxgears"
    echo -e "  --no-log       Skip logging results to a file"
}

# Function for colored output
function print_color() {
    echo -e "${1}${2}${RESET}"
}

# Check for required commands
function check_command() {
    if ! command -v "$1" &> /dev/null; then
        print_color "${RED}" "Command '$1' not found."
        return 1
    else
        print_color "${GREEN}" "Command '$1' found."
        return 0
    fi
}

# Collect system information
function system_info() {
    DISTRIBUTION=$(lsb_release -d | awk -F"\t" '{print $2}' || echo "Unknown distribution")
    CPU=$(lscpu | grep "Model name" | awk -F":" '{print $2}' | xargs)
    GPU=$(lspci | grep -i "vga" | awk -F":" '{print $2}' | xargs)
    ARCH=$(uname -m)
    KERNEL=$(uname -r)
    TIMESTAMP=$(date)
    MEMORY=$(free -h | grep Mem | awk '{print $2}')
    SWAP=$(free -h | grep Swap | awk '{print $2}')
    UPTIME=$(uptime)

    print_color "${CYAN}" "============================"
    print_color "${CYAN}" "     System Information     "
    print_color "${CYAN}" "============================"
    print_color "${GREEN}" "Distribution: $DISTRIBUTION"
    print_color "${GREEN}" "CPU: $CPU"
    print_color "${GREEN}" "GPU: $GPU"
    print_color "${GREEN}" "Architecture: $ARCH"
    print_color "${GREEN}" "Kernel: $KERNEL"
    print_color "${GREEN}" "Memory: $MEMORY"
    print_color "${GREEN}" "Swap: $SWAP"
    print_color "${GREEN}" "Uptime: $UPTIME"
    print_color "${GREEN}" "Test Time: $TIMESTAMP"
    print_color "${CYAN}" "=================================="
}

# Check for required libraries and drivers
function check_graphics() {
    print_color "${CYAN}" "     Graphics Component Check     "
    print_color "${CYAN}" "=================================="
    check_command "glxinfo"
    check_command "vulkaninfo"
    check_command "clang"
    check_command "vkcube"
    print_color "${CYAN}" "============================"
}

# Run tests and display results
function run_tests() {
    SUCCESS=0

    print_color "${YELLOW}" "Running vkcube to check Vulkan..."
    if command -v vkcube &> /dev/null; then
        vkcube &
        sleep 1  # Wait for 1 second
        pkill -f vkcube  # Terminate vkcube
        print_color "${GREEN}" "vkcube started and closed after 1 second."
    else
        print_color "${RED}" "Failed to start vkcube."
        SUCCESS=1
    fi

    print_color "${YELLOW}" "Running glxgears to check OpenGL..."
    if command -v glxgears &> /dev/null; then
        glxgears &
        sleep 1  # Wait for 1 second
        pkill -f glxgears  # Terminate glxgears
        print_color "${GREEN}" "glxgears started and closed after 1 second."
    else
        print_color "${RED}" "Failed to start glxgears."
        SUCCESS=1
    fi

    return $SUCCESS
}

# Log results to report file
function log_results() {

    if [ "$RUN_LOG" = true ]; then
        {
            echo "========================"
            echo "     Report Log         "
            echo "========================"
            echo "Distribution: $DISTRIBUTION"
            echo "CPU: $CPU"
            echo "GPU: $GPU"
            echo "Architecture: $ARCH"
            echo "Kernel: $KERNEL"
            echo "Memory: $MEMORY"
            echo "Swap: $SWAP"
            echo "Uptime: $UPTIME"
            echo "Test Time: $TIMESTAMP"
            echo "========================"
            echo "Graphics Component Check"
            echo "========================"
            if [ "$1" -eq 0 ]; then
                echo "All tests passed successfully."
            else
                echo "Some tests failed. Please check logs above."
            fi
            echo "========================"
        } > "$LOGFILE"
        print_color "${GREEN}" "Results have been logged to $LOGFILE"
    else
        print_color "${YELLOW}" "Logging skipped."
    fi
}

# Main execution with argument parsing
while [[ $# -gt 0 ]]; do
    case "$1" in
        --help)
            display_help
            exit 0
            ;;
        --no-tests)
            RUN_TESTS=false
            ;;
        --no-log)
            RUN_LOG=false
            ;;
        *)
            print_color "${RED}" "Unknown option: $1"
            display_help
            exit 1
            ;;
    esac
    shift
done

system_info
check_graphics
FAILURE=0

# Gather results from the checks
for cmd in glxinfo vulkaninfo clang vkcube; do
    if ! check_command "$cmd"; then
        FAILURE=1
    fi
done

# Run the tests if not skipped
if [ "$RUN_TESTS" = true ]; then
    run_tests || FAILURE=1
fi

# Log results
log_results $FAILURE

if [ "$FAILURE" -eq 1 ]; then
    print_color "${RED}" "Some checks or tests failed. See the report for details."
else
    print_color "${GREEN}" "All checks and tests passed successfully!"
fi
