#include<iostream>
#include<string.h>
#include<conio.h>
#include<fstream>
#include<stdlib.h>
using namespace std;
void writelists()
{
    fstream out1,out2;
    int i,m,n;
    char name[20];
    out1.open("input1.txt",ios::out);
    out2.open("input2.txt",ios::out);
    if((!out1)||(!out2))
    {
        cout<<"file creation error\n";
        getch();
        exit(0);
    }
    cout<<"Enter the number of names for file 1 \n";
    cin>>m;
    cout<<"Enter the names in ascending order \n";
    for(i=0;i<m;i++)
    {
        cin>>name;
        out1<<name;
        out1<<'\n';
    }
    cout<<"Enter the number of names for file 2\n";
    cin>>n;
    cout<<"Enter the names in ascending order\n";
    for(i=0;i<n;i++)
    {
        cin>>name;
        out2<<name;
        out2<<'\n';
    }
    out1.close();
    out2.close();
    }
    int main()
    {
        char list1[100][20],list2[100][20];
        int i=0,j=0,m=0,n=0;
        fstream out1,out2,out3;
        writelists();
        out1.open("input1.txt",ios::in);
        out2.open("input2.txt",ios::in);
        out3.open("output1.txt",ios::out);
        if((!out3)||(!out1)||(!out2))
        {
            cout<<"file creation error";
            getch();
            exit(0);
        }
        m=0;
        n=0;
        while(!out1.eof())
        {
            out1.getline(list1[m],20,'\n');
            cout<<list1[m]<<"\t";
            m++;
        }
        cout<<endl;
        while(!out2.eof())
        {
            out2.getline(list2[n],20,'\n');
            cout<<list2[n]<<"\t";
            n++;       
        }
        cout<<"\n";
        m--;
        n--;
        cout<<"\n Elements common to both files are:\n";
        for(i=0; i<m; i++)
        {
        	for(j=0; j<n; j++){
        		if(strcmp(list1[i],list2[j])==0)
            	{
                	out3<<list1[i];
                	cout<<list1[i]<<"\n";
                	out3<<'\n';
            	}
			}
            
        }
        getch();

    }
