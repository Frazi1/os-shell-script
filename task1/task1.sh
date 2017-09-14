#!/bin/bash
./format_input.sh |
   ./cnt.awk  |
   sort  -nrk 3  |
   head -10
exit 0

