#ifndef SG_TREE
#define SG_TREE
#include "No_SG.h"
#include <math.h>

class SG_Tree{
	private:
		No_SG *raiz;
		double Alpha; // Parametro que verifica desbalanceamento
		int qtde; // Quantidade de itens na arvore
    int h; // Parametro temporario global q armazena o valor da profundidade da arvore

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
			std::cout << "Armazenando no vetor\n";
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
				std::cout << "Balanceando Esquerda\n";
			}

			aux[b + meio]->setDir(construirBalanceado(aux, b + meio + 1, tam_sg - meio - 1));\

			if (aux[b + meio]->getDir() != NULL){
				aux[b + meio]->getDir()->setPai(aux[b + meio]);
				std::cout << "Balanceando Direita\n";
			}
			return aux[b + meio];
		}

		void VerificaDesbalanceio(int h, No_SG* inserido){
			//std::cout << h << " > " << logH(qtde, Alpha) << std::endl;
			if (h > logH(qtde, Alpha)) {
				//std::cout << "Desbalanceada!!\n";

				// Buscar o scapeGoat
				// while ( (3 * grandeza(inserido)) <= (2 * grandeza(inserido->getPai())) ){
				while ( (grandeza(inserido)/grandeza(inserido->getPai())) >= Alpha ){
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
			std::cout << "Reconstruindo Arvore\n";
			int tam_sg = grandeza(scapeGoat);
			/* DEBUG
			if (scapeGoat == NULL) {
                std::cout << "SG null\n";
			}
			else
                std::cout << scapeGoat->getValor() << std::endl;

			std::cout << tam_sg << std::endl;
			*/
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
			/* DEBUG
			if (inserido != NULL)
        std::cout << " Valor inserido: " << inserido->getValor() << " pai: " << inserido->getPai()->getValor() << std::endl;
      */
		  VerificaDesbalanceio(h, inserido);

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
		        	else {
		            	return no;
		        	}
	    		}
		}

		/*
		void verificaDireito(No_SG* no){
			std::cout << "h: " << h << std::endl;
			if(h > logH(qtde ,Alpha)){
				std::cout << "Desbalanceada - " << ((float)grandeza(no)/(float)grandeza(no->getDir())) << std::endl;
				if((float)(grandeza(no)/grandeza(no->getDir())) >= Alpha){
                    std::cout << "AQUI ????\n";
					if (no == raiz)
						reconstruirArvore(no);
					else
						reconstruirArvore(no->getPai());
				}
			}
		}
		void verificaEsquerdo(No_SG* no){
			std::cout << "h: " << h << std::endl;
			if(h > logH(qtde ,Alpha)){
				std::cout << "Desbalanceada - " << ((float)grandeza(no)/(float)grandeza(no->getEsq())) << std::endl;
				// if ( (filho / pai) >= Alpha)
				if( ((float)grandeza(no->getEsq())/(float)grandeza(no)) >= Alpha ){
					if (no == raiz)
						reconstruirArvore(no);
					else
						reconstruirArvore(no->getPai());
				}
			}
		}
		*/
		No_SG* inserindoRec(int valor, No_SG* no){
			h++;
			if(no->getValor() > valor) {
				if(no->getEsq() != NULL){
					return inserindoRec(valor, no->getEsq());
				}
				else{
					qtde++;
					no->setEsq(new No_SG(valor));
					no->getEsq()->setPai(no);
				}
			}
			else if(no->getValor() < valor){
				if(no->getDir() != NULL){
					return inserindoRec(valor, no->getDir()) ;
				}
				else{
					qtde++;
					no->setDir( new No_SG(valor));
					no->getDir()->setPai(no);
				}
			}
			if(no->getDir() != NULL){
				std::cout << "dir nao null\n";
				if( ((float)grandeza(no->getDir())/(float)grandeza(no)) >= Alpha ){
					std::cout << "sg?\n";
					return no;
				}
			}
			if(no->getEsq() != NULL){
				std::cout << "esq nao null\n";
				if ( ((float)grandeza(no->getEsq())/(float)grandeza(no)) >= Alpha ){
					std::cout << "sg?\n";
					std::cout << no->getValor() << std::endl;
					return no;
				}
			}
			return NULL;
		}

	protected:

	public:
		SG_Tree(double A = 2.0/3.0) {
			raiz = NULL;
			Alpha = A;
			qtde = 0;
		}

		~SG_Tree() {
			destruir(raiz);
		}

		/*
		bool inserir(int valor) {
			int h = inserindo(valor); // h recebe a altura da inserção de v
			if (h == -1) return false;
			return true;
		}

		*/
		void inserir(int valor){
			h = 0;
			No_SG* sg = NULL;
			if (raiz == NULL){
            raiz = new No_SG(valor);
						qtde++;
			}
			else {
                No_SG* sg = inserindoRec(valor, raiz);
                //std::cout << "h: " << h << std::endl;
                //std::cout << "logH: " << logH(qtde, Alpha) << std::endl;
                //std::cout << "h >= logH: " << ((h >= (float)logH(qtde, Alpha) )? 1 : 0) << std::endl;
			}
			if (sg != NULL){
				std::cout << "Arvore Desbalanceada\n";
			}
		}




		void remover(int valor) {
			raiz = removendo(valor, raiz);
		}

		/*
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
		*/
		// Versao recursiva da funcao busca...
		No_SG* buscar(int valor){
            return buscando(valor, raiz);
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
