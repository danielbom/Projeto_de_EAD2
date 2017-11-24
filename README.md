# Projeto_de_EAD2

Projeto de Estruturas de Dados 2
Sobre a Arvore ScapeGoat Tree
UTFPR/CM - 2017/2

http://www.geeksforgeeks.org/scapegoat-tree-set-1-introduction-insertion/
http://www.sanfoundry.com/java-program-implement-scape-goat-tree/
https://people.csail.mit.edu/rivest/pubs/GR93.pdf
http://opendatastructures.org/ods-java/8_Scapegoat_Trees.html
https://brilliant.org/wiki/scapegoat-tree/
http://www.geeksforgeeks.org/scapegoat-tree-set-1-introduction-insertion/
http://people.scs.carleton.ca/~maheshwa/Honor-Project/scapegoat.pdf

interessantissimo
http://www.boost.org/doc/libs/1_64_0/doc/html/intrusive/sg_set_multiset.html


insersao 1 - 10 9 7 6 3 1 0 8 9 4 5 2   15 12 16 13 11
insersao 2 - 15 12 16 13 11   10 9 7 6 3 1 0 8 9 4 5 2

true 1.1 - alpha 0.5
PreOrder:
10 7 3 1 0    2 5 4 6 9 8 15 12 11 13 16

false 1.1 - alpha 0.5
PreOrder:
10 9 7 6 3 1 0    2 4 5 8 15 12 11 13 16

true 2 - alpha 0.5
PreOrder:
15 8 3 1 0    2 6 5 4 7 11 10 9 13 12 16

false 2 - alpha 0.5
PreOrder:
15 12 11 10 9 6 1 0    3 2 4 5 8 7 13 16

true 1.2 - alpha 0.6
PreOrder:
10 9 3 1 0    2 6 5 4 8 7 15 12 11 13 16

false 1.2 - alpha 0.6
PreOrder:
10 9 7 6 3 1 0    2 4 5 8 15 12 11 13 16

false 1.3 - alpha 0.6
PreOrder:
10 9 7 6 3 1 0    2 4 5 8 15 12 11 13 16