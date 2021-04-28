# Mini EP1 - Linguagem lenta
# Nome: Lara Ayumi Nagamatsu
# NUSP: 9910568
# como rodar: 
#   digite no terminal:
#   1.1 python3 mini_ep1.py
#   obs: caso queira medir o tempo, rode no terminal:
#   1.2 time python3 mini_ep1.py


def main():
    N = 1 << int(input("Digite o N: "))
    primos = 0
    primosEspeciais = 0
    crivo = [None] * (N+1)

    for i in range(2, N):
        crivo[i] = True

    for i in range(2, N):
        if crivo[i] == True:
            primos = primos + 1
            
            if i%4 != 3:
                primosEspeciais = primosEspeciais +1
            
            for j in range(i*2, N, i):
                crivo[j] = False

    print("Primos: ", primos, "\nPrimos especiais: ", primosEspeciais)


main()