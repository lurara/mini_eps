/* Mini EP2 - Linguagem Rápida
 * Nome: Lara Ayumi Nagamatsu
 * NUSP: 9910568
 * como compilar:  
 *   digite no terminal:
 *   1.  make mini_rapido
 *   isso gerará o executável "mini", rode no terminal:
 *   2.1  ./mini
 *   obs: caso queira testar o tempo, rode no terminal:
 *   2.2  time ./mini
 */


#include <stdio.h>  //printf, scanf
#include <stdlib.h> //malloc, free

// implementado: contabilização apenas de ímpares

int main() {
    int N;
    printf("Insira o N: ");
    scanf("%d", &N);
    N = 1 << N;       // operação de bitshift

    // contabilizando 2:
    int primos = 1;
    int primosEspeciais = 1;
    int crivoSize = (N/32)/2;
    if(N%32) // se for != 0
        crivoSize++;

    int *crivo = malloc((N/2)*sizeof(int));
    int actual = 0;

    for(int i = 0; i <= N/2; i++) {
        crivo[i] = 1;
    }

    // i representa o número de vdd
    for(int i = 1; i < N/2; i++) {
        if(crivo[i] == 1) {
            primos++;
            actual = (i*2)+1;
            
            if((actual)%4 != 3)
                primosEspeciais++;
            
            for(int j = actual*3; j < N; j = j + 2*actual)
                crivo[j/2] = 0;
        }
    }

    printf("Primos: %d\nPrimos especiais: %d\n", primos, primosEspeciais);
    
    free(crivo);  // libera memória alocada

    return 0;
}
