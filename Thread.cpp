//http://www.tutorialspoint.com/cplusplus/cpp_multithreading.htm gcc -lpthread 
//http://www.bogotobogo.com/cplusplus/multithreading_pthread.php
//home/tovantran/Ctest/k_r/thread/Thread.cpp --> 2015-11-02 by ./.tv  owner: tovantran

#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

#define NUM_THREADS     5

void *PrintHello(void *threadid);
char thread_msg[] = "Hello Thread !"; //global

struct thread_data{
   int  thread_id;
   int  count;
   char *message;
//   char message[];
};

int main ()
{
   pthread_t threads[NUM_THREADS];
   int rc;
   int i;
   void *ret_join;
   struct thread_data td[NUM_THREADS];
   
   for( i=0; i < NUM_THREADS; i++ ){
      cout << "main() : creating thread, " << i << endl;
      td[i].thread_id = i;
      td[i].count = i;  //count == id
      td[i].message = (char *)" Hello Thread ! "; //warning: deprecated conversion from string constant to ‘char*’ [-Wwrite-strings]
      rc = pthread_create(&threads[i], NULL, 
//                          &PrintHello, (void *)&i);
														&PrintHello, (void *)&td[i]);
			  
      if (rc){  //NE is error !rc is  rc == 0 if False rc == 1 is True
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);  //<cstdlib>
         //break;
      }
 
   rc = pthread_join(threads[i], &ret_join);  //equivalent to delay wait for thread exit before join don't need to pthread_exit(NULL)
   if (rc){  //NE is error !rc is  rc == 0 if False rc == 1 is True
         cout << "Error:unable to create thread," << rc << endl;
         exit(EXIT_FAILURE);  //<cstdlib>
         //break;
         }
   }
   printf("Thread joined returned %s\n", (char *)ret_join);
   printf("Thread joined returned %s\n", (char *)td[i].message);
   printf("Thread joined returned %s\n", thread_msg);  //global
   pthread_exit(NULL);
}

void *PrintHello(void *threadarg) //void pointer not function so &PrintHello or PrintHello is ok 
{
   struct thread_data *t;
   t = (struct thread_data *) threadarg;
//   int tid;
//   tid = *(int *)threadid;  //cast (void pointer) see cast void pointer on cplusplus.doc
   cout << "Hello World! Thread ID, " << t->thread_id << endl;
   strcpy(thread_msg, "Thread GoodBye");  //need array[] or malloc so copy to. Pointer is not OK to strcpy but t->message = "Hello";
    t->message = const_cast<char *>("Thread GoodBye");
//	cout << t->message << endl;
//   pthread_exit(NULL);
//   return 0;
//  char *p = "Exit from thread";
//  pthread_exit(p);
	pthread_exit(const_cast<char *>("'Exit from thread'"));
}
