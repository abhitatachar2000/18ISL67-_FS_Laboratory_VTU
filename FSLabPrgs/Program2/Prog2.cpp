#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<iomanip>
#include<stdlib.h>
#include<string.h>

#define filename "std2.txt"
using namespace std;
fstream ifile;

class student
{
	char usn[15],name[20],age[5],branch[6],sem[5];
	public:
		void fopen(fstream &ifile,char *fn, std::_Ios_Openmode mode);
		void read();
		void pack();
		void display();
		void unpack();
		int search();
		void modify(int);
};

void student::fopen(fstream &sfile,char *fn,std::_Ios_Openmode mode)
{
	sfile.open(fn,mode);
	if(!sfile)
	{
		cout<<"Unable to open a file"<<endl;
		getch();
		exit(1);
	}
}

void student::read()
{
	cout<<"Enter the usn number:"; cin>>usn;
	cout<<"Enter the name:"; cin>>name;
	cout<<"Enter the age:"; cin>>age;
	cout<<"Enter the branch:"; cin>>branch;
	cout<<"Enter the sem:"; cin>>sem;
	pack();
}

void student::pack()
{
	char buffer[75];
	strcpy(buffer,usn); strcat(buffer,"|");
	strcat(buffer,name); strcat(buffer,"|");
	strcat(buffer,age); strcat(buffer,"|");
	strcat(buffer,branch); strcat(buffer,"|");
	strcat(buffer,sem); strcat(buffer,"|");
	ifile.fill('*');
	ifile<<setiosflags(ios::left)<<setw(sizeof(student))<<buffer<<endl;
}

void student::display()
{
	char buffer[75];
	cout<<setiosflags(ios::left);
	cout<<setw(15)<<"USN"<<setw(20)<<"NAME"<<setw(5)<<"AGE";
	cout<<setw(10)<<"BRANCH"<<setw(5)<<"SEM"<<endl;
	while(1)
	{
		unpack();
		if(ifile.eof())
			break;
		if(usn[0]!='$')
		{
			cout<<setw(15)<<usn<<setw(20)<<name<<setw(5)<<age;
			cout<<setw(10)<<branch<<setw(5)<<sem<<endl;
		}
	}
}

void student::unpack()
{
	char dummy[75];
	ifile.getline(usn,15,'|');
	ifile.getline(name,20,'|');
	ifile.getline(age,5,'|');
	ifile.getline(branch,6,'|');
	ifile.getline(sem,5,'|');
	ifile.getline(dummy,75,'\n');
}

int student::search()
{
	int flag;
	char susn[15];
	cout<<"enter the usn to be searched:";
	cin>>susn;
	while(!ifile.eof())
	{
		flag=ifile.tellg();
		unpack();
		if(usn[0]!='$' &&strcmp(usn,susn)==0)
		{
			cout<<"USN:"<<usn<<"\n"<<"NAME:"<<name<<"\n"<<"AGE:"<<age;
			cout<<"\n"<<"BRANCH:"<<branch<<"\n"<<"SEM:"<<sem<<"\n";
			return flag;
		}
		}
	return -1;
}

void student::modify(int recpos)
{
	ifile.seekp(recpos,ios::beg);
	ifile.seekp(0,ios::end);
	read();
}

int main()
{
	int ch,flag;
	student s;
	for(;;)
	{
		cout<<endl<<"1.Read\n2.Display\n3.Search\n4.Modify\n5.Exit\n"<<endl;
		cout<<"Enter the choice:";
		cin>>ch;
		switch(ch)
		{
			case 1:
				s.fopen(ifile,filename,ios::app);
				cout<<"Enter student details: \n";
				s.read();
				break;
			case 2: 
				s.fopen(ifile,filename,ios::in);
				cout<<"The student details are:"<<endl;
				s.display();
				break;
			case 3:
				s.fopen(ifile,filename,ios::in);
				cout<<"Searching based on USN number"<<endl;
				flag=s.search();
				if(flag==-1)
					cout<<"Record not found"<<endl;
				break;
			case 4: 
				s.fopen(ifile,filename,ios::in | ios::out);
				cout<<"To modify the record based on USN"<<endl;
				flag=s.search();
				if(flag==-1)
					cout<<"Record not found"<<endl;
				else
					s.modify(flag);
				break;
			case 5:
				exit(0);
			default:
				cout<<"Invalid input"; break;
		}
		ifile.close();
	}
}

		

