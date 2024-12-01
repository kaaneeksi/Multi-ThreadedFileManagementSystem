#ifndef THREADS_H
#define THREADS_H

void initialize_threads_and_semaphores();
void start_main_thread();
void *main_thread_function(void *arg);
void simulate_client_request(const char *action);
void clean_up_resources();

#endif
