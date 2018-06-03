#!/usr/bin/env bash
valgrind --show-reachable=yes --leak-check=full --error-exitcode=1 -q ./main

