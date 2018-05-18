#!/bin/sh

strace -r -c -o searchtrace.txt ./search /etc > /dev/null
strace -r -c -o findtrace.txt find /etc > /dev/null
strace -r -c -o searchtrace1.txt ./search /etc -exec echo \{\} \; > /dev/null
strace -r -c -o findtrace1.txt find /etc -exec echo \{\} \; > /dev/null

# get numbers
printf "# search /etc\n"
cat searchtrace.txt | grep [0-9] | cut -c37- | cut --complement -c5-14 | head -n -1
printf "\n# find /etc\n"
cat findtrace.txt | grep [0-9] | cut -c37- | cut --complement -c5-14 | head -n -1
printf "\n# search /etc -exec echo \{\} \;\n"
cat searchtrace1.txt | grep [0-9] | cut -c37- | cut --complement -c5-14 | head -n -1
printf "\n# find /etc -exec echo \{\} \;\n"
cat findtrace1.txt | grep [0-9] | cut -c37- | cut --complement -c5-14 | head -n -1
