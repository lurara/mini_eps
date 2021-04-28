/* Mini EP1 - Linguagem Rápida
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

int main() {
    int N;
    printf("Insira o N: ");
    scanf("%d", &N);
    N = 1 << N;       // operação de bitshift

    int primos = 0;
    int primosEspeciais = 0;
    int *crivo = malloc((N+1)*sizeof(int)); // cria lista de booleanos com n+1 elementos

    for(int i = 2; i <= N; i++) {
        crivo[i] = 1;
    }

    for(int i = 2; i <= N; i++) {
        if(crivo[i] == 1) {
            //printf("%d ", i);
            primos++;
            
            if(i%4 != 3)
                primosEspeciais++;
            
            for(int j = i*2; j <= N; j = j+i)
                crivo[j] = 0;
        }
    }

    printf("Primos: %d\nPrimos especiais: %d\n", primos, primosEspeciais);
    
    free(crivo);  // libera memória alocada

    return 0;
}