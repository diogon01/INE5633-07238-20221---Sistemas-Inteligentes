// Programa para imprimir o caminho do nó raiz para o nó de destino
// para algoritmo de quebra-cabeça N*N -1 usando Custo Uniforme
// A solução assume que a instância do quebra-cabeça é solucionável
#include <bits/stdc++.h>
using namespace std;
#define N 3

// Estrutura do Nodo
struct Nodo
{
	// stores the parent Nodo of the current Nodo
	// helps in tracing path when the answer is found
	Nodo* pai;

	// Define a matriz de posições do tabuleiro
	int matriz[N][N];

	// Aloca as coordenadas do tabuleiro
	int x, y;

	// Aloca o custo de cada movimento
	int custo;

	// Aloca o nível da arvóre de busca
	int nivel;
};

// Objeto de comparação a ser usado para ordenar
struct comparacao
{
	bool operator()(const Nodo* lhs, const Nodo* rhs) const
	{
		return (lhs->custo + lhs->nivel) > (rhs->custo + rhs->nivel);
	}
};

// Função que imprime o tabuleiro (Matriz)
int imprimirTabuleiro(int matriz[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%d ", matriz[i][j]);
		printf("\n");
	}
}

// Função para adicionar um novo Nodo
Nodo* novoNodo(int matriz[N][N], int x, int y, int novoX,
			int novoY, int nivel, Nodo* pai)
{
	// Aloca em memória um novo Nodo (ponteiro)
    Nodo* nodo = new Nodo;
	// Define o Nodo pai da arvóre de busca
	nodo->pai = pai;
	// Aloca na memória dados do Nodo pai para o Nodo atual
	memcpy(nodo->matriz, matriz, sizeof nodo->matriz);
	// Move a peça uma posição
	swap(nodo->matriz[x][y], nodo->matriz[novoX][novoY]);
	// Define o número de peças mal alocadas
	nodo->custo = INT_MAX;
	// Define o número de movimentos até agora (nível da arvóre de busca)
	nodo->nivel = nivel;
	// Define as coordenadas X do novo Nodo
	nodo->x = novoX;
    // Define as coordenadas Y do novo Nodo
	nodo->y = novoY;
    // Retorna o novo Nodo a ser visitado
	return nodo;
}

// Define as coordenadas do tabuleiro
// baixo, esquerda, cima, direita
int linha[] = { 1, 0, -1, 0 };
int coluna[] = { 0, -1, 0, 1 };

// Função para calcular o custo de peças mal colocadas
// Número de peças diferente de 0 fora de sua posição final
int calcularCusto(int inicial[N][N], int final[N][N])
{
	int contador = 0;
	for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
		if (inicial[i][j] && inicial[i][j] != final[i][j])
		contador++;
	return contador;
}

// Função para verificar se (x, y) é uma coordenada de matriz válida
int eValido(int x, int y)
{
	return (x >= 0 && x < N && y >= 0 && y < N);
}

// Imprime o Nodo raiz para o Nodo de destino
void imprimirCaminho(Nodo* raiz)
{
	if (raiz == NULL)
		return;
	imprimirCaminho(raiz->pai);
	imprimirTabuleiro(raiz->matriz);

	printf("\n");
}

// Função para resolver algoritmo de N*N - 1 quebra-cabeça usando  
// Branch and Bound. x e y são coordenadas de blocos em branco
// em estado inicial
void resolve(int inicial[N][N], int x, int y,
		int final[N][N])
{
	// Cria uma fila de prioridade para armazenar Nodos
	// na arvóre de busca;
	priority_queue<Nodo*, std::vector<Nodo*>, comparacao> pq;
	// Cria um Nodo raiz
	Nodo* raiz = novoNodo(inicial, x, y, x, y, 0, NULL);
    // Calcula o custo do novo Nodo
	raiz->custo = calcularCusto(inicial, final);
	// Adiciona o nodo Raiz à lista de Nodos ativos;
	pq.push(raiz);
	// Encontra um Nodo não visitado com menor custo,
	// adiciona seus filhos à lista de Nodos visitados
	// e finalmente o exclui da lista.
	while (!pq.empty())
	{
		// Encontra um Nodo ao vivo com o menor custo estimado
		Nodo* minimo = pq.top();
		// O Nodo encontrado é excluído da lista de nodos ativos 
		pq.pop();
		// Verifica se Nodo tem custo 0
		if (minimo->custo == 0)
		{
			// Imprime o caminho do nodo Raiz ao destino;
			imprimirCaminho(minimo);
			return;
		}
		// Máximo de 3 filhos para cada Nodo (verificar melhor)
		for (int i = 0; i < 4; i++)
		{
			if (eValido(minimo->x + linha[i], minimo->y + coluna[i]))
			{
				// Cria um Nodo filho e calcula seu custo 
				Nodo* _nodo_filho = novoNodo(minimo->matriz, minimo->x,
							minimo->y, minimo->x + linha[i],
							minimo->y + coluna[i],
							minimo->nivel + 1, minimo);
				_nodo_filho->custo = calcularCusto(_nodo_filho->matriz, final);

				// Adicionar filho à lista de Nodos ativos
				pq.push(_nodo_filho);
			}
		}
	}
}

// Código inicial
int main()
{
	// Estado inicial
	int inicial[N][N] =
	{
		{1, 3, 4},
		{8,6,2},
		{7,0,5}
	};

	// Estado Final (solução)
	int final[N][N] =
	{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 0}
	};

	// Blank tile coordinates in initial
	// configuration
	int x = 1, y = 2;

	resolve(inicial, x, y, final);

	return 0;
}
