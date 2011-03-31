#include "book.h"

Book::Book()
{
	setID(0);
	setTitle("");
	setAuthor("");
	setNumAvailable(0);
}

Book::Book(string bookTitle, string bookAuthor, unsigned int bookQuantity)
{
	setNumBooks(numBooks+1);
	setID(numBooks);
	setTitle(bookTitle);
	setAuthor(bookAuthor);
	setNumAvailable(bookQuantity);
}

void Book::setID(IdentNum bookID)
{
	ID=bookID;
}
void Book::setTitle(string bookTitle)
{
	title=bookTitle;
}
void Book::setAuthor(string bookAuthor)
{
	author=bookAuthor;
}
void Book::setNumAvailable(unsigned int numBooks)
{
	numAvailable=numBooks;
}
void Book::setNumBooks(IdentNum num)
{
	numBooks=num;
}
IdentNum Book::getID() const
{
	return ID;
}
string Book::getTitle() const
{
	return title;
}
string Book::getAuthor() const
{
	return author;
}
unsigned int Book::getNumAvailable() const
{
	return numAvailable;
}

void Book::loanBook()
{
	setNumAvailable(numAvailable - 1);
}

void Book::returnBook()
{
	setNumAvailable(numAvailable + 1);
}