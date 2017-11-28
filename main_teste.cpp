#include <iostream>
#include "SG_Tree.h"

using namespace std;

int main () {
  SG_Tree *sg = new SG_Tree(0.6);

  /*sg->inserir(3);
  sg->inserir(2);
  sg->inserir(1);*/

  sg->inserir(10);
  sg->inserir(9);
  sg->inserir(7);
  sg->inserir(6);
  sg->inserir(3);
  sg->inserir(1);
  sg->inserir(0);
  //sg->preOrder();
  //cout<<endl;
  sg->inserir(8);
  sg->inserir(9);
  sg->inserir(4);
  sg->inserir(5);
  sg->inserir(2);

  cout << "InOrder:\n";
  sg->inOrder();
  cout << endl;
  //sg->remover(8);

  cout << "PosOrder:\n";
  sg->posOrder();
  cout << endl;
  //sg->remover(4);

  cout << "PreOrder:\n";
  sg->preOrder();
  cout << endl << endl;

  cout << sg->buscar(0)->getValor() << endl;

  delete sg;
  return 0;
}
