#ifndef SG_TREE
#define SG_TREE
#include "No_SG.h"
#include <math.h>

class SG_Tree{
private:
	No_SG *raiz ;
	double Alpha; // Parametro que verifica desbalanceamento
	int qtde ; // Quantidade de itens na arvore

	double logbx(double base, double value){
		return (log(value) / log(base)) ;
	}
	int logH(int h, double alpha) {
		return (int)ceil(logbx((1.0/alpha), h));
	}

	int tam(No_SG *r) {

		if (r == NULL) {
			return 0;
		}

		int t = 1;
		t += tam(r->getEsq());
		t += tam(r->getDir());
		return t;
	}

	void reconstruirArvore(No_SG *scapeGoat){
		return ;
	}

	int inserindo(int v) {
		if (raiz == NULL) {
			raiz = new No_SG(v);
			qtde++;
			return 0;
		}

		No_SG *aux = raiz;
		No_SG *inserido = NULL;
		bool feito = false;
		int h = 0;

		do {
			if (v > aux->getValor()) {
				if (aux->getDir() == NULL) {
					aux->setDir( new No_SG(v) ); // Insere
					inserido = aux->getDir(); // in aponta pro nó inserido
					feito = true;
				}
				else {
					aux = aux->getDir(); // Busca na arvore direita
				}
			}
			else if (v < aux->getValor()) {
				if (aux->getEsq() == NULL) {
					aux->setEsq( new No_SG(v) ); // Insere
					inserido = aux->getEsq(); // in aponta pro nó inserido
					feito = true;
				}
				else {
					aux = aux->getEsq(); // Busca na arvore esquerda
				}
			}
			else {
				return -1; // Já existe
			}
			h++;
		} while(!feito);

		if (h > logH(qtde, Alpha)) {
			std::cout << "Desbalanceada!!\n";
			// Buscar a nova raiz
			while (3 * tam(inserido) <= 2 * tam(inserido->getPai())){
				inserido = inserido->getPai();
			}

			// Reconstruir a nova arvore em relação a nova raiz
			reconstruirArvore(aux->getPai());
		}

		qtde++;
		return h;
	}

	void preOrder(No_SG* no){
		if (no == NULL) return ;
		std::cout << no->getValor() << " " ;
		preOrder(no->getEsq());
		preOrder(no->getDir());
	}
	void posOrder(No_SG* no){
		if (no == NULL) return ;
		posOrder(no->getEsq());
		posOrder(no->getDir());
		std::cout << no->getValor() << " " ;
	}
	void inOrder(No_SG* no){
		if (no == NULL) return ;
		inOrder(no->getEsq());
		std::cout << no->getValor() << " " ;
		inOrder(no->getDir());
	}

	void destruir(No_SG* no){
		if(no == NULL) return ;
		destruir(no->getEsq());
		destruir(no->getDir());
		delete no ;

	}
protected:

public:
	SG_Tree(double A = 2.0/3.0) {
		raiz = NULL;
		Alpha = A;
	}

	~SG_Tree() {
		destruir(raiz);
	}

	bool inserir(int valor) {
		int h = inserindo(valor); // h recebe a altura da inserção de v
		if (h == -1) return false;
		return true;
	}

	void remover(int valor);

	void buscar(int valor);

	void preOrder(){
		preOrder(raiz);
	}

	void posOrder(){
		posOrder(raiz);
	}

	void inOrder(){
		inOrder(raiz);
	}
};

#endif
