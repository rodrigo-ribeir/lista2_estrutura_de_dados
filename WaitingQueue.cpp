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
        queue->elderlyCounter++;
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


}
