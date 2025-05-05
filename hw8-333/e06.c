#include<stdio.h>
#include <unistd.h>
#include<signal.h>

void handle_sigint(int sig)

{

printf("Caught signal %d\n", sig);

}

int main()

{

int flag = 5;

signal(SIGINT, handle_sigint);

while(flag){

flag--;

sleep(10);

}

return 0;

}
