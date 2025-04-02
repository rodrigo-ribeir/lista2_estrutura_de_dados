#ifndef WAITINGQUEUE.H
#define WAITINGQUEUE.H


struct Client {
    char name[50];
    int priority; // 0 geral; 1 idoso
};


struct QueueNode {
    Client client;
    QueueNode* next;
    QueueNode* previous;
};

struct Queue {
    QueueNode* head;  // Primeiro elemento da fila
    QueueNode* tail;   // Último elemento da fila
    int count;         // Número de elementos na fila
};

struct WaitingQueue {
    int elderlyCounter;  // Contador de idosos atendidos
    int generalCounter;  // Contador de "gerais" atendidos
    Queue elderlyQueue;  // Fila de idosos
    Queue generalQueue;  // Fila de clientes gerais
};


WaitingQueue* createQueue();

void enqueue(WaitingQueue* queue, Client client);

#endif