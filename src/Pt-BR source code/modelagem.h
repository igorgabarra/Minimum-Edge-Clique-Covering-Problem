#ifndef modelagem_h
#define modelagem_h

#include <vector>
#include <list>
#include <set>

using namespace std;

class Grafo{
	vector<list<int>> listaAdjacencia;
	vector<bool> listaAdjacencia_marcacao;
	set<vector<int>> clique;
	int quantidadeVertices = 0;

public:
	Grafo(int);
	~Grafo();

	void insereVertice(int, int);
	void mostraGrafo();
	void mostraCliques();
	void inicializacao_BronKerbosch();
	void bronKerbosch(vector<int>, vector<int>, vector<int>);
	bool verifica_TodosVerticesMarcados(vector<int>);
	void marcaVertices(vector<int>);
	void ordena();
};

#endif