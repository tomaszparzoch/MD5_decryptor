#include "data.h"

int load_hashes()
{
  char trash[TRASH_BUFFOR];
  FILE *f_hashes;
  data.nhash = 0;
  cons.ready = 0;
  delete.n = 0;
  f_hashes = fopen("hashes", "r");

  if( f_hashes == NULL ){
    perror("Hashes");
    return -1;
  }

  while( feof(f_hashes) == 0 && data.nhash  < N_HASHES_LIMIT ){
    
    fscanf(f_hashes, "%s", trash);
    fscanf(f_hashes, "%s", data.hashes[data.nhash]); /* do ogarniacia fscanf buffor overflow */
    data.nhash++;
  }

  if( data.nhash == N_HASHES_LIMIT )
    printf("Zapelniono bufor haszy!\n");
  
  return 0;
 
}

int load_dictionary()
  /* Laduje slownik do pamieci dynamicznej w formie tablicy jednowymiarowej.
     Potem ogarnalem, ze moglbym to zrobic do tablicy dwuwymiarowej,
     ale funkcja IMO wyglada ok - jest prosta i czytelna */
{
  dic_mem = NULL;
  FILE *dic;
  dic = fopen(DICTIONARY, "r");

  if( dic == NULL ){
    perror(DICTIONARY);
    exit(-1);
  }

  fseek(dic, 0, SEEK_END);
  dic_size = ftell(dic);
  fseek(dic, 0, SEEK_SET);
  
  dic_mem = (char*)malloc(dic_size);

  fread(dic_mem, 1, dic_size, dic);
  fclose(dic);

  return 0;
}
