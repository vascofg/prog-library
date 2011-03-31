#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include "mainFunctions.h"
using namespace std;

/* askForConfirmation()
This Function has no parameters.
It asks the user for a confirmation of a previous action
Returns 1 if positive answer
Returns 0 if negative answer
Returns -1 if invalid answer
Returns -2 if no answer -> user probably wants to cancel
*/
int askForConfirmation()
{
	string temp;
	getline(cin,temp);
	if (temp.size() == 1)
	{   
		istringstream iss(temp);
	    char tempChar;
	    iss >> tempChar;
	    if (toupper(tempChar) == 'N')
		    return 0;
	    else if (toupper(tempChar) == 'S')
            return 1;
		else return -1;
	}
	else if (temp.size() == 0)
			return -2;
	else
		return -1;
}

/* askIfCancel()
This function has no parameters
It asks if user wants to cancel an action.
Returns true if positive answer
Returns false if negative answer
*/
bool askIfCancel()
{
	do
	{
		cout << "\nDeseja cancelar? (S/N): ";
		int option = askForConfirmation();
		if (option == 1)
		{
			cout << "\nAccao cancelada pelo utilizador!\n";
			return true;
		}
		else if (option == 0)
		{
			cout << '\n';
			return false;
		}
		else cout << "Opcao Invalida!\n";
	}
	while (true);
}

/* askForID
This function has parameters:
 - IdentNum &ID - Can be userID or bookID
 - Library &library - needed to verify if ID is valid
 - string askMessage - string that will be displayed when asking user for input
 - bool isUser - True if parameter &ID is an User ID and False if &ID is a Book ID
 Returns:
 - True - If the ID was read successfuly
 - False - If the User canceled the action
 This function is used to ask user for an ID in several situations all across the program.
*/
bool askForID(IdentNum &ID, Library &library, string askMessage, bool isUser)
{
	bool done;
	bool cancel;
	do
	{
		string tempID;
		cancel = false;
		done = false;
		cout << askMessage;
		getline(cin,tempID);
		istringstream issID(tempID);
		if (issID >> ID)
		{
			if (isUser)
			{
				User userTemp = library.getUserByID(ID);
				if (userTemp.getID() != 0)
					done = true;
			}
			else
			{
				Book bookTemp = library.getBookByID(ID);
				if (bookTemp.getID() != 0)
					done = true;
			}
			if (!done)
				cout << "ID Invalido!\n";
		}
		else if (issID.str() == "")
			cancel = askIfCancel();
		else if (!done)
			cout << "ID Invalido!\n";
	}
	while (!done && !cancel);
	if (cancel)
		return false;
	else
		return true;
}

/* bookIsRequested
Parameters:
- User userTemp
- IdentNum bookID
This function searches the vector BooksRequested of the userTemp
for the bookID.
Returns True if it was found and False if it wasn't found.
*/

bool bookIsRequested(User userTemp, IdentNum bookID)
{
	bool found = false;
	vector<IdentNum> v = userTemp.getRequestedBooks();
	for (size_t i = 0; i < v.size(); ++i)
	{
		if (v[i] == bookID)
		{
			found = true;
			break;
		}
	}
	return found;
}

/* Parameters:
- Library &library - necessary to change the state of an user in the library
This function prompts the user for the ID of the user whose state he
wants to change and sets the user state accordingly.
No return.
*/

void readAndSetUserState(Library &library)
{
	IdentNum userID;
	bool cancel = !askForID(userID, library, "ID de Utilizador?: ", 1);
	bool activeBool;
	bool done;
	if (!cancel)
	{
		do
		{
			cancel = false;
			done = false;
			User userTemp = library.getUserByID(userID);
			activeBool=!userTemp.isActive();
			cout << "\nMudar o estado do utilizador " << library.getUserByID(userID).getName() << " para ";
			if (activeBool)
				cout << "Activo? (S/N): ";
			else
				cout << "Inactivo? (S/N): ";
			int option = askForConfirmation();

			switch (option)
			{
			case 1:
				library.updateActive(userID, activeBool);
				cout << "\nEstado alterado com sucesso!\n";
				done = true;
				break;
			case 0:
				cout << "\nEstado nao alterado!\n";
				done = true;
				break;
			case -1:
				cout << "\nOpcao Invalida!";
				break;
			case -2:
				cancel = askIfCancel();
			}
		}
		while (!done && !cancel);
	}
}

