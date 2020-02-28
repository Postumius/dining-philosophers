#include <pthread.h>
#include <stdlib.h>
#include "util.h"
#include <stdio.h>

typedef struct chopstick {
  int num;
  pthread_mutex_t* lock;
} chopstick;

chopstick min(chopstick x, chopstick y) {
  return (x.num < y.num)? x: y;
}

chopstick max(chopstick x, chopstick y) {
  return (x.num > y.num)? x: y;
}

typedef struct seat {
  int num;
  int is_hungry;
  chopstick left;
  chopstick right;
} seat;

void* philosopher(void* chair) {
  seat* spot = (seat*)chair;
  chopstick min_stick = min(spot->left, spot->right);
  chopstick max_stick = max(spot->left, spot->right);
  
  while(1) {    
    printf("%d is thinking\n", spot->num);
    sleep_ms(500);
    
    pthread_mutex_lock(min_stick.lock);
    pthread_mutex_lock(max_stick.lock);

    spot->is_hungry = 0;
    printf("%d is eating\n", spot->num);
    sleep_ms(500);
    
    pthread_mutex_unlock(max_stick.lock);
    pthread_mutex_unlock(min_stick.lock);    
  }
  return NULL;
}
  

int main() {
  
  pthread_mutex_t sticks[5]; //= malloc(sizeof(pthread_mutex_t*) * 5);
  seat seating[5];
  for(int i=0; i<5; i++) {
    seating[i].num = i;
    
    int left_n = (i+1)%5;
    chopstick left = {left_n, &sticks[left_n]};
    seating[i].left = left;
    
    int right_n = i%5;
    chopstick right = {right_n, &sticks[right_n]};
    seating[i].right = right;
    
    pthread_mutex_init(&sticks[i], NULL);
  }
  
  pthread_t threads[5];
  for(int i=0; i<5; i++) {
    pthread_create(&threads[i], NULL, philosopher, &seating[i]);
  }

  while(1) {
    sleep_ms(10000);
    for(int i=0; i<5; i++) {
      if (seating[i].is_hungry) {
        printf("the guest in seat %d has gone hungry for 10 seconds!\n", i);
        exit(-1);
      } else {
        seating[i].is_hungry = 1;
      }
    }
  }
  return 0;
}
