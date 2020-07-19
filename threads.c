#include "threads.h"
#include <unistd.h>

void * produce0()
{
  char word[50];
  char word_md5[33];
  size_t psd = 0; /* position indicator for dictionary */

  while( psd < dic_size ){
    
    read_word(&psd, &(*word));

    if( word[0] >= 'A' && word[0] <= 'Z') 
      word[0] = word[0] + 32; /*first low */
 
    md5_pass(&(*word), &(*word_md5));
    compare_md5(&(*word_md5), &(*word));
  }

  while( psd < dic_size ){
    
    read_word(&psd, &(*word));

    if( word[0] >= 'A' && word[0] <= 'Z') 
      word[0] = word[0] + 32; /*first low */

    for( int i = 0; i < 10; i++ )
      pass_maker(&(*word), i);
  }
  
  psd = 0;
  while( psd < dic_size ){
    
    read_word(&psd, &(*word));

    if( word[0] >= 65 && word[0] <= 90) 
      word[0] = word[0] + 32; /*first low */

    for( int i = 9; i < 100; i++ )
      pass_maker(&(*word), i);
  }
} 

void * produce1()
{
  char word[50];
  char word_md5[33];
  size_t psd = 0; /* position indicator for dictionary */

  while( psd < dic_size ){
    
    read_word(&psd, &(*word));

    if( word[0] >= 97 && word[0] <= 122)
      word[0] = word[0] - 32; /*first up*/
 
    md5_pass(&(*word), &(*word_md5));
    compare_md5(&(*word_md5), &(*word));
  }

  psd = 0;
  while( psd < dic_size ){
    
    read_word(&psd, &(*word));

    if( word[0] >= 97 && word[0] <= 122)
      word[0] = word[0] - 32; /*first up*/

    for( int i = 0; i < 10; i++ )
      pass_maker(&(*word), i);
  }
  psd = 0;
  while( psd < dic_size ){
    
    read_word(&psd, &(*word));

    if( word[0] >= 97 && word[0] <= 122)
      word[0] = word[0] - 32; /*first up*/

    for( int i = 9; i < 100; i++ )
      pass_maker(&(*word), i);
      } 
}

void * produce2()
{
  char word[50];
  char word_md5[33];
  size_t psd = 0; /* position indicator for dictionary */
  int i;

  while( psd < dic_size ){
    
    read_word(&psd, &(*word));
    i = 0;
    while(word[i] != '\0'){
      word[i] = toupper(word[i]);
      i++;
    }

 
    md5_pass(&(*word), &(*word_md5));
    compare_md5(&(*word_md5), &(*word));
  }

  psd = 0;
  while( psd < dic_size ){
    
    read_word(&psd, &(*word));

    i = 0;
    while(word[i] != '\0'){
      word[i] = toupper(word[i]);
      i++;
    }

    for( int i = 0; i < 10; i++ )
      pass_maker(&(*word), i);
  }
  psd = 0;
  while( psd < dic_size ){
    
    read_word(&psd, &(*word));

    i = 0;
    while(word[i] != '\0'){
      word[i] = toupper(word[i]);
      i++;
    }

    for( int i = 9; i < 100; i++ )
      pass_maker(&(*word), i);
      }
}
  
void * consume()
{

  int n = data.nhash;

  pthread_mutex_lock(&cons.mutex);

  for( int i = 0; i < n; i++){
    
    pthread_cond_wait(&cons.cond_c, &cons.mutex);
    printf("%d %s = %s\n", i, cons.password_md5, cons.password);
    sprintf(delete.cracked_hash[delete.n+1], "%s", cons.password_md5);
    delete.n++;
    cons.ready--;
    pthread_cond_signal(&cons.cond_p);
    
  }

  printf("Zlamano wszystkie hasla!\n");
  
  pthread_mutex_unlock(&cons.mutex);
  
}

void * deleter()
{
  int i;
  
  while(1){ /* pytanie czy taka petla nie zamula za bardzo programu? */
    
    while( delete.n != 0 ){
      pthread_rwlock_wrlock(&data.rw);

      i = 0;
      while( i < data.nhash ){
	if( strcmp(delete.cracked_hash[delete.n], data.hashes[i]) == 0 ){
	  printf("Usuwam %s - nhash = %d\n", data.hashes[i], data.nhash);
	  sprintf(data.hashes[i], "%s", data.hashes[data.nhash]);
	  data.nhash--;
	  i--;
	}
	i++;
      }
      delete.n--;
      pthread_rwlock_unlock(&data.rw);
    }    
  }     
}
  
    
  
    
