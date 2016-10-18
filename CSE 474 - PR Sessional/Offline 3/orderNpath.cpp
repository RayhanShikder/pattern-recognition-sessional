#include<iostream>
#include<string>

using namespace std;

int lcs[2][5000];
int path[2][5000];

string str1,str2;

void printPath(int i,int j)
{
    if(i==0 && j==0)return;
    int ii = i%2;



if(lcs[1-ii][j+1]==min(lcs[ii][j],min(lcs[1-ii][j],lcs[ii][j+1]))+1)
            {

                if(lcs[1-ii][j+1]==1+lcs[1-ii][j])
                {
                    //addPrevRow();
                    printPath(i-1,j-1);
                    cout<<"change "<<str1[i]<<" to "<<str2[j]<<endl;

                }
                else if(lcs[1-ii][j+1]==lcs[ii][j+1]+1)
                {
                    //addPrevRow();
                    printPath(i-1,j);
                    cout<<"delete "<<str1[i]<<endl;

                }
                else if(lcs[1-ii][j+1]==lcs[1-ii][j]+1)
                {

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

    for(int k=0;k<=1;k++)
    {
        lcs[k][0]=k;
    }

    int curcol=str2.size();

    for(int p=str1.size();p>0;p--)
    {

    for(int i=0;i<=p;i++)
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
            if(p==str1.size())
            {
                cout<<"result "<<lcs[p&1][str2.size()]<<endl;
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
    //cout<<lcs[1][str2.size()]<<endl;



//printPath(str1.size()-1,str2.size()-1);

    return 0;


}


