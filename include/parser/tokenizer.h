#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef struct tokens_type *Tokens;

Tokens tokenize(const char *input);
void print_tokens(const Tokens);
void free_tokens(Tokens);

#endif // !TOKENIZER_H
