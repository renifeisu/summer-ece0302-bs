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
	if((stringList.size() < 1) || (cutTest1(stringList) == false) || (cutTest2(candidateStringVector, stringList) == false)) // invalid palindrome check
	{
		return; 
	} // END IF
	else if(stringList.size() == 1) // one word to check
	{
		// check if the string is a palindrome
		if(isPalindrome(stringList.at(0)))
		{
			palindromeVector.push_back(stringList); // add palindrome to vector
			palindromeCount++; // increment palindrome count
		}
		return;
	} // END ELSE IF word check
	else // sentence to check
	{
		/** Temporary string vector, to not modify current string vector*/
		std::vector<std::string> recursiveTempStringVector; // holds temporary values of current string vector
		for(int i = 0; i < currentStringVector.size(); i++) // copies current string vector into temp string vector
		{
			recursiveTempStringVector.push_back(currentStringVector.at(i));
		}

		/** Recursion to fill the candidate string vector and make temp string vector empty*/
		if(recursiveTempStringVector.size() > 0)
		{
			for(int i = 0; i < recursiveTempStringVector.size(); i++)
			{
				std::vector<std::string> tempV1, tempV2;
				tempV1 = recursiveTempStringVector;
				tempV2 = candidateStringVector;
				candidateStringVector.push_back(recursiveTempStringVector.at(i)); // Copies first element in string list into empty list
				recursiveTempStringVector.erase(recursiveTempStringVector.begin() + i); // Erases first element in string list
				recursiveFindPalindromes(candidateStringVector, recursiveTempStringVector); // Recursion to empty string list
				recursiveTempStringVector = tempV1;
				candidateStringVector = tempV2;
			}
		}

		/** Checking to see if candidate vector is palindrome*/
		else
		{
			std::string recursiveString = ""; // empty string
			for(int k = 0; k < candidateStringVector.size(); k++)
			{
				recursiveString += candidateStringVector.at(k); // string will be concatenated words
			} 
			if(isPalindrome(recursiveString))
			{
				palindromeVector.push_back(candidateStringVector); // add palindrome to vector
				palindromeCount++; // increment palindrome count
			}
		} // end check permutations
	} // END ELSE sentence check
} // end method

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
	palindromeCount = 0; // no palindromes exist
}

FindPalindrome::~FindPalindrome()
{
	std::vector<std::string>().swap(stringList); // string list swapped with an empty vector to free memory
	palindromeVector.clear(); // cleared palindrome vector
}

int FindPalindrome::number() const
{
	return palindromeCount; // returns palindrome count
}

void FindPalindrome::clear()
{
	stringList.clear(); // removes all elements from string vector
	palindromeVector.clear(); // removes all elements from palindrome vector
	palindromeCount = 0; // resets palindrome count
}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	std::vector<int> count; // stores frequency of letters in string
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz"; // alphabet string

	/*******************************************************************/
	/** Combining all strings in the string vector into a single string*/
	/** std::string fullStr*/
	/*******************************************************************/
	std::string str; // represents a string in the string vector
	std::string fullStr = ""; // represents the concatenation of strings in the string vector

	for(int i = 0; i < stringVector.size(); i++) // loop to concatenate all strings
	{
		str = stringVector.at(i);
		fullStr += str;
	}

	convertToLowerCase(fullStr); // make string case insensitive

	/**********************************************************************/
	/** Finding the frequency of each character in the concatenated string*/
	/** std::vector<int> count*/
	/**********************************************************************/

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

	/**************************************************************************/
	/** Checks the frequency vector to see if it meets the cut test conditions*/
	/** int check*/
	/**************************************************************************/

	std::vector<int> oddFrequencies; // checking odd frequencies to account for double counting
	for(int i = 0; i < fullStr.size(); i++) // loop to check the frequencies stored in the count vector
	{
		int a = count.at(i) % 2; // check if any of the frequencies are odd
		if(a == 1)
		{
			oddFrequencies.push_back(i);
		}
	}
	
	for(int i = 0; i < oddFrequencies.size(); i++)
	{
		for(int j = 0; j < oddFrequencies.size(); j++)
		{
			if(fullStr[oddFrequencies.at(i)] != fullStr[oddFrequencies.at(j)])
			{
				return false; // failed cut test 1
			}
		}
	}
	
	return true; // cut test 1 passed
}

bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{
	/*******************************************************************/
	/** Combining all strings in the string vector into a single string*/
	/** std::string str1, str2*/
	/*******************************************************************/

	std::string str1 = "", str2 = ""; // concatenated string of string vectors
	std::string str; // represents a string in a string vector
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz"; // alphabet string
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

	convertToLowerCase(str1); // make string case insensitive
	convertToLowerCase(str2); // make string case insensitive

	/*******************************************************************/
	/** Figuring out which vector is larger*/
	/** int sizeCompare*/
	/*******************************************************************/

	if(str1.size() >= str2.size()) // number of characters in stringVector1 > stringVector2
	{
		sizeCompare = 1;
	}
	else // otherwise
	{
		sizeCompare = 2;
	}

	/**********************************************************************/
	/** Finding the frequency of each character in concatenated strings*/
	/** std::vector<int> count1, count2*/
	/**********************************************************************/

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

	/**************************************************************************/
	/** Checks the frequency vector to see if it meets the cut test conditions*/
	/** std::vector<int> check*/
	/**************************************************************************/

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
	/**************************************************************************/
	/** Check if string input is valid*/
	/** std::string value*/
	/**************************************************************************/

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

	/**************************************************************************/
	/** Check if string is unique*/
	/** std::string str1, str2*/
	/**************************************************************************/

	// exception; added string must be unique
	int check = 0; // need to check if any of the strings in current string list match the string being added
	std::string str1, str2 = value;
	convertToLowerCase(str2);
	if(stringList.size() > 0)
	{
		for(int i = 0; i < stringList.size(); i++)
		{
			str1 = stringList.at(i);
			convertToLowerCase(str1);
			if(str1 == str2)
			{
				check =  1;
			}
		}
	}
	
	if(check == 1)
	{
		return false;
	}

	/**************************************************************************/
	/** Adds string value to stringList and recomputes palindromes*/
	/**************************************************************************/
	else
	{
		stringList.push_back(value); // appends a string to the end of the string list
		palindromeVector.clear(); // empties palindrome vector
		recursiveFindPalindromes(std::vector<std::string>(), stringList); // finds sentence palindromes from the string list
		palindromeCount = palindromeVector.size(); // recomputes the number of sentence palindromes found through recursion

		return true;
	}
}

bool FindPalindrome::add(const vector<string> & stringVector)
{	
	int c = 0; // keeps track of how many words get added given the vector

	for(int a = 0; a < stringVector.size(); a++) // check each string in the string vector
	{
		/**************************************************************************/
		/** Check if string input is valid*/
		/** std::string value*/
		/**************************************************************************/

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
			// do nothing
		}

		/**************************************************************************/
		/** Check if string input is unique*/
		/** std::string str1, str2*/
		/**************************************************************************/
		
		// exception; added string must be unique
		else
		{
			int check = 0; // need to check if any of the strings in current string list match the string being added

			std::string str1, str2 = value;
			convertToLowerCase(str2);
			if(stringList.size() > 0)
			{
				for(int i = 0; i < stringList.size(); i++)
				{
					str1 = stringList.at(i);
					convertToLowerCase(str1);
					if(str1 == str2)
					{
						check =  1;
					}
				}
			}

			if(check == 1)
			{
				// do nothing
			}

	/**************************************************************************/
	/** Adds string values to stringList and recomputes palindromes*/
	/**************************************************************************/
			else
			{
				std::string value = stringVector.at(a); // represents a string the string vector
				stringList.push_back(value); // appends a string to the end of the string vector

				palindromeVector.clear(); // empties palindrome vector
				recursiveFindPalindromes(std::vector<std::string>(), stringList); // finds sentence palindromes from the string list
				palindromeCount = palindromeVector.size(); // recomputes the number of sentence palindromes found through recursion

				c++;
			} // end ELSE checked string uniqueness
		} // end ELSE checked string validity
	} // end looping words in vector

	if(c == stringVector.size())
	{
		return true; // have to add at least 1 word to return true
	}
	else
	{
		return false;
	}
} // end method

vector< vector<string> > FindPalindrome::toVector() const
{
	return palindromeVector; // the vector containing all the palindromes from the stringList
}

