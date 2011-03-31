#include "library.h"
#include "mainFunctions.h"
#include <cstddef>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

Library::Library()
{
	filenameBooks = "";
	filenameUsers = "";
}

Library::Library(string fileUsers, string fileBooks)
{
	filenameBooks = fileBooks;
	filenameUsers = fileUsers;
}

Library::~Library()
{
	saveBooks();
	saveUsers();
}

User Library::getUserByID(IdentNum userID) const
{
	if (userID > users.size() || userID <= 0)
		return User();
	else return users[userID-1];
}

void Library::addUser(User usertemp)
{
	users.push_back(usertemp);
}

void Library::addBook(Book booktemp)
{
	books.push_back(booktemp);
}

void Library::showUsers() const
{
	IdentNum i;
	if (users.size()==0)
		cout << "Nao existem utilizadores registados.\n";
	else
	{
		cout << "#### Utilizadores ####\n";
		cout << "--------------------------------------------------------------- \n";
		cout << "| ID   | Nome                                       | Activo  |\n";
		cout << "--------------------------------------------------------------- \n";
		cout << setiosflags(ios::left);
		for (i=1;i<=users.size();i++)
		{
			User userTemp=getUserByID(i);
			cout << "| " << setw(MAXIDLENGTH) << userTemp.getID() << "| " << setw(MAXNAMELENGTH) << userTemp.getName() << "| ";
			if (userTemp.isActive())
				cout << setw(8) << "Sim" << "|\n";
			else cout << setw(8) << "Nao" << "|\n";
		}
		cout << resetiosflags(ios::left);
		cout << "--------------------------------------------------------------- \n";
	}
}

void Library::showUsers(string search) const
{
	IdentNum i;
	User userTemp;
	vector <IdentNum> usersFound;
	for (i=1;i<=users.size();i++)
	{
		userTemp=getUserByID(i);
		string userName = userTemp.getName();
		size_t counter = 0;		// conta as vezes seguidas que detecta chars iguais
		bool found = false;		// quando counter for igual a search.size() found = true
		for (size_t k = 0; k < userName.size() && !found; ++k) 
		{
			if (counter < search.size())
			{
				char temp1 = toupper(search[counter]);
				char temp2 = toupper(userName[k]);
				if (temp1 == temp2)
					if (temp1 == ' ')
						if (counter > 0)
							counter++;
						else counter = 0;
					else counter++; 
				else counter = 0;
			}
			if (counter == search.size())
			{
				found = true;
			}
		}
		if (found)
			usersFound.push_back(userTemp.getID());
	}
	if (usersFound.size()==0)
		cout << "Nao foi encontrado nenhum utilizador com esses termos.\n";
	else
	{
		cout << "#### Utilizadores ####\n";
		cout << "--------------------------------------------------------------- \n";
		cout << "| ID   | Nome                                       | Activo  |\n";
		cout << "--------------------------------------------------------------- \n";
		cout << setiosflags(ios::left);
		for(size_t k = 0;k<usersFound.size();k++)
		{
			i = usersFound[k];
			User userTemp=getUserByID(i);
			cout << "| " << setw(MAXIDLENGTH) << userTemp.getID() << "| " << setw(MAXNAMELENGTH) << userTemp.getName() << "| ";
			if (userTemp.isActive())
				cout << setw(8) << "Sim" << "|\n";
			else cout << setw(8) << "Nao" << "|\n";
		}
		cout << resetiosflags(ios::left);
		cout << "--------------------------------------------------------------- \n";
	}
}

Book Library::getBookByID(IdentNum bookID) const
{
	if (bookID > books.size() || bookID <= 0)
		return Book();
	else return books[bookID-1];
}

