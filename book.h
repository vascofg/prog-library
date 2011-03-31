#ifndef BOOK_H
#define BOOK_H

#include <string>

#include "defs.h"

using namespace std;

class Book {

private:
	static IdentNum numBooks; //total number of books - used to obtain ID of each new book
	IdentNum ID; // unique book identifier (unsigned integer)
	string title; // book title
	string author; // book author OR authors 
	unsigned int numAvailable; // number of available items with this title

public:
	//constructors
	Book();
	Book(string bookTitle, string bookAuthor, unsigned int bookQuantity);

	//get methods
	IdentNum getID() const;
	string getTitle() const;
	string getAuthor() const;
	unsigned int getNumAvailable() const;	

	//set methods
	void setID(IdentNum bookID);
	void setTitle(string bookTitle);
	void setAuthor(string bookAuthor);
	void setNumAvailable(unsigned int numBooks);
	static void setNumBooks(IdentNum num);

//	void addBooks(int bookQuantity);       //Nao foi precisa esta funçao
	void loanBook();
	void returnBook();
};

#endif