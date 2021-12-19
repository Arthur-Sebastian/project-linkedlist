/*
	Authored by 
	Artur Sebastian Miller
	Nov, 2021
*/

#include "sequence.hpp"

/*
	(DE)CONSTRUCTORS
*/

template<typename Key, typename Info>
Sequence<Key, Info>::Sequence() {
	#ifdef DEBUG 
	std::cout << "[C_DEFLT]-";
	#endif
	head = nullptr;
	length = 0;
	#ifdef DEBUG 
	std::cout << "< Success.\n";
	#endif
}

template<typename Key, typename Info>
Sequence<Key, Info>::Sequence(const Key& key, const Info& inf) {
	#ifdef DEBUG 
	std::cout << "[C_INIT_]-";
	#endif
	head = nullptr;
	length = 0;
	push_front(key, inf);
	//debug output handled by push_front
}

template<typename Key, typename Info>
Sequence<Key, Info>::Sequence(const Sequence<Key, Info>& src) {
	#ifdef DEBUG
	std::cout << "[C_COPY_]-" << mln_beg;
	#endif
	//initialize empty list first
	head = nullptr;
	length = 0;
	//run the clone helper on this object
	_clone(src);
	#ifdef DEBUG
	std::cout << "[C_COPY_]-" << mln_end;
	#endif
}

template<typename Key, typename Info>
Sequence<Key, Info>::~Sequence() {
	#ifdef DEBUG
	std::cout << "[D_DEFLT]-";
	#endif
	purge();
	//debug output handled by purge
}

/*
	OPERATORS
*/

