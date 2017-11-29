#ifndef SG_TREE
#define SG_TREE
#include "No_SG.h"
#include <math.h>

class SG_Tree{
	private:
		No_SG *raiz;
		double Alpha; // Parametro que verifica desbalanceamento
		int qtde; // Quantidade de itens na arvore
        int hMax; // Parametro que guarda o maior h inserido para executar a remoção
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
				std::cout << "Desbalanceada!!\n";


				// Buscar o scapeGoat
				// while ( (3 * grandeza(inserido)) <= (2 * grandeza(inserido->getPai())) ){
				while ( grandeza(inserido) <= Alpha*grandeza(inserido->getPai()) ){
				//std::cout << "Se " <<(3 * grandeza(inserido)) << " <= " << (2 * grandeza(inserido->getPai())) << " SOBE " <<std::endl;
					inserido = inserido->getPai();
					//std::cout << "Se " <<(3 * grandeza(inserido)) << " <= " << (2 * grandeza(inserido->getPai())) << " SOBE " <<std::endl;
				}

				// Reconstruir a nova arvore em relação a nova raiz
				// reconstruirArvore(inserido->getPai()); // ANTERIOR
				// reconstruirArvore(inserido); // TESTE
				// O problema nao era a funcao grandeza, mas sim neste ponto.
				// Essa mudança tecnicamente concertou o erro.
				// Antes se meu SG era a raiz ele enviava um pai NULL e nao executava
				// Talvez um if, else??? pois o modelo do site geeksforgeeks manda o pai???
				if (inserido == raiz)
					reconstruirArvore(inserido);
				else
					reconstruirArvore(inserido->getPai());
			}
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

            VerificaDesbalanceio(h, inserido);

			qtde++;
			return h;
		}
        /* ******************************************************************** */
		void removendo2(int v){
            if (raiz == NULL){
                return ;
            }
            No_SG* aux = raiz;
            bool feito = false;

            do {
                if (v > aux->getValor()) {
                    if(aux->getDir() != NULL) {
                        if(aux->getDir()->getValor() == valor) {
                            aux = aux->getDir();
                            d = true;
                        }
                        else {
                            aux = no->getDir();
                        }
                    }
                    else{
                        return ;
                    }
                }
                else if (v < aux->getValor()) {
                    if(aux->getEsq() != NULL) {
                        if(aux->getEsq()->getValor() == valor) {
                            aux = no->getEsq();
                            e = true;
                        }
                        else {
                            aux = no->getEsq();
                        }
                    }
                    else{
                        return ;
                    }
                }
                else {
                    if(aux->getDir() == NULL && aux->getEsq() == NULL) {
                        if (e == true)
                            no->setEsq(NULL);
                        else if(d == true)
                            no->setDir(NULL);
                        feito = true;
                    }
                    else if (aux->getEsq() != NULL && aux->getDir() != NULL){
                        No_SG* menorMaiores = aux->getDir();
                        while(menorMaiores->getEsq() != NULL)
                            menorMaiores = menorMaiores->getEsq();
                        aux->setValor( menorMaiores->getValor() );
                        valor = menorMaiores->getValor();
                    }
                    else {
                        if(aux->getEsq() != NULL){
                            if (e == true)
                                no->setEsq(aux->getEsq());
                            else if(d == true)
                                no->setDir(aux->getEsq());
                        }
                        else{
                            if (e == true)
                                no->setEsq(aux->getDir());
                            else if(d == true)
                                no->setDir(aux->getDir());
                        }
                        feito = true;
                    }
                }
            }(!feito);

            if (aux != NULL){

            }

		}
		/* *********************************************************** */

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

		No_SG* removendoRec(int valor, No_SG* no){
            No_SG* aux = NULL;
            No_SG* sg = NULL;
            bool d, e;
            d = e = false;
            if(valor > no->getValor()){
                if(no->getDir() != NULL) {
                    if(no->getDir()->getValor() == valor) {
                        aux = no->getDir();
                        d = true;
                    }
                    else {
                        sg = removendoRec(valor, no->getDir());
                        if(sg != NULL)
                            return sg;
                    }
                }
                else
                    return NULL;
            }
            else if(valor < no->getValor()){
                if(no->getEsq() != NULL) {
                    if(no->getEsq()->getValor() == valor){
                        aux = no->getEsq();
                        e = true;
                    }
                    else {
                        sg = removendoRec(valor, no->getEsq());
                        if(sg != NULL)
                            return sg;
                    }
                }
                else
                    return NULL;
            }
            else {
                aux = no;
            }
            // Removendo
            if(aux!=NULL){
                if(aux->getDir() == NULL && aux->getEsq() == NULL) {
                    delete aux;
                    if (e == true)
                        no->setEsq(NULL);
                    else if(d == true)
                        no->setDir(NULL);
                }
                else if (aux->getEsq() != NULL && aux->getDir() != NULL){
                    No_SG* menorMaiores = aux->getDir();
                    while(menorMaiores->getEsq() != NULL)
                        menorMaiores = menorMaiores->getEsq();
                    aux->setValor( menorMaiores->getValor() );


                    if(sg != NULL)
                        return sg;
                }
                else {
                    if(aux->getEsq() != NULL){
                        if (e == true)
                            no->setEsq(aux->getEsq());
                        else if(d == true)
                            no->setDir(aux->getEsq());
                        delete aux;
                    }
                    else{
                        if (e == true)
                            no->setEsq(aux->getDir());
                        else if(d == true)
                            no->setDir(aux->getDir());
                        delete aux;
                    }
                }
            }
            if (hMax > logH(qtde, Alpha)) {
                if(no->getDir() != NULL)
                    if( grandeza(no->getDir()) <= Alpha*grandeza(no) )
                        return no;

                if(no->getEsq() != NULL)
                    if ( grandeza(no->getEsq())<= Alpha*grandeza(no)  )
                        return no;
            }

            return NULL;
		}
	protected:

	public:
        /// 0.66 ~ 2/3
		SG_Tree(double A = 0.66) {
			raiz = NULL;
            setAlpha(A);
			qtde = 0;
			hMax = 0;
			sgb = false;
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
            No_SG* sg = removendoRec(valor, raiz);
            if(sg != NULL) {
                //std::cout << valor << " Arvore Desbalanceada na delecao\n";
                if (sg == raiz)
                    reconstruirArvore(sg);
                else
                    reconstruirArvore(sg->getPai());

                hMax = logH(qtde, Alpha);
                qtde--;
            }
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
