#include "movie.h"
#include <iomanip>
#include "util.h"
#include <sstream>
using namespace std;

// constructor for the movie
Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) : Product(category, name, price, qty) {
	genre_ = genre;
	rating_ = rating;

	findKeywords(name);
	keywords_.insert(convToLower(genre_));
}
// destructor
Movie::~Movie() {

}
// retuns the genre
std::string Movie::getGenre() {
	return genre_;
}
// returns the rating
std::string Movie::getRating() {
	return rating_;
}
// outputs the book's information
std::string Movie::displayString() const {
	stringstream ss;
	double price = getPrice();
	ss << fixed << setprecision(2) << price;
	return getName() + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + ss.str() + " " + to_string(getQty()) + " left.";
}
// returns the set of keywords
std::set<std::string> Movie::keywords() const {
	return keywords_;	
}
// finds the keywords
void Movie::findKeywords(std::string str) {
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
// dumps the Movie's information into a file
void Movie::dump(std::ostream& os) const {
	os << convToLower(category_) << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}