#include <iostream>
#include "WaitingQueue.h"

using namespace std;
using namespace WaitingQueueTAD;

int main() {
    

    cout << "Criando fila" << endl;
    WaitingQueue* queue = createQueue();

    Client c1 = {"João", 1};  // Idoso
    Client c2 = {"Maria", 0}; // Geral
    Client c3 = {"Pedro", 1}; // Idoso
    Client c4 = {"Ana", 0};   // Geral

    enqueue(queue, c1);
    enqueue(queue, c2);
    enqueue(queue, c3);
    enqueue(queue, c4);

    Client next;
    if (peek(queue, &next)) {
        cout << "Próximo cliente: " << next.name << endl;
    }

    if (dequeue(queue, &next)) {
        cout << "Cliente atendido: " << next.name << endl;
    }
    char name[] = "Maria";
    if (removeClient(queue, name)) {
        cout << "Maria removida da fila!" << endl;
    }

    deleteQueue(queue);
    cout << "Fila deletada!" << endl;

    return 0;
}
