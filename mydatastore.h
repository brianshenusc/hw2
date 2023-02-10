#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "util.h"
#include <string>
#include <set>
#include <vector>
#include <map>
#include <queue>


class MyDataStore : public DataStore {
public:
	MyDataStore();
	~MyDataStore();
	/**
    * Adds a product to the data store
    */
  void addProduct(Product* p);

  /**
    * Adds a user to the data store
    */
  void addUser(User* u);

  /**
    * Performs a search of products whose keywords match the given "terms"
    *  type 0 = AND search (intersection of results for each term) while
    *  type 1 = OR search (union of results for each term)
    */
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  /**
    * Reproduce the database file from the current Products and User values
    */
  void dump(std::ostream& ofile);
  /**
  * Adds a product to the user's cart
  */
  void addToCart(std::string username, Product* p);
  /**
  *  View's the user's cart
  */
  void viewCart(std::string username);
  /**
  *  Buys the user's cart if they have enough money and there is enough in stock
  */
  void buyCart(std::string username);
	/**
  *  Accessor method that returns userVec
  */
  std::vector<User*> getUserVec();
  /**
  *  Accessor method that returns productVec
  */
  std::vector<Product*> getProductVec();

private:
	std::vector<Product*> productVec;
	std::vector<User*> userVec;
  std::map<std::string, std::set<Product*>> keyProductMap; 
  std::map<std::string, std::queue<Product*>> userCartsMap; 
  
};


#endif