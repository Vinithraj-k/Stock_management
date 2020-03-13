#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include<time.h>
using namespace std;
int n1;
class warehouse
{
private:
	
	int no;
	char item[20];
	float price;
	int stock;
	
public:
	void dispItem()
	{
		cout<<no<<"\t"<<item;	
	}
		void getData()
	{
			int i;
			cout<<"\n\n";
			cout<<"\n ITEM NAME:"<<item;
			cout<<"\n\n NEED TO UPDATE PRICE(0/1):";
			cin>>i;
			if(i==1)
			{
			cout<<"\n ENTER THE PRICE:";
			cin>>price;
			}
			cout<<"\n ENTER THE PURCHASED STOCK:";
			cin>>i;
			stock+=i;
	}
	void dispalyData()
	{
		
		cout<<"ITEM NO:"<<no;
		cout<<"\n ITEM:"<<item;
		cout<<"\n PRICE:"<<price;
		cout<<"\n STOCK AVAILABLE:"<<stock;
		cout<<"\n\n";
	}
	float retprice()
	{
		return price;
	}
	int retStock()
	{
		return stock;
	}
	void update(int sales)
	{
		stock=stock-sales;
	}
	int  retItno()
	{
		return no;
	}
	
	
};
class Outstock 
{
	int no;
	int demand;
	public:
		 
		void disp()
		{
			cout<<"\n"<<no<<demand;
		}
		int retno()
		{
			return no;
		}
		int retdem()
		{
			return demand;
		}
};
struct node
{
	int nu;
	warehouse w;
	int sales;
	int rate;
	struct node *next; 
}n;
void display(struct node n)
{
	cout<<"\n";
	cout<<"\nITEM-NO:"<<n.nu;
	cout<<"\nSOLD:"<<n.sales;
	cout<<"\n RATE:"<<n.rate;
	cout<<"\n STOCK ON PREVIOUS DAY:\n";
	n.w.dispalyData();
	cout<<"\n";
}
int start()
{
	
	warehouse s;
	ifstream f1;
	f1.open("warehouse.bin",ios::in);
	if(!f1)
		{
			cout<<"\t\t\t\n ERROR 404 NOT FOUND! \n\n\n";
			exit(0);
		}
		else
		{
			f1.seekg(0,ios::end);
			int l=0;
			l=f1.tellg();
			n1=(l/sizeof(s));
		}
		return n1;
}

struct sales
{
	char da[80];
	int total;
};
int main()
{
	n1=start();
	int d,m,count=0 ;
	ifstream f,f1; 
	
	warehouse w[n1];
	int dem[n1]={0},sale1[n1]={0};
	f.open("warehouse.bin",ios::in);
	for(int i=1;i<=n1;i++)
	{
		f.read((char*)&w[i],sizeof(w));
	}
	f.close();
		for(int i=1;i<=n1;i++)
		w[i].dispalyData();
		 		 
	char x[80];
	time_t raw;
	sales s;
	
	 Outstock p;
	
	f1.open("Demand_stock.bin",ios::in);
	if(!f1)
		cout<<"errror";
 				
				f1.read((char*)&p,sizeof(p));
				while(!f1.eof())
				{
				 	dem[p.retno()]+=p.retdem();			 
				f1.read((char*)&p,sizeof(p));	
				}
				f1.close();
					
	struct tm* time1;
	time(&raw);
	time1 = localtime(&raw);
	strftime(x,80,"%d-%m-%y.bin",time1);
	m=time1->tm_mon;
	d=time1->tm_mday;
	time1->tm_year=2018-1900;

	do{
	time1->tm_mon=m;
	time1->tm_mday=d;
	strftime(x,80,"%d-%m-%y.bin",time1);
	f1.open(x,ios::in);
	if(f1)
	{
		f1.read((char*)&n,sizeof(n));
				while(!f1.eof())
				{
				 
				 	sale1[n.nu]+=n.sales;
					 			 
				f1.read((char*)&n,sizeof(n));	
				}
				
	}
	 f1.close();
	d=d-1;
	if(d==0)
	{
		d=31;
		m=m-1;
		if(m==0)
			m=12;
	}
	count++;
}while(count!=30);
f1.close();
 back:
for(int i=1;i<=n1;i++)
				{
					 
					w[i].dispItem();
					if(dem[i]==0 && sale1[i]==0)
						d=10;
					else
						d=((dem[i]*0.75)+(sale1[i]*1.25));
					cout <<"   \tDEMAND:" <<dem[i] <<"\tSALES:" <<  sale1[i]<<"\t STOCK_AVAIL:"<< w[i].retStock()<<"\t RECOMMENDED:"<<d<<"\n";	 
				}
				
				
cout<<"\n REFILLING WAREHOUSE:\n\n";
	do{
		do{
		cout<<"\n ENTER THE ITEM NUMBER:";
		cin>>d;
		}while(d<=0 || d>n1);
		w[d].getData();
		cout<<"\n ITEM UPDATED!\n\n\n";
		cout<<"\n ENTER ANOTHER ITEM?[0/1] :";
		cin>>d;
		if(d==1)
	 	goto back;
	}while(d==1);
	system("cls");
	cout<<"\n\n CURRENT STOCK:\n\n";
	
		ofstream k;
		k.open("warehouse.bin",ios::in);
		for(int i=1;i<=n1;i++)
		{
		w[i].dispalyData();
		k.write((char*)&w[i],sizeof(w[i]));
		}
	k.close();
	
	
			  
			 
}
	


