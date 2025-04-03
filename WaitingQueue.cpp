#include "WaitingQueue.h"
#include<cstring>

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
        queue->elderlyQueue.count--;
        queue->elderlyCounter++;
    }
    // Se há clientes gerais e já foram atendidos dois idosos
    else if (queue->generalQueue.head) { 
        nodeToRemove = queue->generalQueue.head;
        queue->generalQueue.head = nodeToRemove->next;
        queue->generalQueue.count--;
        queue->elderlyCounter = 0; // Reinicia o contador de idosos atendidos
    }
    // Se não há clientes gerais, atender idoso mesmo que a regra quebre
    else if (queue->elderlyQueue.head) { 
        nodeToRemove = queue->elderlyQueue.head;
        queue->elderlyQueue.head = nodeToRemove->next;
        queue->elderlyQueue.count--;
        queue->elderlyCounter++;
    }

    // Atualizar tail caso a fila tenha ficado vazia
    if (!queue->elderlyQueue.head) queue->elderlyQueue.tail = nullptr;
    if (!queue->generalQueue.head) queue->generalQueue.tail = nullptr;

    if (nodeToRemove) {
        *returnClient = nodeToRemove->client;
        delete nodeToRemove;
        return 1;
    }
    
    return -1; // Caso extremo que não deve ocorrer
}

int removeClient(WaitingQueue* queue, char* name) {
    QueueNode *prev = nullptr, *current = queue->elderlyQueue.head;
    
    // Buscar na fila de idosos
    while (current) {
        if (strcmp(current->client.name, name) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                queue->elderlyQueue.head = current->next;
            }
            if (!queue->elderlyQueue.head) {
                queue->elderlyQueue.tail = nullptr;
            }
            delete current;
            queue->elderlyQueue.count--;
            return 1;
        }
        prev = current;
        current = current->next;
    }

    // Restaurar os ponteiros para fazer a buscar na fila geral
    prev = nullptr;
    current = queue->generalQueue.head;
    
    while (current) {
        if (strcmp(current->client.name, name) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                queue->generalQueue.head = current->next;
            }
            if (!queue->generalQueue.head) {
                queue->generalQueue.tail = nullptr;
            }
            delete current;
            queue->generalQueue.count--;
            return 1;
        }
        prev = current;
        current = current->next;
    }
    
    return 0; // Cliente não encontrado
}

Client* getQueueOrder(const WaitingQueue* queue, int* numClients) {
    *numClients = queue->elderlyQueue.count + queue->generalQueue.count;
    if (*numClients == 0) {
        return nullptr;
    }

    Client* order = new Client[*numClients];
    int index = 0;
    QueueNode* elderlyCurrent = queue->elderlyQueue.head;
    QueueNode* generalCurrent = queue->generalQueue.head;
    int elderlyCount = queue->elderlyQueue.count;
    int generalCount = queue->generalQueue.count;

    while (elderlyCount > 0 || generalCount > 0) {
        // Atender dois idosos, se disponíveis
        for (int i = 0; i < 2 && elderlyCount > 0; i++) {
            if (elderlyCurrent) {
                order[index++] = elderlyCurrent->client;
                elderlyCurrent = elderlyCurrent->next;
                elderlyCount--;
            }
        }
        // Atender um não idoso, se disponível
        if (generalCount > 0) {
            if (generalCurrent) {
                order[index++] = generalCurrent->client;
                generalCurrent = generalCurrent->next;
                generalCount--;
            }
        }
    }
    
    return order;
}


void deleteQueue(WaitingQueue* queue) {
    QueueNode* current;
    
    // Liberar memória da fila de idosos
    current = queue->elderlyQueue.head;
    while (current) {
        QueueNode* temp = current;
        current = current->next;
        delete temp;
    }
    queue->elderlyQueue.head = nullptr;
    queue->elderlyQueue.tail = nullptr;
    queue->elderlyQueue.count = 0;
    
    // Liberar memória da fila geral
    current = queue->generalQueue.head;
    while (current) {
        QueueNode* temp = current;
        current = current->next;
        delete temp;
    }
    queue->generalQueue.head = nullptr;
    queue->generalQueue.tail = nullptr;
    queue->generalQueue.count = 0;
    
    // Liberar a estrutura da fila principal
    delete queue;
}

}
