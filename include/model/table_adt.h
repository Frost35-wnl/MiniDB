#ifndef TABLE_ADT_H
#define TABLE_ADT_H
#include <stdbool.h>
#include "./row_adt.h"

#ifndef COLUMN_WIDTH_DISPLAY
    //Define the minimum width of each value to be displaied
#define COLUMN_WIDTH_DISPLAY 12
#endif /* ifndef COLUMN_WIDTH_DISPLAY */

typedef struct table_type *Table;

    //field_names must contain NULL at the end
Table create_table(const char *name, const char **field_names);
    //return number of rows
bool add_row(Table table, const Row row);
    //free a table with rows
void free_table(Table table);
    //print table and return number of rows printed
int print_table(const Table table);
    //return number of rows
int get_table_length(const Table table);

#endif // !TABLE_ADT_H