void Library::showBooks() const
{
	IdentNum i;
	if (books.size()==0)
		cout << "Nao existem livros registados.\n";
	else
	{
		cout << "#### Livros ####\n";
		cout << "---------------------------------------------------------------------------- \n";
		cout << "| ID   | Titulo                        | Autor                    | Disp.  |\n";
		cout << "---------------------------------------------------------------------------- \n";
		cout << setiosflags(ios::left);
		for (i=1;i<=books.size();i++)
		{
			Book bookTemp = getBookByID(i);
			cout << "| " << setw(MAXIDLENGTH) << bookTemp.getID() << "| " << setw(MAXTITLELENGTH) << bookTemp.getTitle() << "| " << setw(MAXAUTHORLENGTH) << bookTemp.getAuthor() << "| " << setw(MAXQUANTITYLENGTH) << bookTemp.getNumAvailable() << "|\n";
		}
		cout << resetiosflags(ios::left);
		cout << "---------------------------------------------------------------------------- \n";
	}
}

void Library::showBooks(string search, int option) const
{
	IdentNum i;
	vector <IdentNum> booksFound;
	for (i=1;i<=books.size();i++)
	{
		string searchString;
		Book bookTemp=getBookByID(i);
		if(option==0)
			searchString = bookTemp.getAuthor();
		else
			searchString = bookTemp.getTitle();
		size_t counter = 0;		// conta as vezes seguidas que detecta chars iguais
		bool found = false;		// quando counter for igual a search.size() found = true
		for (size_t k = 0; k < searchString.size() && !found; ++k) 
		{
			if (counter < search.size())
			{
				char temp1 = toupper(search[counter]);
				char temp2 = toupper(searchString[k]);
				if (temp1 == temp2)
					if (temp1 == ' ')
						if (counter > 0)
							counter++;
						else counter = 0;
					else counter++; 
				else counter = 0;
			}
			if (counter == search.size())
			{
				found = true;
			}
		}
		if (found)
			booksFound.push_back(bookTemp.getID());
	}
	if (booksFound.size()==0)
		cout << "\nNao foi encontrado nenhum livro com esses termos.\n";
	else
	{
		cout << "\n#### Livros ####\n";
		cout << "----------------------------------------------------------------------------\n";
		cout << "| ID   | Titulo                        | Autor                    | Disp.  |\n";
		cout << "----------------------------------------------------------------------------\n";
		cout << setiosflags(ios::left);
		for(size_t k = 0;k<booksFound.size();k++)
		{
			i = booksFound[k];
			Book bookTemp=getBookByID(i);
			cout << "| " << setw(MAXIDLENGTH) << bookTemp.getID() << "| " << setw(MAXTITLELENGTH) << bookTemp.getTitle() << "| " << setw(MAXAUTHORLENGTH) << bookTemp.getAuthor() << "| " << setw(MAXQUANTITYLENGTH) << bookTemp.getNumAvailable() << "|\n";
		}
		cout << resetiosflags(ios::left);
		cout << "----------------------------------------------------------------------------\n";
	}
}

void Library::loadUsers()
{
	ifstream infile(filenameUsers.c_str());
	if (!infile.is_open())
	{
		cout << "O ficheiro " << filenameUsers << " nao existe. A criar...\n";
		saveUsers();
		infile.open(filenameUsers.c_str());
	}
	if (infile.fail())
	{
		cout << "Erro ao ler o ficheiro "<< filenameUsers << "!";
		return;
	}
	bool done = false;
	string tempStr;
	istringstream Line;
	do
	{
		char tempChar;
		getline(infile,tempStr);
		Line.clear();
		Line.str(tempStr);
		Line >> tempChar;
		if (tempChar == '\\')
		{
			IdentNum userID, bookID;
			string userName;
			bool userActive;
			bool noName = true;
			getline(infile,tempStr);//userID
			Line.clear();
			Line.str(tempStr);
			Line >> userID;
			getline(infile,tempStr);//userName
			Line.clear();
			Line.str(tempStr);
			while (Line >> tempStr)
			{
				if (noName)
				{
					userName = tempStr;
					noName = false;
				}
				else userName = userName + " " + tempStr;
			}
			getline(infile,tempStr);//userActive
			Line.clear();
			Line.str(tempStr);
			Line >> userActive;
			getline(infile,tempStr);//booksRequested
			Line.clear();
			Line.str(tempStr);			
			User userTemp(userName);
			Line >> bookID;
			if (bookID != 0)
			{
				userTemp.borrowBook(bookID);
				while (Line >> bookID)
					userTemp.borrowBook(bookID);
			}
			userTemp.setID(userID);
			userTemp.setActive(userActive);
			users.push_back(userTemp);
		}
		else 
		{
			done = true;
			infile.close();
		}
	}
	while (!done);
}

