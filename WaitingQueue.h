#ifndef WAITINGQUEUE_H
#define WAITINGQUEUE_H

/**
 * @file WaitingQueue.h
 * @brief Definição das estruturas e funções para manipulação de uma fila de espera com prioridade.
 */

namespace WaitingQueueTAD {

/**
 * @struct Client
 * @brief Representa um cliente na fila de espera.
 */
struct Client {
    char name[50];  ///< Nome do cliente.
    int priority;   ///< Prioridade do cliente (0 para geral, 1 para idoso).
};

/**
 * @struct QueueNode
 * @brief Nó de uma fila encadeada, representando um cliente na fila.
 */
struct QueueNode {
    Client client;     ///< Dados do cliente.
    QueueNode* next;   ///< Ponteiro para o próximo nó na fila.
    QueueNode* previous; ///< Ponteiro para o nó anterior na fila (não utilizado no código atual, mas útil para futuras expansões).
};

/**
 * @struct Queue
 * @brief Representa uma fila encadeada de clientes.
 */
struct Queue {
    QueueNode* head;  ///< Primeiro elemento da fila.
    QueueNode* tail;  ///< Último elemento da fila.
    int count;        ///< Número de elementos na fila.
};

/**
 * @struct WaitingQueue
 * @brief Estrutura que gerencia as filas de espera, separando clientes gerais e idosos.
 */
struct WaitingQueue {
    int elderlyCounter;  ///< Contador de idosos atendidos consecutivamente.
    int generalCounter;  ///< Contador de clientes gerais atendidos.
    Queue elderlyQueue;  ///< Fila de idosos.
    Queue generalQueue;  ///< Fila de clientes gerais.
};

/**
 * @brief Cria e inicializa uma fila de espera.
 * @return Ponteiro para a estrutura WaitingQueue recém-alocada.
 */
WaitingQueue* createQueue();

/**
 * @brief Insere um cliente na fila apropriada, de acordo com sua prioridade.
 * @param queue Ponteiro para a estrutura WaitingQueue.
 * @param client Estrutura contendo os dados do cliente a ser inserido.
 */
void enqueue(WaitingQueue* queue, Client client);

/**
 * @brief Retorna o próximo cliente a ser atendido sem removê-lo da fila.
 * @param queue Ponteiro para a estrutura WaitingQueue.
 * @param returnClient Ponteiro para armazenar os dados do cliente retornado.
 * @return 1 se houver cliente a ser atendido, 0 se a fila estiver vazia.
 */
int peek(const WaitingQueue* queue, Client* returnClient);

/**
 * @brief Remove e retorna o próximo cliente a ser atendido.
 * @param queue Ponteiro para a estrutura WaitingQueue.
 * @param returnClient Ponteiro para armazenar os dados do cliente removido.
 * @return 1 se um cliente foi removido, 0 se a fila estiver vazia.
 */
int dequeue(WaitingQueue* queue, Client* returnClient);

/**
 * @brief Remove um cliente específico da fila pelo nome.
 * @param queue Ponteiro para a estrutura WaitingQueue.
 * @param name Nome do cliente a ser removido.
 * @return 1 se o cliente foi removido, 0 se ele não foi encontrado.
 */
int removeClient(WaitingQueue* queue, char* name);

/**
 * @brief Obtém a ordem dos clientes na fila, considerando a prioridade de atendimento.
 * @param queue Ponteiro para a estrutura WaitingQueue.
 * @param numClients Ponteiro para armazenar o número total de clientes na fila.
 * @return Ponteiro para um array dinâmico contendo a ordem dos clientes.
 */
Client* getQueueOrder(const WaitingQueue* queue, int* numClients);

/**
 * @brief Libera toda a memória alocada para a fila de espera.
 * @param queue Ponteiro para a estrutura WaitingQueue a ser desalocada.
 */
void deleteQueue(WaitingQueue* queue);

} // namespace WaitingQueueTAD

#endif // WAITINGQUEUE_H
