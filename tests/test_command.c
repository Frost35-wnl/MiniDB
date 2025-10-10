#include "../include/commands/create.h"
#include "../include/context.h"
#include <stdbool.h>
#include <stdio.h>

bool test_create();

int main(void) {
  if (test_create())
    printf("handle_create works with success \n\n");
  return 0;
}

bool test_create() {

  DBContext ctx = init_context();

  const char *table1_tokens[] = {"TABLE1", "Number", "Freq", "Total", NULL};
  const char *table2_tokens[] = {"TABLE2", "True", "False", NULL};

  handle_create(ctx, table1_tokens);
  print_table(get_current_table(ctx));
  handle_create(ctx, table2_tokens);
  print_table(get_current_table(ctx));
  return true;
}
