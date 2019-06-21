#ifndef modelagem_h
#define modelagem_h

#include <vector>
#include <list>

using namespace std;

class Vertice{
public:
	//Vertice adjacente;
	int adjacente; // Vertice eh adjacente a qual outro
	bool foiMarcado; // Vertice ja foi marcado no clique?

	Vertice(int, bool=false);
	~Vertice();
};

class Grafo{
	vector<list<Vertice*>> listaAdjacencia;
	set<vector<Vertice*>> clique;
	int quantidadeVertices = 0;

public:
	Grafo(int);
	~Grafo();

	void insereVertice(int, int);
	void mostraGrafo();
	void mostraClique();
	void inicializacao_BronKerbosch();
	void bronKerbosch(vector<Vertice*>, vector<Vertice*>, vector<Vertice*>);
	void ordena();
};

#endif