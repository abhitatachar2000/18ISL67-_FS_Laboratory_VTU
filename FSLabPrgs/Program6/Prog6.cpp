#include<fstream>
#include<stdio.h>
#include<iomanip>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#define datafile "stud6.txt"
#define indexfile "pind6.txt"
#define sindexfile "sind6.txt"
using namespace std;
fstream dfile,ifile,sifile;
int i,indsize,sindsize;
char buffer[100],skey[20];


void fopen(fstream &file, char *fn,std::_Ios_Openmode mode)
{
	file.open(fn,mode);
	if(!file)
	{
		cout<<"Unable to open a file";
		exit(1);
	}
}
class student
{
	char dusn[15],name[20],age[5],branch[6],sem[5];
	public:
		void read();
		void pack();
	    	int search(char *);
		void remove();
		void datadisp();
		void unpack();
}s;



class index
{
	public:
		char iusn[15],addr[5];
		void initial();
		void write();
}id[50],in;

class sindex
{
	public :
		  char sname[20],susn[15];
		  void sinitial();
		  void swrite();
}sid[50],sin;


void index::initial()
{
	ifile.open(indexfile,ios::in);
	if(!ifile)
	{
		   indsize=0;
		   return;
	}
   for(indsize=0;;indsize++)
   {
		ifile.getline(id[indsize].iusn,15,'|');
		ifile.getline(id[indsize].addr,5,'\n');
		if(ifile.eof())
			break;
   }
   ifile.close();
}


 void sindex::sinitial()
{
	sifile.open(sindexfile,ios::in);
	if(!sifile)
	{
		   sindsize=0;
		   return;
	}
   for(sindsize=0;;sindsize++)
   {
		sifile.getline(sid[sindsize].sname,20,'|');
		sifile.getline(sid[sindsize].susn,15,'\n');
		if(sifile.eof())
			break;
   }
   sifile.close();

}


void index::write()
{
	fopen(ifile,indexfile,ios::out);
	for(i=0;i<indsize;i++)
		ifile<<id[i].iusn<<"|"<<id[i].addr<<"\n";
}

void sindex::swrite()
{
	fopen(sifile,sindexfile,ios::out);
	for(i=0;i<sindsize;i++)
		sifile<<sid[i].sname<<"|"<<sid[i].susn<<"\n";
}



void student::read()
{
	int k;
	cout<<"Enter the usn number:";  cin>>dusn;
	if(search(dusn)>=0)
	{
		  cout<<"USN is already present we can't add to index file\n";
		  return;
	}
	for(i=indsize;i>0;i--)
	{
	   if(strcmp(dusn,id[i-1].iusn)<0)
			id[i]=id[i-1];
	   else
			break;
	}
	fopen(dfile,datafile,ios::app);
	cout<<"Enter the name: ";    	cin>>name;
	cout<<"Enter the age: ";     	cin>>age;
	cout<<"Enter the branch: ";  	cin>>branch;
	cout<<"Enter the semester: ";   	cin>>sem;
	pack();
	dfile.seekg(0,ios::end);
	k=dfile.tellg();
	dfile<<buffer<<"\n";
	strcpy(id[i].iusn,dusn);
	sprintf(id[i].addr, "%d",k);
	indsize++;
	for(i=sindsize;i>0;i--)
	{
		if(strcmp(name,sid[i-1].sname)<0)
			sid[i]=sid[i-1];
		else if((strcmp(name,sid[i-1].sname)==0) && (strcmp(dusn,sid[i-1].susn)<0))
				sid[i]=sid[i-1];
		else
				break;
	}
	strcpy(sid[i].sname,name);
	strcpy(sid[i].susn,dusn);
	sindsize++;
}


void student::pack()
{
		strcpy(buffer,dusn);	strcat(buffer,"|");
		strcat(buffer,name);	strcat(buffer,"|");
		strcat(buffer,age);	strcat(buffer,"|");
		strcat(buffer,branch);	strcat(buffer,"|");
		strcat(buffer,sem);	strcat(buffer,"|");
}



