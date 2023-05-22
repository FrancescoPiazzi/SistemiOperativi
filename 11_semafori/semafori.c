// pthread_mutex_lock(&lock): blocca lock, attende che si sblocchi se blocaato
// pthread_mutex_unlock(&lock): sblocca lock
// i semafori creati con PTHREAD_MUTEX_RECURSIVE 
// possono essere bloccati più volte per sbloccare un thread
// bloccato più volte è necessario sbloccarlo quel numero di volte