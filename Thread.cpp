//http://www.tutorialspoint.com/cplusplus/cpp_multithreading.htm gcc -lpthread 
//home/tovantran/Ctest/k_r/thread/Thread.cpp --> 2015-11-02 by ./.tv  owner: tovantran

#include <iostream>
#include <pthread.h>

using namespace std;

#define NUM_THREADS     5

void *PrintHello(void *threadid) //void pointer not function so &PrintHello or PrintHello is ok 
{
   long tid;
   tid = (long)threadid;  //cast (void pointer)
   cout << "Hello World! Thread ID, " << tid << endl;
   pthread_exit(NULL);
//   return 0;
}

int main ()
{
   pthread_t threads[NUM_THREADS];
   int rc;
   int i;
   for( i=0; i < NUM_THREADS; i++ ){
      cout << "main() : creating thread, " << i << endl;
      rc = pthread_create(&threads[i], NULL, 
                          &PrintHello, (void *)i);

      if (rc){  //NE is error !rc is  rc == 0 if False rc == 1 is True
         cout << "Error:unable to create thread," << rc << endl;
         //exit(-1);
         break;
      }
   }
   for (int i = 0; i < 100000; i++)
   		//wait to thread completed before exit
   pthread_exit(NULL);
}
