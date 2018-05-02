#ifndef BTNODE_H_
#define BTNODE_H_
#include <sstream>
#include <string>
#include <algorithm>

struct MorseCodeString : public std::string
{
	MorseCodeString(std::string str) : std::string(str) {}

	bool operator<(MorseCodeString rhs)
	{
		MorseCodeString sLhs = *this;
		MorseCodeString sRhs = rhs;

		if (!sRhs.length()) {
			if (sLhs[0] == '.') return true;
			else return false;
		} else if (!sLhs.length()) {
			if (sRhs[0] == '.') false;
			else return true;
		}

		if (sRhs.length() < sLhs.length()) {
			if (sLhs[sRhs.length()] == '_') return false;
			else return true;
		} else if (sLhs.length() < sRhs.length()) {
			if (sRhs[sLhs.length()] == '_') return true;
			else return false;
		} else if (sLhs.length() == sRhs.length()) {
			if (sLhs[sLhs.length() - 1] == '.' && sRhs[sRhs.length() - 1] == '_') return true;
			else return false;
		}

		throw std::runtime_error("I shouldnt be here");
	}
};

/** A node for a Morse code Tree. */
template <typename T>
struct BTNode
{
	char data;
	MorseCodeString morseCode;
	BTNode<T> * left;
	BTNode<T> * right;

	// Constructor
	BTNode(const T& the_data, BTNode<T>* left_val = NULL, BTNode<T>* right_val = NULL, std::string morseCode = "") :
		data(the_data), left(left_val), right(right_val), morseCode(morseCode) {}

	// Destructor (to avoid warning message)
	virtual ~BTNode() {}

	// to_string
	virtual std::string to_string() const {
		std::ostringstream os;
		os << data;
		return os.str();
	}

}; // End BTNode

// Overloading the ostream insertion operator
template<typename Item_Type>
std::ostream& operator<<(std::ostream& out,
	const BTNode<Item_Type>& node) {
		return out << node.to_string();
}

#endif
