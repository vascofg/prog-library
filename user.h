#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

#include "defs.h"

using namespace std;

class User {

private:
	static IdentNum numUsers; //total number of users - used to obtain ID of each new user
	IdentNum ID; // unique user identifier (unsigned integer)
	string name; // user name
	bool active; // only active users can request books
	vector<IdentNum> requestedBooks; // books presently loaned to the user

public:
	//constructors 
	User();
	User(string name);

	//get methods
	IdentNum getID() const;
	string getName() const;
	bool isActive() const;
	vector<IdentNum> getRequestedBooks() const;

	bool hasBooksRequested() const;	

	//set methods
	void setID(IdentNum userID);
	void setName (string userName);
	void setActive(bool status);
	void setRequestedBooks(const vector<IdentNum> &booksRequestedByUser);
	static void setNumUsers(IdentNum num);
	
	void borrowBook(IdentNum bookID);
	void returnBook(IdentNum bookID);
};

#endif