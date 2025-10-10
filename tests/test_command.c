#include "../include/context.h"
#include "../include/model/row_adt.h"
#include "../include/model/table_adt.h"
#include <stdbool.h>
#include <stdio.h>

int main(void) {
  DBContext ctx = init_context();
  printf("The init_context function works fine\n");

  const char *title1[] = {"Number", "Freq", "Total", NULL};
  Table table1 = create_table("TABLE 1", title1);
  const char *list1[] = {"0", "0", "0", NULL};
  Row row1 = create_row(list1);
  const char *list2[] = {"1", "2", "3", NULL};
  Row row2 = create_row(list2);
  add_row(table1, row1);
  add_row(table1, row2);

  const char *title2[] = {"True", "False", NULL};
  Table table2 = create_table("TABLE 2", title2);
  const char *list3[] = {"O", "X", NULL};
  Row row3 = create_row(list3);
  const char *list4[] = {"O", "O", NULL};
  Row row4 = create_row(list4);
  add_row(table2, row3);
  add_row(table2, row4);

  printf("Tables created\n");

  printf("\nSelect table1\n");
  set_current_table(ctx, table1);
  Table tmp = get_current_table(ctx);
  print_table(tmp);

  printf("\nSwitch table2\n");
  set_current_table(ctx, table2);
  Table tmp2 = get_current_table(ctx);
  print_table(tmp2);

  free_context(ctx);
  printf("Test successfull\n");

  return 0;
}
