#include <iostream>
#include "WaitingQueue.h"

using namespace std;
using namespace WaitingQueueTAD;

int main() {
    WaitingQueue* queue = createQueue();

    // Adicionando clientes à fila
    Client c1 = {"Ana", 1};
    Client c2 = {"Bruno", 0};
    Client c3 = {"Carlos", 1};
    Client c4 = {"Daniel", 0};
    Client c5 = {"Eduarda", 1};
    Client c6 = {"Fernando", 0};

    enqueue(queue, c1);
    enqueue(queue, c2);
    enqueue(queue, c3);
    enqueue(queue, c4);
    enqueue(queue, c5);
    enqueue(queue, c6);

    // Exibir a ordem de atendimento esperada
    int numClients;
    Client* order = getQueueOrder(queue, &numClients);
    
    cout << "Ordem de atendimento:" << endl;
    for (int i = 0; i < numClients; i++) {
        cout << order[i].name << endl;
    }
    delete[] order;

    removeClient(queue, (char*)"Daniel");

    // Atender clientes
    cout << "\nAtendendo clientes:" << endl;
    Client servedClient;
    while (dequeue(queue, &servedClient)) {
        cout << "Atendido: " << servedClient.name << endl;
    }
    
    // Removendo um cliente inexistente
    cout << "\nTentando remover 'Gustavo' (não existe na fila)..." << endl;
    if (!removeClient(queue, (char*)"Gustavo")) {
        cout << " Cliente não encontrado." << endl;
    }
    
    // Limpando memória
    deleteQueue(queue);
    return 0;
}
