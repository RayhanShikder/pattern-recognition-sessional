#include<iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<cstring>


using namespace std;


int main()
{

    ios_base::sync_with_stdio(0);

	ifstream fin;
	fin.open("train.txt",ifstream::in);
	double z1,z2,z3;
	vector<double> w_arr;
	w_arr.resize(3);
    w_arr[0]= rand()%100;
    w_arr[1]= rand()%100;
    w_arr[2]= rand()%100;


   // ofstream myfile;
   // myfile.open ("example.txt");
    std::string line;
    vector< vector<double>> samples;


    vector<double>temp;
    vector<int>atts;

    double learning_rate=0.3;


    while(fin>>z1>>z2>>z3)
    {
        temp.push_back(z1);
        temp.push_back(z2);
        temp.push_back(z3);

        samples.push_back(temp);
        temp.clear();

    }
    fin.close();

bool flag=true;
int iter=0;



while(flag){

    flag=false;

    vector<double>temp_w = w_arr;

        for(int i=0;i<samples.size();i++)
        {
                double s= w_arr[0]*samples[i][0]+ w_arr[1]*samples[i][1]+ w_arr[2];

                double d=0;

                if(s>0 && samples[i][2]==1)
                {
                    flag=true;
                    d=-1;
                    temp_w[0]+= d*learning_rate*samples[i][0];
                    temp_w[1]+= d*learning_rate*samples[i][1];
                    temp_w[2]+= d*learning_rate*1;

                }
                else if(s<0 && samples[i][2]==2)
                {
                    flag=true;
                    d=1;
                    temp_w[0]+= d*learning_rate*samples[i][0];
                    temp_w[1]+= d*learning_rate*samples[i][1];
                    temp_w[2]+= d*learning_rate*1;

                }



                //cout<<samples[i][j]<<" ";


        }
                    iter++;

            w_arr= temp_w;



}

cout<<iter<<endl;

cout<<w_arr[0]<<" "<<w_arr[1]<<" "<<w_arr[2]<<endl;



fin.open("test.txt",ifstream::in);
	iter = 0;
	int error = 0;

	samples.clear();


z1=0.0;z2=0.0;z3=0.0;
    while(fin>>z1>>z2>>z3)
    {
        double s = z1*w_arr[0] + z2*w_arr[1]+ w_arr[2];
        double ans=0.0;

        if(s>0 && z3!=2.0)
        {
            error++;
            ans=2;
        }
        else if(s<0 && z3!=1.0)
        {
            error++;
            ans=1;
        }
        else
        {
            ans = z3;
        }

        cout<<"expected "<<z3<<" found: "<<ans<<endl;

    }

    cout<<"error "<<error<<endl;
    fin.close();



    return 0;
}
