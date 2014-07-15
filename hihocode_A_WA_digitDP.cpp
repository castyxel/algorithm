//方法有识，总之在WA中
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;
const int mid = 105;
const int mod = (1e9)+7;
const int maxpos = 19;
int dp[maxpos][10][2*mid+10];
int mones[maxpos], tens[maxpos];
int uplimit[19], lowlimit[19], ed, lena, lenb, ups[19], lows[19];
int dfs(int pos, int digit, int sum, bool isup, bool islow, int& cnt) {
	cnt = 0;
	int sumup = 0;
	int times;
	if(dp[pos][digit][sum]!=-1 && !islow && !isup){
		cnt++;
		return dp[pos][digit][sum];
	}
	if(pos == ed-1) {
		if(sum==mid+digit*mones[pos]){
			cnt++;
			return digit;
		}
		else return -1;
	}
	if(isup && islow) {
		for(int i=lowlimit[pos+1]; i<=uplimit[pos+1]; i++) {
			if(i==lowlimit[pos+1]) {
				int tmp = dfs(pos+1, i, sum-(mones[pos])*digit, isup&&(uplimit[pos+1]==i), true, times);
				if(tmp>=0 && dp[pos][digit][sum]<0)dp[pos][digit][sum]=0;
				if(tmp>=0){
					dp[pos][digit][sum] += tens[ed-pos-1]*digit*times+tmp;
					cnt++;
					sumup += times;
				}
			} else if(i==uplimit[pos+1]) {
				int tmp = dfs(pos+1, i, sum-(mones[pos])*digit, true, islow&&(lowlimit[pos+1]==i), times);
				if(tmp>=0 && dp[pos][digit][sum]<0)dp[pos][digit][sum]=0;
				if(tmp>=0){
					dp[pos][digit][sum] += tens[ed-pos-1]*digit*times+tmp;
					cnt++;
					sumup += times;
				}
			} else {
				int tmp = dfs(pos+1, i, sum-(mones[pos])*digit, false, false, times);
				if(tmp>=0 && dp[pos][digit][sum]<0)dp[pos][digit][sum]=0;
				if(tmp>=0){
					dp[pos][digit][sum] += tens[ed-pos-1]*digit*times+tmp;
					cnt++;
					sumup += times;
				}
			}
			dp[pos][digit][sum] %= mod;
		}
	} else if(isup) {
		for(int i=0; i<=uplimit[pos+1]; i++) {
			if(i==uplimit[pos+1]) {
				int tmp = dfs(pos+1, i, sum-(mones[pos])*digit, true, islow&&(i==lowlimit[pos+1]), times);
				if(tmp>=0 && dp[pos][digit][sum]<0)dp[pos][digit][sum]=0;
				if(tmp>=0){
					dp[pos][digit][sum] += tens[ed-pos-1]*digit*times+tmp;
					cnt++;
					sumup += times;
				}
			} else {
				int tmp = dfs(pos+1, i, sum-(mones[pos])*digit, false, false, times);
				if(tmp>=0 && dp[pos][digit][sum]<0)dp[pos][digit][sum]=0;
				if(tmp>=0){
					dp[pos][digit][sum] += tens[ed-pos-1]*digit*times+tmp;
					cnt++;
					sumup += times;
				}
			}
			dp[pos][digit][sum] %= mod;
		}
	} else if(islow) {
		for(int i=lowlimit[pos+1]; i<=9; i++) {
			if(i==lowlimit[pos+1]) {
				int tmp = dfs(pos+1, i, sum-(mones[pos])*digit, isup&&(i==uplimit[pos+1]), true, times);
				if(tmp>=0 && dp[pos][digit][sum]<0)dp[pos][digit][sum]=0;
				if(tmp>=0){
					dp[pos][digit][sum] += tens[ed-pos-1]*digit*times+tmp;
					cnt++;
					sumup += times;
				}
			} else {
				int tmp = dfs(pos+1, i, sum-(mones[pos])*digit, false, false, times);
				if(tmp>=0 && dp[pos][digit][sum]<0)dp[pos][digit][sum]=0;
				if(tmp>=0){
					dp[pos][digit][sum] += tens[ed-pos-1]*digit*times+tmp;
					cnt++;
					sumup += times;
				}
			}
			dp[pos][digit][sum] %= mod;
		}

	} else {
		for(int i=0; i<=9; i++) {
			int tmp = dfs(pos+1, i, sum-(mones[pos])*digit, false, false, times);
			if(tmp>=0 && dp[pos][digit][sum]<0)dp[pos][digit][sum]=0;
			if(tmp>=0){
				dp[pos][digit][sum] += tens[ed-pos-1]*digit*times+tmp;
				cnt++;
				sumup += times;
			}
			dp[pos][digit][sum] %= mod;
		}
	}
	cnt = sumup;
	if(dp[pos][digit][sum]==-1) dp[pos][digit][sum]--;
	return dp[pos][digit][sum];
}
void getin(ll num, int n[], int& len){
	len=0;
	while(num){
		n[len++]=num%10;
		num/=10;
	}
	reverse(n, n+len);
}
void Copy(int a[], int b[], int len){
	for(int i=0; i<len ;i++)
		a[i]=b[i];
}
int main(){
	ll a, b;
	int k;
	mones[0]=1;
	for(int i=1; i<20; i++)
		mones[i] = (-1)*mones[i-1];
	ll tenst = 1;
	tens[0]=1;
	for(int i=1; i<=18; i++){
		tenst = 10*tens[i-1];
		tenst %= mod;
		tens[i] = tenst;
	}

	while(cin>>a>>b>>k){
		k+=mid;
		for(int i=0; i<20; i++) uplimit[i]=9, lowlimit[i]=-1;
		memset(dp, -1, sizeof(dp));
		getin(b, ups, lena);
		getin(a, lows, lenb);
		int ans = 0;
		for(int i=lenb; i<=lena; i++){
			memset(dp, -1, sizeof(dp));
			if(i==lenb){
				Copy(lowlimit, lows, i);
			}else{
				if(i==lenb+1)memset(lowlimit, 0, sizeof(lowlimit));
				lowlimit[0]=1;
			}
			if(i==lena){
				Copy(uplimit, ups, i);
			}
			ed = i;
			for(int j=lowlimit[0]; j<=uplimit[0]; j++){
				bool islow, isup;
				if(j==lowlimit[0]) islow = true;
				else islow = false;
				if(j==uplimit[0] ) isup = true;
				else isup = false;
				int tp;
				int tmp = dfs(0, j, k, isup, islow, tp);
				if(tmp>=0) ans += tmp;
				ans %= mod;
			}
		}
		printf("%d\n", ans);
	}
}
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;
const int mid = 105;
const int mod = (1e9)+7;
const int maxpos = 19;
int dp[maxpos][10][2*mid+10];
int mones[maxpos], tens[maxpos];
int uplimit[19], lowlimit[19], ed, lena, lenb, ups[19], lows[19];
int dfs(int pos, int digit, int sum, bool isup, bool islow, int& cnt) {
	cnt = 0;
	int sumup = 0;
	int times;
	if(dp[pos][digit][sum]!=-1 && !islow && !isup){
		cnt++;
		return dp[pos][digit][sum];
	}
	if(pos == ed-1) {
		if(sum==mid+digit*mones[pos]){
			cnt++;
			return digit;
		}
		else return -1;
	}
	if(isup && islow) {
		for(int i=lowlimit[pos+1]; i<=uplimit[pos+1]; i++) {
			if(i==lowlimit[pos+1]) {
				int tmp = dfs(pos+1, i, sum-(mones[pos])*digit, isup&&(uplimit[pos+1]==i), true, times);
				if(tmp>=0 && dp[pos][digit][sum]<0)dp[pos][digit][sum]=0;
				if(tmp>=0){
					dp[pos][digit][sum] += tens[ed-pos-1]*digit*times+tmp;
					cnt++;
					sumup += times;
				}
			} else if(i==uplimit[pos+1]) {
				int tmp = dfs(pos+1, i, sum-(mones[pos])*digit, true, islow&&(lowlimit[pos+1]==i), times);
				if(tmp>=0 && dp[pos][digit][sum]<0)dp[pos][digit][sum]=0;
				if(tmp>=0){
					dp[pos][digit][sum] += tens[ed-pos-1]*digit*times+tmp;
					cnt++;
					sumup += times;
				}
			} else {
				int tmp = dfs(pos+1, i, sum-(mones[pos])*digit, false, false, times);
				if(tmp>=0 && dp[pos][digit][sum]<0)dp[pos][digit][sum]=0;
				if(tmp>=0){
					dp[pos][digit][sum] += tens[ed-pos-1]*digit*times+tmp;
					cnt++;
					sumup += times;
				}
			}
			dp[pos][digit][sum] %= mod;
		}
	} else if(isup) {
		for(int i=0; i<=uplimit[pos+1]; i++) {
			if(i==uplimit[pos+1]) {
				int tmp = dfs(pos+1, i, sum-(mones[pos])*digit, true, islow&&(i==lowlimit[pos+1]), times);
				if(tmp>=0 && dp[pos][digit][sum]<0)dp[pos][digit][sum]=0;
				if(tmp>=0){
					dp[pos][digit][sum] += tens[ed-pos-1]*digit*times+tmp;
					cnt++;
					sumup += times;
				}
			} else {
				int tmp = dfs(pos+1, i, sum-(mones[pos])*digit, false, false, times);
				if(tmp>=0 && dp[pos][digit][sum]<0)dp[pos][digit][sum]=0;
				if(tmp>=0){
					dp[pos][digit][sum] += tens[ed-pos-1]*digit*times+tmp;
					cnt++;
					sumup += times;
				}
			}
			dp[pos][digit][sum] %= mod;
		}
	} else if(islow) {
		for(int i=lowlimit[pos+1]; i<=9; i++) {
			if(i==lowlimit[pos+1]) {
				int tmp = dfs(pos+1, i, sum-(mones[pos])*digit, isup&&(i==uplimit[pos+1]), true, times);
				if(tmp>=0 && dp[pos][digit][sum]<0)dp[pos][digit][sum]=0;
				if(tmp>=0){
					dp[pos][digit][sum] += tens[ed-pos-1]*digit*times+tmp;
					cnt++;
					sumup += times;
				}
			} else {
				int tmp = dfs(pos+1, i, sum-(mones[pos])*digit, false, false, times);
				if(tmp>=0 && dp[pos][digit][sum]<0)dp[pos][digit][sum]=0;
				if(tmp>=0){
					dp[pos][digit][sum] += tens[ed-pos-1]*digit*times+tmp;
					cnt++;
					sumup += times;
				}
			}
			dp[pos][digit][sum] %= mod;
		}

	} else {
		for(int i=0; i<=9; i++) {
			int tmp = dfs(pos+1, i, sum-(mones[pos])*digit, false, false, times);
			if(tmp>=0 && dp[pos][digit][sum]<0)dp[pos][digit][sum]=0;
			if(tmp>=0){
				dp[pos][digit][sum] += tens[ed-pos-1]*digit*times+tmp;
				cnt++;
				sumup += times;
			}
			dp[pos][digit][sum] %= mod;
		}
	}
	cnt = sumup;
	if(dp[pos][digit][sum]==-1) dp[pos][digit][sum]--;
	return dp[pos][digit][sum];
}
void getin(ll num, int n[], int& len){
	len=0;
	while(num){
		n[len++]=num%10;
		num/=10;
	}
	reverse(n, n+len);
}
void Copy(int a[], int b[], int len){
	for(int i=0; i<len ;i++)
		a[i]=b[i];
}
int main(){
	ll a, b;
	int k;
	mones[0]=1;
	for(int i=1; i<20; i++)
		mones[i] = (-1)*mones[i-1];
	ll tenst = 1;
	tens[0]=1;
	for(int i=1; i<=18; i++){
		tenst = 10*tens[i-1];
		tenst %= mod;
		tens[i] = tenst;
	}

	while(cin>>a>>b>>k){
		k+=mid;
		for(int i=0; i<20; i++) uplimit[i]=9, lowlimit[i]=-1;
		memset(dp, -1, sizeof(dp));
		getin(b, ups, lena);
		getin(a, lows, lenb);
		int ans = 0;
		for(int i=lenb; i<=lena; i++){
			memset(dp, -1, sizeof(dp));
			if(i==lenb){
				Copy(lowlimit, lows, i);
			}else{
				if(i==lenb+1)memset(lowlimit, 0, sizeof(lowlimit));
				lowlimit[0]=1;
			}
			if(i==lena){
				Copy(uplimit, ups, i);
			}
			ed = i;
			for(int j=lowlimit[0]; j<=uplimit[0]; j++){
				bool islow, isup;
				if(j==lowlimit[0]) islow = true;
				else islow = false;
				if(j==uplimit[0] ) isup = true;
				else isup = false;
				int tp;
				int tmp = dfs(0, j, k, isup, islow, tp);
				if(tmp>=0) ans += tmp;
				ans %= mod;
			}
		}
		printf("%d\n", ans);
	}
}

