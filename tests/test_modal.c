#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/model/row_adt.h"
#include "../include/model/table_adt.h"

bool test_row_adt(void);
bool test_table_adt(void);

int main(int argc, char *argv[])
{
  printf("\n");
  if (test_row_adt())
    printf("Row adt model works fine\n");
  printf("\n");
  if (test_table_adt())
    printf("\n\nTable adt mode works fine");

  return EXIT_SUCCESS;
}

bool test_table_adt() {

    const char *list[] = {"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday", NULL};
    Table table = create_table("Count of the week", list);

    printf("\nThe create_table function works fine\n");

    const char *values1[] = {"0", "0", "0", "0", "0", "0", "0", NULL};
    Row week1 = create_row(values1);
    const char *values2[] = {"1", "1", "1", "1", "1", "1", "1", NULL};
    Row week2 = create_row(values2);
    const char *values3[] = {"4", "70", "149", "7896", "1", "69", "123789", NULL};
    Row week3 =  create_row(values3);

    bool result1 = add_row(table, week1);
    bool result2 = add_row(table, week2);
    bool result3 = add_row(table, week3);

    if (result1 && result2)
        printf("The add_row function works fine\n");

    printf("\n\tThe length of the table is : %d\n\n", get_table_num_fields(table));

    print_table(table);
    free_table(table);

    return true;
}

bool test_row_adt() {

//We need const list
 const char *list1[] = {"abc", "edf", NULL};
 const char *list2[] = {"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday", NULL};

  Row row1 = create_row(list1);
  Row row2 = create_row(list2);

  printf("The create_row function works fine\n\n");

  int row1_values = print_row(row1);
  int row2_values = print_row(row2);

  if (row1_values == 2 && row2_values == 7)
      printf("\n\nThe print_row function works fine\n");
  else
      printf("The print_row function has some problems");

  free_row(row1);
  free_row(row2);

  printf("The free_row function works fine\n");

  return true;
}
