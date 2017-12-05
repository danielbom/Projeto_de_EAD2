#ifndef SG_TREE
#define SG_TREE
#include "No_SG.h"
#include <math.h>

class SG_Tree{
	private:
		No_SG *raiz;
		double Alpha; /// Parametro que verifica desbalanceamento
		int qtde; /// Quantidade de itens na arvore
        int hMax; /// Parametro que guarda o maior h inserido para executar a remoção
        No_SG* temp; /// Armazena o cara que recebeu o posto de hMax
        // Se executar uma remoção e uma reordenação, hMax = log(qtde, Alpha)

        // Se true, durante a inserção busca o scapegoat, se necessário, realiza a reordenação com ele
        // Caso contrário, executa inserção e depois busca o scapegoat durante a reordenação

        // Verificou-se uma mudança na reordenação, para a alteração do parametro 'sgb'
        // Para True, ele reordena melhor o lado esquerdo
        // Para False, ele tem uma ordenação um pouco pior
        // Imagino que seja pq a busca do 'scapegoat' p/ false, busca apenas pelos nós anteriores ao inserido
        // ja p/ true, ele verifica os dois filhos do vertice.

		double logbx(double base, double value){
			return (log(value) / log(base));
		}
		int logH(int h, double alpha) {
		    //std::cout << h << " " << alpha << " " << (int)ceil(logbx((1.0/alpha), h)) << std::endl;
			return (int)ceil(logbx((1.0/alpha), h));
		}

		int grandeza(No_SG *no) {
			if (no == NULL)
				return 0;

			return 1 + grandeza(no->getEsq()) + grandeza(no->getDir());
		}

		int armazenarNoVetor(No_SG* no, No_SG** vet, int pos){
			//std::cout << "Armazenando no vetor\n";
			if (no == NULL){
				return pos;
			}
			pos = armazenarNoVetor(no->getEsq(), vet, pos);
			vet[pos++] = no;
			return armazenarNoVetor(no->getDir(), vet, pos);
		}

		No_SG *construirBalanceado(No_SG **aux, int b, int tam_sg){
			if (tam_sg == 0){
				return NULL;
			}

			int meio = tam_sg / 2;
			aux[b + meio]->setEsq(construirBalanceado(aux, b, meio));

			if (aux[b + meio]->getEsq() != NULL){
				aux[b + meio]->getEsq()->setPai(aux[b + meio]);
				//std::cout << "Balanceando Esquerda\n";
			}

			aux[b + meio]->setDir(construirBalanceado(aux, b + meio + 1, tam_sg - meio - 1));\

			if (aux[b + meio]->getDir() != NULL){
				aux[b + meio]->getDir()->setPai(aux[b + meio]);
				//std::cout << "Balanceando Direita\n";
			}
			return aux[b + meio];
		}

		void VerificaDesbalanceio(int h, No_SG* inserido){
			//std::cout << h << " > " << logH(qtde, Alpha) << std::endl;
			if (h > logH(qtde, Alpha)) {
                if(h > hMax){
                    temp = inserido;
                    hMax = h;
                }

                No_SG* aux = encontreScapeGoat(inserido);
                for(int i = 0; i<qtde && aux->getPai() != NULL; i++){
                    inserido = aux;
                    aux = encontreScapeGoat(inserido->getPai());
                }

				if (inserido == raiz)
					reconstruirArvore(inserido);
				else
					reconstruirArvore(inserido->getPai());

                hMax = logH(qtde, Alpha);
			}
		}

		No_SG* encontreScapeGoat(No_SG* no){
            while ( grandeza(no) <= Alpha*grandeza(no->getPai()) ){
                no = no->getPai();
            }
            return no;
		}

		void reconstruirArvore(No_SG *scapeGoat){
			//std::cout << "Reconstruindo Arvore\n";
			int tam_sg = grandeza(scapeGoat);
			No_SG *pai = scapeGoat->getPai();
			No_SG **vetor = new No_SG* [tam_sg];
			armazenarNoVetor(scapeGoat, vetor, 0);

			if (pai == NULL){
				raiz = construirBalanceado(vetor, 0, tam_sg);
				raiz->setPai(NULL);
			}
			else if (pai->getDir() == scapeGoat){
				pai->setDir(construirBalanceado(vetor, 0, tam_sg));
				pai->getDir()->setPai(pai);
			}
			else{
				pai->setEsq(construirBalanceado(vetor, 0, tam_sg));
				pai->getEsq()->setPai(pai);
			}
		}

		int inserindo(int v) {
			//std::cout << "inserindo\n";
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

            VerificaDesbalanceio(h+1, inserido);

			qtde++;
			return h;
		}

		void preOrder(No_SG* no){
			if (no == NULL) {
                std::cout << "- ";
                return ;
			}
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
			if(no == NULL){
				return ;
			}

			destruir(no->getEsq());
			destruir(no->getDir());

			delete no ;
		}

		No_SG* removendo(int valor, No_SG* no){
			if (no == NULL){
				return NULL;
			}
			else {
				if (no->getValor() < valor) {
					no->setDir( removendo(valor, no->getDir()) );
				}
				else if (no->getValor() > valor) {
					no->setEsq( removendo(valor, no->getEsq()) );
				}
				else {
					if (no->getEsq() == NULL && no->getDir() == NULL){
                        qtde--;
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
                            qtde--;
							No_SG* aux = no->getEsq();
							delete no;
							return aux;
						}
						else {
						    qtde--;
							No_SG* aux = no->getDir();
							delete no;
							return aux;
						}
					}
				}
			}

		}

		No_SG* buscando(int valor, No_SG* no){
            if(no == NULL)
                return NULL;
            else {
                if(valor > no->getValor())
                    return buscando(valor, no->getDir());
                else if (valor < no->getValor())
                    return buscando(valor, no->getEsq());
                else
                    return no;
            }
		}

	protected:

	public:
        /// 0.66 ~ 2/3
		SG_Tree(double A = 0.66) {
			raiz = NULL;
            setAlpha(A);
			qtde = 0;
			hMax = 0;
		}
		~SG_Tree() {
			destruir(raiz);
		}
		// Versao recursiva da funcao busca...
		No_SG* buscar(int valor){
            return buscando(valor, raiz);
		}

		bool inserir(int valor){
            int h = inserindo(valor);
            if(h == -1)
                return false;
            return true;
		}
		void remover(int valor){
            if (raiz == NULL)
                return ;
            if (temp->getValor() == valor){
                temp = temp->getPai();
            }
            raiz = removendo(valor, raiz);
            if(temp != NULL){
                VerificaDesbalanceio(hMax+1, temp);
            }
		}
		double getAlpha(){
            return Alpha;
        }
		void setAlpha(double A){
		    // ScapeGoat Tree suporta Alpha entre 0.5 e 1
            if(A > 1 || A < 0.5)
                A = 0.66;
			else
                Alpha = A;
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
