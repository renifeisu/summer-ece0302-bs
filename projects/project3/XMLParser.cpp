// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

// TODO: Implement the constructor here
XMLParser::XMLParser()
{
	elementNameBag = new Bag<std::string>(); // creates an empty bag for elements
	parseStack = new Stack<StringTokenType>(); // creates an empty stack for checking tags
	t_check = false;
	p_check = false;
}  // end default constructor

// TODO: Implement the destructor here
XMLParser::~XMLParser()
{
	elementNameBag->clear(); // clears bag
	parseStack->clear(); // clears stack
}  // end destructor

// TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	tokenizedInputVector.clear(); // clears the tokenized input vector 

	bool valid = true; // the bool value that will be returned
	
	std::string invalidCharacters = "!\"#$%&\'()*+,/;<=>?@[\\]^`{|}~"; // tag name cannot include these characters
	std::string invalidStart = "-.01234567890"; // first character of tage name cannot include these characters

	std::string tempInput = inputString; // temporary variable to store input
	std::string tempChar = ""; // temporary variable to store a character
	std::string tempString = ""; // temporary variable to store a string
	bool tempBool = false; // temporary variable to store a bool

	Stack<std::string> delimiters; // stack to store delimiters and check if delimiter pairs are valid
	
	// inputString cannot be empty
	if(tempInput.size() == 0)
	{
		valid = false;
		return valid;
	}
	
	int cSpace = 0;
	for(int i = 0; i < tempInput.size(); i++)
	{
		if(std::isspace(tempInput.at(i)))
		{
			cSpace++;
		}
	}
	if(cSpace == tempInput.size())
	{
		return false;
	}

	Bag<std::string> *nameBag = new Bag<std::string>();
	// while loop to store valid and invalid tag names in nameBag
	while(tempInput.size() != 0)
	{
		if(tempInput.at(0) == '<')
		{
			if(delimiters.isEmpty()) // nested delimiters are not valid
			{
				tempBool = true; // enables characters to be added to tempString
				tempChar = "<";
				delimiters.push(tempChar); // stores < into delimiter stack
			}
			else if(delimiters.peek() == "<")
			{
				valid = false; // function will return false
				tempBool = true; // enables characters to be added to tempString
				tempChar = "<";
				delimiters.push(tempChar); // stores < into delimiter stack
			}
			else if(delimiters.peek() == "&") // end content
			{
				tempBool = true; // enables characters to be added to tempString

				tempChar = "<";
				delimiters.push(tempChar); // stores < into delimiter stack

				nameBag->add(tempString); // adds a valid/invalid tag name into nameBag
				tempString = ""; // resets tempString
			}
			else
			{
				tempBool = true; // enables characters to be added to tempString
				tempChar = "<";
				delimiters.push(tempChar); // stores < into delimiter stack
			}
		}
		else if(tempInput.at(0) == '>')
		{
			if(delimiters.isEmpty())
			{
				valid = false;
			}
			else if((delimiters.peek() == "<") && (tempBool = true)) // valid delimiter pair
			{
				nameBag->add(tempString); // adds a valid/invalid tag name into nameBag
				tempString = ""; // resets tempString
			}
			else if(delimiters.peek() == "&") // end content
			{
				valid = false; // tag cannot start with >

				tempChar = ">";
				delimiters.push(tempChar); // stores > into delimiter stack

				nameBag->add(tempString); // adds a valid/invalid tag name into nameBag
				tempString = ""; // resets tempString
			}
			else // nested delimiters are not valid
			{
				valid = false;
			}

			tempBool = false; // resets tempBool
			tempChar = ">";
			delimiters.push(tempChar); // stores > into delimiter stack
		}
		else
		{
			if(delimiters.isEmpty())
			{
				tempBool = true;
				tempString += "<";
				tempChar = "&";
				delimiters.push(tempChar);
			}
			else if(delimiters.peek() == ">") // content start
			{
				tempBool = true;
				tempString += "<";
				tempChar = "&";
				delimiters.push(tempChar);
			}
			else if(delimiters.peek() == "&") // continue content
			{
				tempBool = true;
			}
			else
			{
				// do nothing
			}

			if(tempBool == true) // if top of delimiter stack starts with < or is content, add character to tempString
			{
				tempString += tempInput.at(0);
			}
		}

		tempInput.erase(tempInput.begin()); // removes the first element in tempInput
	}

	if(tempString.size() != 0) // in case the input is just content
	{
		nameBag->add(tempString);
		tempString = "";
	}

	if(valid == false)
	{
		return false;
	}

	// check if delimiters are correctly paired
	int cOpen = 0;
	int cClose = 0;
	while(!delimiters.isEmpty())
	{
		if(delimiters.peek() == "<")
		{
			cOpen++;
		}
		else if(delimiters.peek() == ">")
		{
			cClose++;
		}
		delimiters.pop();
	} 
	if(cOpen != cClose)
	{
		return false;
	}

	std::vector<std::string> tempTokens = nameBag->toVector(); // converts the linked names in nameBag into a vector of names
	std::reverse(tempTokens.begin(), tempTokens.end());
	std::vector<TokenStruct> tokenVector; // temporary tokenVector for only this input string

	for(int i = 0; i < tempTokens.size(); i++)
	{
		tempBool = true; // sets temporary bool value
		TokenStruct tempToken; // temporary token

		if(tempTokens.at(i).size() == 0) // tag names cannot be empty
		{
			return false;
		}
		else if(tempTokens.at(i).at(0) == '<') // content
		{
			tempToken.tokenType = CONTENT;
			tempTokens.at(i).erase(tempTokens.at(i).begin());
		}
		else if(tempTokens.at(i).at(0) == '/') // </ > : end tag
		{
			tempToken.tokenType = END_TAG;
			tempTokens.at(i).erase(tempTokens.at(i).begin());
		}
		else if((tempTokens.at(i).at(0) == '?') && (tempTokens.at(i).back() == '?')) // <? ?> : declaration
		{
			tempToken.tokenType = DECLARATION;
			tempTokens.at(i).erase(tempTokens.at(i).begin());
			tempTokens.at(i).pop_back();
		}
		else if(tempTokens.at(i).back() == '/') // < /> : empty tag
		{
			tempToken.tokenType = EMPTY_TAG;
			tempTokens.at(i).pop_back();
		}
		else // < > start tag
		{
			tempToken.tokenType = START_TAG;
		}

		tempString = tempTokens.at(i); // sets temporary string value to a tag name

		if(tempToken.tokenType == START_TAG && std::isspace(tempString.at(0))) // for start tags, tokenString cannot start with a whitespace
		{
			valid = false;
		}

		if(valid == false)
		{
			return valid;
		}

		// Only for declaration, start, and end tags, truncates tempString if there is a white space in the tag name
		if((tempToken.tokenType == START_TAG || tempToken.tokenType == EMPTY_TAG) && (tempBool == true))
		{
			int tempSize = tempString.size(); // temporary integer variable, set to tempString size

			// checks when the first white space occurs (if at all)
			for(int k = 0; k < tempSize; k++)
			{
				if(std::isspace(tempString.at(k)))
				{
					tempSize = k; // tempSize is set to the first white space position
					break;
				}
			}

			tempString.resize(tempSize);
		}

		// Checks if tempString starts with an invalid character
		if(tempToken.tokenType != CONTENT && tempToken.tokenType != DECLARATION)
		{
			for(int j = 0; j < invalidStart.size(); j++)
			{
				if((tempString.at(0) == invalidStart.at(j)) || std::isspace(tempString.at(0)))
				{
					tempBool = false; 
				}
			}
		}

		// Checks if tempString (tag name) is valid
		if(tempToken.tokenType != CONTENT && tempToken.tokenType != DECLARATION)
		{
			for(int k = 0; k < tempString.size(); k++)
			{
				for(int l = 0; l < invalidCharacters.size(); l++)
				{
					if((tempString.at(k) == invalidCharacters.at(l)) || (std::isspace(tempString.at(k))))
					{
						tempBool = false;
					}
				}
			}
		}

		if(tempBool == true && valid == true) // if tempString is valid
		{
			for(int k = 0; k < tempString.size(); k++)
			{
				if(!std::isspace(tempString.at(k)))
				{
					tempToken.tokenString = tempString; // gives tempToken a valid tokenString
					tokenizedInputVector.push_back(tempToken); // appends tempToken to the tokenizedInputVector

					tokenVector.push_back(tempToken); // also appends to tokenVector
					break;
				}
			}
		}
		else
		{
			valid = false;
		}
	}
	
	nameBag->clear(); // resets nameBag

	if(valid == true)
	{
		t_check = true;
	}

	return valid;
}  // end

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput()
{
	bool valid = true; // the bool value that will be returned

	if(tokenizedInputVector.size() == 0) // tokenVector cannot be empty
	{
		return false;
	}

	// Whitespace or any other content is not allowed at the beginning of an xml file
	if(tokenizedInputVector.at(0).tokenType == CONTENT)
	{	
		std::string cString = tokenizedInputVector.at(0).tokenString;
		int spaceCheck = -1;
		for(int c = 0; c < cString.size(); c++)
		{
			if(!std::isspace(cString.at(c)))
			{
				spaceCheck = 0;
				break;
			}
		}

		if(spaceCheck == -1)
		{
			tokenizedInputVector.erase(tokenizedInputVector.begin());
		}
	}

	// Same for at the end of the xml file
	if(tokenizedInputVector.back().tokenType == CONTENT)
	{
		int spaceCheck = -1;
		std::string cString = tokenizedInputVector.back().tokenString;
		for(int c = 0; c < cString.size(); c++)
		{
			if(!std::isspace(cString.at(c)))
			{
				spaceCheck = 0;
				break;
			}
		}

		if(spaceCheck == -1)
		{
			tokenizedInputVector.pop_back();
		}
	}

	if(tokenizedInputVector.size() == 0) // tokenVector cannot be empty
	{
		return false;
	}

	// Checking if the xml doc starts with a start tag
	StringTokenType tType = CONTENT;
	for(int i = 0; i < tokenizedInputVector.size(); i++)
	{
		if(tokenizedInputVector.at(i).tokenType != CONTENT && tokenizedInputVector.at(i).tokenType != DECLARATION)
		{
			tType = tokenizedInputVector.at(i).tokenType;
			break;
		}
	}
	if(tType != START_TAG)
	{
		return false;
	}

	// Checking if the xml doc ends with an end tag
	tType = CONTENT;
	for(int i = tokenizedInputVector.size() - 1; i > 0; i--)
	{
		if(tokenizedInputVector.at(i).tokenType != CONTENT && tokenizedInputVector.at(i).tokenType != DECLARATION)
		{
			tType = tokenizedInputVector.at(i).tokenType;
			break;
		}
	}
	if(tType != END_TAG)
	{
		return false;
	}

	Stack<std::string> tempName; // temporary stack for element names
	Bag<std::string> tempNamev2; // temporary bag for element names, checks for root element

	// Checks if all start tags have an end tag, and if matching start/end tags have the same tag name
	for(int i = 0; i < tokenizedInputVector.size(); i++)
	{
		if((tokenizedInputVector.at(i).tokenType == START_TAG) || (tokenizedInputVector.at(i).tokenType == END_TAG))
		{
			if(parseStack->isEmpty())
			{
				parseStack->push(tokenizedInputVector.at(i).tokenType);
				tempName.push(tokenizedInputVector.at(i).tokenString);
			}
			else if(parseStack->peek() == START_TAG && tokenizedInputVector.at(i).tokenType == END_TAG)
			{
				parseStack->pop();
				if(tempName.peek() == tokenizedInputVector.at(i).tokenString)
				{
					elementNameBag->add(tempName.peek());
					tempName.pop();
				}
			}
			else
			{
				parseStack->push(tokenizedInputVector.at(i).tokenType);
				tempName.push(tokenizedInputVector.at(i).tokenString);
			}

			tempNamev2.add(tokenizedInputVector.at(i).tokenString);
		}
	}

	std::vector<std::string> names = tempNamev2.toVector();
	if(!(parseStack->isEmpty()) || !(tempName.isEmpty()) || names.size() == 0)
	{
		return false;
	}
	if(names.at(0) != names.back() || names.size() % 2 > 0)
	{
		return false;
	}

	if(valid == true)
	{
		p_check = true;
	}
	return valid;
}

// TODO: Implement the clear method here
void XMLParser::clear()
{
	elementNameBag->clear();
	parseStack->clear();
	tokenizedInputVector.clear();
	t_check = false;
	p_check = false;
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const
{
	if(tokenizedInputVector.size() == 0 || !t_check || !p_check)
	{
		std::logic_error description("Not tokenized/parsed");
		throw description;
	}

	return elementNameBag->contains(inputString);
}

// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const
{
	if(tokenizedInputVector.size() == 0 || !t_check || !p_check)
	{
		std::logic_error description("Not tokenized/parsed");
		throw description;
	}
	
	return elementNameBag->getFrequencyOf(inputString);
}

