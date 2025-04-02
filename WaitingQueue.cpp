#include<WaitingQueue.h>

namespace WaitingQueueTAD {

WaitingQueue* createQueue() {
    WaitingQueue* queue = new WaitingQueue;
    queue->generalCounter = 0;
    queue->elderlyCounter = 0;
     // Inicializa as filas de idosos e geral
     queue->elderlyQueue.head = nullptr;
     queue->elderlyQueue.tail = nullptr;
     queue->elderlyQueue.count = 0;
 
     queue->generalQueue.head = nullptr;
     queue->generalQueue.tail = nullptr;
     queue->generalQueue.count = 0;
 
     return queue;
}

void enqueue(WaitingQueue* queue, Client client) {
    QueueNode* newNode = new QueueNode{client, nullptr};

    if (client.priority == 1) { // Cliente idoso
        if (!queue->elderlyQueue.head) { // Fila vazia
            queue->elderlyQueue.head = queue->elderlyQueue.tail = newNode;
        } else {
            queue->elderlyQueue.tail->next = newNode;
            queue->elderlyQueue.tail = newNode;
        }
        queue->elderlyQueue.count++;
    } else { // Cliente geral
        if (!queue->generalQueue.head) { // Fila vazia
            queue->generalQueue.head = queue->generalQueue.tail = newNode;
        } else {
            queue->generalQueue.tail->next = newNode;
            queue->generalQueue.tail = newNode;
        }
        queue->generalQueue.count++;
    }
}

int peek(WaitingQueue* queue, Client* returnClient) {

    if (queue->elderlyQueue.count == queue->generalQueue.count == 0) {
        return 0; // Ambas as filas estão vazias
    }

    // Se há idosos e ainda não foram atendidos dois consecutivos
    if (queue->elderlyQueue.count > 0 && queue->elderlyCounter < 2) {
        *returnClient = queue->elderlyQueue.head->client;
        return 1;
    }

    // Se há clientes gerais e já foram atendidos dois idosos
    if (queue->generalQueue.head && queue->elderlyCounter == 2) {
        *returnClient = queue->generalQueue.head->client;
        queue->elderlyCounter = 0;
        return 1;
    }

    // Se não há clientes gerais, atender idoso mesmo que a regra quebre
    if (queue->elderlyQueue.head) {
        *returnClient = queue->elderlyQueue.head->client;
        return 1;
    }

    return 0; // Caso extremo de erro (não deveria ocorrer)
}

}
