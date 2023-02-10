#include "clothing.h"
#include "util.h"
#include <iomanip>
#include <sstream>
using namespace std;

// constructor for the Clothing
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) : Product(category, name, price, qty) {
	size_ = size;
	brand_ = brand;
	findKeywords(name);
	findKeywords(brand);
}
// destructor
Clothing::~Clothing() {

}
// returns the size
std::string Clothing::getSize() {
	return size_;
}
// returns the brand
std::string Clothing::getBrand() {
	return brand_;
}
// outputs the Clothing's information
std::string Clothing::displayString() const {
	stringstream ss;
	double price = getPrice();
	ss << fixed << setprecision(2) << price;
	return getName() + "\nSize: " + size_ + " Brand: " + brand_ + "\n" + ss.str() + " " + to_string(getQty()) + " left.";
}
// returns the set of keywords
std::set<std::string> Clothing::keywords() const {
	return keywords_;	
}
// finds the keywords
void Clothing::findKeywords(std::string str) {
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
// dumps the Clothing's information into a file
void Clothing::dump(std::ostream& os) const {
	os << convToLower(category_) << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;

}