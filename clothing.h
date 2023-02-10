#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"
#include "util.h"
#include <string>
#include <iostream>

class Clothing : public Product {
	public:
		// constructor
		Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
		// destructor
		~Clothing();
		// accessor methods
		std::string getSize();
		std::string getBrand();
		std::set<std::string> keywords() const;
		// prints out the Clothing's information
		std::string displayString() const;
		// returns the keywords of the Clothing
		void findKeywords(std::string str);
		// outputs the information to a file
		void dump(std::ostream& os) const;

	private:
		// clothing size
		std::string size_;
		// clothing brand
		std::string brand_;
		// set of keywords
		std::set<std::string> keywords_;
};

#endif