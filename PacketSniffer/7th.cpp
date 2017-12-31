#include<string>
#include<cstring>
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int main(int argc, char *argv[])
{
    vector<string> vect,v2;
    vector<string> :: iterator it;
    string st;
    int c1=0,c2=0,c3=0,c4=0,i;
    ifstream dfile("data4.csv");
    if(dfile.is_open())
    {
		while( getline (dfile, st))
		{
			string delimiter = ",";

			size_t pos = 0;
			string token;
			while ((pos = st.find(delimiter)) != string::npos) {
			    token = st.substr(0, pos);
			//    cout << token << endl;
			    vect.push_back(token);
			    st.erase(0, pos + delimiter.length());
			}
			//cout << st << endl;
			/*for(it=vect.begin();it!=vect.end();it++)
			{
				cout << *it << " ";
			}
			cout << endl;*/
			//vect[4] = (string)vect[4];
			//cout << vect[4] << endl;
			//if(vect[4]=="UDP")
			vect[4].erase(vect[4].begin());
			vect[4].erase(vect[4].end()-1);

			//cout << vect[4] << endl;

			if(vect[4]==("UDP"))
			{
				c1++;
			}
			if(vect[4]==("TCP"))
			{
				c2++;
			}
			if(vect[4]==("ICMP"))
			{
				c3++;
			}
			//cout << c1 << " " << c2 << " " << c3 << endl;
			vect.clear();
		}
		cout << "No. of UDP packets: " << c1 << endl;
		cout << "No. of TCP packets: " << c2 << endl;
		cout << "No. of ICMP packets: " << c3 << endl;
		
	    dfile.close();
	}
}


