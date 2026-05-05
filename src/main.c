#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 8192
#define DEFAULT_MAX_INVALID_SHOW 20

void print_help(const char *program_name) {
    printf("csv-inspector-c\n");
    printf("A small CLI tool to inspect CSV column consistency.\n\n");

    printf("Usage:\n");
    printf("  %s <csv_file> [options]\n\n", program_name);

    printf("Options:\n");
    printf("  --help                Show this help message\n");
    printf("  --max-show <number>   Number of invalid lines to display. Default: %d\n",
           DEFAULT_MAX_INVALID_SHOW);

    printf("\nExamples:\n");
    printf("  %s samples\\sample_broken.csv\n", program_name);
    printf("  %s samples\\sample_broken.csv --max-show 50\n", program_name);
    printf("  %s samples\\sample_broken.csv --max-show 0\n", program_name);
}

int count_csv_columns(const char *line) {
    int columns = 1;
    int in_quotes = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        char c = line[i];

        if (c == '"') {
            if (in_quotes && line[i + 1] == '"') {
                i++;
            } else {
                in_quotes = !in_quotes;
            }
        } else if (c == ',' && !in_quotes) {
            columns++;
        } else if (c == '\n' || c == '\r') {
            break;
        }
    }

    return columns;
}

int is_empty_line(const char *line) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r') {
            return 0;
        }
    }
    return 1;
}

int parse_options(int argc, char *argv[], int *max_show) {
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            print_help(argv[0]);
            return 1;
        } else if (strcmp(argv[i], "--max-show") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: --max-show requires a number.\n");
                return -1;
            }

            *max_show = atoi(argv[i + 1]);

            if (*max_show < 0) {
                fprintf(stderr, "Error: --max-show must be 0 or greater.\n");
                return -1;
            }

            i++;
        } else {
            fprintf(stderr, "Error: Unknown option: %s\n", argv[i]);
            fprintf(stderr, "Use --help to see usage.\n");
            return -1;
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_help(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "--help") == 0) {
        print_help(argv[0]);
        return 0;
    }

    const char *file_path = argv[1];
    int max_show = DEFAULT_MAX_INVALID_SHOW;

    int option_result = parse_options(argc, argv, &max_show);

    if (option_result == 1) {
        return 0;
    } else if (option_result == -1) {
        return 1;
    }

    FILE *fp = fopen(file_path, "r");

    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];

    long total_lines = 0;
    long valid_lines = 0;
    long invalid_lines = 0;
    long empty_lines = 0;

    int header_columns = -1;
    int invalid_shown = 0;

    clock_t start = clock();

    while (fgets(line, sizeof(line), fp) != NULL) {
        total_lines++;

        if (is_empty_line(line)) {
            empty_lines++;
            continue;
        }

        int columns = count_csv_columns(line);

        if (header_columns == -1) {
            header_columns = columns;
            valid_lines++;
            continue;
        }

        if (columns == header_columns) {
            valid_lines++;
        } else {
            invalid_lines++;

            if (invalid_shown < max_show) {
                printf("[INVALID] line=%ld columns=%d expected=%d\n",
                       total_lines, columns, header_columns);
                invalid_shown++;
            }
        }
    }

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    fclose(fp);

    printf("\n=== CSV Inspection Result ===\n");
    printf("File           : %s\n", file_path);
    printf("Header columns : %d\n", header_columns);
    printf("Total lines    : %ld\n", total_lines);
    printf("Valid lines    : %ld\n", valid_lines);
    printf("Invalid lines  : %ld\n", invalid_lines);
    printf("Empty lines    : %ld\n", empty_lines);
    printf("Max show       : %d\n", max_show);
    printf("Elapsed time   : %.3f sec\n", elapsed);

    if (max_show == 0 && invalid_lines > 0) {
        printf("\nNote: Invalid line details are hidden because --max-show is 0.\n");
    } else if (invalid_lines > max_show) {
        printf("\nNote: Only first %d invalid lines are shown.\n", max_show);
    }

    return 0;
}