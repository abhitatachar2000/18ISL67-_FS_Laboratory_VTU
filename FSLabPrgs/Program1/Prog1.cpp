#include<iostream>
#include<stdio.h>
#include<fstream>
#include<iomanip>
#include<stdlib.h>

using namespace std;

void reverse(char *s,char *r){
	int j, len;
	for(len=0;s[len]!='\0';len++);
	for(j=len-1; j>=0; j--)
		r[len-j-1] = s[j];
	r[len]='\0';
}

int main(){
	char name[10][20],rev[10][20],input[20],output[20],str[20],rstr[20];
	int i, n, len;
	fstream ifile, ofile;
	cout<<"Enter the number of names to read: "<<endl;
	cin>>n;
	cout<<"Enter the names: "<<endl;
	for(i=0;i<n;i++)
		cin>>name[i];
	for(i=0;i<n;i++)
		reverse(name[i], rev[i]);
	cout<<"Names in reverse order are: "<<endl;
	for(i=0;i<n;i++)
		cout<<"Original name: "<<name[i]<<setw(25)<<"Reversed name: "<<rev[i]<<endl;
		
	cout<<"Enter the name of the file that contains names: ";
	cin>>input;
	ifile.open(input, ios::in);
	if(!ifile)
	{
		cout<<"file doesnot exist";
		exit(1);
	}
	cout<<"Enter the file name to store the reverse names: ";
	cin>>output;
	ofile.open(output, ios::out);
	while(!ifile.eof())
	{
		ifile.getline(str,20);
		reverse(str,rstr);
		ofile<<rstr<<endl;
	}
	return 0;
	
}
