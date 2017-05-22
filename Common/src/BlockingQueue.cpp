#include "BlockingQueue.h"
#include <string>

template <class T>
void BlockingQueue<T>::put(T t)
{
	Lock l(mutex);
	_queue.push(t);
	mutex.signal();
}

template <class T>
T BlockingQueue<T>::pull()
{
   Lock l(mutex);
   if(_queue.empty())
   {
       mutex.wait();
   }

   T t = _queue.front();
   _queue.pop();

   return t;
}

template <class T>
const bool BlockingQueue<T>::estaVacia()
{
	return _queue.empty();
}

template <class T>
void BlockingQueue<T>::esperar()
{
	this->mutex.wait();
}




template class BlockingQueue<std::string>;
