#ifndef DISPATCHER_H
#define DISPATCHER_H
#include "../context.h"
#include "../parser/parser.h"

void dispatch_command(DBContext ctx, ParesedCommand cmd);

#endif // !DISPATCHER_H
