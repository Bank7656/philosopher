#!/bin/bash
set -e

make > /dev/null
valgrind --tool=helgrind ./philo 4 400 200 200
valgrind --leak-check=full ./philo 4 400 200 200