void Library::updateName(IdentNum userID, string userName)
{
	User userTemp = getUserByID(userID);
	userTemp.setName(userName);
	users[userID-1]=userTemp;
}

void Library::updateActive(IdentNum userID, bool userActive)
{
	User userTemp = getUserByID(userID);
	userTemp.setActive(userActive);
	users[userID-1]=userTemp;
}

void Library::loanBook(IdentNum userID, IdentNum bookID)
{
	Book bookTemp = getBookByID(bookID);
	bookTemp.loanBook();
	books[bookID-1] = bookTemp;
	User userTemp = getUserByID(userID);
	userTemp.borrowBook(bookID);
	users[userID-1]=userTemp;
}

void Library::returnBook(IdentNum userID, IdentNum bookID)
{
	Book bookTemp = getBookByID(bookID);
	bookTemp.returnBook();
	books[bookID-1] = bookTemp;
	User userTemp = getUserByID(userID);
	userTemp.returnBook(bookID);
	users[userID-1] = userTemp;
}

void Library::saveUsers()
{
	ofstream outfile;
	outfile.open(filenameUsers.c_str());
	for (size_t i = 0; i < users.size(); ++i)
	{
		User userTemp = users[i];
		outfile << "\\----------- User (ID / Name / State(1-Active; 0-Inactive) / IDs of Books Requested) ------------\\\n";
		outfile << (i + 1)						<< "\n";
		outfile << userTemp.getName() << "\n";
		outfile << userTemp.isActive() << "\n";
		vector<IdentNum> tempBookIDs = userTemp.getRequestedBooks();
		if (tempBookIDs.size() == 0)
			outfile << 0;
		else 
			for (size_t k = 0; k < tempBookIDs.size(); ++k)
				outfile << tempBookIDs[k] << " ";
		outfile << "\n";
	}
	outfile		<< "---------------------------------------- END OF FILE ---------------------------------------------";
	outfile.close();
}

void Library::loadBooks()
{
	ifstream infile(filenameBooks.c_str());
	if (!infile.is_open())
	{
		cout << "O ficheiro " << filenameBooks << " nao existe. A criar...\n";
		saveBooks();
		infile.open(filenameBooks.c_str());
	}
	if (infile.fail())
	{
		cout << "Erro ao ler o ficheiro "<< filenameBooks << "!";
		return;
	}
	bool done = false;
	string tempStr;
	istringstream Line;
	do
	{
		char tempChar;
		getline(infile,tempStr);
		Line.clear();
		Line.str(tempStr);
		Line >> tempChar;
		if (tempChar == '\\')
		{
			IdentNum bookID;
			string bookTitle;
			string bookAuthor;
			int bookQuantity;
			getline(infile,tempStr);//bookID
			Line.clear();
			Line.str(tempStr);
			Line >> bookID;
			getline(infile,tempStr);//bookQuantity
			Line.clear();
			Line.str(tempStr);
			Line >> bookQuantity;
			getline(infile,tempStr);//bookTitle
			Line.clear();
			Line.str(tempStr);
			bool noString=true;
			while (Line >> tempStr)
			{
				if (noString)
				{
					bookTitle = tempStr;
					noString = false;
				}
				else bookTitle = bookTitle + " " + tempStr;
			}
			getline(infile,tempStr);//bookAuthor
			Line.clear();
			Line.str(tempStr);
			noString=true;
			while (Line >> tempStr)
			{
				if (noString)
				{
					bookAuthor = tempStr;
					noString = false;
				}
				else bookAuthor = bookAuthor + " " + tempStr;
			}
			Book bookTemp(bookTitle, bookAuthor, bookQuantity);
			bookTemp.setID(bookID);
			books.push_back(bookTemp);
		}
		else 
		{
			done = true;
			infile.close();
		}
	}
	while (!done);
}

