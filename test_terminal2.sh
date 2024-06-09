#!/bin/sh

# Clear the terminal
printf '\033[H\033[2J'

# Change the terminal output mode
printf '\033(0'

# Output of an 8x8 pseudographic frame
printf '\033[10;5H'
printf "lqqqqqqk"
printf '\033[11;5H'
printf "x      x"
printf '\033[12;5H'
printf "x      x"
printf '\033[13;5H'
printf "x      x"
printf '\033[14;5H'
printf "x      x"
printf '\033[15;5H'
printf "x      x"
printf '\033[16;5H'
printf "x      x"
printf '\033[17;5H'
printf "mqqqqqqj"

# Output of a pseudographic digit
printf '\033[12;7H'
printf "aaaa"
printf '\033[13;7H'
printf "a"
printf '\033[14;7H'
printf "aaaa"
printf '\033[15;7H'
printf "a  a"
printf '\033[16;7H'
printf "aaaa"

# Move the cursor to the 18th row 1 column
printf '\033[18;1H'

# Return to the standard output mode
printf '\033(B'
