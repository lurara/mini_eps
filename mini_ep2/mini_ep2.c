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

 //reduzir o tamanho do vetor pela metade pulando os números pares, isso permite criar um vetor com a metade do tamanho
 //usar bits para guardar os Booleanos. A ideia é que você use uma estrutura baseada em bit arrays para reduzir mais ainda o tamanhodo vetor

#include <stdio.h>  //printf, scanf
#include <stdlib.h> //malloc, free

int main() {
    int N;
    printf("Insira o N: ");
    scanf("%d", &N);
    N = 1 << N;       // operação de bitshift

    int primos = 0;
    int primosEspeciais = 0;
    int *crivo = malloc((N/2)*sizeof(int));
    int actual = 0;

    for(int i = 0; i <= N/2; i++) {
        crivo[i] = 1;
    }

    // contabilizando 2:
    primos++;
    primosEspeciais++;

    // i representa o número de vdd
    for(int i = 1; i < N/2; i++) {
        if(crivo[i] == 1) {
            primos++;
            actual = (i*2)+1;
            //printf("%d ", actual);
            
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