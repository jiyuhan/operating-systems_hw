#!/bin/bash
#ls -Sr ./Problem_5_hidden_dir/.* 2>&1 | awk 'NR<4' | xargs stat --printf='%i %b %A %h %U %G %s %.16y %n\n' |

ls -S -r -lis -N --time-style="+%b%e %Y" ./Problem_5_hidden_dir/.* 2>&1 | awk 'NR<4'
