#include <stdio.h>
#include <pthread.h>

#include "data.h"
#include "func.h"
#include "threads.h"

#include <unistd.h>

int main()
{
  pthread_t tid_produce[3], tid_consume, tid_deleter;
  
  printf("Program do lamania hasel metoda slownikowa\n");

  load_dictionary();
  printf("Zaladowano slownik\n");

  if( load_hashes() == 0)
    printf("Wczytano %d haszy (limit: %d)\n", (data.nhash+1), (N_HASHES_LIMIT+1));

  data.rw = (pthread_rwlock_t)PTHREAD_RWLOCK_INITIALIZER; /* to potrzebne? */
  cons.mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
  cons.cond_c = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
  cons.cond_p = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
  
  pthread_create(&tid_consume, NULL, consume, NULL);
  pthread_create(&tid_deleter, NULL, deleter, NULL);
  
  pthread_create(&tid_produce[0], NULL, produce0, NULL);
  pthread_create(&tid_produce[1], NULL, produce1, NULL);
  pthread_create(&tid_produce[2], NULL, produce2, NULL);

  pthread_join(tid_consume, NULL);
 


  free(dic_mem);
  
  return 0;
}



