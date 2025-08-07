
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;


enum enATMchoice
{
	eQuickWithDraw = 1,
	eNormalWithdraw = 2,
	eDeposit=3,
	eCheckBalance=4,
	eLogout=5
};


enum enQuickWithdraw
{
	Twenty = 1,
	Fifty=2,
	Hundred=3,
	TwoHundred=4,
	FourHundred=5,
	SixHundred = 6,
	EightHundred=7,
	Thousand=8,
	Exit=9
};



struct strClient
{
	string accNo;
	string pincode;
	string clientName;
	string phonenumber;
	bool isMarked = false;
	double balance;
};



void Login();
vector<strClient> loadClient(string filename); //getting client from a file

//Global Variables
strClient currClient;
string ClientFileName = "clients.txt";


void ShowMainMenu(int& choice)
{
	system("cls");
	cout << "===========================\n";
	cout << "\t\t ATM Main Menu Screen\n";
	cout << "===========================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "===========================\n";
	cout << "Choose what do you want to do ? [1 to 8]: ";
	cin >> choice;
}

vector<string> splitString(string line, string del)
{
	int pos;
	vector<string> token;
	while ((pos = line.find(del)) != string::npos)
	{
		token.push_back(line.substr(0, pos));
		line.erase(0, pos + del.length());
	}
	if (!line.empty())
	{
		token.push_back(line);
	}
	return token;

}

strClient ConvertLineToRecord(string line)
{
	strClient client;
	string separator = "#//#";
	string builder = " ";
	int count = 0;
	vector<string> token = splitString(line, "#//#"); //tokens 
	client.accNo = token[0]; //account number
	client.pincode = token[1]; //pincode
	client.clientName = token[2];
	client.phonenumber = token[3];
	client.balance = stod(token[4]);

	return client;
}

vector<strClient> loadClient(string filename) //getting client from a file
{
	vector<strClient> myvec;
	strClient client;
	fstream myfile;
	string line;
	myfile.open(filename, ios::in);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			client = ConvertLineToRecord(line);
			myvec.push_back(client);
		}
	}
	myfile.close();
	return myvec;
}


string convertRecordToLine(strClient client, string del)
{
	string line = "";
	line = client.accNo + del + client.pincode + del + client.clientName + del + client.phonenumber + del + to_string(client.balance);
	return line;
}




bool FindClientWithAccountNumber(string accountNumber)
{
	vector<strClient> myvec = loadClient("clients.txt");
	for (strClient n : myvec)
	{
		if (n.accNo == accountNumber)
		{
			cout << "\n\t\t\tClient is found. The following details..:\n";
			cout << "-----------------\n";
			cout << "Accont Number: " << n.accNo << endl;
			cout << "Pin Code:\t " << n.pincode << endl;
			cout << "Name:\t\t" << n.clientName << endl;
			cout << "Phone:\t " << n.phonenumber << endl;
			cout << "Account Balance: " << n.balance << endl;
			cout << "-----------------\n\n\n\n";
			return true;
		}
	}
	cout << "The Client is not found !\n";
	return false;


}



bool FindClientWithAccountNumberAndPincode(string accountNumber,string pincode)
{
	vector<strClient> myvec = loadClient("clients.txt");
	for (strClient n : myvec)
	{
		if (n.accNo == accountNumber && n.pincode==pincode)
		{
			return true;
		}
	}
	return false;
}


strClient SaveClientInfo(string accountNumber)
{
	vector<strClient> myvec = loadClient("clients.txt");
	for (strClient n : myvec)
	{
		if (n.accNo == accountNumber)
		{
			return n;
		}
	}
	cout << "The Client is not found !";

}


void SaveDataToFile(vector<strClient> myvec)
{
	fstream file;
	file.open("clients.txt", ios::out);
	string line;
	if (file.is_open())
	{
		for (strClient n : myvec)
		{
			line = convertRecordToLine(n, "#//#");
			file << line << endl;
		}
	}
}


