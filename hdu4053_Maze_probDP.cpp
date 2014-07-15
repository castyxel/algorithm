//dp当前概率 ＝ 返回1概率＊期望 ＋ 返回父亲节点概率＊期望 ＋ 去其它节点概率＊期望，对于儿子节点，也是这样写，再把儿子节点回代，整理成这样一个公式
//dp 当前节点 ＝ 系数 P ＊ 返回1期望 ＋ 系数 B ＊ 返回父亲节点期望 ＋ 系数 C * 去其它节点期望
//回溯到1节点，整理公式，得到dp1，即1节点到最终节点期望
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
const int maxn = 100015;
double k[maxn], e[maxn];
double p[maxn], b[maxn], c[maxn];
double dpa;
vector<int>t[maxn];
double eps = 1e-10;
bool zero(double x) {
	return fabs(x)<eps;
}
void dfs(int u, int pre){
	int sz = t[u].size();
	double goon = 1-k[u]-e[u];
	p[u] = k[u];
	b[u] = 1/(sz*1.0)*goon;
	c[u] = goon;
	double a=0, vper = b[u];
	for(int i=0; i<sz; i++){
		int v=t[u][i];
		if(v==pre) continue;
		dfs(v, u);
		a += vper*b[v];
		p[u] += vper*p[v];
		c[u] += vper*c[v];
	}
	a = 1-a;
	p[u] /= a;
	b[u] /= a;
	c[u] /= a;
	if(u==1){
		if(zero(1-p[u])) dpa=-1;
		else dpa = c[u]/(1-p[u]);
	}
}
void clear(int n){
	for(int i=0; i<=n; i++)t[i].clear();
}
int main(){
	int ncase;
	cin>>ncase;
	int id=0;
	while(ncase--){
		id++;
		int n;
		scanf("%d", &n);
		clear(n);
		int u, v;
		for(int i=0; i<n-1; i++){
			scanf("%d%d", &u, &v);
			t[u].push_back(v);
			t[v].push_back(u);
		}
		for(int i=1; i<=n; i++){
			scanf("%lf%lf", &k[i], &e[i]);
			k[i]/=100;
			e[i]/=100;
		}
		dfs(1, 0);
		printf("Case %d: " ,id);
		if(dpa<0){
			printf("impossible\n");
		}else{
			printf("%.4lf\n", dpa);
		}

	}
}

