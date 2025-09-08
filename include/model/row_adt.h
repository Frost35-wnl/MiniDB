#ifndef ROW_ADT_H
#define ROW_ADT_H

typedef struct row_type *Row;

Row create_row(const char **values,int num_fields);
void free_row(Row r);
int print_row(Row r);
#endif // !ROW_ADT_H
