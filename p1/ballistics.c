/**
    @file ballistics.c
    @author Stephen Gonsalves (dkgonsal)
    This program reads user input and returns a table with their calculated
    data for ballistic missle trajectories at various launch angles.
  */
  
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/** Gravitational constant for acceleration */
#define GRAV_CONSTANT 9.81

/** Max number of rows in the table */
#define MAX_ROWS 19

/** Degrees increase on the table */
#define DEG_INTERVAL 5

/** Constant for 180 degrees */
#define FLT_ARC 180

/** Value used in flight time calculation */
#define FLT_TIME_VAL 2


/** The flightTime() method calculates the amount of time the ballistic
    missile is airborne, or time-to-impact. 
    @param angle is the angle at which the missle was launched.
    @param v0 is the initial velocity of the missle when launched.
    @return the flight time as a double value.
  */
double flightTime( int angle, double v0 )
{
  double fltTime = 0;
  
  // Calculate and return the flight time
  double sinRad = sin(angle * (M_PI / FLT_ARC));
  fltTime = (FLT_TIME_VAL * sinRad * v0) / GRAV_CONSTANT;
  return fltTime;
  
}

/** The tableHeader() method prints the header of the table, starting
    on a new line of text.
  */
void tableHeader()
{
  // Start on a new line
  putchar('\n');
  
  // Print the table header
  printf("%10s | %10s | %10s | %10s\n", "angle", "v0", "time", "distance");
  printf("-----------+------------+------------+-----------\n");

}

/** The tableRow() method prints each row of data to the table. The distance
    the missle travels is also calculated within this method.
    @param angle is the angle at which the missle is launched. It is an 
                 integer value that corresponds to the current row.
    @param v0 is the initial velocity of the missile received through 
              user input.
    @param t is the amount of time it takes for the missle to impact.
  */
void tableRow( int angle, double v0, double t )
{
  // Calculate distance traveled
  double distance = v0 * t * cos(angle * (M_PI / FLT_ARC));

  // Print the row of data to the table
  printf("%10d | ", angle);
  printf("%10.3f | ", v0);
  printf("%10.3f | ", t);
  printf("%10.3f\n", distance);

}

/** Starting point of the program. The main() method prompts the user for
    input and saves the input value as a decimal integer to 3 decimal places.
    The method will then print the table by calling the other methods for 
    calculations and table printing.
    @return a 0 representing successful termination of the program.
  */
int main()
{
  double v0 = 0;
  printf("V0: ");
  scanf("%lf", &v0);
  
  // Print the table
  int rowCount = 1;
  int angle = 0;
  tableHeader();
  while (rowCount <= MAX_ROWS) {
    tableRow(angle, v0, flightTime(angle, v0));
    angle += DEG_INTERVAL;
    rowCount++;
  }
  
  // Exit the program
  return EXIT_SUCCESS;
  
}