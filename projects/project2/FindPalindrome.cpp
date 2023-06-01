#include <string>
#include <vector>
#include <iostream>
#include "FindPalindrome.hpp"

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

// helper function to convert string to lower case
static void convertToLowerCase(string & value)
{
	for (int i=0; i<value.size(); i++) {
		value[i] = tolower(value[i]);
	}
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(vector<string>
        candidateStringVector, vector<string> currentStringVector)
{
	// TODO need to implement this recursive function!
	return;
}

// private function to determine if a string is a palindrome (given, you
// may change this if you want)
bool FindPalindrome::isPalindrome(string currentString) const
{
	locale loc;
	// make sure that the string is lower case...
	convertToLowerCase(currentString);
	// see if the characters are symmetric...
	int stringLength = currentString.size();
	for (int i=0; i<stringLength/2; i++) {
		if (currentString[i] != currentString[stringLength - i - 1]) {
			return false;
		}
	}
	return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	stringList = new std::vector<std::string>(0); // empty palindrome instance
	palindromeVector = new std::vector<std::string>(0); // no palindromes to find from empty list of strings
	palindromeCount = 0; // no palindromes = 0 palindromes to date
}

FindPalindrome::~FindPalindrome()
{
	std::vector<std::string> *tempV_1 = new std::vector<std::string>(0); // empty temporary vectors
	std::vector<std::string> *tempV_2 = new std::vector<std::string>(0);
	
	stringList->swap(*tempV_1); // string list swapped with an empty vector
	palindromeVector->swap(*tempV_2); // palindrome vector swapped with an empty vector
}

int FindPalindrome::number() const
{
	return palindromeCount; // returns palindrome count
}

void FindPalindrome::clear()
{
	palindromeVector->clear(); // removes all elements from palindrome vector
	palindromeCount = 0; // resets palindrome count
}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	
	return false;
}

bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{
	// TODO need to implement this...
	return false;
}

bool FindPalindrome::add(const string & value)
{
	// exception; added string must only contain letters
	int count = 0; // need to check how many letters the input contains
	std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; // string of letters
	for(int i = 0; i < value.size(); i++)
	{
		for(int j = 0; j < alphabet.size(); j++)
		{
			if(value[i] == alphabet[j])
			{
				count++;
			}
		}
	}
	if(count != value.size()) // number of letters has to match size of string
	{
		return false;
	}

	// exception; added string must be unique
	int check = 0; // need to check if any of the strings in current string list match the string being added
	std::string str1, str2 = value;
	convertToLowerCase(str2);
	for(int i = 0; i < stringList->size(); i++)
	{
		str1 = stringList->at(i);
		convertToLowerCase(str1);
		if(str1 == str2)
		{
			check =  1;
		}
	}
	if(check = 1)
	{
		return false;
	}

	else
	{
		stringList->push_back(value); // appends a string to the end of the string list
		palindromeVector->clear(); // empties palindrome vector
		recursiveFindPalindromes(*palindromeVector, *stringList); // finds sentence palindromes from the string list
		palindromeCount = palindromeVector->size(); // recomputes the number of sentence palindromes found through recursion

		return true;
	}
}

bool FindPalindrome::add(const vector<string> & stringVector)
{
	for(int a = 0; a < stringVector.size(); a++) // check each string in the string vector
	{
		std::string value = stringVector.at(a); // value represents a string in the stringVector

		// exception; added string must only contain letters
		int count = 0; // need to check how many letters the input contains
		std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; // string of letters
		for(int i = 0; i < value.size(); i++)
		{
			for(int j = 0; j < alphabet.size(); j++)
			{
				if(value[i] == alphabet[j])
				{
					count++;
				}
			}
		}
		if(count != value.size()) // number of letters has to match size of string
		{
			return false;
		}

		// exception; added string must be unique
		int check = 0; // need to check if any of the strings in current string list match the string being added
		std::string str1, str2 = value;
		convertToLowerCase(str2);
		for(int i = 0; i < stringList->size(); i++)
		{
			str1 = stringList->at(i);
			convertToLowerCase(str1);
			if(str1 == str2)
			{
				check =  1;
			}
		}
		if(check = 1)
		{
			return false;
		}
	}

	for(int i = 0; i < stringVector.size(); i++) // appends all the strings to the string list
	{
		std::string value = stringVector.at(i); // represents a string the string vector
		stringList->push_back(value); // appends a string to the end of the string vector
	}

	palindromeVector->clear(); // empties palindrome vector
	recursiveFindPalindromes(*palindromeVector, *stringList); // finds sentence palindromes from the string list
	palindromeCount = palindromeVector->size(); // recomputes the number of sentence palindromes found through recursion

	return true;

}

vector< vector<string> > FindPalindrome::toVector() const
{
	// TODO need to implement this...
	return vector< vector<string> >();
}

