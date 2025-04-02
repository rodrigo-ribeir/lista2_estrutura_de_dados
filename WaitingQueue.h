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

struct WaitingQueue {
    int generalCounter;
    int elderlyCounter;

};

WaitingQueue* createQueue();

#endif