#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>

#include "defs.h"
#include "book.h"
#include "user.h"

using namespace std;

class Library {

private:
	vector<User> users; // all users that are registered or were registered in the library
	vector<Book> books; // all books that are registered or were registered in the library
	string filenameUsers; // name of the file where users are saved at the end of each program run
	string filenameBooks; // name of the file where books are saved at the end of each program run

public:
	// constructors
	Library();
	Library(string fileUsers, string fileBooks);

	// destructor
	~Library();

	// get functions
	User getUserByID(IdentNum userID) const;
	Book getBookByID(IdentNum bookID) const;

	// user management
	void addUser(User);
	void updateName(IdentNum userID, string userName);
	void updateActive(IdentNum userID, bool userActive);

	// book management
	void addBook(Book);

	// loaning management
	void loanBook(IdentNum userID, IdentNum bookID);
	void returnBook(IdentNum userID, IdentNum bookID);

	// file management methods
	void loadUsers();
	void loadBooks();
	void saveUsers();
	void saveBooks();

	// information display
	void showUsers() const;
	void showUsers(string str) const;
	void showBooks() const;
	void showBooks(string str, int op) const;            //
	void showAvailableBooks(User, bool &foundAny) const; //
	void showBooksOfUser(User) const;
};

#endif