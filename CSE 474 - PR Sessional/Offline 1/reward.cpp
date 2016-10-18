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
const double rho = 1;

int main(void){
	ios_base::sync_with_stdio(0);
	
	srand(time(0));
	
	w.resize(3,0);
	//~ rep(i,len(w))w[i] = rand()%1000;
	
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
	
	int cnt= 0,cur=0,tot_true=0;
	
	while(true){
		double d = x[cur]*w[0]+y[cur]*w[1]+w[2];
		if((d>0 && cls[cur]==2) || (d<0 && cls[cur]==1)){ //correctly classified
			tot_true++;
			cur++;
			cur %= len(cls);
			if(tot_true==len(cls))break;
			continue;
		}
		
		if((d<0 || fabs(d)<eps) && cls[cur]==2){ //d<0 => class 1
			w[0] += rho*x[cur];
			w[1] += rho*y[cur];
			w[2] += rho*1;
		}else if((d>0 || fabs(d)<eps) && cls[cur]==1){ //d>0 => class 2
			w[0] -= rho*x[cur];
			w[1] -= rho*y[cur];
			w[2] -= rho*1;
		}
		tot_true = 0;
		cnt++;
		cur++;
		cur%=len(cls);
	}
	
	cout<<"w generated with "<<cnt<<" iterations."<<endl;
	cout<<"w[0]= "<<w[0]<<" w[1]="<<w[1]<<" w[2]="<<w[2]<<endl;
	
	fin.open("test.txt",ifstream::in);
	cnt = 0;
	int wrong = 0;
	while(fin>>t1>>t2>>c){
		double d = w[0]*t1+w[1]*t2+w[2];
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
