#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;
const string clientsfilename = " client.txt";
void showmainemenue();
void showTransachtionsmenue();
struct xclient
{
	string Acountnumber;
	string pincode;
	string Name;
	string phone;
	double Acountbalance;
	bool Markfordelete = false;
};
vector<string> splitString(string S1, string Delim)
{
	vector<string> vString;
	short pos = 0; 
	string sWord;
	 
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
			if (sWord != "")
			{
				vString.push_back(sWord);
			}
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1);
	}return vString;
}  
xclient convredrecord(string line, string sebritr = "//")
{
	xclient  client;
	vector <string> vclientdata ;
	vclientdata = splitString(line, sebritr);
	client.Acountnumber = vclientdata[0];
	client.pincode = vclientdata[1];
	client.Name = vclientdata[2];
	client.phone = vclientdata[3];
	client.Acountbalance = stod(vclientdata[4]);

	return client;
}
string convredrecordtoline(xclient client, string sebritr = "//")
{
	string stclientrecord = "";
	stclientrecord += client.Acountnumber + sebritr;
	stclientrecord += client.pincode + sebritr;
	stclientrecord += client.Name + sebritr;
	stclientrecord += client.phone + sebritr;
	stclientrecord += to_string (client.Acountbalance );
	return stclientrecord;
}
bool clientexistsbyacountnumber(string Acountnumber, string filename)
{
	vector <xclient> vclients;
	fstream myfile;  
	myfile.open(filename, ios::in); //read mode

	if (myfile.is_open())
	{
		string line;
		xclient client;
		while (getline(myfile, line))
		{          
			client = convredrecord(line);
			if (client.Acountnumber == Acountnumber)     
			{               
				myfile.close();
			    return true;      
			}           
			vclients.push_back(client);
		}       
		myfile.close();
	} 
	return false;
} 
xclient readnewclient()
{
	xclient client;
	cout << "Enter Acount Number ? ";
	getline(cin >> ws, client.Acountnumber);

	while (clientexistsbyacountnumber(client.Acountnumber, clientsfilename))
	{
		cout << "\nClient with [" << client.Acountnumber << "] Already Exists, Enter Anoter Acount Number ";
		getline(cin >> ws, client.Acountnumber);
	}
	cout << "Enter Pin Code ? ";
	getline(cin, client.pincode);

	cout << "Enter Name ? ";
	getline(cin, client.Name);

	cout << "Enter Phone ? ";
	getline(cin, client.phone);

	cout << "Enter Acount Balance ? ";
	cin >> client.Acountbalance;
	return client;
}
vector <xclient>loadcleintdata(string filename)
{
	vector <xclient> vclients;
	fstream myfile;

	myfile.open(filename, ios::in);
	
	if (myfile.is_open())
	{
		string line;
		xclient client;
		while (getline(myfile, line))
		{
			client = convredrecord(line);
			vclients.push_back(client);
		}
	     myfile.close();

	}
	return vclients;
	
}
void printClientrecord(xclient client)
{
	cout << "|" << setw(15) << left << client.Acountnumber;
	cout << "|" << setw(11) << left << client.pincode;
	cout << "|" << setw(39) << left << client.Name;
	cout << "|" << setw(12) << left << client.phone;
	cout << "|" << setw(12) << left << client.Acountbalance;
}
void PrintClientRecordBalanceLine(xclient client)
{

	cout << "| " << setw(15) << left << client.Acountnumber;
	cout << "| " << setw(40) << left << client.Name;
	cout << "| " << setw(12) << left << client.Acountbalance;
}
void showallclientscren()
{
	vector <xclient> vclients = loadcleintdata(clientsfilename);
	cout << "\n\t\t\t\t\t Client List (" << vclients.size() << ") Client(s).";
	cout << "\n--------------------------------------------------------";
	cout << "-----------------------------------------\n";

	cout << "|" << setw(15) << left << " Acount Number ";
	cout << "|" << setw(10) << left << " Pin Code  ";
	cout << "|" << setw(39) << left << " Client Name ";
	cout << "|" << setw(12) << left << " Phone ";
	cout << "|" << setw(12) << left << " Balance ";

	cout << "\n--------------------------------------------------------";
	cout << "-----------------------------------------\n";

	if (vclients.size() == 0)

		cout << "\t\t\t\tNo Clients Available In The System!";
	else
		for (xclient client : vclients)
		{
			printClientrecord(client);
			cout << endl;
		}
	cout << "\n--------------------------------------------------------";
	cout << "-----------------------------------------\n";
}
void showtotalbalance()
	
