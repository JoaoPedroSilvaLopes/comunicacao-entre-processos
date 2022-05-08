#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

#define PHILOS 6
#define DELAY 5000
#define FOOD 50

void *filosofo (void *id);
void pegarGarfo (int, int, char *);
void deixarGarfo (int, int);
int comidaNaMesa ();

pthread_mutex_t garfo[PHILOS];
pthread_t philo[PHILOS];
pthread_mutex_t food_lock;
int sleep_seconds = 30;

int main (int argn, char **argv) {
  int i;
  
  if (argn == 2)
    sleep_seconds = atoi (argv[1]);
  
  pthread_mutex_init (&food_lock, NULL);
  for (i = 0; i < PHILOS; i++)
    pthread_mutex_init (&garfo[i], NULL);
  for (i = 0; i < PHILOS; i++)
    pthread_create (&philo[i], NULL, filosofo, (void *)i);
  for (i = 0; i < PHILOS; i++)
    pthread_join (philo[i], NULL);
  return 0;
}

void *filosofo (void *num) {
  int id;
  int i, garfoEsquerda, garfoDireita, f;
  
  id = (int)num;
  printf ("Filósofo %d acabou de pensar e agora está pronto para comer.\n", id);
  garfoDireita = id;
  garfoEsquerda = id + 1;
  
  if (garfoEsquerda == PHILOS)
    garfoEsquerda = 0;

  while (f = comidaNaMesa ()) {

    if (id == 1)
      sleep (sleep_seconds);

    if ((id % 2) == 0) {
      pegarGarfo (id, garfoEsquerda, "esquerda");
      pegarGarfo (id, garfoDireita, "direita");
    }
    else {
      pegarGarfo (id, garfoDireita, "direita");
      pegarGarfo (id, garfoEsquerda, "esquerda");
    }

    //pegarGarfo (id, garfoDireita, "direita");
    //pegarGarfo (id, garfoEsquerda, "esquerda");

    printf ("Filósofo %d: está comendo.\n", id);
    usleep (DELAY * (FOOD - f + 1));
    deixarGarfo (garfoEsquerda, garfoDireita);
  }

  printf ("Filósofo %d acabou de comer.\n", id);
  return (NULL);
}

int comidaNaMesa () {
  static int food = FOOD;
  int myfood;

  pthread_mutex_lock (&food_lock);
  if (food > 0) {
    food--;
  }
  myfood = food;
  pthread_mutex_unlock (&food_lock);
  printf ("Comida restante %d.\n", food);
  return myfood;
}
	
void pegarGarfo (int phil, int c, char *hand) {
  pthread_mutex_lock (&garfo[c]);
  printf ("Filósofo %d: pegou o garfo da %s %d\n", phil, hand, c);
}
	
void deixarGarfo (int c1, int c2) {
  pthread_mutex_unlock (&garfo[c1]);
  pthread_mutex_unlock (&garfo[c2]);
}
