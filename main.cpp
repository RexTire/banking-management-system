#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std ;

class account
{
	int acno ;
	char name[50] ;
	int deposit ;
	char type ;
public :
	void create_account() ;	      //function to get data from user
	void show_account() const ;	  //function to show data on screen
	void modify() ;          	  //function to add new data
	void dep(int) ;	              //function to accept amount and add to balance amount
	void draw(int) ;	          //function to accept amount and subtract from balance amount
	void report() const ;	      //function to show data in tabular format
	int retacno() const ;	      //function to return account number
	int retdeposit() const ;	  //function to return balance amount
	char rettype() const ;	      //function to return type of account
} ;

void account :: create_account()
{
	cout << "\n\tEnter The account No. : " ;
	cin >> acno ;
	cout << "\tEnter The Name of The account Holder : " ;
	cin.ignore() ;
	cin.getline(name,50) ;
	cout << "\tEnter Type of The account (C/S) : " ;
	cin >> type ;
	type = toupper(type) ;
	cout << "\tEnter The Initial amount(>=500 for Saving and >=1000 for current ) : " ;
	cin >> deposit ;
	cout << "\n\n\n\tAccount Created.. :)" ;
}

void account :: show_account() const
{
	cout << "\n\tAccount No. : " << acno ;
	cout << "\n\tAccount Holder Name : " << name ;
	cout << "\n\tType of Account : " << type ;
	cout << "\n\tBalance amount : " << deposit ;
}



void account :: modify()
{
	cout << "\n\tAccount Number: " << acno ;
	cout << "\n\tModify Account Holder Name: " ;
	cin.ignore() ;
	cin.getline(name , 50) ;
	cout << "\tModify Type of Account: " ;
	cin >> type ;
	type = toupper(type) ;
	cout << "\tModify Balance Amount: " ;
	cin >> deposit ;
}


void account :: dep(int x)
{
	deposit += x ;
}

void account :: draw(int x)
{
	deposit -= x ;
}

void account :: report() const
{
	cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}


int account :: retacno() const
{
	return acno ;
}

int account::retdeposit() const
{
	return deposit ;
}

char account::rettype() const
{
	return type ;
}



void write_account();	           //function to write record in binary file
void display_sp(int);	           //function to display account details given by user
void modify_account(int);	       //function to modify record of file
void delete_account(int);	       //function to delete record of file
void display_all();		           //function to display all account details
void deposit_withdraw(int, int);   // function to desposite/withdraw amount for given account
void intro();	                   //introductory screen function




int main()
{
	char ch ;
	int num ;
	intro() ;
	do
	{
		system("cls");
		cout << endl ;
		cout << "\tMAIN MENU" << endl ;
		cout << "\t---------" << endl ;
		cout << "\t01. OPEN NEW ACCOUNT" << endl ;
		cout << "\t02. DEPOSIT AMOUNT" << endl ;
		cout << "\t03. WITHDRAW AMOUNT" << endl ;
		cout << "\t04. BALANCE ENQUIRY"<< endl ;
		cout << "\t05. ALL ACCOUNT HOLDER LIST" << endl ;
		cout << "\t06. CLOSE AN ACCOUNT" << endl ;
		cout << "\t07. MODIFY AN ACCOUNT" << endl ;
		cout << "\t08. EXIT" << endl ;
		cout << "\n\n\tSelect Your Option (1-8): " ;
		cin >> ch ;
		system("cls") ;
		switch(ch)
		{
		case '1' :
			write_account() ;
			break ;

		case '2' :
			cout << "\n\tEnter Account Number: " ;
			cin >> num ;
			deposit_withdraw(num, 1) ;
			break ;

		case '3' :
			cout << "\n\tEnter Account Number: " ;
			cin >> num ;
			deposit_withdraw(num, 2) ;
			break ;

		case '4' :
			cout << "\n\tEnter Account Number: " ;
			cin >> num ;
			display_sp(num) ;
			break ;

		case '5' :
			display_all() ;
			break ;

		case '6' :
			cout << "\n\tEnter Account Number: " ;
			cin >> num ;
			delete_account(num) ;
			break ;

		 case '7' :
			cout << "\n\tEnter Account Number: " ;
			cin >> num ;
			modify_account(num) ;
			break ;

		 case '8' :
			cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tThanks for using bank management system :)\n\n\n\n\n" ;
			break ;

		 default :
		     cout << "\a" ;
		}
		cin.ignore() ;
		cin.get() ;
	}

	while(ch!='8') ;

	return 0 ;
}


//function to write in file
void write_account()
{
	account ac ;
	ofstream outFile ;
	outFile.open("account.dat" , ios :: binary | ios :: app) ;
	ac.create_account() ;
	outFile.write(reinterpret_cast<char *> (&ac) , sizeof(account)) ;
	outFile.close() ;
}


