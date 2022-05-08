#include <semaphore.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define N 5
#define CATS 5
#define DOGS 5

char buffer[5];       
typedef int semaphore; 
semaphore mutex = 1;
semaphore full = 0;
semaphore empty = N;

void catWantsToEnter();
void dogWantsToEnter();
void catLeaves();
void dogLeaves();

void catWantsToEnter() {
  char cat;

  if (mutex == 0 && full != 0) {
    printf("Gato não pode entrar! \n");
  }

  if (full == 0) {
    printf("Sala Vazia \n");
  }

  while (TRUE && mutex != 0 && empty != 0) {
    cat = 'C';
    empty--;
    mutex = 0;
    buffer[full] = cat;
    printf("Gato entrou na sala! \n");
    full++;
    dogWantsToEnter();
    printf(" sala: %s \n", buffer);
    mutex = 1;
  }
  catLeaves();
}

void dogWantsToEnter() {
  char dog;

  if (mutex == 0 && full != 0) {
    printf("Cachorro não pode entrar! \n");
  }

  if (full == 0) {
    printf("Sala Vazia \n");
  }

  while (TRUE && mutex != 0 && empty != 0) {
    dog = 'D';
    empty--;
    mutex = 0;
    buffer[full] = dog;
    printf("Cachorro entrou na sala! \n");
    full++;
    catWantsToEnter();
    printf(" sala: %s \n", buffer);
    mutex = 1;
  }
  dogLeaves();
}

void catLeaves() {
  char cat;

  while (TRUE && mutex == 1) {
    buffer[full - 1] = '\0';
    full--;
    empty++;
    printf("Gato saiu da sala!");
    printf(" sala: %s \n", buffer);
    if (full == 0) {
      mutex--;
    }
  }
}

void dogLeaves() {
  char dog;

  while (TRUE && mutex == 1) {
    buffer[full - 1] = '\0';
    full--;
    empty++;
    printf("Cachorro saiu da sala!");
    printf(" sala: %s \n", buffer);
    if (full == 0) {
      mutex--;
    }
  }
}

int main() {
  catWantsToEnter(); // Gato entrando e cachorro não pode entrar
  dogWantsToEnter(); // Cachorro entrando e gato não pode entrar
  return 0;
}
