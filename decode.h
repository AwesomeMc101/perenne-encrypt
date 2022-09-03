#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>

#include "encode.h"

namespace Util
{
	std::vector<std::string> splitKey(std::string key)
	{
		std::vector<std::string> keys;

		std::string stringBuilder = "";
		for (int i = 0; i < key.length(); i++)
		{
			stringBuilder += key[i];
			if (((i+1) % 5) == 0)
			{
				keys.push_back(stringBuilder);
				//::cout << "\nPush: " << stringBuilder;
				stringBuilder.clear();
			}
		}
		return keys;
	}
}

std::string decode(encodedString eS)
{
	std::vector<std::string> keys = Util::splitKey(eS.key);
	
	for (std::string key : keys)
	{
		if (key == "RRRRR")
		{
			std::reverse(eS.encodedValue.begin(), eS.encodedValue.end());
		}
		if (key[0] == 'R' && key[1] == 'A' && key[2] == 'I')
		{
			char aVal = key[3];
			char bVal = key[4];

			std::vector<size_t> aPos, bPos;

			for (int i = 0; i < eS.encodedValue.length(); i++)
			{
				if (eS.encodedValue[i] == aVal)
				{
					aPos.push_back(i);
				}
				else if (eS.encodedValue[i] == bVal)
				{
					bPos.push_back(i);
				}
			}
			for (size_t loc : aPos)
			{
				eS.encodedValue[loc] = bVal;
			}
			for (size_t loc : bPos)
			{
				eS.encodedValue[loc] = aVal;
			}
		}
	}
	std::string undone;
	Hex::hex2ascii(eS.encodedValue, undone);
	return undone;
}