#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include "util.h"
#include <string>
#include <iostream>


class Book : public Product {
public:
	// constructor
	Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author);
	// destructor
	~Book();
	// accessor methods
	std::string getISBN();
	std::string getAuthor();
	// prints out the book's information
	std::string displayString() const;
	// returns the keywords_ set
	std::set<std::string> keywords() const;
	// finds the keywords of the book
	void findKeywords(std::string str); 
	// outputs the information to a file
	void dump(std::ostream& os) const;
private:
	// isbn number
	std::string isbn_;
	// author
	std::string author_;
	// set of keywords
	std::set<std::string> keywords_;
	
};

#endif