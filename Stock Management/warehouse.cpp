#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string.h>
int n1=0;
using namespace std;
class items
{
private:
	
	int no;
	char item[20];
	float price;
	int stock;
	
public:
	items()
	{
		no=n1;
	}
	void getData()
	{
			cout<<"\n\n";
			no=(++no);
			cout<<"\n ENTER THE ITEM NAME:";
			cin>>item;
			cout<<"\n ENTER THE PRICE:";
			cin>>price;
			cout<<"\n ENTER THE PURCHASED STOCK:";
			cin>>stock;
	}
	void dispalyData()
	{
		
		cout<<"ITEM NO:"<<no;
		cout<<"\n ITEM:"<<item;
		cout<<"\n PRICE:"<<price;
		cout<<"\n STOCK AVAILABLE:"<<stock;
		cout<<"\n\n";
	}
	char* name()
	{
		return item;
	}
friend int check(char n[]);
};
int check(char n[])
{
	items s;
	ifstream f1;
	f1.open("warehouse.bin",ios::in);
	f1.read((char*)&s,sizeof(s));
		while(!f1.eof())
			{
			if(strcmp(n,s.item)==0)
					return 0;
			f1.read((char*)&s,sizeof(s));
			}
		return 1;
	f1.close();
	
}
void start()
{
	items s;
	ifstream f1;
	f1.open("warehouse.bin",ios::in);
	if(!f1)
		{
			cout<<"\t\t\t\n WELCOME TO WAREHOUSE! \n\n\n";
		}
		else
		{
			f1.seekg(0,ios::end);
			int l=0;
			l=f1.tellg();
			n1=(l/sizeof(s));
		}
}
int main()
{
		
	int n;
	start();
	ofstream f;
	f.open("warehouse.bin",ios::app);
	k:
	cout<<"\n ENTER THE NUMBER OF ITEMS PURCHASED[0 TO VIEW STOCK]:";
	cin>>n;
	if(n==0)
		{
				if(n1==0)
				{
				cout<<"\n NO STOCKS AVAILABE!\n\n";
				goto k;
				}
		}
	items s;
	for(int j=0;j<n;j++)
	{
		q:
		s.getData();
		if(check(s.name())==1)
			f.write((char*)&s,sizeof(s));
			else
			{
				cout<<"\n ITEM ALREADY EXISTS!";
				goto q;
			}
	}
	f.close();
	ifstream f1;
	system("cls");
	cout<<"\n AVAILABLE STOCK:\n\n";
	f1.open("warehouse.bin",ios::in);
	f1.read((char*)&s,sizeof(s));
		while(!f1.eof())
			{
			s.dispalyData();
			f1.read((char*)&s,sizeof(s));
			}
	f1.close();
	
	system("pause");
}
