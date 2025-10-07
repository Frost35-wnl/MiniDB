#ifndef CONTEXT_H
#define CONTEXT_H
#include "../include/storage/table_data_file.h"
#include "../include/storage/table_meta_file.h"
#include "./model/table_adt.h"
#include <stdbool.h>

typedef struct context_type *DBContext;

// Create empty context
DBContext init_context();
// Switch selected table
void set_current_table(DBContext ctx, Table t);
// Access the selected table
Table get_current_table(DBContext ctx);
// Cleanup context
void free_context(DBContext ctx);
// Load table
Table load_table(const char *table_name);
// Save table
bool save_table(const Table table);
#endif // !CONTEXT_H
