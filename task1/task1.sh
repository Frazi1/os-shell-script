#!/bin/bash
./format_input.sh
 | ./cnt.awk
 | sort  -nrk 2
 | head -10
exit 0

