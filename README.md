# csv-inspector-c



A small C CLI tool to inspect CSV column consistency.



## Features



- Checks column count consistency in CSV files
- Uses the first non-empty line as the expected column count
- Supports quoted fields with commas
- Shows invalid line numbers
- Supports `--max-show`
- Displays processing time

## Build

```cmd
gcc -Wall -Wextra -O2 -o csv\_inspector.exe src\\main.c

```

## Generate sample CSV
```cmd
python tools\generate_sample_csv.py --rows 100000 --broken 50
```

## Usage
```cmd
csv_inspector.exe samples\sample_broken.csv
```
```cmd
csv_inspector.exe samples\sample_broken.csv --max-show 50
```
```cmd
csv_inspector.exe samples\sample_broken.csv --max-show 0
```

## Example output
```cmd
[INVALID] line=2115 columns=3 expected=5
[INVALID] line=2371 columns=3 expected=5

=== CSV Inspection Result ===
File           : samples\sample_broken.csv
Header columns : 5
Total lines    : 100001
Valid lines    : 99951
Invalid lines  : 50
Empty lines    : 0
Max show       : 20
Elapsed time   : 0.021 sec
```



