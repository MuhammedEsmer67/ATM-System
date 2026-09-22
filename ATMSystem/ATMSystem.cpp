#include <iostream>
#include <fstream>
#include "StringOper.h"
#include "io_utils.h"

using namespace std;

struct stClientData
{
	string AccountNumber;
	string PinCode;
	string UserName;
	string PhoneNumber;
	float AccountBalance;
	bool MarkWantedClient = true;
};

enum enOptionList { QuikWithdraw = 1, NormalWithdraw = 2, Deposit = 3, CheckBalance = 4, ChangePinCode = 5, Logout = 6 };

const string ClientsFileName = "Clients Records";
const string Delim = "#//#";
stClientData CurrentClient;

void prATMMainMenue(vector <stClientData>&);

bool fnCheckIfCanWithdraw(stClientData CurrentClient)
{
	return (CurrentClient.AccountBalance > 5);
}

stClientData fnFillClientRecord(string Record, string Delim)
{
	vector <string> vSplitedWords = String::fnSplitString(Record, Delim);
	stClientData ClientRecord;

	ClientRecord.AccountNumber = vSplitedWords[0];
	ClientRecord.PinCode = vSplitedWords[1];
	ClientRecord.UserName = vSplitedWords[2];
	ClientRecord.PhoneNumber = vSplitedWords[3];
	ClientRecord.AccountBalance = stof(vSplitedWords[4]);

	return ClientRecord;
}

void prUpdateClientData(vector <stClientData>& vClientsData, stClientData CurrentClient)
{
	for (stClientData& Client : vClientsData)
	{
		if (CurrentClient.AccountNumber == Client.AccountNumber)
		{
			Client = CurrentClient;
			break;
		}
	}
}

vector <stClientData> fnReadFromClientFile(string ClientsFileName, string Delim)
{
	fstream File;
	vector <stClientData> vClientsRecords;
	ClientsFileName += ".txt";

	File.open(ClientsFileName, ios::in);

	if (File.is_open())
	{
		string Record = "";
		stClientData ClientRecord;

		while (getline(File, Record))
		{
			ClientRecord = fnFillClientRecord(Record, Delim);
			vClientsRecords.push_back(ClientRecord);
		}
	}

	File.close();

	return vClientsRecords;
}

void prGoBackToMainMenue(vector <stClientData>& vClientsData)
{
	cout << "\nPress any key to return to main menu...";
	system("pause > 0");
	prATMMainMenue(vClientsData);
}

bool fnCheckIfClientDataExists(string AccountNumber, string PinCode, stClientData& CurrentClient, vector <stClientData>& vClientsData)
{
	for (stClientData& Client : vClientsData)
	{
		if (Client.AccountNumber == AccountNumber && Client.PinCode == PinCode)
		{
			CurrentClient = Client;
			return true;
		}
	}

	return false;
}

string fnConvertClientRecordToString(stClientData ClientRecord, string Delim)
{
	string RecordLine = "";

	RecordLine += ClientRecord.AccountNumber + Delim;
	RecordLine += ClientRecord.PinCode + Delim;
	RecordLine += ClientRecord.UserName + Delim;
	RecordLine += ClientRecord.PhoneNumber + Delim;
	RecordLine += to_string(ClientRecord.AccountBalance);

	return RecordLine;
}

void prUpdateClientFile(string ClientsFileName, string Delim, vector <stClientData> vClientsData)
{
	fstream File;
	ClientsFileName += ".txt";

	File.open(ClientsFileName, ios::out);

	if (File.is_open())
	{
		string Text = "";

		for (stClientData& Client : vClientsData)
		{
			if (Client.MarkWantedClient)
			{
				Text = fnConvertClientRecordToString(Client, Delim);
				File << Text << endl;
			}
		}
	}

	File.close();
}

int fnDepositClientBalance(int DepositAmount)
{
	return CurrentClient.AccountBalance += DepositAmount;
}

