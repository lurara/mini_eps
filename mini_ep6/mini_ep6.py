# O que preciso fazer: checo o número de rodadas, esse será o número de threads 
# checo o nome do path que vou ter que chamar
# crio vetores de 100 espaços, cada um com a variável identificada por sua posição
# chamo o Fisher Yates (os vetores estão embaralhados)
# chamo cada thread para o sleepsort
# fim

import threading
import random
import subprocess
import queue
from subprocess import PIPE

def thread_function(rand, path, q, times):

    for i in range(0, times):
        random.shuffle(rand)
            
        # Transforma itens da lista em string e depois em lista...
        output = [str(x) for x in rand]
        output.insert(0, path)

        # Envia
        result = subprocess.run(output, stdout=PIPE)

        # Transforma seq. de bytes em lista de string
        str_b = (result.stdout).decode('ascii')
        inputs = list(map(str, str_b.split()))
        ideal = [str(x) for x in list(range(1, 101))]

        # Retorna
        if(inputs == ideal):
            q.put(True)
            #print("Funcionou!\n")
        else:
            q.put(False)
            #print("Não funcionou!\n")


def main():
    path = input("Digite o path: ")
    N = int(input("Digite o N: "))

    rand_list = list()
    ok = 0
    times = 1
    q = queue.Queue()
    times_list = list()

    # Número de threads...
    if(N > 80):
        times = N//80
        resto = N%80
        rng = 80
    else:
        rng = N
        times = N

    # Aleatorização
    random.seed()
    
    for index in range(rng):
        rand = list(range(1, 101))
        random.shuffle(rand)
        rand_list.append(rand)

        if(rng == 80):
            if(index < N%80):
                times_list.append( times + 1 )
            else:
                times_list.append( times )
        else:
            times_list.append(1)


    # Criação de threads
    threads = list()
    for index in range(rng):
        x = threading.Thread(target=thread_function, args=(rand_list[index], path, q, times_list[index]))
        threads.append(x)
        x.start()
    
    # Join
    for index, thread in enumerate(threads):
        thread.join()

    while not q.empty():
        if(q.get() == True):
            ok = ok + 1
    
    if ok >= N*(0.9):
        #print(ok," de ", N*(0.9))
        print("Ok!")
    else:
        #print(ok," de ", N*(0.9))
        print("NOT Ok!")

    
    
    
main()

#ref: https://realpython.com/intro-to-python-threading/#starting-a-thread