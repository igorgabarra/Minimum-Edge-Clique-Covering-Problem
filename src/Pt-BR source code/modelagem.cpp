#include <iostream>
#include <list>
#include <set>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>

#include "modelagem.h"

using namespace std;

Vertice::Vertice(int destino){
	adjacente = destino;
}

Vertice::~Vertice(){}

// ------------------------------------------------------------------------------

Grafo::Grafo(int tamanho){
	quantidadeVertices = tamanho;
	listaAdjacencia.resize(tamanho);
}

Grafo::~Grafo(){}

void Grafo::insereVertice(int verticeOrigem, int verticeDestino){
	// Adiciona verticeDestino como adjacente a verticeOrigem
	listaAdjacencia[verticeOrigem] .push_back(new Vertice(verticeDestino));
	// Adiciona verticeOrigem como adjacente a verticeDestino
	listaAdjacencia[verticeDestino].push_back(new Vertice(verticeOrigem ));
}

void Grafo::mostraGrafo(){
	for(int i=0; i<quantidadeVertices; i++){
		// Para cada vertice do grafo, mostra lista de seus adjacentes
		for(auto it : listaAdjacencia[i])
			cout << it->adjacente << " "

		cout << endl;
	}
	cout << endl;
}

void Grafo::mostraClique(){
	cout << " Numero de cliques encontrados no grafo: " << clique.size() << endl;
}

void Grafo::inicializacao_BronKerbosch(){
	vector<Vertice*> cliqueAtual, semPossibilidade, possiveis;

	cout << " Procurando" << endl;

	for(vector<Vertice*>::size_type i=0; i<listaAdjacencia.size(); i++)
		listaAdjacencia.push_back(new Vertice(i));

	// Execucao do algoritmo proposto por Bron Kerbosch
	bronKerbosch(cliqueAtual, possiveis, semPossibilidade);
}

void Grafo::bronKerbosch(vector<Vertice*> cliqueAtual, vector<Vertice*> possiveis, vector<Vertice*> semPossibilidade){
	// Se conjunto de vertices possiveis e semPossibilidade estiverem vazios, entao encontrou clique maximal
	if(possiveis.empty() && semPossibilidade.empty())
		// Se pelo menos um vertice nao estiver marcado, significa que encontrou clique novo
		if(!verifica_TodosVerticesMarcados(cliqueAtual)){
			// Marca todos os vertices do clique atual
			clique.insert(marcaVertices(cliqueAtual));
		}

	else{ // Caso contrario
		for(vector<Vertice*>::size_type vertice = 0; vertice<possiveis.size(); vertice++){
			// Criacao novos conjuntos de vertices possiveis e semPossibilidade
			vector<Vertice*> novoPossiveis, novoSemPossibilidade;
			novoPossiveis.clear();
			novoSemPossibilidade.clear();

			// Para cada vertice disponivel no conjunto de possiveis
			for(auto verticeAdjacente : listaAdjacencia[possiveis[vertice]]]){

			}
		}



	}
}