void ShowQuickWithdrawScreen()
{
	system("cls");
	cout << "=================================="<<endl;
	cout << "\t\tQuickdraw Withdraw" << endl;
	cout << "==================================" << endl;

	cout << "[1] 20" << setw(9) << "[2] 50" << endl;
	cout << "[3] 100" << setw(9) << "[4] 200" << endl;
	cout << "[5] 400" << setw(9) << "[6] 600" << endl;
	cout << "[7] 800" << setw(10) << "[8] 1000" << endl;
	cout << "[9] Exit" << endl;
	cout << "==================================" << endl;
}

void EditBalance(strClient& client, vector<strClient> &myvec)
{
	for (strClient& n:myvec)
	{
		if (n.accNo == client.accNo)
		{
			n.balance = client.balance;
			return;
		}
	}
}



int ReturnClientBalance()
{
	return currClient.balance;
}

void ATMQuickwithDraw()
{
	int choice;
	bool isValid;
	char confirm;
	int OrgBalance = currClient.balance;
	do
	{
		isValid = true;
		ShowQuickWithdrawScreen();
		cout << "your Balance is " << ReturnClientBalance() << endl;
		cout << "Choose What to withdraw from [1] to [8] ? " << endl;
		cin >> choice;


		if (choice == enQuickWithdraw::Exit)
		{
			cout << "Press Any Key To Go Back To Main Menu...";
			system("pause>0");
			return;
		}
		
		if (choice == enQuickWithdraw::Twenty && currClient.balance >= enQuickWithdraw::Twenty)
		{
			currClient.balance = currClient.balance - 20;
		}
		else if (choice == enQuickWithdraw::Fifty && currClient.balance >= enQuickWithdraw::Fifty )
		{
			currClient.balance = currClient.balance - 50;
		}
		else if (choice == enQuickWithdraw::Hundred && currClient.balance >= enQuickWithdraw::Hundred )
		{
			currClient.balance = currClient.balance - 100;
		}
		else if (choice == enQuickWithdraw::TwoHundred && currClient.balance >= enQuickWithdraw::TwoHundred )
		{
			currClient.balance = currClient.balance - 200;
		}
		else if (choice == enQuickWithdraw::FourHundred && currClient.balance >= enQuickWithdraw::FourHundred)
		{
			currClient.balance = currClient.balance - 400;
		}
		else if (choice == enQuickWithdraw::EightHundred && currClient.balance >= enQuickWithdraw::EightHundred)
		{
			currClient.balance = currClient.balance - 800;
		}
		else if (choice == enQuickWithdraw::Thousand && currClient.balance >= enQuickWithdraw::Thousand)
		{
			currClient.balance = currClient.balance - 1000;
		}

		if (currClient.balance < 0)
		{
			cout << "The Amount Exceeds Your Balance, Make Another Choice." << endl;
			system("pause");
			currClient.balance = OrgBalance;
			isValid = false;
		}

	} while (!isValid);


	vector<strClient> myvec = loadClient(ClientFileName);
	EditBalance(currClient, myvec);
	SaveDataToFile(myvec);
	cout << "Done Successfully. New Balance: " << currClient.balance << endl;
	system("pause");
	return;
}


void ShowNormalWithdrawScreen()
{
	system("cls");
	cout << "==================================" << endl;
	cout << "\t\t Normal Withdraw Screen" << endl;
	cout << "==================================" << endl;


}


