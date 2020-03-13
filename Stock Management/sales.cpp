#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int n1=0,date;
char x[80];
using namespace std;
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
	char retitemName()
	{
		return item[20];
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
		Outstock(int a,int d)
		{
			no=a;
			demand=d;
		}
};
struct node
{
	int nu;
	warehouse w;
	int sales;
	int rate;
	struct node *next; 
}*root=0,*h;
struct sales
{
	char da[80];
	int total;
};
void dip(struct node *n)
{
	cout<<"\n";
	cout<<"\nITEM-NO:"<<n->nu;
	cout<<"\nSOLD:"<<n->sales;
	cout<<"\n RATE:"<<n->rate;
	cout<<"\n STOCK ON PREVIOUS DAY:\n";
	n->w.dispalyData();
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

int checkItem(struct node t)
{
	fstream f1;
	struct node n;
	f1.open(x,ios::in | ios::out);
	if(!f1)
		return 0;
	f1.read((char*)&n,sizeof(n));
	cout<<n.nu<<t.nu;
	while(!f1.eof())
	{
		 
		if(n.nu==t.nu)
		{
			 
			n.rate+=t.rate;
			n.sales+=t.sales;
			f1.seekp(0,ios::cur);
			f1.seekp(f1.tellg()-sizeof(n));
			f1.write((char*)&n,sizeof(struct node));
			f1.close();
			return 1;
		}
		
		f1.read((char*)&n,sizeof(n));
	}

	return 0;
}
void saveToday(fstream &f)
{
	int total=0;
	cout<<"\n TODAYS SALES:";
	struct node *l=h,t;
	while(l->next!=0)
	{
		cout<<"\n";
		l->rate=(l->w.retprice()*l->sales);
		total+=l->rate;
		dip(l);
		t=*l;
		 if(checkItem(t)==0)
		{
		 
		f.write((char*)&t,sizeof(struct node));
	 
		}
		l=l->next;
	}
	l->rate=(l->w.retprice()*l->sales);
	dip(l);
	t=*l;
	 
	total+=l->rate;
		if(checkItem(t)==0)
		{
			 
			f.write((char*)&t,sizeof(struct node));
			 
		}
	f.close();
	sales d;
	strcpy(d.da,x);
	d.total=total;
	ofstream s;
	s.open("sales.bin",ios::app);
	s.write((char*)&d,sizeof(d));
	s.close();
}
int update()
{
	warehouse s;
	struct node *t=h;
	fstream f1;
	f1.open("warehouse.bin",ios::in | ios::out);
		f1.read((char*)&s,sizeof(s));
		while(!f1.eof())
			{
				t=h;
				if(t->next!=0 || t==root)
				{
					while(t->next!=0)
					{
						if(t->nu==s.retItno())
						{
							
							s.update(t->sales);
							f1.seekp(0,ios::cur);
							f1.seekp(f1.tellg()-sizeof(s));
							f1.write((char*)&s,sizeof(s));
							 goto next;	
						}
						t=t->next;
					}
							if(t->nu==s.retItno())
						{
							s.update(t->sales);
								f1.seekp(0,ios::cur);
							f1.seekp(f1.tellg()-sizeof(s));
							f1.write((char*)&s,sizeof(s));
							goto next;	
						}
				}
			next:
			f1.read((char*)&s,sizeof(s));
			}
	
	f1.close();
	return 0;
	
}

int main()
{
	int n=start(),d,a;
	time_t raw;
	struct tm* time1,*tm1;
	time( &raw);
	time1 = localtime(&raw);	
	date=time1->tm_mday;
	 strftime(x,80,"%d-%m-%y.bin",time1);
	ifstream f1;
	ofstream f0;
	f0.open("Demand_stock.bin",ios::app);
	warehouse z[n];
	f1.open("warehouse.bin",ios::in);
	for(int i=0;i<n;i++)
	{
		f1.read((char*)&z[i],sizeof(z));
		
	}
	f1.close();
		system("cls");
	cout<<"ITEM-NO"<<"\t"<<"ITEM"<<"\n";
	for(int i=0;i<n;i++)
	{
		z[i].dispItem();
		cout<<"\n";
	}
	st:
	while(1)
	{
		d=a=0;
	cout<<"\n\n=========================================\n\n";
	cout<<"\n\n ENTER THE ITEM NUMBER[-1 to quit]:";
	cin>>d;
	
	if(d==-1)
		break;
	if(d>n1 || d<0)
	{
		cout<<"\n INVALID ITEM NUMBER,RE-ENTER:";
		goto st;
	}
	if(z[d-1].retStock()<1)
			{
				Outstock stk(z[d-1].retItno(),10);
				f0.write((char*)&stk,sizeof(stk));
				cout<<"\nWARNING: OUT OF STOCK\n\n";
				goto st;
			}
	else
	{
		cout<<"\n ENTER THE AMOUNT OF STOCK TO BE SOLD:";
		cin>>a;
				
		if(root==0)
			{
				root=new node;
				root->w=z[d-1];
				root->nu=d;
					if(root->w.retStock()<(root->sales+a))
					{
						
							delete root;
							root=0;
								Outstock stk(z[d-1].retItno(),a);
								f0.write((char*)&stk,sizeof(stk));
				 				cout<<"\nWARNING: OUT OF STOCK\n\n";
								goto st;
					}
				else
					{
					root->sales=a;
					root->next=0;
					h=root;
					}
					
					
			}
		else
			{
			
				node *l=h;
				
				if(l->next!=0 || l==root)
				{
					while(l->next!=0)
					{
						if(l->nu==d)
						{
							if(l->w.retStock()<(l->sales+a))
							{
								Outstock stk(z[d-1].retItno(),a);
								f0.write((char*)&stk,sizeof(stk));
				 				cout<<"\nWARNING: OUT OF STOCK\n\n";
								goto st;
							}
							else
								l->sales+=a;
								goto st;
						}
						l=l->next;
					}
						if(l->nu==d)
						{
							if(l->w.retStock()<(l->sales+a))
							{
								Outstock stk(z[d-1].retItno(),a);
								f0.write((char*)&stk,sizeof(stk));
								cout<<"\nWARNING: OUT OF STOCK\n\n";
								goto st;
							}
							else	
								l->sales+=a;
								goto st;
						}
				}
				l=new node;
				l->w=z[d-1];
				l->nu=d;
				l->sales=0;
				if(l->w.retStock()<(l->sales+a))
					{
								
						delete l;
							Outstock stk(z[d-1].retItno(),a);
							f0.write((char*)&stk,sizeof(stk));
							cout<<"\nWARNING: OUT OF STOCK\n\n";
							goto st;
					}
				else
					{
					l->sales=a;
					l->next=h;
					h=l;
					}
						
			}					
		}
		cout<<"\n";
		time( &raw);
		tm1 = localtime(&raw);		
		 if(date>tm1->tm_mday)
		 {
		 	system("cls");
		 	cout<<"\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t PLEASE RESTART THE PROGRAM !";
		 	break;
		 }
		 		
		
	}
	if(root!=0)
	{
	cout<<"\n executed";
	fstream f;
	f.open(x,ios::in | ios::app);
	saveToday(f);
	update();
	}
}
	
	

