#include<iostream>
#include<string>
#include<cstdlib>
#include<cmath>
using namespace std;

int lcs[2][5000];
int path[2][5000];
string s1,s2;
string paths;


int editDist(string str1,string str2)
{

    //cout<<str1<<" "<<str2<<endl;

        for(int i=0;i<=str1.size();i++)
    {



        int ii=i&1;



        //for(int l=0;l<=str2.size();l++)cout<<lcs[0][l]<<" ";
        //cout<<endl;





        for(int j=0;j<=str2.size();j++)
        {

            if(i==0)
            {
                lcs[ii][j]=j;
                path[ii][j]=0;//insert
                continue;
            }
            if(j==0)
            {
                lcs[ii][j]=i;
                path[ii][j]=1;//delete
                continue;

            }


            if(str1[i-1]==str2[j-1])
            {

                lcs[ii][j]= lcs[1-ii][j-1];
                path[ii][j]=4;//nochange

            }
            else
            {
                lcs[ii][j] = 1+ min(lcs[1-ii][j-1],min(lcs[ii][j-1],lcs[1-ii][j]));

                path[ii][j]=3;//replace


            }

        }

        //printPath();



/*
        for(int k=0;k<=str2.size();k++)
        {
            lcs[ii][k]=lcs[1-ii][k];
            //cout<<lcs[1-ii][k]<<" ";
        }
*/
       // cout<<endl;

    }

                //cout<<"result "<<lcs[str1.size()&1][str2.size()]<<endl;
    return lcs[str1.size()&1][str2.size()];

}


int find(int i1,int j1,int i2,int j2)
{

int j=(j2-j1)/2;

int min=10000000;
int mini=-1;
    for(int i=i1;i<=i2;i++)
    {
        if(editDist(s1.substr(i1,i),s2.substr(j1,j))+editDist(s1.substr(i,i2),s2.substr(j,j2))<min)
        {
            min = editDist(s1.substr(i1,i),s2.substr(j1,j))+editDist(s1.substr(i,i2),s2.substr(j,j2));
            mini=i;
        }
    }

    paths+=s1[mini];
    paths+="->";
    paths+=s2[j];


    return mini;

}


void findPath(int srci,int srcj,int sinki,int sinkj)
{

if(abs(sinkj-srcj)<=1)return;//adjacent coloumn

int i = find(srci,srcj,sinki,sinkj);

findPath(srci,srcj,i,(sinkj-srcj)/2);
findPath(i,(sinkj-srcj)/2,sinki,sinkj);



}
int main()
{

    paths="";

    cin>>s1>>s2;
    cout<<"result "<<editDist(s1,s2)<<endl;

    findPath(0,0,s1.size()-1,s2.size()-1);
    cout<<"path "<<paths<<endl;

    return 0;
}