void ATMnormalWithdraw()
{
	ShowNormalWithdrawScreen();


	int OrgBalance = currClient.balance;
	int amount;
	char confirm;
	const int remainder = 5;
	do
	{
		currClient.balance = OrgBalance;
		cout << "Enter An Amount Mulitple Of 5's ? ";
		cin >> amount;
		currClient.balance -= amount;
		if (currClient.balance < 0)
		{
			cout << "The Withdraw Amount Can Not Exceed The Balance" << endl << endl;
			system("pause");
			ShowNormalWithdrawScreen();
		}
	} while (amount%remainder!=0 || amount<0 || currClient.balance<0);

	cout << "Are You Sure You Want To Perform This Transaction? Y/N? ";
	cin >> confirm;

	if (toupper(confirm) != 'Y')
	{
		cout << "Press Any Key To Return To Main Menu...";
		system("pause>0");
		return;
	}

	vector<strClient> myvec = loadClient(ClientFileName);
	EditBalance(currClient, myvec);
	SaveDataToFile(myvec);
	cout << "Done Successfully! New Balance: " << currClient.balance << endl;
	cout << "\nPress Any Key To Go Back To Main Menu...";
	system("pause>0");
}


void ShowDepositScreen()
{
	system("cls");
	cout << "==================================" << endl;
	cout << "\t\t  Deposit Screen" << endl;
	cout << "==================================" << endl;
}



void ATMdeposit()
{
	ShowDepositScreen();
	
	int amount;
	char confirm;

	do
	{
		cout << "Enter a positive deposit number? ";
		cin >> amount;
	} while (amount<0);
	
	currClient.balance += amount;

	cout << "Are You Sure You Want To Perform This Operation? Y/N? ";
	cin >> confirm;

	if (toupper(confirm) != 'Y')
	{
		cout << "Operation Is Cancelled" << endl << endl;
		cout << "Press Any Key To Turn Back To Main Menu...";
		system("pause>0");
		return;
	}
	vector<strClient> myvec = loadClient(ClientFileName);
	EditBalance(currClient, myvec);
	SaveDataToFile(myvec);
	cout << "Sucess! New Balance: " << currClient.balance << endl<<endl;
	cout << "Press Any Key To Turn Back To Main Menu...";
	system("pause>0");
}


void ShowCheckBalanceScreen()
{
	system("cls");
	cout << "==================================" << endl;
	cout << "\t\t  Check Balance Screen" << endl;
	cout << "==================================" << endl;
}

void CheckBalance()
{
	ShowCheckBalanceScreen();
	cout <<"Your Balance is: "<< currClient.balance<<endl;
	cout << "Press Any Key To Go Back To Main Menu...";
	system("pause>0");
}



void MainMenu()
{
	int choice;

	do
	{
		ShowMainMenu(choice);
		switch (choice)
		{

			case enATMchoice::eQuickWithDraw:
			{
				ATMQuickwithDraw();
				break;
			}
			case enATMchoice::eNormalWithdraw:
			{
				ATMnormalWithdraw();
				break;
			}

			case enATMchoice::eDeposit:
			{
				ATMdeposit();
				break;
			}
			
			case enATMchoice::eCheckBalance:
			{
				CheckBalance();
				break;
			}

			case enATMchoice::eLogout:
			{
				Login();
				break;
			}

		}


	} while (choice != enATMchoice::eLogout);


}

void showLoginScreen()
{
	cout << "----------------------------------------------\n";
	cout << "\t\t Log in Screen\n";
	cout << "----------------------------------------------\n";
}
void ReturnClientInfoFromAccNo()
{
	vector<strClient> myvec = loadClient(ClientFileName);
	for (strClient& n : myvec)
	{
		if (n.accNo == currClient.accNo)
		{
			currClient.balance = n.balance;
			currClient.phonenumber = n.phonenumber;
			return;
		}
	}

}

void Login()
{
	system("cls");
	string accNo;
	string pincode;
	showLoginScreen();
	while(true)
	{
		cout << "Enter AccountNumber ? ";
		cin >> accNo;
		cout << "Enter pincode? ";
		cin >> pincode;

		if (FindClientWithAccountNumberAndPincode(accNo,pincode))//result is true
		{
			ReturnClientInfoFromAccNo();
			MainMenu();
		}
		else
		{
			system("cls");
			showLoginScreen();
			cout << "Invalid AccNo/pincode!" << endl;
		}

	}
	

}


int main()
{
	Login();
}