template<typename Key, typename Info>
bool Sequence<Key, Info>::operator==(const Sequence<Key, Info>& cmp) const {
	//check lengths first
	if(length != cmp.length) {
		return false;
	}
	//then start comparing elements
	Element* it1 = head;
	Element* it2 = cmp.head;
	while(it1 != nullptr) {
		if(it1 -> key != it2 -> key ||
		   it1 -> info != it2 -> info) {
		   return false;
		}
		it1 = it1 -> next;
		it2 = it2 -> next;
	}
	//loop exited without mismatches
	return true;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::operator!=(const Sequence<Key, Info>& cmp) const {
	return !(*this == cmp);
}

template<typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator=(const Sequence<Key, Info>& src) {
	_clone(src);
	return *this;
}

template<typename Key, typename Info>
Sequence<Key, Info> Sequence<Key, Info>::operator+(const Sequence<Key, Info>& src) const {
	Sequence<Key, Info> newSequence(*this);
	Element* current = src.head;
	while(current != nullptr) {
		newSequence.push_back(current -> key, current -> info);
		current = current -> next;
	}
	return newSequence;
}

template<typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator+=(const Sequence<Key, Info>& src) {
	*this = *this + src;
	return *this;
}

template<typename Key, typename Info>
std::ostream& operator<< (std::ostream& str, const Sequence<Key, Info>& seq) {
	typename Sequence<Key, Info>::Element* current = seq.head;
	while(current != nullptr) {
		str << '[' << current -> key
		<< "] " << current -> info << "\n";
		current = current -> next;
	}
	return str;
}

/*
	ITERATOR METHODS AND OPERATORS
*/
template<typename Key, typename Info>
Sequence<Key, Info>::iterator::iterator() {
	current = nullptr;
}

template<typename Key, typename Info>
Sequence<Key, Info>::iterator::iterator(const Sequence<Key, Info>& of) {
	current = of.head;
}

template<typename Key, typename Info>
Sequence<Key, Info>::iterator::iterator(const iterator& src) {
	current = src.current;
}

template<typename Key, typename Info>
typename Sequence<Key,Info>::iterator&
Sequence<Key, Info>::iterator::operator=(const iterator& src) {
	current = src.current;
	return *this;
}

template<typename Key, typename Info>
//prefix
typename Sequence<Key, Info>::iterator& 
Sequence<Key, Info>::iterator::operator++() {
	if(current != nullptr)
		current = current -> next;
	else 
		throw std::out_of_range("Iterator out of bounds");
	return *this;
}

template<typename Key, typename Info>
//postfix
typename Sequence<Key, Info>::iterator
Sequence<Key, Info>::iterator::operator++(int) {
	iterator prev(*this);
	++(*this);
	return prev;
}

template<typename Key, typename Info>
Info Sequence<Key, Info>::iterator::operator*() const {
	if(current != nullptr)
		return current -> info;
	else
		throw std::domain_error("Iterator not valid");
		
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::iterator::operator==(const iterator& cmp) const {
	return current == cmp.current;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::iterator::operator!=(const iterator& cmp) const {
	return current != cmp.current;
}

template<typename Key, typename Info>
Key Sequence<Key, Info>::iterator::key() const {
	if(current != nullptr)
		return current -> key;
	else return Key();
}

template<typename Key, typename Info>
Info Sequence<Key, Info>::iterator::info() const {
	if(current != nullptr)
		return current -> info;
	else return Info();
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::iterator::end() const {
	return (current == nullptr);
}

/*
	INSERTION METHODS
*/

template<typename Key, typename Info>
bool Sequence<Key, Info>::push_front(const Key& key, const Info& inf) {
	#ifdef DEBUG
	std::cout << "[M_PSFRN]-";
	#endif
	//add new element to the front
	Element* temp;
	try {
		temp = new Element({key, inf, nullptr});
	}
	//if memory allocation fails notify user
	catch(const std::exception& exc) {
		#ifdef DEBUG
		std::cout << exc_mrk
			  << "< " << exc.what() << "\n";
		#endif
		return false;
	}
	//adding to non-empty list case
	if(!empty()) {
		temp -> next = head;
		head = temp;
	}
	//first sequence element case
	else {
		head = temp;
	}
	length++;
	#ifdef DEBUG
	std::cout << code_0;
	#endif
	return true;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::push_back(const Key& key, const Info& inf) {
	#ifdef DEBUG
	std::cout << "[M_PSBCK]-";
	#endif
	//add new element to the back
	Element* temp;
	try {
		temp = new Element({key, inf, nullptr});
	}
	catch(const std::exception& exc) {
		#ifdef DEBUG
		std::cout << exc_mrk
			  << "< " << exc.what() << "\n";
		#endif
		return false;
	}
	//adding to non-empty list case
	if(!empty()) {
		Element* tail = head;
		while(tail -> next != nullptr) {
			tail = tail -> next;
		}
		tail -> next = temp;
	}
	//first sequence element case
	else {
		head = temp;
	}
	length++;
	#ifdef DEBUG
	std::cout << code_0;
	#endif
	return true;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::insert_after(const Key& key,  const Info& inf, 
		  		       const Key& what, int n_what      ) {
	#ifdef DEBUG
	std::cout << "[M_INSAF]-";
	#endif
	//now try finding the element to insert after
	SearchResult item = _find(what, n_what);
	if(item.target == nullptr) {
		return false;
	}
	try {
		item.target -> next = new Element({key, inf, item.target -> next});
	}
	catch(const std::exception& exc) {
		#ifdef DEBUG
		std::cout << exc_mrk
			  << "< " << exc.what() << "\n";
		#endif
		return false;
	}
	length++;
	return true;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::insert_before(const Key& key,  const Info& inf, 
		  		        const Key& what, int n_what      ) {
	#ifdef DEBUG
	std::cout << "[M_INSBF]-";
	#endif
	//now try finding the element to insert after
	SearchResult item = _find(what, n_what);
	if(item.predecessor == nullptr) {
		//check if search was successful
		if(item.target == nullptr)
			return false;
		//if it was push front
		push_front(key, inf);
		return true;
	}
	try {
		item.predecessor -> next = new Element({key, inf, item.predecessor -> next});
	}
	catch(const std::exception& exc) {
		#ifdef DEBUG
		std::cout << exc_mrk
			  << "< " << exc.what() << "\n";
		#endif
		return false;
	}
	length++;
	return true;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::replace(const Key& key,   const Info& inf, 
		     		  const Key& what, int n_what       ) {
	#ifdef DEBUG
	std::cout << "[M_REPLC]-";
	#endif
	//try finding
	SearchResult item = _find(what, n_what);
	if(item.target == nullptr) {
		return false;
	}
	item.target -> key = key;
	item.target -> info = inf;
	return true;
}

/*
	REMOVAL METHODS
*/

template<typename Key, typename Info>
bool Sequence<Key, Info>::purge() {
	#ifdef DEBUG
	std::cout << "[M_PURGE]-";
	#endif
	//check if sequence is empty
	if(empty()) {
		#ifdef DEBUG
		std::cout << code_3;
		#endif
		return false;
	}
	//iterate through all elements and deallocate
	Element* current = head;
	Element* next;
	while(current != nullptr){
		next = current -> next;
		delete current;
		current = next;
	}
	//mark sequence as empty again
	head = nullptr;
	length = 0;
	#ifdef DEBUG
	std::cout << code_0;
	#endif
	return true;
}

template<typename Key, typename Info>
Info Sequence<Key, Info>::pop_front()
{
	#ifdef DEBUG
	std::cout << "[M_PPFRN]-";
	#endif
	//check for empty list
	if(empty()) {
		#ifdef DEBUG
		std::cout << code_3;
		#endif
		return Info();
	}
	//otherwise delete head and stitch
	Element* newHead = head -> next;
	Info temp = head -> info;
	delete head;
	head = newHead;
	length--;
	#ifdef DEBUG
	std::cout << code_0;
	#endif
	return temp;
}

template<typename Key, typename Info>
Info Sequence<Key, Info>::pop_back()
{
	#ifdef DEBUG
	std::cout << "[M_PPBCK]-";
	#endif
	//check for empty list
	if(empty()) {
		#ifdef DEBUG
		std::cout << code_3;
		#endif
		return Info();
	}
	//remove the end
	Element* current = head;
	Element* previous = nullptr;
	while(current -> next != nullptr) {
		previous = current;
		current = current -> next;
	}
	Info temp = current -> info;
	delete current;
	previous -> next = nullptr;
	//update length	
	length--;
	#ifdef DEBUG
	std::cout << code_0;
	#endif
	return temp;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::remove_after(const Key&  what, int n_what) {
	#ifdef DEBUG
	std::cout << "[M_RMAFT]-";
	#endif
	//perform a search for an element and its predecessor
	SearchResult result = _find(what, n_what);
	//check if search was successful
	if(result.successor == nullptr) {
		return false;
	}
	//remove and stitch list
	else {
		Element* next = result.successor -> next;
		delete result.successor;
		result.target -> next = next;
	}
	//update length
	length--;
	return true;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::remove_before(const Key&  what, int n_what) {
	#ifdef DEBUG
	std::cout << "[M_RMBEF]-";
	#endif
	//perform a search for an element and its predecessor
	SearchResult result = _find(what, n_what);
	//check if search was successful
	if(result.predecessor == nullptr) {
		return false;
	}
	//head case
	if(result.predecessor == head) {
		pop_front();
		return true;
	}
	//find element before predecessor
	Element* current = head;
	while(current != nullptr) {
		if(current -> next == result.predecessor) {
			break;
		}
		current = current -> next;
	}
	//remove and stitch list
	delete result.predecessor;
	current -> next = result.target;
	//update length
	length--;
	return true;
}


template<typename Key, typename Info>
bool Sequence<Key, Info>::remove(const Key&  what, int n_what) {
	#ifdef DEBUG
	std::cout << "[M_REMOV]-";
	#endif
	//perform a search for an element and its predecessor
	SearchResult result = _find(what, n_what);
	//check if search was successful
	if(result.target == nullptr) {
		return false;
	}
	//remove and stitch list
	else {
		delete result.target;
		if(result.predecessor != nullptr)
			result.predecessor -> next = result.successor;
		else
			head = result.successor;
	}
	//update length	
	length--;
	return true;
}

/*
	GETTER METHODS
*/

template<typename Key, typename Info>
bool Sequence<Key, Info>::empty() const {
	return (head == nullptr && !length);
}

template<typename Key, typename Info>
unsigned int Sequence<Key, Info>::size() const {
	return length;
}

template<typename Key, typename Info>
Info Sequence<Key, Info>::get_info(const Key& key, int n_key) const {
	#ifdef DEBUG
	std::cout << "[M_GTINF]-";
	#endif
	//otherwise proceed to search
	SearchResult result = _find(key, n_key);
	if(result.target != nullptr) return result.target -> info;
	return Info();
}

template<typename Key, typename Info>
void Sequence<Key, Info>::print() const {
	#ifdef DEBUG
	std::cout << "[M_PRINT]-" << mln_beg;
	#endif
	Element* current = head;
	//check if sequence is empty	
	if(empty()) {
		#ifdef DEBUG
		std::cout << "[M_PRINT]-< ";
		#endif
		std::cout << "Sequence empty!\n";
		#ifdef DEBUG
		std::cout << "[M_PRINT]-" << mln_end;
		#endif
		return;
	}
	//iterate through all elements printing
	while(current != nullptr) {
		#ifdef DEBUG
		std::cout << "[M_PRINT]-< ";
		#endif
		std::cout << "Key ";
		std::cout << current -> key << ": ";
		std::cout << current -> info << std::endl;
		current = current -> next;
	}
	#ifdef DEBUG
	std::cout << "[M_PRINT]-" << mln_end;
	#endif
}

template<typename Key, typename Info>
typename Sequence<Key, Info>::iterator
Sequence<Key, Info>::begin() const {
	//return a new iterator for the list
	iterator itr(*this);
	return itr;	
}

template<typename Key, typename Info>
typename Sequence<Key, Info>::iterator
Sequence<Key, Info>::end() const {
	//use private constructor to return end
	return iterator();
}

/*
	UTILITY METHODS
*/

template<typename Key, typename Info>
bool Sequence<Key, Info>::clear_info(const Info& filler) {
	#ifdef DEBUG
	std::cout << "[M_CLINF]-";
	#endif
	//check for empty list
	if(empty()) {
		#ifdef DEBUG
		std::cout << code_3;
		#endif
		return false;
	}
	//iterate through elements clearing info
	Element* current = head;
	while(current != nullptr) {
		current -> info = filler;
		current = current -> next;
	}
	#ifdef DEBUG
	std::cout << code_0;
	#endif
	return true;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::swap(const Key& what, const Key& dest,
			       int n_what,      int n_dest      ) {
	#ifdef DEBUG
	std::cout << "[M_SWAP_]-" << mln_beg;
	#endif
	SearchResult item1 = _find(what, n_what);
	SearchResult item2 = _find(dest, n_dest);
	//at least one of the elements was not found, abort
	if(item1.target == nullptr || item2.target == nullptr) {
		return false;
	}
	//both found, swap payloads
	Element temp = *item1.target;
	item1.target -> key = item2.target -> key;
	item1.target -> info = item2.target -> info;
	item2.target -> key = temp.key;
	item2.target -> info = temp.info;
	#ifdef DEBUG
	std::cout << "[M_SWAP_]-" << mln_end;
	#endif
	return true;
}

/*
	HELPERS
*/

template<typename Key, typename Info>
typename Sequence<Key, Info>::SearchResult 
Sequence<Key, Info>::_find(const Key& key, int n_key) const {
	#ifdef DEBUG
	std::cout << "[H_FIND_]-";
	#endif
	//check if argument is even valid
	if(n_key < 1) {
		#ifdef DEBUG
		std::cout << code_1;
		#endif
		return SearchResult({nullptr, nullptr, nullptr});
	}
	//check if there's where to search
	if(empty()) {
		#ifdef DEBUG
		std::cout << code_3;
		#endif
		return SearchResult({nullptr, nullptr, nullptr});
	}
	//perform a search for target and its neighbours
	Element* current = head;
	Element* previous = nullptr;
	int n_ocr = 0;
	while(current != nullptr) {
		if(current -> key == key) {
			n_ocr++;
		}
		if(n_ocr == n_key) {
			SearchResult result({
			previous,
			current,
			current -> next
			});
			#ifdef DEBUG
			std::cout << code_0;
			#endif
			return result;
		}
		previous = current;
		current = current -> next;
	}
	//give back empty search result if failed
	#ifdef DEBUG
	std::cout << "< Key '" << key
		  << ":" << n_key << "' not found.\n";
	#endif
	return SearchResult({nullptr, nullptr, nullptr});
}

template<typename Key, typename Info> 
bool Sequence<Key, Info>::_clone(const Sequence<Key, Info>& src) {
	#ifdef DEBUG
	std::cout << "[H_CLONE]-" << mln_beg;
	#endif
	//sequences already equal
	if(*this == src) {
		#ifdef DEBUG
		std::cout << "[H_CLONE]-" << code_0;
		std::cout << "[H_CLONE]-" << mln_end;
		#endif
		return true;
	}
	//start cloning clean
	if(!empty()) purge();
	#ifdef DEBUG
	if(src.empty()) {
		std::cout << "[H_CLONE]-" << code_0;
	}
	#endif
	//iterate through source pushing content into this
	Element* current = src.head;
	while(current != nullptr) {
		if(!push_back(current -> key, current -> info)) {
			return false;
		}
		current = current -> next;
	}
	#ifdef DEBUG
	std::cout << "[H_CLONE]-" << mln_end;
	#endif
	return true;
}

/*
	EXTERNAL FUNCTIONS
*/

template <typename Key, typename Info>
Sequence<Key, Info> join(const Sequence<Key, Info>& left,
			 const Sequence<Key, Info>& rght,
			 Info (*aggregator)(const Info&, const Info&)) {
	#ifdef DEBUG
	std::cout << "[F_JOIN_]-";
	#endif
	//require two sequences to be of the same length and non-empty
	if( left.size() != rght.size() || !left.size() ) {
		#ifdef DEBUG
		std::cout << "> Sequences not equal size"
			  << " or at least one is empty!\n";
		#endif
		//return new empty sequence
		return Sequence<Key, Info>();
	}
	//prepare to merge
	Sequence<Key, Info> newSequence;
	typename Sequence<Key, Info>::iterator itr_l = left.begin();
	typename Sequence<Key, Info>::iterator itr_r = rght.begin();
	//iterate through two equal size lists
	while( !itr_l.end() && !itr_l.end() ) {
		//equal keys, aggregate and push
		if(itr_l.key() == itr_r.key()) {
			Info newInfo = aggregator(itr_l.info(), itr_r.info());
			newSequence.push_back(itr_l.key(), newInfo);
			itr_l++;
			itr_r++;
		}
		//one is smaller than the other
		else if(itr_l.key() > itr_r.key()) {
			newSequence.push_back( itr_l.key(), itr_l.info() );
			itr_l++;
		}
		else {
			newSequence.push_back( itr_r.key(), itr_r.info() );
			itr_r++;
		}
	}
	#ifdef DEBUG
	std::cout << code_0;
	#endif
	//everything succeeded, return join result
	return newSequence;
}






