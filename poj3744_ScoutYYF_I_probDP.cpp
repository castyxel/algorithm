//写错快速幂还有初始化错误……简直神烦……
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 15;
int mpt[maxn];
struct mat {
	double m[3][3];
	void setone() {
		for(int i=0; i<3; i++) {
			for(int j=0; j<3; j++) {
				m[i][j]=0;
			}
		}
		for(int i=0; i<3; i++)
			m[i][i]=1;
	}
	void setzero() {
		for(int i=0; i<3; i++) {
			for(int j=0; j<3; j++)
				m[i][j] = 0;
		}
	}
	void setp(double p) {
		setzero();
		m[0][0] = p;
		m[0][1] = 1-p;
		m[1][0] = 1;
		m[2][1] = 1;
	}
};
mat operator*(mat& a, mat& b) {
	mat ret;
	ret.setzero();
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			for(int k=0; k<3; k++) {
				ret.m[i][j] += a.m[i][k] * b.m[k][j];
			}
		}
	}
	return ret;
}
mat quickpow(mat a, int b) {
	mat ret;
	ret.setone();
	while(b) {
		if(b&1) {
			ret = ret*a;
		}
		a = a*a;
		b>>=1;
	}
	return ret;
}
bool cannot(int n) {
	if(mpt[0]==1) return true;
	for(int i=0; i<n-1; i++) {
		if(mpt[i]+1==mpt[i+1]) return true;
	}
	return false;
}
double gao(int n, double p) {
	mat a;
	double dpi_2=0, dpi_1=1;
	double ret;
	mpt[n]=mpt[n-1]+2;
	n++;
	for(int i=0; i<n; i++) {
		a.setp(p);
		int b;
		if(i>0 ) b = mpt[i]-mpt[i-1];
		else b = mpt[i]-1;
		if(b==0) continue;
		if(mpt[i]==2){
			double pi_1 = 1;
			dpi_1 = 0;
			dpi_2 = pi_1;
			ret = pi_1;
		}else{
			a.setp(p);
			a=quickpow(a, b-1);
			double pi_1 = a.m[0][0] * dpi_1 + a.m[0][1] * dpi_2;
			dpi_1 = 0;
			dpi_2 = pi_1;
			ret = pi_1;
		}
	}
	return ret;
}
int main() {
	int n;
	double prob;
	while(cin>>n>>prob) {
		for(int i=0; i<n; i++)cin>>mpt[i];
		sort(mpt, mpt+n);
		if(cannot(n)) {
			printf("0.0000000\n");
		} else {
			printf("%.7lf\n", gao(n, prob));
		}
	}
}

