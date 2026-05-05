# \# csv-inspector-c

# 

# 

# 

# A small C CLI tool to inspect CSV column consistency.

# 

# 

# 

# \## Features

# 

# 

# 

# \- Checks column count consistency in CSV files

# \- Uses the first non-empty line as the expected column count

# \- Supports quoted fields with commas

# \- Shows invalid line numbers

# \- Supports `--max-show`

# \- Displays processing time

# 

# \## Build

# 

# ```cmd

# gcc -Wall -Wextra -O2 -o csv\\\_inspector.exe src\\\\main.c

# 

# ```

# 

# \## Generate sample CSV

# ```cmd

# python tools\\generate\_sample\_csv.py --rows 100000 --broken 50

# ```

# 

# \## Usage

# ```cmd

# csv\_inspector.exe samples\\sample\_broken.csv

# ```

# ```cmd

# csv\_inspector.exe samples\\sample\_broken.csv --max-show 50

# ```

# ```cmd

# csv\_inspector.exe samples\\sample\_broken.csv --max-show 0

# ```

# 

# \## Example output

# ```cmd

# \[INVALID] line=2115 columns=3 expected=5

# \[INVALID] line=2371 columns=3 expected=5

# 

# === CSV Inspection Result ===

# File           : samples\\sample\_broken.csv

# Header columns : 5

# Total lines    : 100001

# Valid lines    : 99951

# Invalid lines  : 50

# Empty lines    : 0

# Max show       : 20

# Elapsed time   : 0.021 sec

# ```

# 

# 

# 

# 

