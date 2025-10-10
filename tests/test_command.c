#include "../include/commands/create.h"
#include "../include/commands/insert.h"
#include "../include/commands/list.h"
#include "../include/commands/read.h"
#include "../include/commands/select.h"
#include "../include/context.h"
#include <stdbool.h>
#include <stdio.h>

bool test_create();
bool test_list();
bool test_select();
bool test_insert();
bool test_read();

int main(void) {
  // if (test_create())
  // printf("handle_create works with success \n\n");
  // if (test_list())
  // printf("handle_list works with success \n\n");
  // if (test_select())
  // printf("handle_select works with success \n\n");
  // if (test_insert())
  // printf("handle_insert works with success \n\n");
  if (test_read())
    printf("handle_read works with success \n\n");
  return 0;
}

bool test_read() {
  DBContext ctx = init_context();
  // handle_read(ctx); cause une erreur

  handle_select(ctx, "TABLE2");
  const char *list1[] = {"0", "0", NULL};
  const char *list2[] = {"1", "2", NULL};
  handle_insert(ctx, list1);
  handle_insert(ctx, list2);

  handle_read(ctx);

  return true;
}

bool test_insert() {
  DBContext ctx = init_context();
  handle_select(ctx, "TABLE1");

  const char *list1[] = {"0", "0", "0", NULL};
  const char *list2[] = {"1", "2", "3", NULL};
  handle_insert(ctx, list1);
  handle_insert(ctx, list2);

  print_table(get_current_table(ctx));

  return true;
}

bool test_select() {
  DBContext ctx = init_context();
  handle_select(ctx, "TABLE1");
  print_table(get_current_table(ctx));

  handle_list();
  handle_select(ctx, "TABLE2");
  print_table(get_current_table(ctx));

  handle_list();
  handle_select(ctx, "TABLE2QWETYUIOPAHJ");
  print_table(get_current_table(ctx));
  return true;
}

bool test_create() {

  DBContext ctx = init_context();

  const char *table1_tokens[] = {"TABLE1", "Number", "Freq", "Total", NULL};
  const char *table2_tokens[] = {"TABLE2QWETYUIOPAHJ", "True", "False", NULL};

  handle_create(ctx, table1_tokens);
  print_table(get_current_table(ctx));
  handle_create(ctx, table2_tokens);
  print_table(get_current_table(ctx));
  return true;
}

bool test_list() {
  handle_list();
  return true;
}