void prQuikWithdraw(vector <stClientData>& vClientsData)
{
	short OptionList = 0;
	int QuikWithdrawOptions[9] = { 0,20,50,100,200,400,800,1000 };

	do
	{
		system("cls");

		cout << "_____________________________________________________\n";
		cout << "\t\tQuik Withdraw Screen\n";
		cout << "_____________________________________________________\n";
		cout << "\t[1] 20\t[2] 50\n";
		cout << "\t[3] 100\t[4] 200\n";
		cout << "\t[5] 400\t[6] 600\n";
		cout << "\t[7] 800\t[8] 1000\n";
		cout << "\t[9] Exit.\n";
		cout << "_____________________________________________________\n";
		cout << "\nYour Balance is: " << CurrentClient.AccountBalance << endl << endl;

		OptionList = io::fnReadIntegerNumberInRange("Choose what to do from? [1 to 9] ", 1, 9);

		if (OptionList == 9)
			return;

		if (CurrentClient.AccountBalance < QuikWithdrawOptions[OptionList])
		{
			cout << "\nAmount Exceeds the balance, you can withdraw up to: " << CurrentClient.AccountBalance << endl;
			cout << "\nPress any key to continue...";
			system("pause > 0");
		}

	} while (CurrentClient.AccountBalance < QuikWithdrawOptions[OptionList]);

	bool isPerform = io::fnReadBool("\nAre you sure you want to perform this transaction? (Yes:1, No:0) ");

	if (isPerform)
	{
		CurrentClient.AccountBalance = fnDepositClientBalance(-1 * QuikWithdrawOptions[OptionList]);
		prUpdateClientData(vClientsData, CurrentClient);
		prUpdateClientFile(ClientsFileName, Delim, vClientsData);
		cout << "\nClient updated successfully, new balance is: " << CurrentClient.AccountBalance << endl;
	}
	else
		cout << "\nClient Updated Failed!\n";
}

void prNormalWithdraw(vector <stClientData>& vClientsData)
{
	if (!fnCheckIfCanWithdraw(CurrentClient))
	{
		system("cls");

		cout << "\n_____________________________________________________\n";
		cout << "\n\t\tWithdraw Screen\n";
		cout << "_____________________________________________________\n";
		cout << "\nYour account balance is less then 5$ you cannot withdraw!\n";
		return;
	}

	int WithdrawAmount = 0;

	do
	{
		system("cls");

		cout << "\n_____________________________________________________\n";
		cout << "\n\t\tWithdraw Screen\n";
		cout << "_____________________________________________________\n";
		cout << "\nYour Balance is: " << CurrentClient.AccountBalance << endl << endl;

		WithdrawAmount = io::fnReadPositiveComplicationNumber("Please enter another amount: (5 complications) ", 5);

		if (CurrentClient.AccountBalance < WithdrawAmount)
		{
			cout << "\nAmount Exceeds the balance, you can withdraw up to: " << CurrentClient.AccountBalance << endl;
			cout << "\nPress any key to continue...";
			system("pause > 0");
		}

	}while (CurrentClient.AccountBalance < WithdrawAmount);

	bool isPerform = io::fnReadBool("\nAre you sure you want to perform this transaction? (Yes:1, No:0) ");

	if (isPerform)
	{
		CurrentClient.AccountBalance = fnDepositClientBalance(-1 * WithdrawAmount);
		prUpdateClientData(vClientsData, CurrentClient);
		prUpdateClientFile(ClientsFileName, Delim, vClientsData);
		cout << "\nClient updated successfully, new balance is: " << CurrentClient.AccountBalance << endl;
	}
	else
		cout << "\nClient Updated Failed!\n";
}

void prDeposit(vector <stClientData>& vClientsData)
{
	cout << "\n_____________________________________________________\n";
	cout << "\n\t\tDeposit Screen\n";
	cout << "_____________________________________________________\n";
	cout << "\nYour Balance is: " << CurrentClient.AccountBalance << endl << endl;

	int DepositAmount = io::fnReadPositiveComplicationNumber("Please enter deposit amount: (5 complications) ", 5);

	bool isPerform = io::fnReadBool("\nAre you sure you want to perform this transaction? (Yes:1, No:0) ");

	if (isPerform)
	{
		CurrentClient.AccountBalance = fnDepositClientBalance(DepositAmount);
		prUpdateClientData(vClientsData, CurrentClient);
		prUpdateClientFile(ClientsFileName, Delim, vClientsData);
		cout << "\nClient updated successfully, new balance is: " << CurrentClient.AccountBalance << endl;
	}
	else
		cout << "\nClient Updated Failed!\n";
}

