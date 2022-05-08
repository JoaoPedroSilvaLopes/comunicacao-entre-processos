#include <pthread.h>
#include <stdio.h>

// defines para o funcionamento correto
#define TRUE 1
#define FALSE 0
#define N 5

pthread_mutex_t mutex; // mutex para controlar a regiao critica

int buffer[N]; // array simulando um buffer
int vazio = TRUE; // buffer começando como vazio
int cheio = 0; // contador para verificar se o buffer esta cheio

void produtor(int id) {
  int contadorPosicao = 1;
  int item;
  int aguardarInsercao;

  while (contadorPosicao <= N) {

    // produzir um item
    item = id * 10 + contadorPosicao;

    /* 
    condicionais que verificam se o buffer esta cheio ou nao. 
    se estiver cheio o produtor deve aguardar liberar espaço 
    livre
    */
    do {
      pthread_mutex_lock(&mutex);
      aguardarInsercao = FALSE;
      if (vazio == FALSE) {
        aguardarInsercao = TRUE;
        pthread_mutex_unlock(&mutex);
      }
    } while (aguardarInsercao == TRUE);

    /* 
    verificar qual posição do array do buffer esta vazia
    para adicionar o valor no espaço livre
    */
    for (int j = 0; j < N; j++) {
      if (buffer[j] == NULL) {
        buffer[j] = item;
        break;
      }
    }

    cheio++;
    
    printf("Produtor %d inserindo item %d na posição %d: [%d , %d , %d , %d , %d]\n", 
    id, item, cheio, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

    pthread_mutex_unlock(&mutex);

    if (cheio == 5) {
      vazio = FALSE;
    }
    
    contadorPosicao++;
    sleep(2);
  }
}

void consumidor(int id) {
  int item;
  int aguardarConsumir;

  while (TRUE) {

    /* 
    condicionais que verificam se o buffer esta vazio ou nao,
    se estiver vazio o consumidor deve aguardar os espaços livres
    encherem.
    */
    do {
      pthread_mutex_lock(&mutex);
      aguardarConsumir = FALSE;
      if (vazio == TRUE) {
        aguardarConsumir = TRUE;
        pthread_mutex_unlock(&mutex);
      }
    } while (aguardarConsumir == TRUE);

    /* 
    verificar qual a primeira posição do array do buffer que esta
    ocupada para retirar o valor e deixar o espaço livre
    */
    for (int j = (N - 1); j >= 0; j--) {
      if (buffer[j] != NULL) {
        item = buffer[j];
        buffer[j] = NULL;
        break;
      }
    }

    printf("Consumidor %d consumiu item %d na posição %d: [%d , %d , %d , %d , %d]\n", 
    id, item, cheio, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
    
    cheio--;

    if (cheio == 0) {
      vazio = TRUE;
    }

    pthread_mutex_unlock(&mutex);
    sleep(2);
  }
}

int main() {
  /*
  criação das threads
  */
  pthread_t p1, p2, p3, c1, c2;

  pthread_create(&p1, NULL, (void *)produtor, 1);
  pthread_create(&p2, NULL, (void *)produtor, 2);
  pthread_create(&p3, NULL, (void *)produtor, 3);

  pthread_create(&c1, NULL, (void *)consumidor, 1);
  pthread_create(&c2, NULL, (void *)consumidor, 2);

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  pthread_join(p3, NULL);
  pthread_join(c1, NULL);
  pthread_join(c2, NULL);
}
