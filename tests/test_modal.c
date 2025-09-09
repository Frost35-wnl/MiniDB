#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/model/row_adt.h"

bool test_row_adt(void);

int main(int argc, char *argv[])
{
  if (test_row_adt())
    printf("\nRow adt model works fine\n");

  return EXIT_SUCCESS;
}


bool test_row_adt() {

//We need const list
 const char *list1[] = {"abc", "edf", NULL};
 const char *list2[] = {"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday", NULL};

  Row row1 = create_row(list1);
  Row row2 = create_row(list2);

  printf("\nThe create_row function works fine\n");

  int row1_values = print_row(row1);
  int row2_values = print_row(row2);

  if (row1_values == 2 && row2_values == 7)
      printf("\nThe print_row function works fine\n");
  else
      printf("\nThe print_row function has some problems");

  free_row(row1);
  free_row(row2);

  printf("\nThe free_row function works fine\n");

  return true;
}
