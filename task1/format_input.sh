#!/bin/bash
cat log.txt
 | awk '{print $4, $9}'
 |  cut -c 2-
 |  sed 's/:[0-9][0-9]:[0-9][0-9]:[0-9][0-9]//g'
exit 0
