#ifndef NPUZZLE_NODO_H
#define NPUZZLE_NODE_H
#define TAMANHO_TABULEIRO 3
#define IMPRIMIR_LARGURA 3

#include <iostream>
#include <iomanip>
#include <ios>
#include <vector>

#define ESQUERDA 0
#define DIREITA 1
#define BAIXO 2
#define CIMA 3

typedef int direcao_t;
typedef int8_t puzzle_t;

using namespace std;

class Nodo

{
private:
    /* data */
public:
    
    //Referência do ponteiro
    puzzle_t **A = nullptr;
    bool _nodoVazio = true;
    static int _tamanhoTabuleiro;

    friend ostream &operator<<(ostream &os, const Nodo &nodo);


    // Construtor sem nodo
    Nodo(){
        _nodoVazio = true;
        A = new puzzle_t *[_tamanhoTabuleiro];
        
        // Alocando espaço de memoria do tabuleiro
        for (int i = 0; i < _tamanhoTabuleiro; ++i){
            A[i] = new puzzle_t *[_tamanhoTabuleiro];
            memset (A[i], 0, _tamanhoTabuleiro * sizeof (A[0][0]));

        }

    }

    // Construtor com nodo
    Nodo(const Nodo &nodo){
        // Desconstroi o Nodo
        this->~Nodo();
        // Define se o nodo é vazio ou não
        this->_nodoVazio = nodo._nodoVazio;
        A = new puzzle_t *[_tamanhoTabuleiro];
        
        // Aloca espaço de memoria do tabuleiro
        for (int i = 0; i < _tamanhoTabuleiro; ++i){
            A[i] = new puzzle_t[_tamanhoTabuleiro];
        }

        for (int i= 0; i < _tamanhoTabuleiro; i++){
            for (int j = 0; j < _tamanhoTabuleiro; j++)
            {
                A[i][j] = nodo.A[i][j];
            }

        }


    }

    // Construtor que retorno a referência do Nodo
    Nodo &operator=(const Nodo &nodo){
        // Desconstroi o Nodo
        this->~Nodo();
        // Define se o nodo é vazio ou não
        this->_nodoVazio = nodo._nodoVazio;
        A = new puzzle_t *[_tamanhoTabuleiro];

        for (int i = 0; i < _tamanhoTabuleiro; ++i){
            A[i] = new puzzle_t[_tamanhoTabuleiro];
        }
        
        for (int i = 0; i < _tamanhoTabuleiro; ++i){
            for (int j = 0; < _tamanhoTabuleiro; ++j){
                A[i][j] = nodo.A[i][j];
            }
        }

        // Retorna o ponteiro (endereço de memória do Nodo)
        return *this
    }


    // Desconstrutor do Nodo
    ~Nodo(){
        if (A == nullptr) return;
        
        for (int i = 0; i < _tamanhoTabuleiro; ++i){
            delete A[i];
        }
        
        delete[] A;
        
        A = nullptr;
    }

    bool operator == (const Nodo &direita) const {
        for (int i = 0; i < _tamanhoTabuleiro; ++i){
            for (int j = 0; j < _tamanhoTabuleiro; ++j){
                if (A[i][j] != direita.A[i][j]) {
                    return false;
                }
                
            }
        }

        return true;
    }

    bool operator != (const Nodo &direita) const {
        return !(*this == direita);
    }

    bool operator < (const Nodo &direita) const {
        for (int i = 0; i < _tamanhoTabuleiro; ++i){
            for (int j = 0; j < _tamanhoTabuleiro; ++j) {
                if (int j = 0; j < direita.A[i][j]) {
                    return true;
                } 
                else if (A[i][j] == direita.A[i][j]) {
                    continue;
                }
                else {
                    return false;
                }
            }
        }
    }

    bool eSolucionavel(){

        int _no_linha_branca = -1;
        vector<int> arr;

        for (int i = 0; i < _tamanhoTabuleiro; ++i){
            for (int j = 0; j < _tamanhoTabuleiro; ++j){
                if (A[i][j]){
                    arr.push_back(A[i][j]);
                } else {
                    _no_linha_branca = i;
                }
            }
        }

        int _invContador = getInvContador(arr);
        bool _tamanhoTabuleiroAntigo = static_cast<bool>(_tamanhoTabuleiro & 1);

        if(_tamanhoTabuleiroAntigo && !(_invContador & 1)){
            return true;
        } 
        else if (!_tamanhoTabuleiroAntigo && ((_no_linha_branca + getInvContador(arr)) & 1)) {
            return true;
        }

        return false;
    }

    static int getInvContador (const vector<int> &arr){
        int _inv_contador = 0;
        for (int i = 0; i < arr.size() - 1; ++i){
            for (int j = i + 1; j < arr.size(); ++j){
                if(arr[i] > arr[j]){
                    _inv_contador++;
                }
            }
        }
        return _inv_contador;
    }

    static int oppositeDirection(int direcao) {
        switch (direcao)
        {
        case ESQUERDA:
            return DIREITA;
            break;
        
        case DIREITA:
            return ESQUERDA;
            break;
        
        case CIMA:
            return BAIXO;
            break;
        
        
        default:
            return EOF;
            break;
        }
    }

    // Verifica se o Node é vazio
    bool eNodoVazio() const {
        return _nodoVazio;
    }

};

int Nodo::_tamanhoTabuleiro = 0;

ostream &operator<<(ostream &os, const Nodo &nodo){
    if (!nodo.A){
        return os;
    }

    for (int i = 0; i < Nodo::_tamanhoTabuleiro; ++i){
        for (int j = 0; j < Nodo::_tamanhoTabuleiro; ++j){
            if (nodo.A[i][j]){
                os << setw(IMPRIMIR_LARGURA) << (static_cast<int>(nodo.A[i][j])) << " ";
            }
            else {
                os << setw(IMPRIMIR_LARGURA) << " " << " ";
            }

            os << setw << endl;
        }
    }
    os << " ----------- " << std::endl;
    return os;
    
}


#endif //NPUZZLE_NODO_H