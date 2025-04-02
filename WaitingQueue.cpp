#include<WaitingQueue.h>

namespace WaitingQueueTAD {

WaitingQueue createQueue() {
    WaitingQueue* queue = new WaitingQueue;
    queue->generalCounter = 0;
    queue->elderlyCounter = 0;
    queue->head = nullptr;
    queue->tail = nullptr;
    return queue;
}

}
