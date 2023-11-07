#include <stdio.h>
#include <pthread.h>

// Funcao que calcula o fatorial
void* fatorial(void* arg) {
  int n = *((int*) arg);
  int resultado = 1;
  for (int i = 1; i <= n; i++) {
    resultado *= i;
  }
  return (void*) resultado;
}

int main() {
  // variaveis de exemplo
  // Alterar caso queira validar outros inputs
  int entrada[] = {5, 6, 7}; 

  // Calcula a quantidade de valores informados
  int num_entradas = sizeof(entrada) / sizeof(entrada[0]);

  pthread_t threads[num_entradas];
  void* resultados[num_entradas];

  // Cria threads conforme valores informados
  for (int i = 0; i < num_entradas; i++) {
    pthread_create(&threads[i], NULL, fatorial, &entrada[i]);
  }

  // Aguarda finalizacao das threads
  for (int i = 0; i < num_entradas; i++) {
    pthread_join(threads[i], &resultados[i]);
  }

  // Exibe os resultados
  for (int i = 0; i < num_entradas; i++) {
    printf("Fatorial de %d: %ld\n", entrada[i], (long) resultados[i]);
  }

  return 0;
}