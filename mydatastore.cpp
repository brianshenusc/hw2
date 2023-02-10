#include "mydatastore.h"
#include "util.h"
#include <string>
#include <vector>


using namespace std;


// Default constructor
MyDataStore::MyDataStore() {

}
// Destructor
MyDataStore::~MyDataStore() {
	// deletes the dynamically allocated users and products
	for(unsigned int i=0; i < userVec.size(); i++) {
		delete userVec[i];
	}
	for(unsigned int i=0; i < productVec.size(); i++) {
		delete productVec[i];
	}
}

/**
  * Adds a product to the data store
  */
void MyDataStore::addProduct(Product* p) {
	// adds to productVec
	productVec.push_back(p);
	// gets the keywords of the product that is being added and adds its name + the products with the keyword to keyProductMap
	std::set<std::string> currKeywords = p->keywords();
	typename std::set<std::string>::iterator it;
	for(it = currKeywords.begin(); it != currKeywords.end(); ++it) {
		if(keyProductMap.find(*it) == keyProductMap.end()) {
			std::set<Product*> pSet;
			pSet.insert(p);
			keyProductMap.insert(std::make_pair(*it, pSet));
		}
		// if the key already exists in the map, then the value is updated (adds p to end of the set)
		else {
			std::set<Product*> pSet;
			pSet = keyProductMap.at(*it);
			pSet.insert(p);
			keyProductMap[*it] = pSet;
		}
	}
}


/**
  * Adds a user to the data store
  */
void MyDataStore::addUser(User* u) {
	// adds the user to the end of userVec and makes a key pair for userCartsMap
	userVec.push_back(u);
	std::queue<Product*> q;
	userCartsMap.insert(std::make_pair(u->getName(), q));
}

/**
  * Performs a search of products whose keywords match the given "terms"
  *  type 0 = AND search (intersection of results for each term) while
  *  type 1 = OR search (union of results for each term)
  */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
	// does an AND search
	if(type == 0) {
		std::set<Product*> andTerms;
		// finds the product sets of the products that match the key words in terms
		for(unsigned int i=0; i < terms.size(); i++) {
			if(keyProductMap.find(terms[i]) != keyProductMap.end()) {
				if(andTerms.empty()) {
					andTerms = keyProductMap.at(terms[i]);
				}
				else {
					// makes an intersection of itself and the set containing the products
					andTerms = setIntersection(andTerms, keyProductMap.at(terms[i]));
				}
			}
		}
		// turns the set into a vector and returns it
		std::vector<Product*> andTermsVec(andTerms.begin(), andTerms.end());
		return andTermsVec;
	}
	// does an OR search
	else if(type == 1) {
		std::set<Product*> orTerms;
		// finds the product sets of the products that match the key words in terms
		for(unsigned int i=0; i < terms.size(); i++) {
			if(keyProductMap.find(terms[i]) != keyProductMap.end()) {
				// makes an union of itself and the set containing the products
				orTerms = setUnion(orTerms, keyProductMap.at(terms[i]));
			}
		}
		// turns the set into a vector and returns it
		std::vector<Product*> orTermsVec(orTerms.begin(), orTerms.end());
		return orTermsVec;
	}
	// returns an empty vector if wrong type is inputted
	std::vector<Product*> noTerms;
	return noTerms;
}

/**
  * Adds a product to the user's cart
  */
void MyDataStore::addToCart(std::string username, Product* p) {
	// converts the username to lower case and then adds the product to the correct user's cart
	username = convToLower(username);
	if(userCartsMap.find(username) != userCartsMap.end()) {
		std::queue<Product*> productQ = userCartsMap.at(username);
		productQ.push(p);
		userCartsMap[username] = productQ;
	}
	// prints "Invalid request" if the username does not match
	else {
		cout << "Invalid request" << endl;
	}
}

/**
  *  Buys the user's cart if they have enough money and there is enough in stock
  */
void MyDataStore::buyCart(std::string username) {
	username = convToLower(username);
	std::queue<Product*> productQ;
	if(userCartsMap.find(username) != userCartsMap.end()) {
		productQ = userCartsMap.at(username);
		for(unsigned int i=0; i < userVec.size(); i++) {
			if(userVec[i]->getName() == username) {
				std::queue<Product*> endCart;
				// while productQ is not empty, will check if the user has enough funds to buy the product
				// and will update user's balance and product quantity if so. 
				while(!productQ.empty()) {
					if(userVec[i]->getBalance() >= productQ.front()->getPrice() && productQ.front()->getQty() >= 1) {
						userVec[i]->deductAmount(productQ.front()->getPrice());
						productQ.front()->subtractQty(1);
						productQ.pop();
					}
					// otherwise, add the product to endCart since it was not bought
					else {
						endCart.push(productQ.front());
						productQ.pop();
					}
				}
				productQ = endCart;
			}
		}
		userCartsMap[username] = productQ;
	}
	else {
		cout << "Invalid username" << endl;
		return;
	}
}


/**
  *  View's the user's cart
  */
void MyDataStore::viewCart(std::string username) {
	username = convToLower(username);
	// if the given username is valid, will display the user's current cart
	if(userCartsMap.find(username) != userCartsMap.end()) {
		std::queue<Product*> cart = userCartsMap.at(username);
		int count = 1;
		while(!cart.empty()) {
			cout << "Item " << to_string(count) << endl;
			Product* first = cart.front();
			cout << first->displayString() << endl;
			cart.pop();
			count++;
		}
	}
	else {
		cout << "Invalid username" << endl;
	}
}

/**
  *  Accessor method that returns userVec
  */
std::vector<User*> MyDataStore::getUserVec() {
	return userVec;
}	
/**
  *  Accessor method that returns productVec
  */
std::vector<Product*> MyDataStore::getProductVec() {
	return productVec;
}

/**
  * Reproduce the database file from the current Products and User values
  */
void MyDataStore::dump(std::ostream& ofile) {
	ofile << "<products>" << endl;
	for(unsigned int i=0; i < productVec.size(); i++) {
		productVec[i]->dump(ofile);
	}
	ofile << "</products>\n<users>" << endl;
	for(unsigned int i=0; i < userVec.size(); i++) {
		userVec[i]->dump(ofile);
	}
	ofile << "</users>" << endl;
}