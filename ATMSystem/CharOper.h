#pragma once
#include <iostream>

using namespace std;
namespace Char

{
	char fnInvertAlphabet(char Alphabet)
	{
		return isupper(Alphabet) ? tolower(Alphabet) : toupper(Alphabet);
	}

	bool fnCheckVowelCase(char Alphabet)
	{
		Alphabet = tolower(Alphabet);

		return (Alphabet == 'a' || Alphabet == 'e' || Alphabet == 'i' || Alphabet == 'u' || Alphabet == 'o');
	}
}