/* readBook Title
Parameter:
string &bookTitle
This function prompts user for a bookTitle and assigns it to &bookTitle.
No return.
*/

bool readBookTitle(string &bookTitle)
{
	bool validSize = false;
	bool cancel;
	bool done;
	do
	{
		istringstream iss;
		string tempString;
		do
		{
			cancel = false;
			done = false;
			iss.clear();
			cout << "Titulo do livro: ";
			getline(cin, tempString);
			iss.str(tempString);
			if (iss >> tempString)
			{
				bookTitle = tempString;
				done = true;
			}
			else
			{
				if (iss.str() == "")
					cancel = askIfCancel();
				else 
					cout << "Titulo invalido!\n\n";
			}
		}
		while (!cancel && !done);

		if (!cancel)
		{
			while (iss >> tempString)
				bookTitle = bookTitle + " " + tempString;
			if (bookTitle.size() < MAXTITLELENGTH)
				validSize = true;
			else
				cout << "\nO nome tem de ter menos de " << MAXTITLELENGTH << " caracteres!\n\n";
		}
	}
	while (!validSize && !cancel);
	return !cancel;
}

/* readBookAuthor
Parameter:
string &bookAuthor
This function prompts user for a bookAuthor and assigns it to &bookAuthor.
No return.
*/

bool readBookAuthor(string &bookAuthor)
{
	bool validSize = false;
	bool cancel;
	bool done;
	do
	{		
		istringstream iss;
		string tempString;
		do
		{
			cancel = false;
			done = false;
			iss.clear();
			cout << "Autor do livro: ";
			getline(cin, tempString);
			iss.str(tempString);
			if (iss >> tempString)
			{
				bookAuthor = tempString;
				done = true;
			}
			else
			{
				if (iss.str() == "")
					cancel = askIfCancel();
				else
					cout << "Nome invalido!\n";
			}
		}
		while (!cancel && !done);

		if (!cancel)
		{
			while (iss >> tempString)
				bookAuthor = bookAuthor + " " + tempString;
			if (bookAuthor.size() < MAXAUTHORLENGTH)
				validSize = true;
			else
				cout << "\nO nome tem de ter menos de " << MAXAUTHORLENGTH << " caracteres!\n\n";
		}			
	}
	while (!validSize && !cancel);
	return !cancel;
}

/* readBookQuantity
Parameter:
unsigned int &bookQuantity
This function prompts user for a bookQuantity and assigns it to &bookQuantity.
No return.
*/

bool readBookQuantity(unsigned int &bookQuantity)
{ 
	bool cancel;
	bool done;
	do
	{
		cancel = false;
		done = false;
		string tempString;
		int tempInt;
		cout << "Quantidade de livros: ";
		getline(cin, tempString);
		istringstream iss(tempString);
		if (iss >> tempInt)
		{
			if (tempInt >= 0)
			{
				bookQuantity = tempInt;
				if(bookQuantity>MAXQUANTITY)
					cout << "A quantidade tem que ser menor do que " << MAXQUANTITY << " unidades.\n\n";
				else done = true;
			}
			else
				cout << "Quantidade Invalida!\n";
		}
		else
		{
			if (iss.str() == "")
				cancel = askIfCancel();
			else
				cout << "Por favor insira um numero!\n";
		}
	}
	while (!cancel && !done);
	if (!cancel)
		return true;
	else return false;
}

/* readAndAddBook
Parameter:
Library &library
Calls functions readBookTitle, readBookAuthor and readQuantity.
Then it adds a book with that Title, Author and Quantity to the library &library.
No return.
*/

void readAndAddBook(Library &library)
{
	string bookTitle, bookAuthor;
	unsigned int bookQuantity;
	bool cancel = !readBookTitle(bookTitle);
	if (!cancel)
	{
		cancel = !readBookAuthor(bookAuthor);
		if (!cancel)
		{
			cancel = !readBookQuantity(bookQuantity);
		}
	}
	if(!cancel)
	{
		Book tempBook(bookTitle,bookAuthor,bookQuantity);
		library.addBook(tempBook);
		if (bookQuantity == 1)
			cout << "\n" << bookQuantity << " livro \"" << bookTitle << "\" do autor \"" << bookAuthor << "\" adicionado com sucesso!\n";
		else cout << "\n" << bookQuantity << " livros \"" << bookTitle << "\" do autor \"" << bookAuthor << "\" adicionados com sucesso!\n";
	}
}

/* readOp
This function will be used to ask User for an option after the menu is shown.
Parameter:
- int &op
After reading the User's option, this function will assign it to &op.
*/

