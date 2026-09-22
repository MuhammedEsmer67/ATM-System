#pragma once
#include <iostream>
#include <string>
#include "TimeOper.h"

using namespace std;
namespace io

{
	short fnReadPositiveComplicationNumber(string Message, short ComplicationNumber)
	{
		short PositiveNumber = 0;

		do
		{
			cout << Message;
			cin >> PositiveNumber;
		} while (PositiveNumber < ComplicationNumber || (PositiveNumber % ComplicationNumber));

		return PositiveNumber;
	}

	char fnReadCharacter(string Message)
	{
		char Character = ' ';

		cout << Message;
		cin >> Character;

		return Character;
	}

	char fnReadBool(string Message)
	{
		bool isTrue = true;

		cout << Message;
		cin >> isTrue;

		return isTrue;
	}

	char fnReadAlphabet(string Message)
	{
		char Alphabet = ' ';

		do
		{
			cout << Message;
			cin >> Alphabet;
		} while (Alphabet < 65 || (Alphabet > 90 && Alphabet < 97) || Alphabet > 122);

		return Alphabet;
	}

	short fnReadIntegerNumberInRange(string Message, short From, short To)
	{
		short PositiveNumber = 0;

		do
		{
			cout << Message;
			cin >> PositiveNumber;
		} while (PositiveNumber < From || PositiveNumber > To);

		return PositiveNumber;
	}

	short fnReadPositiveNumber(string Message)
	{
		short PositiveNumber = 0;

		do
		{
			cout << Message;
			cin >> PositiveNumber;
		} while (PositiveNumber < 0);

		return PositiveNumber;
	}

	float fnReadPositiveFloatNumber(string Message)
	{
		float PositiveFloatNumber = 0;

		do
		{
			cout << Message;
			cin >> PositiveFloatNumber;
		} while (PositiveFloatNumber < 0);

		return PositiveFloatNumber;
	}

	string fnReadText(string Message)
	{
		string Text = "";

		cout << Message;
		getline(cin, Text);

		return Text;
	}

	string fnReadString(string Message)
	{
		string Text = "";

		cout << Message;
		cin >> Text;

		return Text;
	}

	Time::stDate fnReadFullDate()
	{
		Time::stDate DateInfo;

		DateInfo.Year = fnReadPositiveNumber("Please enter a year: ");
		DateInfo.Month = fnReadIntegerNumberInRange("Please enter a month: ", 1, 12);
		DateInfo.Day = fnReadIntegerNumberInRange("Please enter a day: ", 1, Time::fnDaysInMonth(DateInfo.Month, DateInfo.Year));

		return DateInfo;
	}

	string fnReadTextWithSkipWhiteSpace(string Message)
	{
		string Text = "";

		cout << Message;
		getline(cin >> ws, Text);

		return Text;
	}
}
