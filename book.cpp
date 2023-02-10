#include "book.h"
#include "util.h"
#include <sstream>
#include <cmath>
#include <iomanip>
using namespace std;

// Constructor for book 
Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) : Product(category, name, price, qty) {
	isbn_ = isbn;
	author_ = author;
	findKeywords(name);
	findKeywords(author_);
	keywords_.insert(convToLower(isbn_));
}
// destructor
Book::~Book() {

}
// returns the ISBN
std::string Book::getISBN() {
	return isbn_;
}
// returns the author
std::string Book::getAuthor() {
	return author_;
}
// displays the Book
std::string Book::displayString() const {
	stringstream ss;
	double price = getPrice();
	ss << fixed << setprecision(2) << price;
	return getName() + "\nAuthor: " + author_ + " ISBN: " + isbn_ + "\n" + ss.str() + " " + to_string(getQty()) + " left.";
}
// returns the set of keywords
std::set<std::string> Book::keywords() const {
	return keywords_;	
}


// finds the keywords 
void Book::findKeywords(std::string str) {
	// gets a set of the string separated at whitespace or punctuation and adds it to keywords_ if its 2 characters or larger
	std::set<std::string> sep = parseStringToWords(str);
	typename std::set<std::string>::iterator it;
	for(it = sep.begin(); it != sep.end(); ++it) {
    std::string lower = convToLower(*it);
  	if(lower.size() >= 2) {
			keywords_.insert(lower);
		}
	}

}
// dumps the Book's information into a file
void Book::dump(std::ostream& os) const {
	os << convToLower(category_) << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;

}