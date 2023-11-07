#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>	

// Declaração do mutex
pthread_mutex_t mutex;

// Funcao que libera o acesso ao edificio
void *liberar(void *arg) {	
  // Bloqueia o mutex
  pthread_mutex_lock(&mutex);

  // Altera o estado do sistema para liberado
  *(int *)arg = 1;	

  // Desbloqueia o mutex
  pthread_mutex_unlock(&mutex);

}

// Funcao que bloqueia o acesso ao edificio
void *bloquear(void *arg) {	
  // Bloqueia o mutex
  pthread_mutex_lock(&mutex);

  // Altera o estado do sistema para bloqueado
  *(int *)arg = 0;

  // Desbloqueia o mutex
  pthread_mutex_unlock(&mutex);

}

int main() {

  // Inicializa o mutex
  pthread_mutex_init(&mutex, NULL);

  // variavel para o estado do sistema
  int liberado = 1;

  // declara duas threads
  pthread_t thread1, thread2;

  // Cria a primeira thread e passa o endereço de "liberado" como argumento
  pthread_create(&thread1, NULL, liberar, (void *)&liberado);

  // Cria a segunda thread e passa o endereço de "liberado" como argumento
  pthread_create(&thread2, NULL, bloquear, (void *)&liberado);

  // Aguarda o termino das threads
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  // Imprime o estado do sistema
  printf("Liberado: %d\n", liberado);

  // Destroi o mutex
  pthread_mutex_destroy(&mutex);

  return 0;
}