#!/bin/bash

less /proc/cpuinfo | grep "processor" | wc -l
