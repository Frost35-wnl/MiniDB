#ifndef TABLE_META_H
#define TABLE_META_H
#include "../config.h"
#include "../model/table_adt.h"
#include "../utils.h"
#include <stdbool.h>

// Metadata functions(.meta)
//  create <table>.meta and save fields
bool create_table_meta(Table t);
// load filed names into Table ADT
Table read_table_meta(const char *table_name);
// delete <table>.meta
void clear_table_meta(const char *table_name);

// Database functions (.db)
bool create_table_data(Table t);
bool write_table_row(const char *table_name, const Row row);
Row **read_table_rows(const char *table_name);
void clear_table_data(const char *table_name);
#endif // !TABLE_META_H
#define TABLE_META_H
