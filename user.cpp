#include "user.h"

User::User()
{
	setID(0);
	setName("");
	setActive(false);
}

User::User(string userName)
{
	setNumUsers(numUsers+1);
	setID(numUsers);
	setName(userName);
	setActive(true);
}

string User::getName() const
{
	return name;
}

IdentNum User::getID() const
{
	return ID;
}

bool User::isActive() const
{
	return active;
}

void User::setActive(bool status)
{
	active = status;
}

void User::setName(string userName)
{
	name = userName;
}

void User::setID(IdentNum userID)
{
	ID=userID;
}

void User::setNumUsers(IdentNum num)
{
	numUsers=num;
}

bool User::hasBooksRequested() const
{
	return (requestedBooks.size() > 0);
}

void User::setRequestedBooks(const vector<IdentNum> &booksRequestedByUser)
{
	requestedBooks = booksRequestedByUser;
}

void User::borrowBook(IdentNum bookID)
{
	vector<IdentNum> userBooks = requestedBooks;
	userBooks.push_back(bookID);
	setRequestedBooks(userBooks);	
}

vector<IdentNum> User::getRequestedBooks() const
{
	return requestedBooks;
}

void User::returnBook(IdentNum bookID)
{
	int vlen = requestedBooks.size() - 1;
	bool found = false;
	int i = 0;
	while (!found)
	{
		if (requestedBooks[i] == bookID)
			found = true;
		else ++i;
	}
	for (i; i < vlen; ++i)
	{
		IdentNum tempID = requestedBooks[i];
		requestedBooks[i] = requestedBooks[i+1];
		requestedBooks[i+1] = tempID;
	}
	requestedBooks.resize(vlen);
}
