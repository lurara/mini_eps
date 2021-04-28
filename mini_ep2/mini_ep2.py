# Mini EP2 - Linguagem lenta
# Nome: Lara Ayumi Nagamatsu
# NUSP: 9910568
# como rodar: 
#   digite no terminal:
#   1.1 python3 mini_ep2.py
#   obs: caso queira medir o tempo, rode no terminal:
#   1.2 time python3 mini_ep2.py

# implementados: contabilização apenas de ímpares

import numpy as np

def main():
    N = 1 << int(input("Digite o N: "))
    primos = 0
    primosEspeciais = 0
    crivo = [None] * (N//2)

    for i in range(0, N//2):
        crivo[i] = True

    primos = primos + 1
    primosEspeciais = primosEspeciais + 1

    for i in range(1, (N//2)):
        if crivo[i] == True:
            primos = primos + 1
            actual = (i*2) + 1
            
            if (actual)%4 != 3:
                primosEspeciais = primosEspeciais +1

                #retirar o primeiro? começar a contar do 1

            # quero pegar todos os indices multiplos de actual e impares para
            # depois tornar False esses indices
            #aux = np.arange(1, N+1)
            #aux2 = np.remainder(aux, 2)       # pegar indices impares, i.e. aux%2 != 0
            #aux3 = np.remainder(aux, actual)  # pegar indices multiplos de actual i.e. aux%actual == 0
            #new = np.where(np.logical_and((aux2 != 0), (aux3 == 0)))[0]
            #newList = [x//2 for x in new]
            #del newList[0]
            #newList = np.asarray(newList)

            #for x in newList:
            #    crivo[x] = False

            #print("\n\ncrivo: \n", crivo)
            for j in range(actual*3, N, 2*actual):
                crivo[j//2] = False

    print("Primos: ", primos, "\nPrimos especiais: ", primosEspeciais)

main()