//function to read specific record from file
void display_sp(int n)
{
	account ac ;
	bool flag {false} ;
	ifstream inFile ;
	inFile.open("account.dat" , ios :: binary) ;
	if(!inFile)
	{
		cout <<"\n\tFile could not be open !! Press any Key..." ;
		return ;
	}

    	while(inFile.read(reinterpret_cast<char *> (&ac) , sizeof(account)))
	{
		if(ac.retacno()==n)
		{
            cout << "\n\tBALANCE DETAILS\n" ;
	        cout << "\t---------------" ;
			ac.show_account() ;
			flag = true ;
		}
	}
	inFile.close() ;
	if(flag == false)
		cout << "\n\tAccount number does not exist" ;
}


//function to modify record of file
void modify_account(int n)
{
	bool found{false} ;
	account ac ;
	fstream File ;
	File.open("account.dat" , ios :: binary | ios :: in | ios :: out) ;
	if(!File)
	{
		cout << "File could not be open !! Press any Key..." ;
		return ;
	}
	while(!File.eof() && found == false)
	{
		File.read(reinterpret_cast < char *> (&ac) , sizeof(account)) ;
		if(ac.retacno() == n)
		{
			ac.show_account() ;
			cout << endl ;
			cout << "\n\tEnter New Details of the Account" << endl ;
			cout << "\t--------------------------------" ;
			ac.modify() ;
			int pos = (-1) * static_cast<int>(sizeof(account)) ;
			File.seekp(pos , ios :: cur) ;
			File.write(reinterpret_cast<char *> (&ac) , sizeof(account)) ;
			cout << "\n\n\tRecord Updated" ;
			found = true ;
		  }
	}
	File.close() ;
	if(found == false)
		cout << "\n\n\tRecord Not Found " ;
}


//function to delete record of file
void delete_account(int n)
{
	account ac ;
	ifstream inFile ;
	ofstream outFile ;
	inFile.open("account.dat" , ios :: binary) ;
	if(!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return ;
	}
	outFile.open("Temp.dat" , ios :: binary) ;
	inFile.seekg(0 , ios :: beg) ;
	while(inFile.read(reinterpret_cast<char *> (&ac) , sizeof(account)))
	{
		if(ac.retacno() != n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account)) ;
		}
	}
	inFile.close() ;
	outFile.close() ;
	remove("account.dat") ;
	rename("Temp.dat" , "account.dat") ;
	cout<<"\n\n\tRecord Deleted .." ;
}


//function to display all accounts deposit list
void display_all()
{
	account ac ;
	ifstream inFile ;
	inFile.open("account.dat" , ios :: binary) ;
	if(!inFile)
	{
		cout << "File could not be open !! Press any Key..." ;
		return ;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n" ;
	cout << "====================================================\n" ;
	cout << "A/c no.      NAME           Type  Balance\n" ;
	cout << "====================================================\n" ;
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report() ;
	}
	inFile.close() ;
}


//function to deposit and withdraw amounts
void deposit_withdraw(int n, int option)
{
	int amt ;
	bool found{false} ;
	account ac ;
	fstream File ;
	File.open("account.dat" , ios :: binary | ios :: in | ios :: out) ;
	if(!File)
	{
		cout << "File could not be open !! Press any Key..." ;
		return ;
	}
	while(!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account)) ;
		if(ac.retacno() == n)
		{
			ac.show_account() ;
			if(option == 1)
			{
			    cout << endl ;
				cout << "\n\tTO DEPOSITE AMOUNT " ;
				cout << "\n\t------------------" ;
				cout << "\n\tEnter The amount to be deposited: " ;
				cin >> amt ;
				ac.dep(amt) ;
			}
			if(option ==2)
			{
			    cout << endl ;
				cout << "\n\tTO WITHDRAW AMOUNT " ;
				cout << "\n\t------------------" ;
				cout << "\n\tEnter The amount to be withdraw: " ;
				cin >> amt ;
				int bal = ac . retdeposit()-amt ;
				if((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
					cout<<"Insufficience balance" ;
				else
					ac.draw(amt) ;
			}
			int pos = (-1) * static_cast<int>(sizeof(ac)) ;
			File.seekp(pos , ios :: cur) ;
			File.write(reinterpret_cast<char *> (&ac), sizeof(account)) ;
			cout << "\n\n\tRecord Updated" ;
			found = true ;
	       }
         }
	File.close() ;
	if(found == false)
		cout<<"\n\n\tRecord Not Found" ;
}


//INTRODUCTION FUNCTION
void intro()
{
	cout << endl << endl << endl;
	cout << endl << endl << endl ;
	cout << endl << endl << endl ;
	cout << "\t\t\t\t\tWelcome to Bank Management System" << endl ;
	cout << "\t\t\t\t\tMade by Mohit Yadav" << endl ;
	cout << "\t\t\t\t\tA2305218459" << endl ;
	cout << "\t\t\t\t\t4CSE7Y" << endl ;
	cout << "\t\t\t\t\tAmity School of Engineering & Technology" << endl ;
	cout << "\t\t\t\t\tAmity University, Noida." << endl ;
	cin.get() ;
}
