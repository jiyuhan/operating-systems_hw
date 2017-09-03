#!/bin/bash

cat problem2.txt | sort -g -r | awk 'NR < 4' >> problem2_highest_values.txt
