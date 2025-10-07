#ifndef TABLE_DATA_H
#define TABLE_DATA_H
#include "../config.h"
#include "../model/table_adt.h"
#include "../utils.h"
#include <stdbool.h>

// Database functions (.db)
bool create_table_data(Table t);
bool write_table_row(const char *table_name, const Row row);
// Read rows from file and Return Row ADT with row_count as pointer
Row *read_table_rows(const char *table_name, int *row_count);
void clear_table_data(const char *table_name);
bool does_table_data_exist(const char *table_name);
#endif // !TABLE_DATA_H
