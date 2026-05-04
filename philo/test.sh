#!/bin/bash

# --- Colors for Output ---
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

PHILO="./philo"

# --- Check if executable exists ---
if [ ! -f "$PHILO" ]; then
    echo -e "${RED}Error: $PHILO executable not found. Please run 'make' first.${NC}"
    exit 1
fi

# --- Main Test Function ---
# Usage: run_test "Test Name" <expect_death: 1 or 0> <timeout_in_seconds> <args...>
run_test() {
    TEST_NAME=$1
    EXPECT_DEATH=$2
    TIMEOUT_SEC=$3
    shift 3
    ARGS="$@"

    # Pad the test name for clean terminal formatting
    printf "${YELLOW}Testing %-25s${NC} args: %-20s ... " "[$TEST_NAME]" "$ARGS"

    # Run the program with a timeout
    OUTPUT=$(timeout $TIMEOUT_SEC $PHILO $ARGS 2>&1)
    EXIT_CODE=$?

    # Count how many times the word "died" appears
    DIED_COUNT=$(echo "$OUTPUT" | grep -c "died")

    if [ "$EXPECT_DEATH" -eq 1 ]; then
        if [ "$DIED_COUNT" -ge 1 ]; then
            echo -e "${GREEN}[OK] Died as expected.${NC}"
        else
            echo -e "${RED}[KO] Expected death, but nobody died!${NC}"
            echo "$OUTPUT" | tail -n 3
        fi
    else
        if [ "$DIED_COUNT" -eq 0 ] && [ "$EXIT_CODE" -eq 124 ]; then
            echo -e "${GREEN}[OK] Survived (timeout reached).${NC}"
        elif [ "$DIED_COUNT" -eq 0 ] && [ "$EXIT_CODE" -eq 0 ]; then
            echo -e "${GREEN}[OK] Finished cleanly (meal limit).${NC}"
        else
            echo -e "${RED}[KO] Unexpected death or crash!${NC}"
            echo "$OUTPUT" | tail -n 3
        fi
    fi
}

echo -e "${CYAN}==============================================================${NC}"
echo -e "${CYAN}                  PHILO ULTIMATE BASH TESTER                  ${NC}"
echo -e "${CYAN}==============================================================${NC}"

echo -e "\n${CYAN}--- 1. EDGE CASES ---${NC}"
# 1 Philo: Must die because they only have one fork.
run_test "1 Philo" 1 2 "1 800 200 200"
# 0 Philos: Should not crash (handle gracefully, maybe exit instantly).
run_test "0 Philos" 0 1 "0 800 200 200"

echo -e "\n${CYAN}--- 2. SURVIVAL (EVEN & ODD) ---${NC}"
# Classic even survival.
run_test "4 Philos (Safe)" 0 4 "4 410 200 200"
# Classic odd survival.
run_test "5 Philos (Safe)" 0 4 "5 800 200 200"
# Tight timings for 3 philos. P3 needs to wait for P1 to finish.
run_test "3 Philos (Tight Safe)" 0 4 "3 610 200 100"

echo -e "\n${CYAN}--- 3. GUARANTEED DEATHS ---${NC}"
# Not enough time for an even group.
run_test "4 Philos (Must Die)" 1 2 "4 310 200 100"
# Death caused by starvation cascade in an odd group.
run_test "3 Philos (Must Die)" 1 2 "3 310 200 100"
# Death because eating takes exactly the same time as dying.
run_test "2 Philos (Exact Death)" 1 2 "2 60 60 60"
# Death because sleeping is longer than time to die.
run_test "5 Philos (Sleep Death)" 1 2 "5 400 200 500"

echo -e "\n${CYAN}--- 4. MEAL LIMITS (OPTIONAL ARG) ---${NC}"
# Even group eating 7 times.
run_test "4 Philos (7 Meals)" 0 5 "4 410 200 200 7"
# Odd group eating 5 times.
run_test "5 Philos (5 Meals)" 0 5 "5 800 200 200 5"
# 1 Philo with meal limit: Should still die before reaching the limit!
run_test "1 Philo (Meal Limit)" 1 2 "1 800 200 200 7"

echo -e "\n${CYAN}--- 5. STRESS TESTS (PERFORMANCE) ---${NC}"
# 200 Philos even: Should handle many threads without crashing.
run_test "200 Philos (Safe)" 0 5 "200 800 200 200"
# 199 Philos odd: Fork management gets heavily tested here.
run_test "199 Philos (Safe)" 0 5 "199 800 200 200"
# 200 Philos meal limit: Checks if Monitor loop can keep up.
run_test "200 Philos (5 Meals)" 0 8 "200 800 200 200 5"

echo -e "${CYAN}==============================================================${NC}"