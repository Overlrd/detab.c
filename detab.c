/*
 * Filename:    detab.c
 *
 * The C Programming Language, second edition,
 * by Brian Kernighan and Dennis Ritchie
 *
 * Exercise 1-20, page 34
 *
 * Write a program detab that replaces tabs in the input with the proper
 * number of blanks to space to the next tab stop. Assume a fixed set of
 * tab stops, say every n columns. Should n be a variable or a symbolic
 * parameter?
 */

#include <stdint.h>
#include <stdio.h>

#define TABWIDTH 8

int main(void) {
  int c, i, col, spaces;

  col = 0;
  while ((c = getchar()) != EOF) {

    if (c == '\t') {
      spaces = (TABWIDTH - (col % TABWIDTH));
      for (i = 0; i < spaces; i++) {
        putchar(' ');
      }
      col += spaces;
    } else {

      putchar(c);
      col++;
      if (c == '\n') {

        col = 0;
      }
    }
  }
  return 0;
}
