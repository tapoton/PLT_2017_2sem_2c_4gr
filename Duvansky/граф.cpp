#include <iostream>
using namespace std;

void proc (int v,int** a,int n)//procedura poiska posledovatelnosti vershin
{
	int** b=a;
	for(int i=0;i<n;i++)
	{
		if(b[v][i]==1)
		{
			b[v][i]=0;
			b[i][v]=0;
			proc(i,b,n);
		}
	
	}
		
	cout<<v;
}
bool svyaz(int** a, int n)//proverka na svyznost
{   
	for(int i=0;i<n;i++)
	{
		bool k=false;
		for(int j=0;j<n;j++)
			if(a[i][j]==1) { k=true;break;}
			if(!k) return false;
	}
		
}
int kol_nechet(int** a, int n)//kolichestvo vershin s nechetnoy stepeniyu
{
	int k=0;
	for(int i=0;i<n;i++)
	{	int s=0;
		for(int j=0;j<n;j++)
			s+=a[i][j];
		if(s%2!=0) k++;
	}
	return k;

}
int necnet_versh(int**a,int n)//vidaet vershinu s nechetnoy stepeniyu
{ 
	for(int i=0;i<n;i++)
	{
		int s=0;
		for(int j=0;j<n;j++)
			s+=a[i][j];
		if(s%2!=0) return i;
	}
}
void main()
{    int n;
     cout<<"vvedite kolichestvo vershin grafa"<<endl;
	 cin>>n;
	int** a= new int*[n];
	for(int i=0;i<n;i++)
		a[i]=new int[n];
	 cout<<"vvedite matricu smezhnosti grapha,numeraciya vershin s 0"<<endl;
	 for(int i=0;i<n;i++)
		 for(int j=0;j<n;j++)
			 cin>>a[i][j];
	 if(svyaz(a,n)&&kol_nechet(a,n)<=2)
	 {
		 if(kol_nechet(a,n)==0) proc(0,a,n);
		 else   proc(necnet_versh(a,n),a,n);
	 }
	 else cout<<"graph nevozmozhno narisovat ne otryvaya ruki";
	  
		
		
		system("pause");

}