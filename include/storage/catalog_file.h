#ifndef CATALOG_H
#define CATALOG_H
#include <stdbool.h>
#include "../utils.h"
#include "../config.h"

  //Add the table and its fields to the catalog
bool add_table_to_catalog(const char *table_name);
  //Read all the tables from catalog
int list_tables();
  //Check if table is already in catalog
bool table_exists(const char *table_name);
  
#endif // !CATALOG_H
