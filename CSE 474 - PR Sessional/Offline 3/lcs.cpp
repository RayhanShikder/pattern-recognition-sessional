#include<iostream>
#include<string>

using namespace std;

int lcs[5000][5000];
int path[5000][5000];

string str1,str2;

void printPath(int i,int j)
{
    if(i==0 && j==0)return;


if(lcs[i+1][j+1]==min(lcs[i][j],min(lcs[i+1][j],lcs[i][j+1]))+1)
            {

                if(lcs[i+1][j+1]==1+lcs[i][j])
                {
                    if(i>0 && j>0)
                    printPath(i-1,j-1);
                    else if(i==0 || j==0)
                    {
                        cout<<"delete "<<str1[i]<<endl;
                    }
                    else
                    cout<<"change "<<str1[i]<<" to "<<str2[j]<<endl;

                }
                else if(lcs[i+1][j+1]==lcs[i][j+1]+1)
                {
                    if(i>0)
                    printPath(i-1,j);
                    cout<<"delete "<<str1[i]<<endl;

                }
                else if(lcs[i+1][j+1]==lcs[i+1][j]+1)
                {
                    if(j>0)
                    printPath(i,j-1);
                    cout<<"insert "<<str2[j]<<endl;


                }

}
else
{
                        printPath(i-1,j-1);
}
}

int main()
{


    cin>>str1>>str2;


    for(int k=0;k<=str2.size();k++)
    {
        lcs[0][k]=k;
    }
    for(int k=0;k<=str2.size();k++)
    {
        lcs[k][0]=k;
    }

    for(int i=0;i<str1.size();i++)
    {


        for(int j=0;j<str2.size();j++)
        {
            if(str1[i]==str2[j])
            {

                lcs[i+1][j+1]= lcs[i][j];

            }
            else
            {
                lcs[i+1][j+1] = 1+ min(lcs[i][j],min(lcs[i+1][j],lcs[i][j+1]));

            }

        }
    }


/*
for(int i=0;i<str1.size();i++)
{
    for(int j=0;j<str2.size();j++)
    {
        cout<<lcs[i+1][j+1]<<" ";
    }
    cout<<endl;
}
*/
    cout<<lcs[str1.size()][str2.size()]<<endl;

//printPath(str1.size(),str2.size());

    return 0;


}

