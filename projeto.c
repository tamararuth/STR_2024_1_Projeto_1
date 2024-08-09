#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>

// Definindo constantes
#define NUM_BARBEIROS 3
#define NUM_CADEIRAS 5
#define NUM_CLIENTES_POR_DIA 30

// Variáveis globais
sem_t sem_cadeiras_espera;      // Semáforo para cadeiras de espera
sem_t sem_barbeiros;            // Semáforo para barbeiros
pthread_mutex_t mutex_cadeiras; // Mutex para proteger o acesso às cadeiras de espera

int cadeiras_ocupadas = 0;       // Número de cadeiras de espera ocupadas
int fila_clientes[NUM_CADEIRAS]; // Fila de IDs dos clientes esperando
int pos_fila = 0;                // Posição de inserção na fila
int pos_atendimento = 0;         // Posição de atendimento na fila

// Função do barbeiro
void* barbeiro(void* arg) {
    int id = *((int*)arg);
    free(arg);                  // Libera a memória alocada para 'id'

    while (1) {
        // Barbeiro dorme até ser acordado por um cliente
        if(cadeiras_ocupadas == 0){
            printf("# Barbeiro %d está dormindo.\n", id);
        } 
        
        sem_wait(&sem_barbeiros); // Caso Demandado um barbeiro ele avança o semaforo
        
        // Barbeiro atende o cliente
        pthread_mutex_lock(&mutex_cadeiras);    

       
        int cliente_id = fila_clientes[pos_atendimento];
        pos_atendimento = (pos_atendimento + 1) % NUM_CADEIRAS;
        cadeiras_ocupadas--;
        pthread_mutex_unlock(&mutex_cadeiras);  // Libera cadeira da fila de espera

        printf("# Barbeiro %d está atendendo o cliente %d.\n", id, cliente_id);

        // Simula o tempo de atendimento
        sleep((rand() % 3) + 5);

        printf("# Barbeiro %d terminou de atender o cliente %d.\n", id, cliente_id);
        
        // Barbeiro verifica se há mais clientes esperando
        sem_post(&sem_cadeiras_espera);
    }
}

// Função do cliente
void* cliente(void* arg) {
    int id = *((int*)arg);
    free(arg);

    printf("- Cliente %d chegou.\n", id);

    pthread_mutex_lock(&mutex_cadeiras);

    if (cadeiras_ocupadas < NUM_CADEIRAS) {
        fila_clientes[pos_fila] = id;
        pos_fila = (pos_fila + 1) % NUM_CADEIRAS;
        cadeiras_ocupadas++;
        printf("- Cliente %d sentou na cadeira de espera.\n", id);
        pthread_mutex_unlock(&mutex_cadeiras);

        // Cliente acorda um barbeiro se necessário
        sem_post(&sem_barbeiros);

        // Cliente espera até ser atendido
        sem_wait(&sem_cadeiras_espera);

    } else {
        printf("- Cliente %d foi embora sem ser atendido, não há cadeiras de espera disponíveis.\n", id);
        pthread_mutex_unlock(&mutex_cadeiras);
    }

    return NULL;
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand(time(NULL));
    pthread_t t_barbeiros[NUM_BARBEIROS];
    pthread_t t_clientes[NUM_CLIENTES_POR_DIA]; // Cria mais clientes que cadeiras de espera

    // Inicializa semáforos e mutex
    sem_init(&sem_cadeiras_espera, 0, 0);
    sem_init(&sem_barbeiros, 0, 0);
    pthread_mutex_init(&mutex_cadeiras, NULL);

    // Inicializa fila de clientes
    for (int i = 0; i < NUM_CADEIRAS; i++) {
        fila_clientes[i] = -1; // Inicializa com valores inválidos
    }

    // Cria threads dos barbeiros
    for (int i = 0; i < NUM_BARBEIROS; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&t_barbeiros[i], NULL, barbeiro, id);
    }

    // Cria threads dos clientes
    for (int i = 0; i < NUM_CLIENTES_POR_DIA; i++) {
        sleep((rand() % 3)); // Simula a chegada aleatória dos clientes
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&t_clientes[i], NULL, cliente, id);
    }

    // Aguarda todas as threads dos clientes terminarem
    for (int i = 0; i < NUM_CLIENTES_POR_DIA; i++) {
        pthread_join(t_clientes[i], NULL);
    }


    // Destroi semáforos e mutex
    sem_destroy(&sem_cadeiras_espera);
    sem_destroy(&sem_barbeiros);
    pthread_mutex_destroy(&mutex_cadeiras);

    return 0;
}
