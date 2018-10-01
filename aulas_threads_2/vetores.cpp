#include <iostream>
#include <pthread.h>
#include <cstdlib>
using namespace std;

struct Argumentos {
	int* vetor;
	int posicao;
	int n;
	int tamanho;
	int tid;
};

void* lerValorVetor(void* argumentos) {
	Argumentos* args = (Argumentos*) argumentos;
	// cout << "thread: " << args->tid << endl;
	for(int i = args->posicao; i < args->n; i++) {
		args->vetor[i] = rand() % 100 + 1;
	}
	pthread_exit(NULL);
}


void* multiplicar(void* argumentos) {
	Argumentos* args = (Argumentos*) argumentos;
	// cout << "thread: " << args->tid << endl;
	for(int i = args->posicao; i < args->n; i++) {
		if(i < args->tamanho / 2) {
			args->vetor[i] *= 2;
		} else {
			args->vetor[i] *= 10;
		}
	}
	pthread_exit(NULL);
}

int main() {
	srand(time(0));
 	int tamanho;
 	cout << "Digite o tamanho do vetor: ";
 	cin >> tamanho;
 	int* vetor = new int[tamanho];
 	cout << "Digite o numero de threads: ";
 	int t;
 	cin >> t;
 	pthread_t threads[t];
 	int sobra = tamanho % t;
	int quantidadePorThread = tamanho / t;
	if(sobra > 0) {
		quantidadePorThread++;
	}

	Argumentos argumentosLeitura[t];
	
	argumentosLeitura[0].vetor = vetor;
	argumentosLeitura[0].posicao = 0;
	argumentosLeitura[0].n = quantidadePorThread;
	argumentosLeitura[0].tid = 1;

	for (int i = 0; i < (t - 1); i++) {
		if(sobra > 0) {
			sobra--;
			if(sobra == 0) {
				quantidadePorThread--;
				sobra--;
			}
		}
		
		pthread_create((&threads[i]), NULL, lerValorVetor, (void*) &(argumentosLeitura[i]));

		argumentosLeitura[i + 1].vetor = vetor;
		argumentosLeitura[i + 1].posicao = argumentosLeitura[i].n;
		argumentosLeitura[i + 1].n = argumentosLeitura[i].n + quantidadePorThread;
		argumentosLeitura[i + 1].tid = argumentosLeitura[i].tid + 1;
		
		// cout << i + 1 << "-esima vez" << endl;
	}
 	pthread_create((&threads[t - 1]), NULL, lerValorVetor, (void*) &(argumentosLeitura[t - 1]));
	// cout << t << "-esima vez" << endl;


 	for(int i = 0; i < t; i++) {
 		pthread_join(threads[i], NULL);
 	}
 	cout << "vetor: ";
 	for(int i = 0; i < tamanho; i++) {
 		cout << vetor[i] << " ";
 	}
	cout << endl;
	
	sobra = tamanho % t;
	quantidadePorThread = tamanho / t;

	if(sobra > 0) {
		quantidadePorThread++;
	}

 	Argumentos argumentosMultiplicacao[t];

	argumentosMultiplicacao[0].vetor = vetor;
	argumentosMultiplicacao[0].posicao = 0;
	argumentosMultiplicacao[0].n = quantidadePorThread;
	argumentosMultiplicacao[0].tamanho = tamanho;
	argumentosMultiplicacao[0].tid = 1;

	for(int i = 0; i < (t - 1); i++) {
		if(sobra >= 0) {
			sobra--;
			if(sobra < 0) {
				quantidadePorThread--;
				sobra--;
			}
		}

		pthread_create((&threads[i]), NULL, multiplicar, (void*) &(argumentosMultiplicacao[i]));
		
		argumentosMultiplicacao[i + 1].vetor = vetor;
		argumentosMultiplicacao[i + 1].posicao = argumentosMultiplicacao[i].n;
		argumentosMultiplicacao[i + 1].n = argumentosMultiplicacao[i].n + quantidadePorThread;
		argumentosMultiplicacao[i + 1].tamanho = tamanho;
		argumentosMultiplicacao[i + 1].tid = argumentosMultiplicacao[i].tid + 1;
		// cout << i + 1 << "-esima vez" << endl;
	}
	pthread_create((&threads[t - 1]), NULL, multiplicar, (void*) &(argumentosMultiplicacao[t - 1]));
	// cout << t << "-esima vez" << endl;
	
	for(int i = 0; i < t; i++) {
		pthread_join(threads[i], NULL);
	}

	cout << "multiplicado: ";
 	for(int i = 0; i < tamanho; i++) {
 		cout << vetor[i] << " ";
 	}

 	cout << endl;
 	return 0;
}