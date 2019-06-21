#include <iostream>
#include <list>
#include <set>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>

#include "modelagem.h"

using std::list;
using std::vector;
using std::set;

using namespace std;

// ------------------------------------------------------------------------------

Grafo::Grafo(int tamanho){
	quantidadeVertices = tamanho;
	listaAdjacencia.resize(tamanho);
	listaAdjacencia_marcacao.resize(tamanho);

	// Nenhum vertice eh inicialmente marcado
	for(unsigned int i=0; i<listaAdjacencia_marcacao.size(); i++)
		listaAdjacencia_marcacao[i] = false;
}

Grafo::~Grafo(){}

void Grafo::insereVertice(int verticeOrigem, int verticeDestino){
	// Adiciona verticeDestino como adjacente a verticeOrigem
	listaAdjacencia[verticeOrigem] .push_back(verticeDestino);
	// Adiciona verticeOrigem como adjacente a verticeDestino
	listaAdjacencia[verticeDestino].push_back(verticeOrigem);
}

void Grafo::mostraGrafo(){
	for(int i=0; i<quantidadeVertices; i++){
		// Para cada vertice do grafo, mostra lista de seus adjacentes
		for(auto it : listaAdjacencia[i])
			cout << it << " ";

		cout << endl;
	}
	cout << endl;
}

void Grafo::mostraCliques(){
	cout << " Numero de cliques encontrados no grafo: " << clique.size() << endl;
}

void Grafo::inicializacao_BronKerbosch(){
	vector<int> cliqueAtual, semPossibilidade, possiveis;

	cout << " Procurando" << endl;

	for(vector<int>::size_type i=0; i<listaAdjacencia.size(); i++)
		possiveis.push_back(i);

	// Execucao do algoritmo proposto por Bron Kerbosch
	bronKerbosch(cliqueAtual, possiveis, semPossibilidade);
}

void Grafo::bronKerbosch(vector<int> cliqueAtual, vector<int> possiveis, vector<int> semPossibilidade){
	// Se conjunto de vertices possiveis e semPossibilidade estiverem vazios, entao encontrou clique maximal
	if(possiveis.empty() && semPossibilidade.empty()){
		// Se pelo menos um vertice nao estiver marcado, significa que encontrou clique novo
		if(!verifica_TodosVerticesMarcados(cliqueAtual)){
			// Marca todos os vertices do clique atual
			clique.insert(cliqueAtual);
			marcaVertices(cliqueAtual);
		}
	}

	else{ // Caso contrario
		for(unsigned int vertice = 0; vertice<possiveis.size(); vertice++){
			// Criacao novos conjuntos de vertices possiveis e semPossibilidade
			vector<int> novoPossiveis, novoSemPossibilidade;
			novoPossiveis.clear();
			novoSemPossibilidade.clear();

			// Para cada vertice disponivel no conjunto de possiveis
			for(auto verticeAdjacente : listaAdjacencia[ possiveis[vertice] ]){
				for(unsigned int contador=0; contador<possiveis.size(); contador++)
					// Se vertice adjacente estiver presente no conjunto de vertices possiveis, entao eh adicionado ao novoPossiveis
					if(verticeAdjacente == possiveis[contador])
						novoPossiveis.push_back(possiveis[contador]);

				for(unsigned int contador=0; contador<semPossibilidade.size(); contador++)
					if(verticeAdjacente == semPossibilidade[contador])
						novoSemPossibilidade.push_back(semPossibilidade[contador]);
			}

			// Adiciona vertice ao conjunto de possivel novo clique
			cliqueAtual.push_back(possiveis[vertice]);

			// Chamada recursiva com adicao de novo vertice no clique atual
			bronKerbosch(cliqueAtual, novoPossiveis, novoSemPossibilidade);

			// Adiciona o vertice como sem possibilidade
			semPossibilidade.push_back(possiveis[vertice]);

			// Remove todos os vertices adicionados para tentativa de encontrar clique maximal
			cliqueAtual.erase(remove(cliqueAtual.begin(), cliqueAtual.end(), possiveis[vertice]), cliqueAtual.end());

			// Remove todos os vertices adicionados para tentativa de encontrar clique maximal
			possiveis.erase(remove(possiveis.begin(), possiveis.end(), possiveis[vertice]), possiveis.end());

			vertice--;
		}
	}
}

bool Grafo::verifica_TodosVerticesMarcados(vector<int> cliqueAtual){
	for(unsigned int i=0; i<listaAdjacencia_marcacao.size(); i++)
		// Se possuir ao menos um vertice nao marcado, clique atual possui vertice nao marcado
		if(listaAdjacencia_marcacao[i] == false)
			return false;

	// Se todos estiverem marcados, retorna que ja existe clique em todos os vertices
	return true;
}

void Grafo::marcaVertices(vector<int> cliqueAtual){
	for(unsigned int i=0; i<cliqueAtual.size(); i++)
		listaAdjacencia_marcacao[ cliqueAtual[i] ] = true;
}