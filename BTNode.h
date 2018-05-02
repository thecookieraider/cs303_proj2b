#ifndef BTNODE_H_
#define BTNODE_H_
#include <sstream>
#include <string>
#include <algorithm>
/** A node for a Morse code Tree. */
template <typename T>
struct BTNode
{
	char data;
	std::string morseCode;
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

	bool operator<(BTNode<T> rhs) const
	{
		/*if (rhs.morseCode.empty()) {
			if (this->morseCode[0] == '.') return true;
			else return false;
		} else if (this->morseCode.empty()) {
			if (rhs.morseCode[0] == '.') return false;
			else return true;
		} else {
			int rScore = std::count(rhs.morseCode.begin(), rhs.morseCode.end(), '_') - std::count(rhs.morseCode.begin(), rhs.morseCode.end(), '.');
			int lScore += std::count(this->morseCode.begin(), this->morseCode.end(), '_') - std::count(this->morseCode.begin(), this->morseCode.end(), '.');

			return rScore > lScore;
		}*/

		int rhsDotCount = std::count(rhs.morseCode.begin(), rhs.morseCode.end(), '.');
		int rhsDashCount = std::count(rhs.morseCode.begin(), rhs.morseCode.end(), '_');
		int lhsDotCount = std::count(this->morseCode.begin(), this->morseCode.end(), '.');
		int lhsDashCount = std::count(this->morseCode.begin(), this->morseCode.end(), '_');

		if (!rhs.morseCode.length()) {
			if (this->morseCode[0] == '.') return true;
			else return false;
		} else if (!this->morseCode.length()) {
			if (rhs.morseCode[0] == '.') return false;
			else return true;
		}

		if (rhsDotCount == lhsDotCount) {
			if (rhsDashCount > lhsDashCount) return true;
			else return false;
		} else if (rhsDashCount == rhsDashCount) {
			if (rhsDotCount > lhsDotCount) return false;
			else return true;
		}

		if (rhsDotCount > lhsDotCount && rhsDashCount > lhsDashCount) {
			return true;
		} else return false;

		return true;
	}
}; // End BTNode

// Overloading the ostream insertion operator
template<typename Item_Type>
std::ostream& operator<<(std::ostream& out,
	const BTNode<Item_Type>& node) {
		return out << node.to_string();
}

#endif
