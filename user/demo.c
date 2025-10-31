#include "user.h"

int main(void) {
    int i;
    for(i = 0; i < 10; i++){
        int pid = fork();
        if(pid == 0){
            // proceso hijo
            settickets(50 * (i + 1)); // tickets distintos
            int j;
            for(j = 0; j < 20; j++){
                // simular carga
                int k;
                for(k = 0; k < 1000000; k++) ;
            }
            printf("Proceso %d con %d tickets terminó\n", getpid(), 50 * (i + 1));
            exit(0);
        }
    }

    // padre espera a todos
    for(i = 0; i < 10; i++)
        wait(0);

    return 0;
}
