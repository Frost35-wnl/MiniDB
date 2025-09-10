#ifndef CONTEXT_H
#define CONTEXT_H
#include "./model/table_adt.h"

typedef struct context_type *DBContext;

  //Create empty context
DBContext init_context();
  //Switch selected table
void set_current_table(DBContext ctx, Table t);
  //Access the selected table
Table get_current_table(DBContext ctx);
  //Cleanup context
void free_context(DBContext ctx);

#endif // !CONTEXT_H



