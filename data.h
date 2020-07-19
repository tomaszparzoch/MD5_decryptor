#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define DICTIONARY "dictionary.txt"
#define N_HASHES_LIMIT 400
#define TRASH_BUFFOR 100

#ifndef DATA

struct{
  pthread_rwlock_t rw;
  char hashes[N_HASHES_LIMIT][33];
  int nhash;
}data;

struct{
  pthread_mutex_t mutex;
  pthread_cond_t cond_c;
  pthread_cond_t cond_p;
  char password[55];
  char password_md5[33];
  int ready;
}cons;

struct{
  char cracked_hash[10][33]; /* tymczasowo nie jest to mallock */
  int n;
}delete;

size_t dic_size;
char *dic_mem;  /*for DICTIONARY*/

#define DATA
#endif

int load_hashes();
int load_dictionary();

