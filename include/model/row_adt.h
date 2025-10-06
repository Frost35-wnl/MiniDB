#ifndef ROW_ADT_H
#define ROW_ADT_H
#include "../config.h"

#ifndef COLUMN_WIDTH_DISPLAY
// Define the minimum width of each value to be displaied
#define COLUMN_WIDTH_DISPLAY 12
#endif /* ifndef COLUMN_WIDTH_DISPLAY */

typedef struct row_type *Row;

// values must contain NULL at the end
Row create_row(const char **values);
// print a row and return numbers of printed values
int print_row(const Row r);
// get the numbers of field for a row
int get_row_fields_count(const Row row);
// get row as a string (value1,value2,value3,...)
char *get_row_str(const Row row);
// free a row
void free_row(Row r);

#endif // !ROW_ADT_H
