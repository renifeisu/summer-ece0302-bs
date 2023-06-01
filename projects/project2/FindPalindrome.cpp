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
	std::vector<std::string> str; // concatenated vector of strings
	str.resize(candidateStringVector.size() + currentStringVector.size());
	std::fill(str.begin(), str.end(), 0);
	for(int i = 0; i < candidateStringVector.size(); i++)
	{
		str.at(i) = candidateStringVector.at(i);
	}
	for(int i = candidateStringVector.size(); i < str.size(); i++)
	{
		str.at(i) = currentStringVector.at(i - candidateStringVector.size());
	}

	// run cut tests
	if ((cutTest1(str) == false) || cutTest2(candidateStringVector, currentStringVector))
	{
		// do nothing
	}
	
	// check if palindrome
	else
	{
		// make a concatenated string of the vector
	}

	// continue recursion

	if(currentStringVector.size() == 0) // end of recursion
	{
		return;
	}
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
	palindromeVector = new std::vector<std::string>(0); // palindrome can't be made from empty string vector
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
	allPalindromes.clear(); // removes all elements from allPalindromes vector
	palindromeCount = 0; // resets palindrome count
}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	std::vector<int> count; // stores frequency of letters in string
	std::string str; // represents a string in the string vector
	std::string fullStr = ""; // represents the concatenation of strings in the string vector

	for(int i = 0; i < stringVector.size(); i++) // loop to concatenate all strings
	{
		str = stringVector.at(i);
		fullStr += str;
	}

	convertToLowerCase(fullStr); // make string case insensitive
	count.resize(fullStr.size()); // sets the size of the count vector to the size of the concatenated string
	std::fill(count.begin(), count.end(), 0); // resets each element in the count vector

	for(int i = 0; i < fullStr.size(); i++) // loop to store frequency of each letter into count vector
	{
		for(int j = 0; j < fullStr.size(); j++)
		{
			if(fullStr[i] == fullStr[j])
			{
				count.at(i) = count.at(i) + 1;
			}
		}
	}

	int check = 0; // checking frequencies
	for(int i = 0; i < fullStr.size(); i++) // loop to check the frequencies stored in the count vector
	{
		int a = count.at(i) % 2; // check if any of the frequencies are odd
		if(a == 1)
		{
			check++; // increments check by one for each odd frequency
		}
	}

	if(check > 1) // failed cut test 1
	{
		return false;
	}
	else // passed cut test 1
	{
		return true;
	}
}

bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{
	std::string str1 = "", str2 = ""; // concatenated string of string vectors
	std::string str; // represents a string in a string vector
	int sizeCompare; // finds which string vector is longer

	for(int i = 0; i < stringVector1.size(); i++) // looping through stringVector1, concatenating each string to one big one
	{
		str = stringVector1.at(i);
		str1 += str; 
	}

	for(int i = 0; i < stringVector2.size(); i++) // looping through stringVector2, concatenating each string to one big one
	{
		str = stringVector2.at(i);
		str2 += str; 
	}

	if(str1.size() >= str2.size()) // number of characters in stringVector1 > stringVector2
	{
		sizeCompare = 1;
	}
	else // otherwise
	{
		sizeCompare = 2;
	}

	convertToLowerCase(str1); // make string case insensitive
	convertToLowerCase(str2); // make string case insensitive
	std::vector<int> count1, count2; // stores frequency of letters in string

	count1.resize(str1.size()); // sets the size of the count vector to the size of the concatenated string
	count2.resize(str2.size());

	std::fill(count1.begin(), count1.end(), 0); // resets each element in the count vector
	std::fill(count2.begin(), count2.end(), 0);

	for(int i = 0; i < str1.size(); i++) // loop to store frequency of each letter into count1 vector
	{
		for(int j = 0; j < str1.size(); j++)
		{
			if(str1[i] == str1[j])
			{
				count1.at(i) = count1.at(i) + 1;
			}
		}
	}

	for(int i = 0; i < str2.size(); i++) // loop to store frequency of each letter into count2 vector
	{
		for(int j = 0; j < str2.size(); j++)
		{
			if(str2[i] == str2[j])
			{
				count2.at(i) = count2.at(i) + 1;
			}
		}
	}

	std::vector<int> check; // checking if the characters in the smaller vector is in the bigger vector
	
	if(sizeCompare == 1) // if stringVector1 is bigger
	{
		check.resize(str2.size());
		std::fill(check.begin(), check.end(), 0);

		for(int i = 0; i < str2.size(); i++) // checking the frequency of characters in vector1 that match vector2
		{
			for(int j = 0; j < str1.size(); j++)
			{
				if(str2[i] == str1[j])
				{
					check.at(i) = check.at(i) + 1;
				}
			}
		}

		for(int i = 0; i < check.size(); i++) // the frequency that each character in vector2 found in vector1 should be >= frequencies stored in the count2 vector
		{
			if(check.at(i) < count2.at(i))
			{
				return false; // failed cut test 2
			}
		}
	}
	else // if stringVector2 is bigger
	{
		check.resize(str1.size());
		std::fill(check.begin(), check.end(), 0);

		for(int i = 0; i < str1.size(); i++) // checking the frequency of characters in vector2 that match vector1
		{
			for(int j = 0; j < str2.size(); j++)
			{
				if(str1[i] == str2[j])
				{
					check.at(i) = check.at(i) + 1;
				}
			}
		}

		for(int i = 0; i < check.size(); i++) // the frequency that each character in vector1 found in vector2 should be >= frequencies stored in the count1 vector
		{
			if(check.at(i) < count1.at(i))
			{
				return false; // failed cut test 2
			}
		}

	}
	
	return true; // passed cut test 2
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
	return allPalindromes; // the vector containing all the palindromes from the stringList
}

