#include "bitset.hpp"
#include <iostream>

Bitset::Bitset() {
    // sets bitset_size to 8
    bitset_size = 8;

    // creates an array for bitset with size 8
    bitset = new intmax_t[bitset_size];

    // loop for setting all bits to 0
    for(intmax_t i = 0; i < bitset_size; i++)
    {
        bitset[i] = 0;
    }
}

Bitset::Bitset(intmax_t size) {
    // sets bitset_size to size
    if(size < 1)
    {
        valid = false;
    }
    else
    {
        bitset_size = size;

        // creates an array for bitset with size bitset_size
        bitset = new intmax_t[bitset_size];

        // loop for setting all bits to 0
        for(intmax_t i = 0; i < bitset_size; i++)
        {
            bitset[i] = 0;
        }
    }
}

Bitset::Bitset(const std::string & value) {
    // sets bitset_size to string value
    bitset_size = value.size();

    // creates an array for bitset with size 8
    bitset = new intmax_t[bitset_size];

    // loop checks to see if characters in string value are 0 or 1
    for(intmax_t i = 0; i < value.size(); i++)
    {
        if (value[i] != '0' && value[i] != '1')
        {
            valid = false;
        }
    }
    // loop for setting all bits to string value
    for(intmax_t i = 0; i < bitset_size; i++)
    {
		if(value[i] == '1')
		{
			bitset[i] = 1;
		}
		else
		{
			bitset[i] = 0;
		}
    }
}

Bitset::~Bitset() {
    // deletes bitset
    delete []bitset; 
    bitset = NULL;
}

intmax_t Bitset::size() const {
    // returns size of bitset
    return bitset_size;
}

bool Bitset::good() const {
    // determines if the bitset is valid

    // checks if bitset size is > 0
    if (bitset_size < 1)
    {
        return false;
    }

    // checks if all bits are 0 or 1
    for(intmax_t i = 0; i < bitset_size; i++)
    {
        if ((bitset[i] != 0) && (bitset[i] != 1))
        {
            return false;
        }
    }
    return valid;
}

void Bitset::set(intmax_t index) {
    // checks if n is within [0, N-1]
    if(index < 0 || index > bitset_size - 1)
    {
        valid = false;
    }
    else
    {
        // sets the nth bit to 1
        bitset[index] = 1;
    }
}

void Bitset::reset(intmax_t index) {
    // checks if n is within [0, N-1]
    if(index < 0 || index > bitset_size - 1)
    {
        valid = false;
    }
    else
    {
        // sets the nth bit to 0
        bitset[index] = 0;
    }
}

void Bitset::toggle(intmax_t index) {
    // checks if n is within [0, N-1]
    if(index < 0 || index > bitset_size - 1)
    {
        valid = false;
    }
    else
    {
        // toggle bit
        if(bitset[index] == 1)
        {
            bitset[index] = 0;
        }
        else
        {
            bitset[index] = 1;
        }
    }
}

bool Bitset::test(intmax_t index) {
    // checks if n is within [0, N-1]
    if(index < 0 || index > bitset_size - 1)
    {
        valid = false;
    }
    if(bitset[index] == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string Bitset::asString() const {
    // string variable to represent bitset as string
    std::string bitstring = "";
    // string variable representing each bit value
    std::string stringval = "";

    // loop to add bit values to bitset string
    for(int i = 0; i < bitset_size; i++)
    {
        stringval = std::to_string(bitset[i]);
        bitstring += stringval;
    }

    return bitstring;
}

