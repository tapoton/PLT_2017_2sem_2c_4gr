#include <iostream>
#include<cstring>
const int NMAX=4;
using namespace std;

bool perif(bool p[NMAX],int ras,int str,int m[NMAX][NMAX],int i,int r)
{
    int y=0;
    bool ok=1;
        while(y <NMAX && ok)
        {
            if(m[str][y]!=0 && p[y])
            {
                ras+=m[str][y];
                p[y]=0;
                if(y==i)
                {
                    if(ras < r && ras!=0)
                    ok=0;
                }
                else 
                perif(p,ras,y,m,i,r);
                ras-=m[str][y];
                
            }
            y++;
        }
    return ok;
}
int main()
{
	int m[NMAX][NMAX]={{0,2,6,9},{2,0,4,8},{6,4,0,0},{9,8,0,0}};
	string city="ABCD";
	int x;
	 cout<<"  ";
	for(int i=0;i<NMAX;i++)
	 cout<<" "<<city[i]<<" ";
	 cout<<endl;
	 
	 for(int i=0;i<NMAX;i++)
	 {  
	   for(int j=0;j<NMAX;j++)
	      {
	         if (j==0)
	         cout<<city[i]<<" ";
	   	    cout<<" "<<m[i][j]<<" ";
	      }
	   cout<<endl;
	 }
	 
	 cout<<"Enter the distance: ";
	 cin>>x;
	 char town;
	 int t;
	 bool p[NMAX];
	     cout<<"Choose the town  ";
	     cin>>town;                          
	     for(int i=0;i<NMAX;i++)
	     {
	         if (town==city[i])
	            t=i;
	     }
	 for(int i=0;i<NMAX;i++)
	 p[i]=1;
	 cout<<x<<" perefir city "<<town<<" :  ";
	 for(int i=0;i<NMAX;i++)
	 {
	     if(i!=t)
	      {
	         if(perif(p,0,t,m,i,x))
	          cout<<city[i]<<"  ";
	      }
	 }
	 
	 return 0;
}

