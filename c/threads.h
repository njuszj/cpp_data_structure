# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <pthread.h>

struct thread {
    int id;
    pthread_t thread;
    void (*entry)(int);
    struct thread *next;
};

struct thread *threads;
void (*join_fn)();

// ********Basics**********

__attribute__((destructor)) static void join_all() {
    for(struct thread *next; threads; threads = next){
        pthread_join(threads->thread, NULL);
        next = threads->next;
        free(threads);
    }
}