int student::search(char * fusn)
{
	int low=0,high=indsize-1,mid;
	while(low <=high)
	{
		mid = (low+high)/2;
		if(strcmp(fusn,id[mid].iusn)==0)
			return mid;
		if(strcmp(fusn,id[mid].iusn)>0)
			low=mid+1;
		else
			high=mid-1;
	}
	return -1;
}

int sec_search()
{
	int pos,j,flag=-1;
	cout<<"\nEnter the name to search(sec key):";
	cin>>skey;
	cout<<"The searched record details are :"<<endl;
	cout<<setiosflags(ios::left);
	cout<<"USN"<<"\t\tname"<<endl;
	fopen(dfile,datafile,ios::in|ios::out);
	for(j=0;j<sindsize;j++)
		 if(strcmp(skey,sid[j].sname)==0)
		  {
			cout<<sid[j].susn<<"\t\t"<<sid[j].sname<<endl;
			flag=j;
		  }
	return flag;
}

void student::remove()
{
	char rusn[10];
	int pos,spos;
	cout<<"Enter the usn number above listed to delete:";
	cin>>rusn;
	for(i=0;i<sindsize;i++)
	{
		  if(strcmp(sid[i].susn,rusn)==0)
		   {
			  spos=i;
			  break;
		   }
	}

	if(strcmp(sid[spos].sname,skey)==0)
	{
		pos=search(rusn);
		dfile.seekp(atoi(id[pos].addr),ios::beg);
		dfile.put('$');
		for(i=pos;i<indsize;i++)
			id[i]=id[i+1];
		indsize--;
		for(i=spos;i<sindsize;i++)
			sid[i]=sid[i+1];
		sindsize--;
	}
	else
		cout<<"USN number and name doesnot match";
}


void student::datadisp()
{
	cout<<setiosflags(ios::left);
	cout<<setw(20)<<"usn"<<setw(20)<<"name"<<setw(20)<<"age"<<setw(20);
	cout<<"branch"<<setw(20)<<"sem\n";
	cout<<"\n";
	while(1)
	{
		unpack();
		if(dfile.eof()) 	
  		break;
	}
	cout<<endl<<"\nThe index file details are:\n "<<endl;
	cout<<setw(10)<<"usn"<<setw(10)<<"address";
	for(i=0;i<indsize;i++)
		 cout<<endl<<setw(10)<<id[i].iusn<<setw(10)<<id[i].addr;
	cout<<endl<<"\nThe secondary file details are:\n " <<endl;
	cout<<setw(20)<<"name"<<setw(15)<<"primary reference";
	for(i=0;i<sindsize;i++)
		  cout<<endl<<setw(20)<<sid[i].sname<<setw(15)<<sid[i].susn;
}

void student::unpack()
{
	 string var;
	 dfile.getline(buffer,100,'\n');
	 i=0;
	 if(buffer[i]!='$')
		while(buffer[i]!='\0')
		{
			if(buffer[i]=='|')
			{	
				if(buffer[i+1]=='\0')
					cout<<var;
				else
					cout<<setw(20)<<var;
				var="";
			}	
			else
				var = var+buffer[i];
			i++;
		}
		cout<<"\n";
}

int main()
{
	int ch,flag;
	in.initial();
	sin.sinitial();
	for(;;)
	{
	cout<<endl<<"1.Read\n2.Display\n3.Search\n4.Delete\n5.Exit\n";
	cin>>ch;
	switch(ch)
	{
		case 1: cout<<endl<<"Enter student details :" <<endl;
				s.read();
				in.write();
				sin.swrite();
				break;
		case 2: fopen(dfile,datafile,ios::in);
			   cout<<"\nThe datafile,indexfile and secondary file\n" <<endl;
			   s.datadisp();
			   break;
		case 3:cout<<"To search based on  sec key\n";
				flag=sec_search();
				if(flag==-1)
				cout<<"No data record\n";
				break;
		case 4: flag=sec_search();
				if(flag==-1)
					cout<<"No data record found\n";
				else
				{
					   s.remove();
					   in.write();
					   sin.swrite();
				 }
				break;
		default :  exit(0);
	   }
	   dfile.close();
	   ifile.close();	
	   sifile.close();
	}
}
