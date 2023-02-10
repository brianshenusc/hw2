#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"
#include "util.h"
#include <string>
#include <iostream>


class Movie : public Product {
	public:
		// constructor
		Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);
		// destructor
		~Movie();
		// accessor methods
		std::string getGenre();
		std::string getRating();
		std::set<std::string> keywords() const;
		// displays the movie's information
		std::string displayString() const;
		// returns the keywords of the movie
		void findKeywords(std::string str); 
		// outputs the information to a file
		void dump(std::ostream& os) const;

	private:
	// movie genre
		std::string genre_;
		// movie rating
		std::string rating_;
		// set of keywords
		std::set<std::string> keywords_;
};

#endif