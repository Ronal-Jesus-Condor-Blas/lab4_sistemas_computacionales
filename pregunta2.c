#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdbool.h>
#include <time.h>

volatile sig_atomic_t mostrar_numeros = 0;

void manejador(int signal) {
    if (signal == SIGALRM) {
        mostrar_numeros = 1;
        alarm(5); // Programa próxima alarma en 5 segundos
    }
}

int main() {
    signal(SIGALRM, manejador);
    alarm(5); // Empieza con 5 segundos de letras
    while (1) {
        if (mostrar_numeros) {
            time_t inicio = time(NULL);
            while (difftime(time(NULL), inicio) < 2) { // Solo durante 2 segundos
                for (int i = 0; i <= 9; ++i) {
                    char digito = i + '0';
                    syscall(SYS_write, 1, &digito, 1);
                    usleep(300000); // tiempo entre cada numero que se muestra
                    // Si pasan los 2 segundos, salen del bucle
                    if (difftime(time(NULL), inicio) >= 2) break;
                }
            }
            mostrar_numeros = 0; // vuele al alfabeto
        } else {
            for (int t = 0; t < 5; t++) { // Bucle de hasta 5 segundos
                for (char c = 'A'; c <= 'Z'; ++c) {
                    syscall(SYS_write, 1, &c, 1); // Imprime letra
                    sleep(1); // 1 seg entre letras
                    if (mostrar_numeros) break;
                }
                if (mostrar_numeros) break;
            }
        }
    }
    return 0;
}
