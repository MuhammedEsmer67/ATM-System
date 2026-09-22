#pragma once
#include <iostream>
#include <vector>
#include "CharOper.h"

using namespace std;
namespace String

{
	enum enWhatToCount { Upper = 1, Lower = 2, All = 3 };

	short fnCountLettersinString(string Text, enWhatToCount WhatToCount = enWhatToCount::All)
	{
		if (WhatToCount == enWhatToCount::All)
			return Text.length();

		short Counter = 0;

		for (short i = 1; i <= Text.length(); i++)
		{
			if (WhatToCount == enWhatToCount::Upper && isupper(Text[i - 1]))
				Counter++;
			else if (WhatToCount == enWhatToCount::Lower && islower(Text[i - 1]))
				Counter++;
		}

		return Counter;
	}

	string fnRemovePunctuationFromString(string Text)
	{
		string PunctuationReomvedText = "";

		for (short i = 1; i <= Text.length(); i++)
		{
			if (!ispunct(Text[i - 1]))
				PunctuationReomvedText += Text[i - 1];
		}

		return PunctuationReomvedText;
	}

	string fnTrimLeft(string Text)
	{
		for (short i = 1; i <= Text.length(); i++)
		{
			if (Text[i - 1] != ' ')
				return Text.substr(i - 1, Text.length() - i + 1);
		}

		return "";
	}

	string fnTrimRight(string Text)
	{
		for (short i = Text.length(); i >= 1; i--)
		{
			if (Text[i - 1] != ' ')
				return Text.substr(0, i);
		}

		return "";
	}

	string fnTrim(string Text)
	{
		return fnTrimLeft(fnTrimRight(Text));
	}

	string fnJoinString(vector <string>& vTextWords, string Delim = " ")
	{
		string Text = "";

		for (string& i : vTextWords)
			Text = Text + i + Delim;

		return Text.substr(0, Text.length() - Delim.length());
	}

	string fnJoinString(string arrTextWords[], short Length, string Delim = " ")
	{
		string Text = "";

		for (short i = 1; i <= Length; i++)
			Text = Text + arrTextWords[i - 1] + Delim;

		return Text.substr(0, Text.length() - Delim.length());
	}

	vector <string> fnSplitString(string Text, string Delim = " ")
	{
		vector <string> vSplitedWords;
		short Pos = 0;
		string Word = "";

		while ((Pos = Text.find(Delim)) != std::string::npos)
		{
			Word = Text.substr(0, Pos);

			if (Word != "")
				vSplitedWords.push_back(Word);

			Text.erase(0, Pos + Delim.length());
		}

		if (Text != "")
			vSplitedWords.push_back(Text);

		return vSplitedWords;
	}
	
	string fnReplaceWordinString(string Text, string WordToReplace, string ReplaceTo)
	{
		short Pos = Text.find(WordToReplace);

		while (Pos != std::string::npos)
		{
			Text = Text.replace(Pos, WordToReplace.length(), ReplaceTo);
			Pos = Text.find(WordToReplace);
		}

		return Text;
	}

	string fnReverseWordsinString(string Text, string Delim = " ")
	{
		vector <string> vTextWords;
		string ReversedText = "";
		vTextWords = fnSplitString(Text, Delim);

		vector <string>::iterator iteration = vTextWords.end();

		while (iteration != vTextWords.begin())
		{
			iteration--;

			ReversedText += *iteration + Delim;
		}

		return ReversedText.substr(0, ReversedText.length() - Delim.length());
	}

	short fnCountWordNumberinString(string Text)
	{
		short WordCounter = 0;
		short Pos = 0;
		string Space = " ";
		string Word = "";

		while ((Pos = Text.find(Space)) != std::string::npos)
		{
			Word = Text.substr(0, Pos);

			if (Word != "")
				WordCounter++;

			Text.erase(0, Pos + Space.length());
		}

		if (Text != "")
			WordCounter++;

		return WordCounter;
	}

