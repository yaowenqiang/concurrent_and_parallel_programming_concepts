static pthread_mutex_t lock;

void increment_n() {
  pthread_mutex_lock(&lock);
  n = n + 1;
  pthread_mutex_unlock(&lock);
}
