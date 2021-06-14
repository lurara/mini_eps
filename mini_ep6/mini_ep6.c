/* OBJETIVO: buscar menor delay tal que o programa gerado passe no verificador para N = 200 
 * dica: iniciar com número de testes menor (p.ex. 20), e delay de 100ms;
 * Nome: Lara Ayumi Nagamatsu 
 * NUSP: 9910568
 * 
 */
#include <stdio.h>  // printf(), ...
#include <stdlib.h> // system(), atoi()
#include <string.h> // strlen(), strtok()
#include <time.h>   // time() ...
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h> // tornar o programa paralelizável

#define BUFSIZE 5000

/* protótipos*/
void fyates(int array[100]);

typedef struct t {
	char * path;
    int ok;
} t_struct;

void * thread(void * str_a) {
	int count = 0;
    int random[100];
	t_struct * str_thread = str_a;
    char * full_path = malloc(strlen(str_thread->path));
    char * str;
    FILE * f;
    char line[BUFSIZE];

	//for(int j = str_thread->start; j < (str_thread->end); j++)
	//	if(advance(str_thread->st, str_thread->data[j], str_thread->data[j+1])) {
	//		count++;
	//	}

    strcpy(full_path, str_thread->path);

    //printf("%s\n", full_path);

    /* aleatorização */
    /*
    fyates(random);
    int len, q = 0;
    
    for(int i = 0; i < 100; i++) {
        strcat(str_thread->path, " ");
        len = snprintf(NULL, 0, "%d", random[i]);
        str = malloc(len + 1);
        snprintf(str, len + 1, "%d", random[i]);
        printf("%s, %d\n", str, q);
        strcat(str_thread->path, str);
        q++;
    }

    printf("%d: %s of size %d\n", pthread_self(), str_thread->path, strlen(str_thread->path));
    */
    /* executável */
    f = popen(str_thread->path, "r");

    while(fgets(line, BUFSIZE, f) != NULL)
        printf("%s\n", line);
    int err;

    //if((err = pclose(f)) != 0)
    //    printf("%d algo errado?\n", err);
    printf("blah\n");

    /* destrinchar buffer */
    int atual, i = 1;
    str = strtok(line, " ");

    while(str != NULL && str_thread->ok) {
        atual = atoi(str);

        if(i < 101 && i != atual) {
            printf("Not OK!!!\n");
            str_thread->ok = 0;
        }

        str = strtok(NULL, " ");
        i++;
    }

    printf("ue\n");
	
	//str_thread->count = count;
	pthread_exit(NULL);
}

/* recebe o caminho do executável e um número N, indicativo de quantas vezes o teste deve ser feito */
int main(int argc, char ** argv) {

    /* checagem de parâmetros passados */
    if(argc <= 2) {
        fprintf(stderr, "O comando precisa de mais argumentos!\n");
        exit(EXIT_FAILURE);
    }

    /* variáveis */
    int N;
    int ok;
    int itr;
    int percent;
    int random[100];
    char line[BUFSIZE];
    char * aux;
    pthread_t * tid;
	t_struct * str;
    //char * full_path;
    char * path;
    //char * str;
    //FILE *f;

    /* inicialização */
    path = argv[1];
    N = atoi(argv[2]);
    itr = 1;
    percent = 0;
    ok = 1;
    //full_path = malloc(strlen(path));
    tid = malloc(sizeof(pthread_t)*N);
	str = malloc(sizeof(t_struct)*N);
    srand((unsigned)time(NULL));

    for(int i = 0; i < 100; i++)
        random[i] = i + 1;

	for(int i = 0; i < N; i++) {
        str[i].ok = 1;
        str[i].path = malloc(strlen(path));
        strcpy(str[i].path, path);

        fyates(random);

        printf("%s \n", str[i].path);
        for(int n = 0; n < 100; n++)
            printf("%d ", random[n]);
        printf("\n");

        int len, q = 0;
        
        for(int j = 0; j < 100; j++) {
            strcat(str[i].path, " ");
            len = snprintf(NULL, 0, "%d", random[j]);
            aux = malloc(len + 1);
            snprintf(aux, len + 1, "%d", random[j]);
            printf("%s, %d\n", aux, q);
            strcat(str[i].path, aux);
            q++;
        }

        printf("END\n");
        //printf("%s of size %d\n", str[i].path, strlen(str[i].path));

        //printf("%d é o num\n", str[i].num);
    }

    for(int i = 0; i < N; i++)
        printf("%s of size %d\n", str[i].path, strlen(str[i].path));
	//separa as threads para rodarem nos len/n intervalos
	//for(int i = 0; i < N; i++)
	//	pthread_create(&tid[i], NULL, thread, (void *) &str[i]);

    /*
    for(int i = 0; i < 100; i++)
        random[i] = i + 1;

    while(itr <= N) {

        strcpy(full_path, path);

        // aleatorização 
        fyates(random);

        for(int i = 0; i < 100; i++) {
            strcat(full_path, " ");
            int len = snprintf(NULL, 0, "%d", random[i]);
            str = malloc(len + 1);
            snprintf(str, len + 1, "%d", random[i]);
            strcat(full_path, str);
        }
        
        // executável
        f = popen(full_path, "r");

        while(fgets(line, BUFSIZE, f) != NULL)
            printf("%s\n", line);
        
        // destrinchar buffer 
        int atual, i = 1;
        str = strtok(line, " ");

        while(str != NULL && ok) {
            atual = atoi(str);

            if(i < 101 && i != atual) {
                printf("Not OK!!!\n");
                ok = 0;
            }

            str = strtok(NULL, " ");
            i++;
        }

        if(ok)
            percent++;

        itr++;
    }*/

    for(int i = 0; i < N; i++) {
		pthread_join(tid[i], NULL);
	}
	
	for(int i = 0; i < N; i++) 
		percent += str[i].ok;

    printf("Percent: %d of %d\n", percent, N);

    if(percent < N*(0.9))
        printf("Not OK!\n");
    else
        printf("OK!\n");

    // liberando memória
    //free(str);
    //free(full_path);
 
    return 0;
}

/* senão, resposta Not OK */
void fyates(int array[100]) {
    
    //for(int i = 0; i < 100; i++)
    //    array[i] = i + 1;

    int aux, j;

    for(int i = 99; i >= 0; i--) {
        j = rand()%100;

        aux = array[j];
        array[j] = array[i];
        array[i] = aux;

    }
}