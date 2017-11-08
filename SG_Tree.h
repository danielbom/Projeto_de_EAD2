#ifndef SG_TREE
#define SG_TREE
#include "No_SG.h"

class SG_Tree{
  private:
    No_SG *raiz;
    void reconstruirArvore();
  protected:

  public:
    SG_Tree() { raiz = NULL; }
    ~SG_Tree() ;
    void inserir(int v) ;
    void remover(int v) ;
    void buscar(int v) ;

};

#endif
