# Mini EP2 - Linguagem lenta
# Nome: Lara Ayumi Nagamatsu
# NUSP: 9910568
# como rodar: 
#   digite no terminal:
#   1.1 python3 mini_ep2.py
#   obs: caso queira medir o tempo, rode no terminal:
#   1.2 time python3 mini_ep2.py

# implementado: contabilização apenas de ímpares

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

            #print("\n\ncrivo: \n", crivo)
            for j in range(actual*3, N, 2*actual):
                crivo[j//2] = False

    print("Primos: ", primos, "\nPrimos especiais: ", primosEspeciais)

main()