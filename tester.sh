#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Counters
TOTAL=0
PASSED=0
FAILED=0

# Program name
PROGRAM="./cub3D"

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}  CUB3D MAP TESTER${NC}"
echo -e "${BLUE}========================================${NC}\n"

# Check if program exists
if [ ! -f "$PROGRAM" ]; then
    echo -e "${RED}Error: $PROGRAM not found. Compile first with 'make'${NC}"
    exit 1
fi

# Function to run a test
run_test() {
    local map_file=$1
    local expected_result=$2  # "success" or "error"
    local test_name=$3
    
    TOTAL=$((TOTAL + 1))
    
    echo -e "${YELLOW}Test $TOTAL: $test_name${NC}"
    echo -e "  Map: ${map_file}"
    echo -e "  Expected: ${expected_result}"
    
    # Run the program with timeout (5 seconds)
    $PROGRAM "$map_file" > /tmp/cub3d_output.txt 2>&1
    exit_code=$?
    
    # Check timeout (exit code 124)
    if [ $exit_code -eq 124 ]; then
        echo -e "  ${RED}✗ TIMEOUT - Infinite loop detected!${NC}\n"
        FAILED=$((FAILED + 1))
        cat /tmp/cub3d_output.txt | tail -20
        return
    fi
    
    # Check result
    if [ "$expected_result" == "success" ]; then
        if [ $exit_code -eq 0 ]; then
            echo -e "  ${GREEN}✓ PASSED${NC}\n"
            PASSED=$((PASSED + 1))
        else
            echo -e "  ${RED}✗ FAILED - Expected success but got error${NC}"
            echo -e "  Exit code: $exit_code"
            cat /tmp/cub3d_output.txt
            echo ""
            FAILED=$((FAILED + 1))
        fi
    else
        if [ $exit_code -ne 0 ]; then
            echo -e "  ${GREEN}✓ PASSED - Correctly detected error${NC}\n"
            PASSED=$((PASSED + 1))
        else
            echo -e "  ${RED}✗ FAILED - Should have failed but succeeded${NC}"
            cat /tmp/cub3d_output.txt
            echo ""
            FAILED=$((FAILED + 1))
        fi
    fi
}

# Valid maps (should succeed)
echo -e "${BLUE}=== VALID MAPS ===${NC}\n"
run_test "maps/test_basic.cub" "success" "Basic valid map"
run_test "maps/test_complex.cub" "success" "Complex valid map"
run_test "maps/test_spaces.cub" "success" "Map with extra spaces"

# Invalid maps (should fail)
echo -e "${BLUE}=== INVALID MAPS ===${NC}\n"
run_test "maps/test_error_duplicate_texture.cub" "error" "Duplicate texture"
run_test "maps/test_error_invalid_rgb.cub" "error" "Invalid RGB value (>255)"
run_test "maps/test_error_multiple_players.cub" "error" "Multiple players"
run_test "maps/test_error_no_player.cub" "error" "No player"
run_test "maps/test_error_open_map.cub" "error" "Map not closed"

# Invalid arguments
echo -e "${BLUE}=== INVALID ARGUMENTS ===${NC}\n"
run_test "nonexistent.cub" "error" "Non-existent file"
run_test "maps/test_basic.txt" "error" "Wrong extension"

# Test with no arguments
TOTAL=$((TOTAL + 1))
echo -e "${YELLOW}Test $TOTAL: No arguments${NC}"
timeout 5s $PROGRAM > /tmp/cub3d_output.txt 2>&1
if [ $? -ne 0 ]; then
    echo -e "  ${GREEN}✓ PASSED${NC}\n"
    PASSED=$((PASSED + 1))
else
    echo -e "  ${RED}✗ FAILED${NC}\n"
    FAILED=$((FAILED + 1))
fi

# Test with too many arguments
TOTAL=$((TOTAL + 1))
echo -e "${YELLOW}Test $TOTAL: Too many arguments${NC}"
timeout 5s $PROGRAM maps/test_basic.cub extra_arg > /tmp/cub3d_output.txt 2>&1
if [ $? -ne 0 ]; then
    echo -e "  ${GREEN}✓ PASSED${NC}\n"
    PASSED=$((PASSED + 1))
else
    echo -e "  ${RED}✗ FAILED${NC}\n"
    FAILED=$((FAILED + 1))
fi

# Summary
echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}  SUMMARY${NC}"
echo -e "${BLUE}========================================${NC}"
echo -e "Total tests: $TOTAL"
echo -e "${GREEN}Passed: $PASSED${NC}"
echo -e "${RED}Failed: $FAILED${NC}"

if [ $FAILED -eq 0 ]; then
    echo -e "\n${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}\n"
    exit 0
else
    echo -e "\n${RED}❌ SOME TESTS FAILED ❌${NC}\n"
    exit 1
fi