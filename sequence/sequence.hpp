/*
	Authored by 
	Artur Sebastian Miller
	Nov, 2021
*/

#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

//dependencies
#include <iostream>
#include <stdexcept>

#ifdef DEBUG
const char* mln_beg = "[BEGIN]\n";
const char* mln_end = "[_END_]\n";
const char* exc_mrk = "[!EXC!]-";
const char* code_0  = "< Success.\n";
const char* code_1  = "< Invalid argument.\n";
const char* code_2  = "< Not found.\n";
const char* code_3  = "< Sequence empty.\n";
#endif

//templated friend workaround
template <typename Key, typename Info>
class Sequence;
template <typename Key, typename Info>
std::ostream& operator<<(std::ostream& str, const Sequence<Key,Info>& seq);

template <typename Key, typename Info>
class Sequence {
public:
	//(de)constructors
	Sequence(); //DONE
	Sequence(const Key& key, const Info& inf); //DONE
	Sequence(const Sequence<Key, Info>& src); //DONE
	~Sequence(); //DONE
	
	//operators
	bool operator==(const Sequence<Key, Info>& cmp) const; //DONE
	bool operator!=(const Sequence<Key, Info>& cmp) const; //DONE
	Sequence<Key, Info>& operator=(const Sequence<Key, Info>& src); //DONE
	Sequence<Key, Info> operator+(const Sequence<Key, Info>& src) const; //DONE
	Sequence<Key, Info>& operator+=(const Sequence<Key, Info>& src); //DONE
	friend std::ostream& operator<< <Key, Info>(std::ostream& str,
					 	    const Sequence<Key, Info>& seq); //DONE
			 	    
	//iterator
	class iterator; //DONE
	
	//insertion methods
	bool push_front(const Key& key, const Info& inf); //DONE
	bool push_back(const Key& key, const Info& inf); //DONE
	bool insert_after(const Key& key,  const Info& inf, 
			  const Key& what, int n_what = 1  ); //DONE
	bool insert_before(const Key& key,  const Info& inf, 
			   const Key& what, int n_what = 1  );  //DONE
	bool replace(const Key& key,   const Info& inf, 
		     const Key& what, int n_what = 1   ); //DONE
	
	//removal methods
	bool purge(); //DONE
	Info pop_front(); //DONE
	Info pop_back(); //DONE
	bool remove_after(const Key& what, int n_what = 1); //DONE
	bool remove_before(const Key& what, int n_what = 1); //DONE
	bool remove(const Key&  what, int n_what = 1); //DONE
	
	//getter methods
	bool empty() const; //DONE
	unsigned int size() const; //DONE
	void print() const; //DONE
	Info get_info(const Key& key, int n_key = 1) const; //DONE
	iterator begin() const; //DONE
	iterator end() const; //DONE
	
	//utility methods
	bool clear_info(const Info& filler); //DONE
	bool swap(const Key& what, const Key& dest,
		  int n_what = 1,  int n_dest = 1  ); //DONE
	
private:
	//storage members
	unsigned int length;
	struct Element {
		Key key;
		Info info;
		Element* next;
	};
	Element* head;
	//helper methods
	struct SearchResult {
		Element* predecessor;
		Element* target;
		Element* successor;
	};
	SearchResult _find(const Key& key, int n_key = 1) const; //DONE
	bool _clone(const Sequence<Key, Info>& src); //DONE
};

template <typename Key, typename Info>
class Sequence<Key, Info>::iterator {
public:
	iterator(const Sequence<Key, Info>& of); //DONE
	iterator(const iterator& src); //DONE
	//uses default destructor
	
	friend Sequence<Key, Info>;
	iterator& operator=(const iterator& src); //DONE
	iterator& operator++(); //DONE
	iterator operator++(int); //DONE
	Info operator*() const; //DONE
	bool operator==(const iterator& itr) const; //DONE
	bool operator!=(const iterator& itr) const; //DONE
	
	//CUSTOM GETTERS
	Key key() const; //DONE
	Info info() const; //DONE
	bool end() const; //DONE
private:
	iterator(); //DONE
	Element* current;
};

template <typename Key, typename Info>
Sequence<Key, Info> join(const Sequence<Key, Info>& left,
			 const Sequence<Key, Info>& rght,
			 Info (*aggregator)(const Info&, const Info&));

#include "sequence_impl.hpp"

#endif