void Library::saveBooks()
{
	ofstream outfile;
	outfile.open(filenameBooks.c_str());
	for (size_t i = 0; i < books.size(); ++i)
	{
		Book bookTemp = books[i];
		outfile << "\\----------- Book (ID / Number of units Available / Title / Author) ------------\\\n"; 
		outfile << (i + 1)						<< "\n";
		outfile << bookTemp.getNumAvailable()	<< "\n";
		outfile << bookTemp.getTitle()			<< "\n";
		outfile << bookTemp.getAuthor()			<< "\n";
	}
		outfile << "------------------------------ END OF FILE --------------------------------------";
	outfile.close();
}

void Library::showAvailableBooks(User userTemp, bool &foundAny) const
{
	cout << '\n';
	foundAny = false;
	IdentNum i;
	vector <IdentNum> booksFound;
	if (books.size()==0)
		cout << "Nao existem livros registados.";
	else
	{
		for (i=1;i<=books.size();i++)
		{
			Book bookTemp = getBookByID(i);
			if(bookTemp.getNumAvailable()!=0 && !bookIsRequested(userTemp, i))
			{
				foundAny = true;
				booksFound.push_back(bookTemp.getID());
			}
		}
	}
	if (!foundAny)
		cout << "Todos os livros da biblioteca ja foram requisitados!";
	else
	{
		cout << "#### Livros ####\n";
		cout << "---------------------------------------------------------------------------- \n";
		cout << "| ID   | Titulo                        | Autor                    | Disp.  |\n";
		cout << "---------------------------------------------------------------------------- \n";
		cout << setiosflags(ios::left);
		for(size_t k = 0;k<booksFound.size();k++)
		{
			i = booksFound[k];
			Book bookTemp = books[i-1];
			cout << "| " << setw(MAXIDLENGTH) << bookTemp.getID() << "| " << setw(MAXTITLELENGTH) << bookTemp.getTitle()  << "| " << setw(MAXAUTHORLENGTH) << bookTemp.getAuthor() << "| " << setw(MAXQUANTITYLENGTH) << bookTemp.getNumAvailable() << "|\n";
		}
		cout << resetiosflags(ios::left);
		cout << "---------------------------------------------------------------------------- \n";
	}
		
}

void Library::showBooksOfUser(User userTemp) const
{
	vector<IdentNum> v = userTemp.getRequestedBooks();
	cout << '\n';
	if (!userTemp.hasBooksRequested())
		cout << "O utilizador nao requisitou nenhum livro!";
	else 
	{
		cout << "#### Livros ####\n";
		cout << "----------------------------------------------------------------------------\n";
		cout << "| ID   | Titulo                        | Autor                    | Disp.  |\n";
		cout << "----------------------------------------------------------------------------\n";
		cout << setiosflags(ios::left);
		for (size_t i = 0; i < v.size(); ++i)
		{
			Book bookTemp = getBookByID(v[i]);
			cout << "| " << setw(MAXIDLENGTH) << bookTemp.getID() << "| " << setw(MAXTITLELENGTH) << bookTemp.getTitle() << "| " << setw(MAXAUTHORLENGTH) << bookTemp.getAuthor() << "| " << setw(MAXQUANTITYLENGTH) << bookTemp.getNumAvailable() << "|\n";
		}
		cout << resetiosflags(ios::left);
		cout << "-----------------------------------------------------------------------------\n";
	}
}
