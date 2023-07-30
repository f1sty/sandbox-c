#include <stdint.h>
#include <stdio.h>
#include <threads.h>

#if __STDC_VERSION__ < 201112L || __STDC_NO_ATOMICS__ == 1
#error "No atomics for you!"
#endif

uint64_t counter = 0;
/* _Atomic uint64_t counter = 0; */

int thread_fn(void *lock) {
  mtx_lock(lock);
  for (uint64_t i = 0; i < 100000000L; ++i) {
    counter += i;
  }
  mtx_unlock(lock);

  return 21;
}

int main(int argc, char *argv[]) {
  thrd_t thread1, thread2;
  mtx_t lock;
  mtx_init(&lock, mtx_plain);

  thrd_create(&thread1, thread_fn, &lock);
  thrd_create(&thread2, thread_fn, &lock);

  int thread1_val;
  int thread2_val;

  thrd_join(thread1, &thread1_val);
  thrd_join(thread2, &thread2_val);

  mtx_destroy(&lock);

  printf("counter: %zu\n", counter);
  printf("the answer is: %d\n", thread1_val + thread2_val);

  return 0;
}
