#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define KEY 51062

union semun{
  int val;
  struct semid_ds * buf;
  unsigned short * array;
  struct seminfo * _buf;
};

int view(){
  int sem_descriptor = semget(KEY, 1, IPC_CREAT | 0600);
  int sem_val = semctl(sem_descriptor, 0, GETVAL);
  return sem_val;
}

int create_set(int N, union semun arg){
  int sem_descriptor = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0600);
  if(sem_descriptor == -1){
    printf("semaphore already exists \n");
  }else{
    printf("semaphore created: %d \n", KEY);
    arg.val = N;
    semctl(sem_descriptor, 0, SETVAL, arg);
    printf("value set to %d \n", view(sem_descriptor));
  }
  return sem_descriptor;
}

int rm(){
  int sem_descriptor = semget(KEY, 1, IPC_CREAT | 0600);
  semctl(sem_descriptor, 0, IPC_RMID);
  printf("semaphore removed \n");
  return 0;
}

int main(int argc, char ** argv){
  if(argc == 2 || argc == 3){
    //char * arg1 = argv[1];
    if(argc == 3 && strcmp(argv[1], "-c") == 0){
      int N;
      sscanf(argv[2], "%d", &N);
      union semun arg;
      int sem_descriptor = create_set(N, arg);
    }else if(strcmp(argv[1], "-v") == 0){
      printf("semaphore value: %d \n", view());
    }else if(strcmp(argv[1], "-r") == 0){
      rm();
    }else{
      printf("there's been an error! \n");
    }
  }else{
    printf("there's been an error! \n");
  }
  return 0;
}