void prCheckBalance()
{
	cout << "\n_____________________________________________________\n";
	cout << "\n\t\tCheck Balance Screen\n";
	cout << "_____________________________________________________\n";
	cout << "Your Balance is: " << CurrentClient.AccountBalance << endl << endl;
}

void prChangePinCode(vector <stClientData>& vClientsData)
{
	cout << "\n_____________________________________________________\n";
	cout << "\n\t\tChange Pin Code Screen\n";
	cout << "_____________________________________________________\n";
	cout << "Your Current pincode is: " << CurrentClient.PinCode << endl << endl;

	CurrentClient.PinCode = io::fnReadString("Please enter your new pincode: ");

	bool isPerform = io::fnReadBool("\nAre you sure you want to change your pincode? (Yes:1, No:0) ");

	if (isPerform)
	{
		prUpdateClientData(vClientsData, CurrentClient);
		prUpdateClientFile(ClientsFileName, Delim, vClientsData);
		cout << "\nClient updated successfully, new pin code is: " << CurrentClient.PinCode << endl;
	}
	else
		cout << "\nClient Updated Failed!\n";
}

void prLoginScreen(vector <stClientData>& vClientsData)
{
	string AccountNumber = "";
	string PinCode = "";
	bool isExist = true;

	do
	{
		system("cls");

		cout << "================================================\n";
		cout << "\t\tLogin Screen\n";
		cout << "================================================\n\n";

		if (!isExist)
			cout << "Invalid Account Number/PinCode!\n";

		AccountNumber = io::fnReadString("Enter AccountNumber: ");
		PinCode = io::fnReadString("Enter PinCode: ");

		isExist = fnCheckIfClientDataExists(AccountNumber, PinCode, CurrentClient, vClientsData);

	} while (!isExist);

	prATMMainMenue(vClientsData);
}

void prDecideWhichOption(enOptionList OptionList, vector <stClientData>& vClientsData)
{
	switch (OptionList)
	{
	case enOptionList::QuikWithdraw:
	{
		prQuikWithdraw(vClientsData);
		prGoBackToMainMenue(vClientsData);
		break;
	}
	case enOptionList::NormalWithdraw:
	{
		prNormalWithdraw(vClientsData);
		prGoBackToMainMenue(vClientsData);
		break;
	}
	case enOptionList::Deposit:
	{
		system("cls");
		prDeposit(vClientsData);
		prGoBackToMainMenue(vClientsData);
		break;
	}
	case enOptionList::CheckBalance:
	{
		system("cls");
		prCheckBalance();
		prGoBackToMainMenue(vClientsData);
		break;
	}
	case enOptionList::ChangePinCode:
	{
		system("cls");
		prChangePinCode(vClientsData);
		prGoBackToMainMenue(vClientsData);
		break;
	}
	default:
		prLoginScreen(vClientsData);
	}
}

void prATMMainMenue(vector <stClientData>& vClientsData)
{
	system("cls");

	cout << "================================================\n";
	cout << "\t\tATM Main Menue Screen\n";
	cout << "================================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Change Pin Code.\n";
	cout << "\t[6] Logout.\n";
	cout << "================================================\n";

	short OptionList = io::fnReadIntegerNumberInRange("Choose what do you want to do? [1 to 6] ", 1, 6);

	prDecideWhichOption(enOptionList(OptionList), vClientsData);
}

int main()
{
	vector <stClientData> vClientsData = fnReadFromClientFile(ClientsFileName, Delim);

	prLoginScreen(vClientsData);

	system("pause > 0");
	return 0;
}