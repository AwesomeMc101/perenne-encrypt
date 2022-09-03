#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <map>

class encodedString
{
public:
	std::string encodedValue;
	std::string key;
};

namespace Hex {
	std::string toHex(std::string str)
	{
		std::stringstream returnVal;
		for (const auto& item : str) {
			returnVal << std::hex << int(item);
		}

		return returnVal.str();
	}

	unsigned char hexval(unsigned char c)
	{
		if ('0' <= c && c <= '9')
			return c - '0';
		else if ('a' <= c && c <= 'f')
			return c - 'a' + 10;
		else if ('A' <= c && c <= 'F')
			return c - 'A' + 10;
		else abort();
	}
	void hex2ascii(const std::string& in, std::string& out)
	{
		out.clear();
		out.reserve(in.length() / 2);
		for (std::string::const_iterator p = in.begin(); p != in.end(); p++)
		{
			unsigned char c = hexval(*p);
			p++;
			if (p == in.end()) break;
			c = (c << 4) + hexval(*p);
			out.push_back(c);
		}
	}
}

encodedString encode(std::string str)
{
	encodedString eS;
	std::string hexed = Hex::toHex(str);
	std::string unhexed;
	

	//RRRRR [Reverse] || FFFFF [Forward]
	srand(time(NULL));
	bool isReverse = ((rand() % 10) > 5);
	if (isReverse)
	{
		eS.key += "RRRRR";
		std::reverse(hexed.begin(), hexed.end());
	}
	else
	{
		eS.key += "FFFFF";
	}

	//RAIxy [Replace All Int x w/ y && vice-versa]
	std::vector<int> replaced;
	for (int i = 0; i < 4; i++)
	{
		entry:
		int toChange = ((rand() % 9 + 1));
		int changeWith = ((rand() % 9 + 1));

		for (int rep : replaced)
		{
			if (rep == toChange || rep == changeWith) {
				goto entry;
			}
		}

		if (toChange == changeWith)
		{
			goto entry;
		}

		replaced.push_back(toChange);
		replaced.push_back(changeWith);

		eS.key += "RAI" + std::to_string(toChange) + std::to_string(changeWith);

		for (int sp = 0; sp < hexed.length(); sp++)
		{
			char toCheck = (hexed.at(sp));
			if (toCheck == '0')
			{
				continue;
			}
			int checkNum = (toCheck - '0');
			if (checkNum == toChange)
			{
				std::string conv = std::to_string(changeWith);
				hexed[sp] = conv[0];
			}
			else if (checkNum == changeWith)
			{
				std::string conv = std::to_string(toChange);
				hexed[sp] = conv[0];
			}
		}
	}

	eS.encodedValue = hexed;
	return eS;
}