	void prPrintStringWords(string Text)
	{
		short Pos = 0;
		string Space = " ";
		string Word = "";

		while ((Pos = Text.find(Space)) != std::string::npos)
		{
			Word = Text.substr(0, Pos);

			if (Word != "")
				cout << Word << endl;

			Text.erase(0, Pos + Space.length());
		}

		if (Text != "")
			cout << Text << endl;
	}

	short fnCountVowelLettersinString(string Text)
	{
		short Counter = 0;

		for (short i = 1; i <= Text.length(); i++)
		{
			if (Char::fnCheckVowelCase(Text[i - 1]))
				Counter++;
		}

		return Counter;
	}

	short fnCountTargetCharacterinString(string Text, char TargetChar, bool MatchCase = true)
	{
		short Counter = 0;

		for (short i = 1; i <= Text.length(); i++)
		{
			if (MatchCase)
			{
				if (Text[i - 1] == TargetChar)
					Counter++;
			}
			else
			{
				if (tolower(Text[i - 1]) == tolower(TargetChar))
					Counter++;
			}
		}

		return Counter;
	}

	short fnCountUpperCharactersinString(string Text)
	{
		short Counter = 0;

		for (short i = 1; i <= Text.length(); i++)
		{
			if (isupper(Text[i - 1]))
				Counter++;
		}

		return Counter;
	}

	string fnLowerFirstLetterofEachWord(string Text)
	{
		bool isFirstLetter = true;

		for (short i = 1; i <= Text.length(); i++)
		{
			if (Text[i - 1] != ' ' && Text[i - 1] != '\t' && Text[i - 1] != '\n' && isFirstLetter)
				Text[i - 1] = tolower(Text[i - 1]);

			isFirstLetter = (Text[i - 1] == ' ' || Text[i - 1] == '\t' || Text[i - 1] == '\n' ? true : false);
		}

		return Text;
	}

	string fnUpperFirstLetterofEachWord(string Text)
	{
		bool isFirstLetter = true;

		for (short i = 1; i <= Text.length(); i++)
		{
			if (Text[i - 1] != ' ' && Text[i - 1] != '\t' && Text[i - 1] != '\n' && isFirstLetter)
				Text[i - 1] = toupper(Text[i - 1]);

			isFirstLetter = (Text[i - 1] == ' ' || Text[i - 1] == '\t' || Text[i - 1] == '\n' ? true : false);
		}

		return Text;
	}

	void prPrintFirstLetterofEachWord(string Text)
	{
		bool isFirstLetter = true;

		for (short i = 1; i <= Text.length(); i++)
		{
			if (Text[i - 1] != ' ' && Text[i - 1] != '\t' && Text[i - 1] != '\n' && isFirstLetter)
				cout << Text[i - 1] << endl;

			isFirstLetter = (Text[i - 1] == ' ' || Text[i - 1] == '\t' || Text[i - 1] == '\n' ? true : false);
		}
	}

	string fnUpperAllCharactersofString(string Text)
	{
		for (short i = 1; i <= Text.length(); i++)
			Text[i - 1] = toupper(Text[i - 1]);

		return Text;
	}

	string fnLowerAllCharactersofString(string Text)
	{
		for (short i = 1; i <= Text.length(); i++)
			Text[i - 1] = tolower(Text[i - 1]);

		return Text;
	}

	string fnReplaceWordinString(string Text, string WordToReplace, string ReplaceTo, bool MatchCase = true)
	{
		vector <string> vTextWords = fnSplitString(Text, " ");

		for (string& i : vTextWords)
		{
			if (MatchCase)
			{
				if (i == WordToReplace)
					i = ReplaceTo;
			}
			else
			{
				if (fnLowerAllCharactersofString(i) == fnLowerAllCharactersofString(WordToReplace))
					i = ReplaceTo;
			}
		}

		return fnJoinString(vTextWords, " ");
	}
}