void readOp(int &op)
{
	int tempOp;
	char test;
	bool read;
	do
	{				// read user option
		read = false;
		cout << "\nOpcao: ";
		string stringOp;
		getline(cin,stringOp);
		istringstream iss(stringOp);
		if (iss >> tempOp)
		{
			if (!(iss >> test))
				if (tempOp >= 0 && tempOp < 10)
				{
					read = true;
					op = tempOp;
				}
		}	
		if (!read)
			cout << "Opcao Invalida!\n";
	}
	while (!read);
}

/* exitFunction
This function is called when user selects option 0.
It will ask for a confirmation and then act accordingly with the answer.
Parameters:
- int &op
- Library &library
If user confirms he wants to exit, this function will save books 
and users to their .txt's. If not, this function assigns &op to -1,
which will cause the program to show the menu again instead of exiting.
No Return.
*/

void exitFunction(int &op, Library &library)
{
	bool done = false;
	do 
	{
		cout << "Deseja mesmo sair?(S/N) ";
		int choice = askForConfirmation();
		if (choice == 0) //Nao sair
		{
			op = -1;
			done = true;
		}
		else if (choice == 1) //Sair
		{
			library.saveUsers();
			library.saveBooks();
			done = true;
		}
	}
	while (!done);
}

/* readAndAddUser
Parameter:
Library &library
Prompts user for a User Name and adds a user with Name to &library
No return.
*/

void readAndAddUser(Library &library)
{
	bool validSize = false;
	bool cancel;
	bool done;
	do
	{
		string userName, tempName;
		istringstream iss;
		
		do
		{
			cancel = false;
			done = false;
			iss.clear();
			cout << "Nome do utilizador: ";
			getline(cin, tempName);
			iss.str(tempName);
			if (!(iss >> userName))
				cancel = askIfCancel();
			else done = true;
		}
		while (!done && !cancel);

		if(!cancel)
		{
			while (iss >> tempName)
				userName = userName + " " + tempName;
			if (userName.size() < MAXNAMELENGTH)
			{
				validSize = true;
				library.addUser(User(userName));
				cout << "\nUtilizador " << userName << " adicionado com sucesso!\n";
			}
			else
				cout << "\nO nome tem de ter menos de " << MAXNAMELENGTH << " caracteres!\n\n";
		}
	}
	while (!validSize && !cancel);
}

/* readFromConfig
reads */
void readFromConfig(string &usersFile, string &booksFile)
{
	ifstream file("config.cfg");
	if (!file.is_open())
	{
		file.close();
		ofstream outfile("config.cfg");
		outfile << "users.txt\n";
		outfile << "books.txt";
		outfile.close();
	}
	if (!file.is_open())
		file.open("config.cfg");
	getline(file, usersFile);
	getline(file, booksFile);
	file.close();
}

void readAndRequestBook(Library &library)
{
	if (library.getUserByID(1).getID() == 0)
		cout << "Nao existem utilizadores registados!\n";
	else if (library.getBookByID(1).getID() == 0)
		cout << "Nao existem livros na biblioteca!\n";
	else
	{
		IdentNum userID, bookID;
		bool done;
		bool cancel;
		User userTemp;
		library.showUsers();
		do
		{
			done = false;
			cancel = !askForID(userID, library, "\nID de Utilizador?: ", 1);
			userTemp = library.getUserByID(userID);
			if (!cancel)
			{
				if (userTemp.getID() == 0)
					cout << "ID de Utilizador Invalido!\n";
				else if (!userTemp.isActive())
					cout << "Utilizador nao esta activo!\n";
				else done = true;
			}
		}
		while (!done && !cancel);
		if (!cancel)
		{
			bool foundAny;
			library.showAvailableBooks(userTemp, foundAny);
			if (foundAny)
			{
				do
				{
					done = false;
					cancel = !askForID(bookID, library, "\nID de Livro?: ", 0);
					if (!cancel)
					{
						bool isBookRequested = bookIsRequested(userTemp, bookID);
						bool bookAvailable = false;
						Book bookTemp = library.getBookByID(bookID);
						if (bookTemp.getID() != 0)
							bookAvailable = true;
						else if (bookTemp.getNumAvailable() > 0)
							bookAvailable = true;
						if (isBookRequested)
							cout << "Esse livro ja foi requisitado pelo utilizador!\n";
						else if (!bookAvailable)
							cout << "Este livro nao esta disponivel!\n";
						else done = true;
					}
				}
				while (!done && !cancel);
				if (!cancel)
				{
					library.loanBook(userID, bookID);
					cout << "\nLivro requisitado com sucesso!\n";
				}
			}
		}
	}
}

