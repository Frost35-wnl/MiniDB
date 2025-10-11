#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef struct tokens_type *Tokens;

Tokens tokenize(const char *input);
void print_tokens(const Tokens);
int get_tokens_count(const Tokens);
char **get_tokens_args(const Tokens);
void free_tokens(Tokens);

#endif // !TOKENIZER_H