{
	vector <xclient> vclients = loadcleintdata(clientsfilename);

	cout << "\n\t\t\t\t\t Client List (" << vclients.size() << ") Client(s).";
	cout << "\n--------------------------------------------------------";
	cout << "-----------------------------------------\n";

	cout << "|" << setw(16) << left << " Acount Number ";
	cout << "|" << setw(41) << left << " Client Name ";
	cout << "|" << setw(12) << left << " Balance ";

	cout << "\n--------------------------------------------------------";
	cout << "-----------------------------------------\n";

	double totalbalances = 0;

	if (vclients.size() == 0)

	cout << "\t\t\t\tNo Clients Available In The System!";

	else
		for (xclient client : vclients)
		{
		    PrintClientRecordBalanceLine(client);
			totalbalances += client.Acountbalance;
			cout << endl;
		}
	cout << "\n--------------------------------------------------------";
	cout << "-----------------------------------------\n";
	cout << "\t\t\t\t\t    Total Balances = " << totalbalances;
}
void printClientcard(xclient cleint)
{
	cout << "\n The following are the client details:\n";
	cout << "\nAcount Number  : " << cleint.Acountnumber;
	cout << "\nPin Code       : " << cleint.pincode;
	cout << "\nClient Name    : " << cleint.Name;
	cout << "\nPhone          : " << cleint.phone;
	cout << "\nBalance        : " << cleint.Acountbalance;
}
bool findcliendbyacountnumber(string Acountnumber, vector <xclient> vcleints, xclient& cleint)
{

	for (xclient c : vcleints)
	{
		if (c.Acountnumber == Acountnumber)
		{
			cleint = c;
			return true;
		}
	}
	return false;
}
xclient changeclientrecord(string Acountnumber)
{
	xclient client;
	client.Acountnumber = Acountnumber;

	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, client.pincode);
	cout << "Enter Name? ";
	getline(cin, client.Name);
	cout << "Enter Phone? ";
	getline(cin, client.phone);
	cout << "Enter AccountBalance? ";
	cin >> client.Acountbalance;
	return client;
}
bool markclientfordeletebyaccountnumber(string acountnumber, vector <xclient>& vclients)
{
	for (xclient& C : vclients)
	{
		if (C.Acountnumber == acountnumber)
		{
			C.Markfordelete = true;
			return true;
		}
	} return false;
}
vector <xclient> savecleintsdatatofile(string filename, vector<xclient> vclients)
{
	fstream myfile;
	myfile.open(filename, ios::out);
	string dataline;
	if (myfile.is_open())
	{
		for (xclient C : vclients)

		{

			if (C.Markfordelete == false)
			{

				dataline = convredrecordtoline(C);
				myfile << dataline << endl;
			}
		}
		myfile.close();
	}
	return vclients;
}
void adddatalinetofile(string filename, string stdataline)
{
	fstream myfile;
	myfile.open(filename, ios::out | ios::app);
	if (myfile.is_open())
	{
		myfile << stdataline << endl;
		myfile.close();
	}
}
void addnewclient()
{
	xclient client;
	client = readnewclient();
	adddatalinetofile(clientsfilename, convredrecordtoline(client));
}
void addnewclients()
{
	char addmori = 'Y';
	do
	{
		cout << "Adeeng New Clients : \n\n";
		addnewclient();
		cout << "\n Client Added Suucssfule, do you want to add more clints ? ( Y & N ) ?";
		cin >> addmori;
	} while (toupper(addmori) == 'Y');


}
bool deleteclientbyacountnumber(string Acountnumber, vector<xclient>& vclients)
{
	xclient client;
	char answer = 'n';
	if (findcliendbyacountnumber(Acountnumber, vclients, client))
	{
		printClientcard(client);
		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			markclientfordeletebyaccountnumber(Acountnumber, vclients);
			savecleintsdatatofile(clientsfilename, vclients);

			 vclients= loadcleintdata(clientsfilename); 

			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << Acountnumber << ") is Not Found!";
		return false;
	}
}
bool updateclientbyacountnumber(string Acountnumber, vector<xclient>& vclients)
{
	xclient client;
	char answer = 'n';

	if (findcliendbyacountnumber(Acountnumber, vclients, client));
	{
		printClientrecord(client);
		cout << "\n\nAre you sure you want update this client? y/n ? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			for (xclient& C : vclients)
			{
				if (C.Acountnumber == Acountnumber)
				{
					C = changeclientrecord(Acountnumber);
					break;
				}
			}  
			savecleintsdatatofile(clientsfilename, vclients);

			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}

}
bool depositbalancetoclientbyaccountnumber(string Acountnumber, double Amount, vector <xclient>& vclients)
{
	char Answer = 'n';
	cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y')
	{
		for (xclient& C : vclients)
		{
			if (C.Acountnumber == Acountnumber) {
				C.Acountbalance += Amount;
				savecleintsdatatofile(clientsfilename, vclients);
				cout << "\n\nDone Successfully. New balance is: " << C.Acountbalance;
				return true;
			}
		}
		return false;
	}
}
string reeadclientacountnumber()
{
	string Acountnumber = "";
	cout << "\n Plese Enter Acount Number ";
	cin >> Acountnumber;
	return Acountnumber;
}
void ShowDeleteClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";
	vector <xclient> vclients = loadcleintdata(clientsfilename);
	string Acountnumber = reeadclientacountnumber();
	deleteclientbyacountnumber(Acountnumber, vclients);
}
void ShowUpdateClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n-----------------------------------\n";
	vector <xclient> vclients = loadcleintdata(clientsfilename);
	string Acountnumber = reeadclientacountnumber();
	updateclientbyacountnumber(Acountnumber, vclients);
}
void showaddnewclientsscreen()
{
	cout << "\n---------------------------------\n";
	cout << "\t Add New Clients Screen ";
	cout << "\n---------------------------------\n";
	addnewclients();
}
void showfindclientscreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";
	vector <xclient> vclients = loadcleintdata(clientsfilename);
	xclient client;
	string AccountNumber = reeadclientacountnumber();
	if (findcliendbyacountnumber(AccountNumber, vclients, client))
		printClientcard(client);
	else
		cout << "\nClient With Acount Number [" << AccountNumber << "] Is Not Found !";
}
void showendscreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\t THANKS :-) ";
	cout << "\n-----------------------------------\n";
}
void showdibosetscreen()
{

	cout << "\n-----------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n-----------------------------------\n";

	xclient client;
	vector <xclient> vclients = loadcleintdata(clientsfilename);
	string Acountnumber = reeadclientacountnumber();

	while (!findcliendbyacountnumber(Acountnumber, vclients, client))
	{
		cout << "\nClient With [" << Acountnumber << "] Does Not Exist\n";
		Acountnumber = reeadclientacountnumber();
	}

	printClientcard(client);

	double Amount = 0;
	cout << "\nPlise Enter Deposit Amount ? ";
	cin >> Amount;
	depositbalancetoclientbyaccountnumber(Acountnumber, Amount, vclients);

}
void showwithdrowscreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tWithdrow Screen";
	cout << "\n-----------------------------------\n";

	xclient client;
	vector <xclient> vclients = loadcleintdata(clientsfilename);
	string Acountnumber = reeadclientacountnumber();


	while (!findcliendbyacountnumber(Acountnumber, vclients, client))
	{
		cout << "\nClient With [" << Acountnumber << "] Does Not Exist.\n";
		Acountnumber = reeadclientacountnumber();
	}
	printClientcard(client);

	double Amount = 0;
	cout << "\nPlise Enter Deposit Amount ";
	cin >> Amount;

	while (Amount > client.Acountbalance)
	{
		cout << "\ Amount Exceeds the balance, you can withdraw up to :" << client.Acountbalance << "] Does Not Exist\n";
		cout << "Plese Enter Another Amount ? ";
		cin >> Amount;
	}
	depositbalancetoclientbyaccountnumber(Acountnumber, Amount * -1, vclients);
}
enum enTransactionoptions
{
	edeposit = 1, ewithdraw = 2,
	etotalbalance = 3, emainmenue = 4,
};
enum enmainmenueoption
{
	elistclient = 1, eaddnewclient = 2,
	edeleteclient = 3, eupdateclient = 4,
	efindclient = 5, eTransachtions = 6,
	eexit = 7
};
void gobakctomainmenue()
{
	cout << "\n\n press any key to go back to main menue....";
	system("pause>0");
	showmainemenue();
}
void GoBackToTransactionsMenue()
{

	cout << "\n\nPress any key to go back to Transactions Menue...";
	system("pause>0");
	showTransachtionsmenue();
}
short readTransactionsMenueOption()
{
	cout << "Choose what do you want to do? [1 to 4]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
void performTransachtionmenueoption(enTransactionoptions Transachtionmenueoption)
{
	switch (Transachtionmenueoption)
	{
	case enTransactionoptions::edeposit:
	{
		system("cls");
		showdibosetscreen();
		GoBackToTransactionsMenue();
		break;
	}
	case enTransactionoptions::ewithdraw:
	{
		system("cls");
		showwithdrowscreen();
		GoBackToTransactionsMenue();
		break;
	}
	case enTransactionoptions::etotalbalance:
	{
		system("cls");
		showtotalbalance();
		GoBackToTransactionsMenue();
		break;
	}
	case enTransactionoptions::emainmenue:
	{
		showmainemenue();
	}
	}
}
void showTransachtionsmenue()
{

	system("cls");
	cout << "===========================================\n";
	cout << " \t\t Transactions Menue Screen \n";
	cout << "===========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Mina Menue.\n";
	cout << "===========================================\n";
	performTransachtionmenueoption((enTransactionoptions)readTransactionsMenueOption());
}
short readmainmenueoption()
{
	
	cout << "Choose what do yue want to do ? [ 1 to 6 ] ? ";
	short number = 0;
	cin >> number;
	return number;
}
void prafremmainmenueopin(enmainmenueoption mainmenueoption)
{
	switch (mainmenueoption)
	{
	case enmainmenueoption::elistclient:
	{
		system("cls");
		showallclientscren();
		gobakctomainmenue();
		break;
	}
	case enmainmenueoption::eaddnewclient:
	
		system("cls");
		showaddnewclientsscreen();
		gobakctomainmenue();
		break;
	
	case enmainmenueoption::edeleteclient:
	
		system("cls");
		ShowDeleteClientScreen();
		gobakctomainmenue();
		break;
	
	case enmainmenueoption::eupdateclient:

		system("cls");
		ShowUpdateClientScreen();
		gobakctomainmenue();
		break;

	case enmainmenueoption::efindclient:

		system("cls");
		showfindclientscreen();
		gobakctomainmenue();
		break;

	case enmainmenueoption::eTransachtions:

		system("cls");
		showTransachtionsmenue();
		break;

	case enmainmenueoption::eexit:
		system("cls");
		showendscreen();
		break;
	}
}
void showmainemenue()
{
	system("cls");
	cout << "===========================================\n";
	cout << " \t\t Main Menue Screen \n";
	cout << "===========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delere Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transachtions.\n";
	cout << "\t[7] Exit.\n";
	cout << "===========================================\n";
	prafremmainmenueopin((enmainmenueoption)readmainmenueoption());
}
int main()
{
	showmainemenue();

 	system("pause>0");
  return 0;
}  



