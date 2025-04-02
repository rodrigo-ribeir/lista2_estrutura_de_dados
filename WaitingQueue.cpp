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

int peek(const WaitingQueue* queue, Client* returnClient) {
    if (!queue->elderlyQueue.head && !queue->generalQueue.head) {
        return 0; // Ambas as filas estão vazias
    }

    // Se há idosos e ainda não foram atendidos dois consecutivos
    else if (queue->elderlyQueue.head && queue->elderlyCounter < 2) {
        *returnClient = queue->elderlyQueue.head->client;
        return 1;
    }

    // Se há clientes gerais e já foram atendidos dois idosos
    else if (queue->generalQueue.head) {
        *returnClient = queue->generalQueue.head->client;
        return 1;
    }

    // Se não há clientes gerais, atender idoso mesmo que a regra quebre
    else if (queue->elderlyQueue.head) {
        *returnClient = queue->elderlyQueue.head->client;
        return 1;
    }

    return -1; // Caso extremo que não deve ocorrer
}



int dequeue(WaitingQueue* queue, Client* returnClient) {
    if (!queue->elderlyQueue.head && !queue->generalQueue.head) {
        return 0; // Ambas as filas estão vazias
    }

    QueueNode* nodeToRemove = nullptr;

    // Se há idosos e ainda não foram atendidos dois consecutivos
    if (queue->elderlyQueue.head && queue->elderlyCounter < 2) {
        nodeToRemove = queue->elderlyQueue.head;
        queue->elderlyQueue.head = nodeToRemove->next;
        queue->elderlyCounter++;
    }
    // Se há clientes gerais e já foram atendidos dois idosos
    else if (queue->generalQueue.head) { 
        nodeToRemove = queue->generalQueue.head;
        queue->generalQueue.head = nodeToRemove->next;
        queue->elderlyCounter = 0; // Reinicia o contador de idosos atendidos
    }
    // Se não há clientes gerais, atender idoso mesmo que a regra quebre
    else if (queue->elderlyQueue.head) { 
        nodeToRemove = queue->elderlyQueue.head;
        queue->elderlyQueue.head = nodeToRemove->next;
        queue->elderlyCounter++;
    }

    // Atualizar tail caso a fila tenha ficado vazia
    if (nodeToRemove && !queue->elderlyQueue.head) {
        queue->elderlyQueue.tail = nullptr;
    }
    if (nodeToRemove && !queue->generalQueue.head) {
        queue->generalQueue.tail = nullptr;
    }

    if (nodeToRemove) {
        *returnClient = nodeToRemove->client;
        delete nodeToRemove;
        return 1;
    }
    
    return -1; // Caso extremo que não deve ocorrer
}


}
