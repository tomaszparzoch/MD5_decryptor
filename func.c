#include "func.h"
#include <unistd.h>

void read_word(size_t *psd, char *word)
{
  int i = 0; /* position char in string - nie wiem czy to jest zrozumiale */
  
  if( *psd < dic_size ){
    while((dic_mem)[*psd] != '\n'){
      sprintf(&word[i], "%c", (dic_mem)[*psd]);
      i++;
      (*psd)++;
           
    }
    (*psd)++;   
  }
  
}

void md5_pass(char *password, char *pass_md5)
{
  unsigned char digest[16];

  MD5((unsigned char*)password, strlen(password), digest);
  for(int i = 0; i < 16; i++)
    sprintf(&pass_md5[i*2], "%02x", digest[i]);
}

void compare_md5(char *pass_md5, char *password)
{
  int i = 0;

  
  pthread_rwlock_rdlock(&data.rw);
  while( i < data.nhash){
    
    if( strcmp(pass_md5, data.hashes[i]) == 0 ){
      /* pytanie czy nie wydajniej by bylo porownywac hashe znak po znaku? */
      
      pthread_mutex_lock(&cons.mutex);
      if(cons.ready != 0){
	pthread_cond_wait(&cons.cond_p, &cons.mutex);
      }
      cons.ready++;
      sprintf(cons.password, "%s", password);
      sprintf(cons.password_md5, "%s", pass_md5);
      /*  printf("%s = %s\n", pass_md5, cons.password); */
      pthread_cond_signal(&cons.cond_c);
      pthread_mutex_unlock(&cons.mutex);
    }
    i++;
    
  }
  pthread_rwlock_unlock(&data.rw);
   
}

void pass_maker(char *word, int i)
{
  char password[55];
  char pass_md5[33];

  sprintf(password, "%s%d", word, i);
  md5_pass(&(*password), &(*pass_md5));
  compare_md5(&(*pass_md5), &(*password));

  sprintf(password, "%d%s", i, word);
    
  md5_pass(&(*password), &(*pass_md5));
  compare_md5(&(*pass_md5), &(*password));
}
  

  
  
