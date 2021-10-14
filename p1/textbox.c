/**
    @file textbox.c
    @author Stephen Gonsalves (dkgonsal)
    This program reads user input and returns text with a textbox around it.
    If there is no input received when the code is executed an empty box 
    will print to the console.
  */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** Width of each line of text in the box. */
#define LINE_WIDTH 60

/** Width of the border of the text box */
#define BORDER_WIDTH 62

/** Symbol used to draw the border around the box. */
#define BORDER '*'

/** Boolean method that reads and prints text to the console. It then 
    returns true if it is the first and last line of the input text.
    @return true if the pointer has not reached EOF. Otherwise, returns
            false.
  */
bool paddedLine()
{
  int paddedCount = 0;
  int ch = getchar();
  
  // Check for EOF
  if (ch == EOF) {
    return false;
  }
  
  // Starting line in the textbox
  putchar(BORDER);
  while (paddedCount < LINE_WIDTH) {
    if (ch == '\n') {
      // Loop until line length requirement is met
      for (int i = 0; i < LINE_WIDTH - paddedCount; i++) {
        putchar(' ');
      }
      paddedCount = LINE_WIDTH;
    } else {
      putchar(ch);
      ch = getchar();
      paddedCount++;
    }
  }
  
  // Trim input that is beyond limit
  while (ch != '\n') {
    ch = getchar();
  }
  
  // Print border and start a new line
  printf("%c\n", BORDER);
  return true;
}

/** Void method that prints the initial and final lines of the textbox
    @param ch is the character that makes up the BORDER of the textbox
    @param count tracks the amount of border chars that have printed
  */
void lineOfChars(char ch, int count)
{
  int counter = count;
  int chBorder = ch;
  
  // Draw the upper and lower borders
  while (counter < BORDER_WIDTH) {
    putchar(chBorder);
    counter++;
  }
  putchar('\n');
}

/** Starting point of the program that calls the paddedLine() and lineOfChars()
    methods for printing output to the console. 
    @return a 0 representing successful termination of the program.
  */
int main()
{
  lineOfChars(BORDER, 0);
  
  // Print text until paddedLine() returns false
  while (paddedLine() != false) {
    paddedLine();
  }
  lineOfChars(BORDER, 0);

  return EXIT_SUCCESS;

}
