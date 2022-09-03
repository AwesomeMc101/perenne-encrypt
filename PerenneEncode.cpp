

#include "decode.h"

int main()
{
    while (1)
    {
        std::cout << "\nEncrypt (1) or Decrypt (2) || ";
        int ans;
        std::cin >> ans;

        if (ans == 1)
        {
            std::string input;
            std::cout << "What to encrypt?\n";
            std::cin.ignore();
            std::getline(std::cin, input);
            encodedString eS = encode(input);
            std::cout << "Your Encrypted String: " << eS.encodedValue;
            std::cout << "Your Key (needed!): " << eS.key;
        }
        if (ans == 2)
        {
            std::string inputa;
            std::cin.ignore();
            std::cout << "What is your encrypted string?";
            std::getline(std::cin, inputa);

            std::string inputb;
            std::cout << "What is your key?";
            std::getline(std::cin, inputb);

            encodedString eS;
            eS.encodedValue = inputa;
            eS.key = inputb;

            std::cout << "Decoded: " << decode(eS);
        }
    }
}
