#!/bin/sh

# Clear the terminal
printf '\033[H\033[2J'

# Move the cursor to the 5th row of the 10th column
printf '\033[5;10H'

# Determine the color of the text in red and the background in black, print the username
printf '\033[38;5;1m'
printf '\033[48;5;0m'
printf "harakki"

# Move the cursor to the 6th row of the 8th column
printf '\033[6;8H'

# Determine the color of the text in green and the background in white, output the group
printf '\033[38;5;2m'
printf '\033[48;5;7m'
printf "Student"

# Move the cursor to 10 row 1 column
printf '\033[10;1H'

# Return the default colors
printf '\033[39m'
printf '\033[49m'
