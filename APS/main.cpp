#include <iostream>
#include <unistd.h>
#include "SG_Tree.h"

using namespace std;

void imprimir(SG_Tree *sg){
	cout<<"\nIn order:\n ";
	sg->inOrder();
	cout << endl;

	cout<<"\nPost order:\n ";
	sg->posOrder();
	cout << endl;

	cout<<"\nPre order:\n ";
	sg->preOrder();
	cout << endl;
}

void menu(SG_Tree *sg){
	system("clear");
	cout << endl;
	cout<<"Árvore ScapeGoat Teste"<<endl;

	char ch;
	int val;

	do
	{
		cout<<"\nOperações da árvore\n";
		cout<<"1. Inserir "<<endl;
		cout<<"2. Contar Nós"<<endl;
		cout<<"3. Buscar"<<endl;
		cout<<"4. Verificar status"<<endl;
		cout<<"5. Tornar árvore vazia"<<endl;
		cout<<"6. Remover"<<endl;
		cout<<"7. Sair"<<endl;

		int choice;

		cout<<"Escolha uma opção: ";
		cin>>choice;
		system("clear");

		switch (choice)
		{
			case 1:{
				do {
					cout<<"Entre com um inteiro para ser inserido: ";
					cin>>val;
					sg->inserir(val);

					imprimir(sg);
					cout<<"\nQuer continuar? (s ou n) \n";
					cin>>ch;
				} while(ch == 's' || ch == 'S');
				break;
			}
			case 2:{
				cout<< "Quantidade de Nós = " << sg->getQuantidade() << endl;
				break;
			}
			case 3:{
				cout<<"Entre com um número interiro para pesquisa: ";
				cin>>val;
				if (sg->buscar(val))
					cout<<val<<" encontrado na árvore"<<endl;
				else
					cout<<val<<" Não encontrado na árvore"<<endl;
				break;
			}
			case 4:{
				cout<<"Status da árvore = ";
				if (sg->isEmpty())
					cout<<"Árvore está vazia"<<endl;
				else
					cout<<"Árvore não está vazia"<<endl;
				menu(sg);
				break;
			}
			case 5:{
				cout<<"\nÁrvore limpa\n";
				float aux = sg->getAlpha();
				delete sg;
				sg = new SG_Tree(aux);
				break;
			}
			case 6:{
				do {
					cout<<"Entre com um inteiro para ser removido: ";
					cin>>val;
					cout << "Removendo... \n";
					sg->remover(val);

					imprimir(sg);
					cout<<"\nQuer continuar? (s ou n) \n";
					cin>>ch;
				} while(ch == 's' || ch == 'S');
				break;
			}
			case 7:{
				cout << endl;
				cout<<"\n DuckTales Uh-Uh !\n";
				cout << endl;
				exit(0);
				break;
			}
			default:{
				cout<<"Entrada inválida!! \n ";
				cout << endl;
				menu(sg);
				break;
			}
		}

		imprimir(sg);
		cout << endl;
	}
	while (true);
	exit(0);
}

int main() {
	system("clear");
	float Alpha;
	cout << "Escolha o Alpha:" << endl;
	cin >> Alpha;
	SG_Tree *sg = new SG_Tree(Alpha);
	menu(sg);

	return 0;

}
