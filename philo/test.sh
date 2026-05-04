#!/bin/bash
set -e

make > /dev/null
./philo 4 400 200 200
