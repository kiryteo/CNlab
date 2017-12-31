
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

class CRC{
public:
	int fs,sz,a,b,rs;
	int dw[20], ds[20], temp[20], crc[15], tf[15], rc[15];
	void getdw();
	void getdiv();
	void showdata();
	void append();
	void division();
	void code();
	void transf();
	int random(int a, int b);
	void rcvgen();

};

void CRC :: getdw()
{
	cout << "enter dw size." << endl;
	cin >> fs;

	cout << "enter dataword." << endl;
	for(int i=0;i<fs;i++)
	{
		cin >> dw[i];
	}

}

void CRC :: getdiv()
{
	cout << "enter divisor size: " << endl;
	cin >> sz;

	cout << "enter divisor: " << endl;
	for(int j=0;j<sz;j++)
	{
		cin >> ds[j];
	}
}

void CRC :: showdata()
{
	cout << "The DW is: ";
	for(int i=0;i<fs;i++)
	{
		cout << dw[i];
	}
	cout << endl;
	cout << "The divisor is: ";
	for(int j=0;j<sz;j++)
	{
		cout << ds[j];
	}
	cout << endl;
}

void CRC :: append()
{
	rs = fs - sz;
	cout << rs << " zeroes to append." << endl;
	for(int k=fs;k<fs+rs;k++)
	{
		dw[k] = 0;
	}
	for(int l=0;l<20;l++)
	{
		temp[l] = dw[l];
	}

	cout << "after appending zero: ";
	for(int i=0;i<fs+rs;i++)
	{
		cout << temp[i] ;
	}
	cout << endl;
}

void CRC :: division()
{
	for(int i=0;i<fs;i++)
	{
		a=0;
		b=i;
		if(temp[b]>=ds[a])
		{
			for(a=0,b=i;a<sz;a++,b++)
			{
				if((temp[b]==1 && ds[a]==1) || (temp[b]==0 && ds[a]==0))
				{
					temp[b]=0;
				}
				else
				{
					temp[b] = 1;
				}
			}
		}
	}
}

void CRC :: code()
{
	for(int i=0,j=fs;i<rs;i++,j++)
	{
		crc[i] = temp[j];
	}

	cout << "CRC bits are: ";
	for(int i=0;i<rs;i++)
	{
		cout << crc[i];
	}
	cout << endl;
}

void CRC :: transf()
{
	cout<<"Transmitted Frame: ";

	    for(int i=0;i<fs;i++)
	    {
	        tf[i]=dw[i];
	    }
	    for(int i=fs,j=0;i<fs+rs;i++,j++)
	    {
	        tf[i]=crc[j];
	    }
	    for(int i=0;i<fs+rs;i++)
	    {
	        cout<<tf[i];
	    }
	cout << endl;
}

void CRC :: rcvgen()
{
	int cnt=0;
	cout << "Enter receiver side frame." << endl;
	for(int i=0;i<fs+rs;i++)
	{
		cin >> rc[i];
	}

	for(int i=0;i<fs+rs;i++)
	{
		if(rc[i]==tf[i])
		{
			cnt++;
		}
	}
	if(cnt==fs+rs)
	{
		cout << "No error found." << endl;
	}
	else
	{
		cout << "Error present." << endl;
	}
}

int main()
{
	CRC c1;
	c1.getdw();
	c1.getdiv();
	c1.showdata();
	c1.append();
	c1.division();
	c1.code();
	c1.transf();

	cout << endl;
	cout << "			Receiver side:			" << endl;
	cout << endl;

	c1.rcvgen();
}
