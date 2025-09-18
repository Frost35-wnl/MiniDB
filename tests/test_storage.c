#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/storage/catalog_file.h"
#include "../include/config.h"

bool catalog_test();

int main(void)
{
  if (catalog_test())
    printf("Catalog runs out of the box");
}

bool catalog_test() {
  
  //Suppose we have created the tables
  const char *title1[] = {"Number", "Freq", "Total", NULL};
  const char *title2[] = {"True", "False", NULL};
  const char *title3[] = {"Jan", "Feb", "Mar", "Ap", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec", NULL};
  add_table_to_catalog("TABLE1");  //Catalog test 
  add_table_to_catalog("TABLE2"); //Catalog test  
  add_table_to_catalog("TABLE 3");

  list_tables();

  printf("Test successfull\n");

  return true;
}
