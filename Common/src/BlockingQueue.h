#ifndef BLOCKINGQUEUE_H_
#define BLOCKINGQUEUE_H_

#include <queue>
#include <stdio.h>
#include "Lock.h"

template <class T> class BlockingQueue
{
private:
    std::queue<T> _queue;
    Mutex mutex;
    BlockingQueue(const BlockingQueue& object);
    BlockingQueue& operator=(const BlockingQueue& object);
public:
	BlockingQueue(){}

	//Devuelve si la cola esta vacia.
	const bool estaVacia();

	//Llama al wait del Mutex. Espera a que entre un evento en la cola.
	void esperar();

	~BlockingQueue(){}

    void put(T t);

     T pull();

};

#endif /* BLOCKINGQUEUE_H_ */

