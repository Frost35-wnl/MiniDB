#ifndef CATALOG_H
#define CATALOG_H
#include "../config.h"
#include "../utils.h"
#include <stdbool.h>

// Add the table and its fields to the catalog
bool add_table_to_catalog(const char *table_name);
// Read all the tables from catalog
void list_catalog_tables();
// Get table count
int get_table_count();
// Check if table is already in catalog
bool does_table_exist(const char *table_name);
// To remove table form catalog
void remove_table_from_catalog(const char *table_name);

#endif // !CATALOG_H
