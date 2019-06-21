#include "modelagem.h" // Algoritmo e modelagem utilizada

#include <chrono> //Time spend
#include <iterator>

#include <cstdio> //FILE, fscanf
#include <vector>

#include <iostream>

using namespace std;
using namespace chrono; //Time spend

int main(int argc, char const* argv[]) {
	FILE* arquivo; //open file

	char caractere;
	char lixeira[10];

	int quantidadeVertices, quantidadeArestas;
	int verticeOrigem, verticeDestino;

	duration<double> time_span2;

	vector<int> todosVertices;

	// Abertura de arquivo
	if((arquivo = fopen(argv[1], "r")) == NULL){
		cout << "Ocorreu algum erro ao abrir o arquivo \"" << argv[1] << "\". Tente novamente." << endl;
		exit(1);
	}

	// Verifica quantidade de vertices e arestas do grafo
	else if(fscanf(arquivo, "%c %[A-z a-z] %d %d '\n'", 
		                    &caractere, lixeira, &quantidadeVertices, &quantidadeArestas)) 
		cout << " V = " << quantidadeVertices 
	      << " - A = " << quantidadeArestas << "." << endl;

	//Em caso de nao conseguir ler o arquivo - conteudo obrigatorio
	else{
		fclose(arquivo);
		exit(1);
	}

	// Criacao e modelagem do grafo
	Grafo grafo(quantidadeVertices);

	// Numero de vezes que vertice do grafo foi mencionado na entrada
	for(auto count = 0; count < quantidadeVertices; count++)
		todosVertices.push_back(0);

	// Indicacao de adjacencia entre verticeOrigem e verticeDestino
	while(fscanf(arquivo, "%c %d %d '\n'", 
		                  &caractere, &verticeOrigem, &verticeDestino) != EOF){
		grafo.insereVertice(verticeOrigem-1, verticeDestino-1);
		// Indica que verticeOrigem foi acionado
		todosVertices[verticeOrigem-1]++;
		// Indica que verticeDestino foi acionado
		todosVertices[verticeDestino-1]++;
	}

	fclose(arquivo);

	grafo.mostraGrafo();

	int maiorCliquePossivel = grafo.descobreMaiorCliquePossivel();
	cout << " Maior clique possivel: " << maiorCliquePossivel << endl;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	// 1- Retira vertices de grau 0
	// 2- Retira vertices de grau 1 e ja adiciona na resposta

	// 3- Calcula clique maximal possivel no grafo?
	grafo.inicializacao_BronKerbosch(maiorCliquePossivel);

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double, std::milli>>(t2 - t1);

	cout << "\n Execution Time " << time_span.count() << " ms " << endl;

	grafo.mostraCliques();	

	return 0;
}