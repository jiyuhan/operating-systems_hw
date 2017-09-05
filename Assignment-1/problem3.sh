#!/bin/bash

gcc -v 2>&1 | grep "gcc version" | awk '{print $3}'
