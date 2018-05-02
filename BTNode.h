#ifndef BTNODE_H_
#define BTNODE_H_
#include <sstream>
#include <string>

/** A node for a Binary Tree. */
template<typename Item_Type>
struct BTNode
{
	Item_Type data;
	std::string morseCode;
	BTNode<Item_Type>* left;
	BTNode<Item_Type>* right;

	// Constructor
	BTNode(const Item_Type& the_data,
		BTNode<Item_Type>* left_val = NULL,
		BTNode<Item_Type>* right_val = NULL) :
		data(the_data), left(left_val), right(right_val) {}

	// Destructor (to avoid warning message)
	virtual ~BTNode() {}

	// to_string
	virtual std::string to_string() const {
		std::ostringstream os;
		os << data;
		return os.str();
	}

	bool operator < (BTNode<Item_Type>& nodeR){
		if (this->morseCode.length() == nodeR.morseCode.length() ) {

			for (int i = 0; i < this->morseCode.length(); i++ ){
				if (this->morseCode[i] != nodeR.morseCode[i]){
					if (this->morseCode[i] == '-'){
						return false;
					}
					else {
						return true; }
				}
			}

		}
		else if (this->morseCode.length() < nodeR.morseCode.length()){
			for (int i = 0 ; i < this->morseCode.length(); i++){
				if (this->morseCode[i] != nodeR.morseCode[i]){
					if (this->morseCode[i] == '-'){
						return true;
					}
					else {
						return false; }
				}

			}
			if (this->morseCode[0]=='.'){
				return true;
			}
			else {
				return false;
			}
		}
		else if (this->morseCode.length() > nodeR.morseCode.length()){
			for (int i = 0 ; i < nodeR.morseCode.length(); i++){
				if (nodeR.morseCode[i] != this->morseCode[i]){
					if (nodeR.morseCode[i] == '-'){
						return true;
					}
					else {
						return false; }
				}

			}
			if (nodeR.morseCode[0]=='.'){
				return false;
			}
			else {
				return true;
			}
		}

	}

}; // End BTNode

// Overloading the ostream insertion operator
template<typename Item_Type>
std::ostream& operator<<(std::ostream& out,
	const BTNode<Item_Type>& node) {
		return out << node.to_string();
}

#endif