void readAndSearchUsers(Library &library)
{
	bool cancel = false, done = false;
	istringstream iss;
	string search;
	if (library.getUserByID(1).getID() == 0)
		cout << "Nao existem utilizadores registados!\n";
	else
	{
		do
		{
			cout << "Escreva os termos pelos quais deseja pesquisar: ";
			getline(cin,search);
			iss.clear();
			iss.str(search);
			char temp;
			if (iss.get(temp))
			{
				if (temp != ' ')
				{
					done = true;
					iss.putback(temp);
				}
				else
					cout << "Input invalido!\n";
			}
			else
				if (iss.str() == "")
					cancel = askIfCancel();
				else
					cout << "Input invalido!\n";
		}
		while(!done && !cancel);
		if (!cancel)
		{
			string temp;
			iss >> search;
			while (iss >> temp)
				search = search + " " + temp;
			cout << '\n';
			library.showUsers(search);
		}
	}
}

void readAndSearchBooks(Library &library)
{
	if (library.getBookByID(1).getID() == 0)
		cout << "Nao existem livros na biblioteca!\n";
	else
	{
		bool cancel = false, done = false;	
		string search;
		istringstream iss;
		int option;
		do
		{
			cout << "Deseja pesquisar por: Autor(0) ou Titulo(1)? ";
			getline(cin, search);
			iss.clear();
			iss.str(search);
			if (!(iss >> option))
			{
				if (iss.str() == "")
					cancel = askIfCancel();
				else 
					cout << "Por favor insira uma opcao entre 0 e 1!\n";
			}
			else 
				if ((option==0) || (option==1))
					done = true;
				else
					cout << "Opcao Invalida!\n";
		} 
		while (!done && !cancel);
		if (!cancel)
		{
			done = false, cancel = false;
			do
			{
				cout << "\nEscreva os termos pelos quais deseja pesquisar: ";
				getline(cin,search);
				iss.clear();
				iss.str(search);
				char temp;
				if (iss.get(temp))
				{
					if (temp != ' ')
					{
						done = true;
						iss.putback(temp);
					}
					else
						cout << "Input invalido!\n";
				}
				else
					if (iss.str() == "")
						cancel = askIfCancel();
					else
						cout << "Input invalido!\n";
			}
			while(!done && !cancel);
			if (!cancel)
			{
				string temp;
				iss >> search;
				while (iss >> temp)
					search = search + " " + temp;
				library.showBooks(search, option);
			}
		}
	}
}

void readAndReturnBook(Library &library)
{
	if (library.getUserByID(1).getID() == 0)
		cout << "Nao existem utilizadores registados!\n";
	else if (library.getBookByID(1).getID() == 0)
		cout << "Nao existem livros na biblioteca!\n";
	else
	{
		IdentNum userID, bookID;
		bool done;
		bool cancel;
		User userTemp;
		library.showUsers();
		do
		{
			done = false;
			cancel = !askForID(userID, library, "\nID de Utilizador?: ", 1);
			userTemp = library.getUserByID(userID);
			if (!cancel)
			{
				if (userTemp.getID() == 0)
					cout << "ID de Utilizador Invalido!\n";
				else if (!userTemp.isActive())
					cout << "Utilizador nao esta activo!\n";
				else if (!userTemp.hasBooksRequested())
					cout << "Utilizador nao tem livros requisitados!\n";
				else done = true;
			}
		}
		while (!done && !cancel);
		if (!cancel)
		{
			library.showBooksOfUser(userTemp);
			do
			{
				done = false;
				cancel = !askForID(bookID, library, "\nID de Livro?: ", 0);
				if (!cancel)
				{
					bool isBookRequested = bookIsRequested(userTemp, bookID);
					if (!isBookRequested)
						cout << "Esse livro nao foi requisitado pelo utilizador!\n";
					else done = true;
				}
			}
			while (!done && !cancel);
			if (!cancel)
			{
				library.returnBook(userID, bookID);
				cout << "\nLivro devolvido com sucesso!\n";
			}
		}
	}
}

int numberOfDigits(int number)
{
	int i = 1;
	do
	{
		number = number / 10;
		if (number > 0)
			++i;
	}
	while (number > 0);
	return i;
}