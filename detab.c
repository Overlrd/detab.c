#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int MAXCHAR = 1000;
int MAXLINE = 1000;
int TABWIDTH = 4;
int REPL = ' ';

void parse_arguments(int argc, char *argv[]);
int read_next_line(char line[], int lim);

void parse_arguments(int argc, char *argv[]) {
  if (argc < 2 || argc > 5) {
    printf("Usage: %s <char> [MAXCHAR] [MAXLINE] [TABWIDTH]\n", argv[0]);

    printf("  <char>       : Character to replace tabs (must be a single "
           "character)\n");
    printf("  [MAXCHAR]    : Maximum number of characters per line (default: "
           "100)\n");
    printf(
        "  [MAXLINE]    : Maximum number of lines to process (default: 100)\n");
    printf(
        "  [TABWIDTH]   : Number of spaces to replace each tab (default: 4)\n");
    exit(1);
  }

  REPL = argv[1][0];
  if (argv[1][1] != '\0') {
    printf("Error: Only one character is allowed for replacement.\n");
    exit(1);
  }

  // Parse MAXCHAR if provided
  if (argc >= 3 && (sscanf(argv[2], "%d", &MAXCHAR)) != 1) {
    printf("Error: Invalid value for MAXCHAR.\n");
    exit(1);
  }

  // Parse MAXLINE if provided
  if (argc >= 4 && (sscanf(argv[3], "%d", &MAXLINE)) != 1) {
    printf("Error: Invalid value for MAXLINE.\n");
    exit(1);
  }

  // Parse TABWIDTH if provided
  if (argc == 5 && (sscanf(argv[4], "%d", &TABWIDTH)) != 1) {
    printf("Error: Invalid value for TABWIDTH.\n");
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  parse_arguments(argc, argv);

  char line[MAXCHAR];
  int lineLen;

  char *output = (char *)malloc(MAXCHAR * MAXLINE * sizeof(char));
  if (output == NULL) {
    fprintf(stderr, "Error allocating memory");
    return 1;
  }

  int outputIndex = 0;
  int outputSize = MAXCHAR * MAXLINE;

  while ((lineLen = read_next_line(line, MAXCHAR)) > 0) {
    for (int i = 0; i < lineLen; i++) {

      if (line[i] == '\t') {

        // Check if we haven't exceced the outputSize
        if (outputIndex + TABWIDTH >= outputSize) {
          fprintf(stderr, "Output buffer is too small\n");
          free(output);
          return 1;
        }

        for (int j = 0; j < TABWIDTH; j++) {
          output[outputIndex++] = REPL;
        }

      } else {

        if (outputIndex + TABWIDTH >= outputSize) {
          fprintf(stderr, "Output buffer is too small\n");
          free(output);
          return 1;
        }

        output[outputIndex++] = line[i];
      }
    }
  }
  printf("%s\n", output);
  free(output);
  return 0;
}

int read_next_line(char *line, int lim) {
  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    line[i] = c;
  }

  if (c == '\n') {
    line[i] = c;
    i++;
  }

  line[i] = '\0';

  return i;
}
