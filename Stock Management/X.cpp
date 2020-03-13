#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
class warehouse
{
private:
	
	int no;
	char item[20];
	float price;
	int stock;
};
struct node
{
	int nu;
	warehouse w;
	int sales;
	int rate;
	struct node *next; 
};
int main()
{
		fstream f;
	struct node n;
	f.open("27-08-18.txt",ios::in | ios::out);
	if(!f)
		exit(0);
	f.read((char*)&n,sizeof(n));
	while(!f.eof())
	{
		cout<<n.nu<<"\t"<<n.sales<<"\n";
		f.read((char*)&n,sizeof(struct node));
		
	}
}
	
