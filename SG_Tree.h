#ifndef SG_TREE
#define SG_TREE
#include "No_SG.h"

class SG_Tree{
  private:
    No_SG *raiz ;
    double Alpha; // Parametro que verifica desbalanceamento
    int qtde ; // Quantidade de itens na arvore
    double logbx(double base, double value){
      return log(value) / log(base) ;
    }
    int logH(int h, double alpha) {
      return ceil(logbx((1.0/alpha), h));
    }
    void reconstruirArvore();
    int inserindo(int v) {
      No_SG *aux = raiz;
      bool make = true;
      int h = 0;
      do {
        if (v > aux->getValor()) {
          if (aux->getDir() != NULL) {
            aux = aux->getDir(); // Busca na arvore direita
          }
          else {
            aux->setDir( new No_SG(v) ); // Insere
            make = false;
          }
        }
        else if (v < aux->getValor()) {
          if (aux->getEsq() != NULL) {
            aux = aux->getEsq(); // Busca na arvore esquerda
          }
          else {
            aux->setDir( new No_SG(v) ); // Insere
            make = false;
          }
        }
        else {
          return -1; // Já existe
        }
        h++;
      }while(make);

      qtde++;
      return h;
    }
    void preOrder(No_SG* no){
      if(no != NULL) {
        std::cout << no->getValor() << " " ;
        preOrder(no->getEsq());
        preOrder(no->getDir());
      }
    }
    void posOrder(No_SG* no){
      if(no != NULL) {
        posOrder(no->getEsq());
        posOrder(no->getDir());
        std::cout << no->getValor() << " " ;
      }
    }
    void inOrder(No_SG* no){
      inOrder(no->getEsq());
      std::cout << no->getValor() << " " ;
      inOrder(no->getDir());
    }
    void destruir(No_SG* no){
      if(no != NULL) {
        posOrder(no->getEsq());
        posOrder(no->getDir());
        delete no ;
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

      if (h > logH(qtde, Alpha)) {
        // Buscar a nova raiz

        // Reconstruir a nova arvore em relação a nova raiz
        reconstruirArvore();
      }

      return h >= 0;
    }
    void remover(int valor) ;
    void buscar(int valor) ;
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
