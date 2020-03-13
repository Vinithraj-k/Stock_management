#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<time.h>
#include<ctime>
int n1;
using namespace std;
class warehouse
{
private:
	
	int no;
	char item[20];
	float price;
	int stock;
	
public:
	warehouse()
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
};
struct node1
{
	int nu;
	warehouse w;
	int sales;
	int rate;
	struct node *next; 
}b;
void dip(struct node1 n)
{
	cout<<"\n";
	cout<<"\nITEM-NO:"<<n.nu;
	cout<<"\nSOLD:"<<n.sales;
	cout<<"\n RATE:"<<n.rate;
	cout<<"\n STOCK ON PREVIOUS DAY:\n";
	n.w.dispalyData();
	cout<<"\n";
}
struct sales
{
	char da[80];
	int total;
}s;
struct node
{
        struct node *lt,*rt;
        struct sales sale;
}*root=0;
void insert(struct sales s,struct node *t)
{
        if(s.total<t->sale.total)
                if(t->lt==0)
                {
                        t->lt=(struct node*)malloc(sizeof(struct node));
                        t=t->lt;
                        t->sale=s;
                        t->lt=0;
                        t->rt=0;
                }
                else
                        insert(s,t->lt);
        else if(s.total>=t->sale.total)
                if(t->rt==0)
                {
                        t->rt=(struct node*)malloc(sizeof(struct node));
                        t=t->rt;
                        t->sale=s;
                        t->lt=0;
                        t->rt=0;
                }
                else
                        insert(s,t->rt);
}
void small()
{
        struct node *f;
        f=(struct node*)malloc(sizeof(struct node));
        f=root;
      if(f==0)
        {
			cout<<"\n SORRY NO SALES RECORDED IN THIS MONTH";
        	return;
		}
        while(f->lt!=0)
                {
                f=f->lt;
                }
                tm time;
       sscanf(f->sale.da,"%d-%d-%d ",&time.tm_mday,&time.tm_mon,&time.tm_year);
        cout<<"\n LOWEST SALES:\n";
		cout<<"\n DATE:"<<time.tm_mday<<"-"<<time.tm_mon<<"-"<<time.tm_year;
		cout<<"\nSALES[low]:"<<f->sale.total;
}void large()
{
        struct node *f;
        f=(struct node *)malloc(sizeof(struct node));
        f=root;
          if(f==0)
        {
			cout<<"\n SORRY NO SALES RECORDED IN THIS MONTH";
        	return;
		}
        while(f->rt!=0)
                {
                f=f->rt;
                }
                tm time;
		sscanf(f->sale.da,"%d-%d-%d ",&time.tm_mday,&time.tm_mon,&time.tm_year);
        cout<<"\n HIGHEST SALES:\n";
		cout<<"\n DATE:"<<time.tm_mday<<"-"<<time.tm_mon<<"-"<<time.tm_year;
		cout<<"\nSALES[high]:"<<f->sale.total;
}
int start()
{
	ifstream f1;
	f1.open("sales.bin",ios::in);
	if(!f1)
		{
			cout<<"ERROR- FILE NOT FOUND!";
			exit(0);
		}
		else
		{
			f1.seekg(0,ios::end);
			int l=0;
			l=f1.tellg();
			return (l/sizeof(s));
		}
}
void disp(struct sales s)
{
	cout<<"\n DATE:"<<s.da;
	cout<<"\n SALES:"<<s.total;
	cout<<"\n";;
}
int main()
{
	int n,m;
	n=start();
	ifstream f;
	f.open("sales.bin",ios::in);
	cout<<"\n ENTER THE MONTH[-1 for comparing All sales]:";
	cin>>m;
	for(int i=0;i<=n;i++)
	{
		f.read((char*)&s,sizeof(struct sales));
		 
		tm time;
		sscanf(s.da,"%d-%d-%d ",&time.tm_mday,&time.tm_mon,&time.tm_year);
		//cout<<time.tm_mday<<"\n"<<time.tm_mon<<"\n"<<time.tm_year;
		if(m==-1)
		{
			if(root==0)
                {
                        root=(struct node*)malloc(sizeof(struct node));
                        root->sale=s;
                        root->lt=0;
                        root->rt=0;
                }
        else
                {
                insert(s,root);
				}
 		}
 		else
 		{
 			if(time.tm_mon==m)
 			{
			 	if(root==0)
                {
                        root=(struct node*)malloc(sizeof(struct node));
                        root->sale=s;
                        root->lt=0;
                        root->rt=0;
                }
        else
                {
                insert(s,root);
				}
			}
		}
 	}
        small();
        cout<<"\n\n\n\n";
        large(); 
        int j;
        cout<<"\n\n\n\n NEED TO VIEW PARTICULAR DAY SALES[0/1]:";
        cin>>j;
        if(j==1)
        {
        	char x[80];
        	time_t tim;
        	tm *time1;
        	int d;
        	time(&tim);
        	time1=localtime(&tim);
        	cout<<"\n\n\n\n ENTER THE DATE:";
        	cin>>d;
        	time1->tm_mday=d;
        	cout<<"\n ENTER THE MONTH:";
        	cin>>m;
        	time1->tm_mon=m-1;
        	time1->tm_year=18;
        	mktime(time1);
        	strftime(x,80,"%d-%m-%y.bin",time1);
        	ifstream f1;
        	f1.open(x,ios::in);
        	f1.read((char*)&b,sizeof(b));
        	while(!f1.eof())
        	{
        		dip(b);
        		f1.read((char*)&b,sizeof(b));
			}
		f1.close();
	}
}

	

