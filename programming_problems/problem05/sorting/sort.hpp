#ifndef _SORT_HPP
#define _SORT_HPP

#include "linked_list.hpp"

template<typename T> LinkedList<T> sort(LinkedList<T> list)
{
	// Selection sorting
	if(list.getLength() < 2)
	{
		// do nothing
	}
	else
	{
		std::size_t count = 0; // checks to see if any changes to list occurred
		for(std::size_t i = 0; i < list.getLength() - 1; i ++)
		{
			for(std::size_t j = i + 1; j < list.getLength(); j++) // finds min value
			{
				T i1 = list.getEntry(i);
				T i2 = list.getEntry(j); // tempPtr points to node i + 1
				if(i2 < i1) // if next item is less than current item, swap
				{
					// swap contents
					list.setEntry(i, i2);
					list.setEntry(j, i1);
					count++; // increments count
				}
			}
		}
		if(count == 0) // if no shifting happened
		{
			return list; 
		}
		else
		{
			sort(list); // recursively call this function
		}
	}
	return list;
}

#endif
