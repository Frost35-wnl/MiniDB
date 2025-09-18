#ifndef TABLE_META_H
#define TABLE_META_H
#include "../config.h"
#include "../model/table_adt.h"
#include <stdbool.h>

//create <t>.meta and save fields
bool write_table_meta(Table t);
//load filed names into Table ADT
Table read_table_meta(char *table_name);

#endif // !TABLE_META_H
#define TABLE_META_H


