#include <iostream>
#include "SG_Tree.h"

using namespace std;

int main () {
  SG_Tree *sg = new SG_Tree(0.5);
  // O é um parametro de inicialização da arvore. Se não for especificado,
  // seu valor padrão é de 0.6, pois detem um desbalanceio muito bom entre eficiencia e custo
  // e é o mais comum nas implementações deste tipo de arvore.

  // A ScapeGoat Tree suporta alpha entre [0.5 , 1], onde
  // 1 é uma BST sem otimização nenhuma e
  // 0.5 busca uma arvore binaria completa sempre

  // Aos operações de inserção e remoção com reordenação para uma arvore semi-balanciada( ou alpha-balanceada )
  // busca garantir uma operação de busca com complexidade de tempo O(log n)

  // ScapeGoat Tree é uma arvore tão eficiente quanto RB Tree, entre outras. Uma das poucas disvantagens
  // é a complexidade de espaco pra reordenação que, no pior caso(raro) é O(n), e no caso medio é O(lon n)

  sg->inserir(10);
  sg->inserir(9);
  sg->inserir(7);
  sg->inserir(6);
  sg->inserir(3);
  sg->inserir(1);
  sg->inserir(0);
  sg->inserir(8);
  sg->inserir(9);
  sg->inserir(4);
  sg->inserir(5);
  sg->inserir(2);
  sg->inserir(15);
  sg->inserir(12);
  sg->inserir(16);
  sg->inserir(13);
  sg->inserir(11);

  cout << "InOrder:\n";
  sg->inOrder();
  cout << endl;
  sg->remover(8);

  cout << "PosOrder:\n";
  sg->posOrder();
  cout << endl;
  sg->remover(4);

  cout << "PreOrder:\n";
  sg->preOrder();
  cout << endl << endl;

  cout << sg->buscar(0)->getValor() << endl;

  // 10 7 3 1 0 2 5 4 6 9 8 15 12 11 13 16 - sem nenhuma remocao
  // 7 3 1 0 2 6 5 12 10 9 11 15 13 16 - com remocao

  // Podemos perceber que a arvore foi reconstruida na remocao
  // Isso deixa a perceber que a arvore esta funcionando corretamente

  delete sg;
  return 0;
}
