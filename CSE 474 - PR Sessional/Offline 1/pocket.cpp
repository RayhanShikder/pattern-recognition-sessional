#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<int> > vvi;
typedef vector<string> vs;
typedef vector<pair<int,int> > vpii;

#define pb push_back
#define mp make_pair
#define PI acos(-1)
#define all(a) (a).begin(),(a).end()
#define len(a) ((int)(a).size())
#define mem(a,n) memset(a,n,sizeof(a))
#define eps 1e-9
#define rep(i,n) for(int i=0;i<(n);i++)
#define repi(i,a,n) for(int i=(a);i<(n);i++)
#define repr(i,a,n) for(int i=(n);i>=(a);i--)


vector<double> w;
const double rho = 0.5;

int main(void){
	ios_base::sync_with_stdio(0);
	
	srand(time(0));
	
	w.resize(3);
	rep(i,len(w))w[i] = rand()%1000;
	
	vector<double>x,y;
	vi cls;
	
	ifstream fin;
	fin.open("train.txt",ifstream::in);
	double t1,t2;
	int c;
	while(fin>>t1>>t2>>c){
		x.pb(t1);
		y.pb(t2);
		cls.pb(c);
	}	
	fin.close();
	
	int cnt= 0;
	vector<double> ws(3,0);
	int bs=0;
	
	while(true){
		vector<double> next_w = w;
		bool b = false;
		int right_cnt = 0;
		rep(i,len(x)){
			double d = x[i]*w[0]+y[i]*w[1]+w[2];
			double del = 0;
			
			if((d>0 && cls[i]==2) || (d<0 && cls[i]==1)){ //correctly classified
				right_cnt++;
			}
			
			if(d>0 && cls[i]==1){ //d>0 => class 2
				del = -1;
				b = true;
			}else if(d<0 && cls[i]==2){ //d<0 => class 1
				del = 1;
				b = true;
			}
			next_w[0] += del*rho*x[i];
			next_w[1] += del*rho*y[i];
			next_w[2] += del*rho*1;
		}
		cnt++;
		
		if(right_cnt>bs){
			bs = right_cnt;
			ws = w;
		}
		
		if(!b)break;
		w = next_w;
	}
	
	cout<<"w generated with "<<cnt<<" iterations."<<endl;
	cout<<"w[0]= "<<w[0]<<" w[1]="<<w[1]<<" w[2]="<<w[2]<<endl;
	
	fin.open("test.txt",ifstream::in);
	cnt = 0;
	int wrong = 0;
	while(fin>>t1>>t2>>c){
		double d = ws[0]*t1+ws[1]*t2+ws[2];
		cout<<"Test "<<cnt++<<": ";
		
		if(d>0){
			wrong += c!=2;
			cout<<"predicted: "<<2<<"\texpected: "<<c<<endl;
		}else{
			wrong += c!=1;
			cout<<"predicted: "<<1<<"\texpected: "<<c<<endl;
		}
	}
	
	fin.close();
	
	cout<<"Total wrong predictions: "<<wrong<<endl;
	
	return 0;
}
