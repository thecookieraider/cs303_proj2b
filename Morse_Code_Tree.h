#pragma once
#include "Binary_Search_Tree.h"
#include <fstream>
#include <string>
#include <map>

class Morse_Code_Tree : public Binary_Search_Tree<char>
{
private:
	std::map<char, std::string> morseCodes;
public:
	//Our only constructor for the class. Takes a filename that contains every
	//letter in the alphabet and the corresponding morse code for it. There should only be one
	//letter per line and the morse code should come right after it - no spaces
	Morse_Code_Tree(std::string fileName)
	{
		//Setup our root and declare variables. Root variable should ALWAYS have an empty string for its morse code
		this->root = new BTNode<char>(' ', NULL, NULL, "");
		std::ifstream fin(fileName);
		std::vector<std::string> codes;

		std::string line;

		//Read in our codes and put them in our vector. We remove anything that isnt a dot or dash and isnt the first character in the string
		while (std::getline(fin, line)) {
			for (auto it = line.begin(); it != line.end();) {
				if (*it != '.' && *it != '_' && it != line.begin()) it = line.erase(it);
				else it++;
			}
			codes.push_back(line);
		}

		//While we still have codes in the vector, sort the vector so that the shortest string are first in the vector and the longest are last.
		//Take the first element in the vector, insert it into our tree and then add it to our map. Then delete the entry.
		while (!codes.empty()) {
			std::sort(codes.begin(), codes.end(), [] (std::string& left, std::string& right) { return left.length() < right.length(); });
			this->insert(root, codes[0][0], codes[0].substr(1));
			morseCodes[codes[0][0]] = codes[0].substr(1);
			codes.erase(codes.begin());
		}
	}

	//Ported insert function from Binary_Search_Tree.h. Difference here that we do a comparison based on the
	//nodes and not their data. So we need to convert the morse code given in the function args to a node every time we want to convert
	virtual bool insert(BTNode<char>*& local_root, const char item, const std::string morseCode)
	{
		if (local_root == NULL) {
			local_root = new BTNode<char>(item, NULL, NULL, morseCode);
			return true;
		} else {
			if (BTNode<char>(item, NULL, NULL, morseCode) < *local_root)
				return insert(local_root->left, item, morseCode);
	 		else if (*local_root < BTNode<char>(item, NULL, NULL, morseCode))
				return insert(local_root->right, item, morseCode);
			else
				return false;
		}
	}

	//Ported insert function from Binary_Search_Tree.h. Difference here that we do a comparison based on the
	//nodes and not their data. So we need to convert the morse code given in the function args to a node every time we want to convert
	const BTNode<char>* find(BTNode<char>* local_root, const std::string target) const
	{
		if (local_root == NULL)
			return NULL;
		if (BTNode<char>(' ', NULL, NULL, target) < *local_root)
			return find(local_root->left, target);
		else if (*local_root < BTNode<char>(' ', NULL, NULL, target))
			return find(local_root->right, target);
		else
			return local_root;
	}

	std::string encode(std::string input)
	{
        //Declare variables
		std::string toReturn = "";

        //Traverse through input string
        for(size_t i = 0; i<input.length(); i++){
			//Find letter in key value in map (make sure lowercaase) get value
			std::string value = morseCodes.find(tolower(input[i]))->second;

			//Add value to string and add space between
			toReturn += value + " ";
		}
		return toReturn;

    }
	std::string decode(std::string input) {
		//Declare variables
		std::string Letters = "" ;
		size_t pos = 0 ;
		std::string token ;
		//Tokenize the string using a while loop. We're going to search for a space
		//and then substring from the beginning of the string to that space. We then search
		//the binary tree for that substring, get the corresponding letter and append it to our
		//decoded string and then remove that token and space from the string
		while ((pos = input.find(' ')) != std::string::npos ) {
			token = input.substr(0, pos);
			Letters += this->find(this->root, token)->data;
			input.erase(0, pos + 1);
		}
		//Get the last token (it isnt taken care of since there is no space at the end of the string)
		token = input.substr(0, pos);
		Letters += this->find(this->root, token)->data;

		return Letters ;

	 }
};