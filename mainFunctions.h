#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H 

#include <string>
#include "library.h"

void readAndSetUserState(Library &library);

void readAndAddBook(Library &library);

bool bookIsRequested(User userTemp, IdentNum bookID);

void readOp(int &op);

int askForConfirmation();

int numberOfDigits(int number);

void exitFunction(int &op, Library &library);

bool askIfCancel();

bool askForID(IdentNum &ID, Library &library, string askMessage);

void readAndAddUser(Library &library);

void readFromConfig(string &usersFile, string &booksFile);

void readAndRequestBook(Library &library);

void readAndReturnBook(Library &library);

bool bookIsRequested(vector<IdentNum> v, IdentNum bookID);

void readAndSearchUsers(Library &library);

void readAndSearchBooks(Library &library);

void showBooksRequestedByUser(User);

#endif
