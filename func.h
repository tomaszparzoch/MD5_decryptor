#include <stdio.h>
#include <openssl/md5.h>
#include <string.h>
#include <pthread.h>

#include "data.h"

void read_word(size_t *psd, char *word);
void md5_pass(char *password, char *word_md5);
void compare_md5(char *pass_md5, char *password);
void pass_maker(char *word, int i);