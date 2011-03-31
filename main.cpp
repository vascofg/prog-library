#include <iostream>
#include <sstream>

#include "mainFunctions.h"
#include "checkos.h"

using namespace std;

//INITIALIZING CLASS FUNCTIONS

IdentNum User::numUsers = 0;    //nas funcoes de load de ficheiros 
IdentNum Book::numBooks = 0;   // estas 2 variaveis vao ser alteradas

//END OF INITIALIZATION

int main ()
{
	string usersFile, booksFile;
	readFromConfig(usersFile,booksFile);    // le do ficheiro cfg os nomes dos ficheiros txt
	                                       //  se algum dos 3 nao existir, e criado

	Library library(usersFile,booksFile);   // cria o objecto library da class Library

	library.loadUsers();                   // carrega do ficheiro txt de utilizadores para a biblioteca
	library.loadBooks();                  //  carrega do ficheiro txt de livros para a biblioteca

	bool firstRun = true;                  // vai servir para mostrar uma mensagem de informacao sobre como cancelar
	                                      //  uma accao apenas na primeira iteracao do ciclo
	int op; //opcao
	do
	{
		if (!firstRun)
			for (int temp = 0; temp <= 7; temp++)
				cout << '\n';
		else
			cout << "\n**** Seja bem vindo a biblioteca PROGRAMACAO TP1 ****\n\n";

		///show menu
		cout << "#### Area de Administracao ####\n\n";
		cout << "1 - Registar Utilizador\n";
		cout << "2 - Adicionar livro\n";
		cout << "3 - Listar todos os utilizadores\n";
		cout << "4 - Listar todos os livros\n";
		cout << "5 - Pesquisar por utilizador\n";
		cout << "6 - Pesquisar por livro\n";
		cout << "7 - Mudar estado de um utilizador\n";
		cout << "\n#### Area de Utlizador ####\n\n";
		cout << "8 - Requisitar Livro\n";
		cout << "9 - Devolver Livro\n";
		
		cout << "\n0 - Saire\n";
		///end menu

		if (firstRun)
		{
			cout << "\nPara cancelar uma accao em qualquer parte do programa,\nprima enter sem escrever nada.\n";
			firstRun = false;
		}

		readOp(op);       //Pergunta e atribui a 'op' a opcao do utilizador
		cout << '\n';

		switch(op) 
		{
		case 0:                               // opcao 0:
			exitFunction(op,library);        //  Pede confirmacao e, em caso positivo, guarda para os ficheiros e sai do programa
			break;

		case 1:                               // opcao 1:
			readAndAddUser(library);         //  Adicionar um utilizador a biblioteca
			library.saveUsers();
			break;

		case 2:                               // opcao 2:
			readAndAddBook(library);         //  Adicionar um Livro a biblioteca
			library.saveBooks();
			break;

		case 3:                               // opcao 3:           
			library.showUsers();             //  Mostra os utilizadores registados
			break;

		case 4:                               // opcao 4:
			library.showBooks();             //  Mostra os livros da biblioteca
			break;

		case 5:                               // opcao 5:
			readAndSearchUsers(library);     //  Pede ao utilizador caracteres, pesquisa
			break;                          //   e mostra no ecra os resultados

		case 6:                               // opcao 6:
			readAndSearchBooks(library);     //  Pergunta ao utilizador se quer pesquisar por autor
			break;                          //   ou titulo, pede caracteres,  pesquisa e mostra os resultados

		case 7:                               // opcao 7:
			library.showUsers();             //  Mostra os utilizadores, pede um ID de utilizador
			readAndSetUserState(library);   //   e pergunta se quer mudar o estado desse utilizador para o estado contrario
			library.saveUsers();
			break;

		case 8:                               // opcao 8:
			readAndRequestBook(library);     //  Mostra os utilizadores, pede um ID de utilizador,
			library.saveUsers();            //   mostra os livros disponiveis a esse utilizador,
			library.saveBooks();           //    pede um ID do Livro a requisitar e executa a requisicao
			break;

		case 9:                               // opcao 9:
			readAndReturnBook(library);      //  Mostra os utilizadores, pede um ID de utilizador,
			library.saveUsers();            //   mostra os livros que esse utilizador possui no momento
			library.saveBooks();           //    pede um ID do livro a devolver e executa a devolucao
			break;
		}
		if (op != 0)           // se a opcao nao e 0, pede ao utilizador para premir enter para continuar
		{
			cout << "\nPrima ENTER para continuar...";
			while(char temp = _getch())
				if (temp == '\n' || temp == '\r')
					break;
		}
	} while (op != 0);
	return 0;
}
