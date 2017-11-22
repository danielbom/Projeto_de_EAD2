#ifndef SG_TREE
#define SG_TREE
#include "No_SG.h"
#include <math.h>

class SG_Tree{
	private:
		No_SG *raiz;
		double Alpha; // Parametro que verifica desbalanceamento
		int qtde; // Quantidade de itens na arvore

		double logbx(double base, double value){
			return (log(value) / log(base));
		}
		int logH(int h, double alpha) {
			return (int)ceil(logbx((1.0/alpha), h));
		}

		int grandeza(No_SG *no) {
			if (no == NULL)
				return 0;

			return 1 + grandeza(no->getEsq()) + grandeza(no->getDir());
		}

		No_SG* construirArvoreBalanceado(No_SG** vet, int pos, int tam){
			std::cout << "construirArvoreBalanceado\n";
			return NULL;
		}

		int armazenarNoVetor(No_SG* no, No_SG** vet, int pos){
			std::cout << "armazenarNoVetor\n";
			if (no == NULL)
				return pos;

			pos = armazenarNoVetor(no->getEsq(), vet, pos);
			vet[pos++] = no;
			return armazenarNoVetor(no->getDir(), vet, pos);
		}

		int toArray(No_SG *sg, No_SG **aux, int b){
			if (sg == NULL) {
				return b;
			}

			b = toArray(sg->getEsq(), aux, b);
			aux[b++] = sg;
			return toArray(sg->getDir(), aux, b);
		}

		No_SG *construirBalanceado(No_SG **aux, int b, int tam_sg){
			if (tam_sg == 0){
				return NULL;
			}

			int meio = tam_sg / 2;
			aux[b + meio]->setEsq(construirBalanceado(aux, b, meio));

			if (aux[b + meio]->getEsq() != NULL){
				aux[b + meio]->getEsq()->setPai(aux[b + meio]);
			}

			aux[b + meio]->setDir(construirBalanceado(aux, b + meio + 1, tam_sg - meio - 1));\

			if (aux[b + meio]->getDir() != NULL){
				aux[b + meio]->getDir()->setPai(aux[b + meio]);
			}
			return aux[b + meio];
		}

		void reconstruirArvore(No_SG *scapeGoat){
			std::cout << "Reconstruindo Árvore\n";
			int tam_sg = grandeza(scapeGoat);
			std::cout << tam << std::endl;
			No_SG *pai = scapeGoat->getPai();
			No_SG **vetor = new No_SG* [tam_sg];
			toArray(scapeGoat, vetor, 0);

			if (pai == NULL)
			{
				raiz = construirBalanceado(vetor, 0, tam_sg);
				raiz->setPai(NULL);
			}
			else if (pai->getDir() == scapeGoat)
			{
				pai->setDir(construirBalanceado(vetor, 0, tam_sg));
				pai->getDir()->setPai(pai);
			}
			else
			{
				pai->setEsq(construirBalanceado(vetor, 0, tam_sg));
				pai->getEsq()->setPai(pai);
			}
		}

		int inserindo(int v) {
			std::cout << "inserindo\n";
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
						inserido = aux->getDir(); // inserido aponta pro nó inserido
						inserido->setPai(aux);
						feito = true;
					}
					else {
						aux = aux->getDir(); // Busca na arvore direita
					}
				}
				else if (v < aux->getValor()) {
					if (aux->getEsq() == NULL) {
						aux->setEsq( new No_SG(v) ); // Insere
						inserido = aux->getEsq(); // inserido aponta pro nó inserido
						inserido->setPai(aux);
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

				// Buscar o scapeGoat
				while ( (3 * grandeza(inserido)) <= (2 * grandeza(inserido->getPai())) ){
					inserido = inserido->getPai();
				}

				// Reconstruir a nova arvore em relação a nova raiz
				reconstruirArvore(inserido->getPai());
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

		No_SG* removendo(int valor, No_SG* no){
			if (no == NULL)
				return NULL;
			else {
				if (no->getValor() < valor)
					no->setDir( removendo(valor, no->getDir()) );
				else if (no->getValor() > valor)
					no->setEsq( removendo(valor, no->getEsq()) );
				else {
					if (no->getEsq() == NULL && no->getDir() == NULL){
						delete no;
						return NULL;
					}
					else if (no->getEsq() != NULL && no->getDir() != NULL){
						No_SG* aux = no->getDir();
						while(aux->getEsq() != NULL)
							aux = aux->getEsq();
						no->setValor( aux->getValor() );

						no->setDir( removendo(aux->getValor(), no->getDir()) );
					}
					else {
						if (no->getEsq() != NULL){
							No_SG* aux = no->getEsq();
							delete no;
							return aux;
						}
						else {
							No_SG* aux = no->getDir();
							delete no;
							return aux;
						}
					}
				}
			}
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

		void remover(int valor) {
			raiz = removendo(valor, raiz);
		}

		No_SG* buscar(int valor){
			No_SG* aux = raiz;
			do {
				if (aux == NULL) {
					return NULL;
				}
				else {
					if (aux->getValor() < valor){
						aux = aux->getDir();
					}
					else if (aux->getValor() > valor){
						aux = aux->getEsq();
					}
					else {
						return aux;
					}
				}
			} while(true);
		}

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
