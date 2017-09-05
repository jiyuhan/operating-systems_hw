#!/bin/bash

ps -ef | grep "/usr/lib/" | grep -v "root" | wc -l
