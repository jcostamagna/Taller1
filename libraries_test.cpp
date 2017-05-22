#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <glog/logging.h>

void* test(void* data) {
   return NULL;
}

int main(int argc, char *argv[] )
{
   pthread_t p;
   pthread_create(&p, NULL, test, NULL);
   LOG(INFO)<<"Testing Glog...";
   return 0;
}


