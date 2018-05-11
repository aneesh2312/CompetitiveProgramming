/*
	Easy problem. Do a dfs, and keep note of how many + and - that a particular subtree needs. For a node X, making all nodes in it's 
	subtree except X zero will require (maximum number of - operations for it's children) + (maximum number of + operations for it's children).
	More detailed explanation in http://codeforces.com/blog/entry/6759
*/
#include <bits/stdc++.h>
#define adj_list vector<vi>
#define endl "\n"
#define INF_INT 2e9
#define INF_LL 2e18
#define matmax 25
#define mod 1000000007
#define mp make_pair
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pair<int, int> >
#define pl pair<ll, ll>
#define pll pair<ll, pair<ll, ll> >
#define vi vector<int>
#define vl vector<ll>
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
using namespace std;
typedef long long int ll;

int lsone(int n)
{
	return (n&-n);
}

void mult(ll a[matmax][matmax], ll b[matmax][matmax], ll c[matmax][matmax], int m, int n, int p)
{
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= p; j++)
		{
			c[i][j] = 0;
			for (int k = 1; k <= n; k++)
			{
				c[i][j] += (a[i][k]*b[k][j])%mod;
				c[i][j] %= mod;
			}
		}
	}
}

void mat_pow(ll a[matmax][matmax], ll c[matmax][matmax], int n, ll p)
{
	if (p == 0)
	{
		for (int i = 1; i <= n; i++)
			c[i][i] = 1;
	}
	else if (p == 1)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
				c[i][j] = a[i][j];
		}
	}
	else
	{
		ll d[matmax][matmax];
		mat_pow(a, d, n, p/2);
		if (p % 2)
		{
			ll e[matmax][matmax];
			mult(d, d, e, n, n, n);
			mult(e, a, c, n, n, n);
		}
		else
		{
			mult(d, d, c, n, n, n);
		}
	}
}

ll pow1(ll a, ll b)
{
	if (b == 0)
		return 1ll;
	else if (b == 1)
		return a;
	else
	{
		ll x = pow1(a, b/2);
		x *= x;
		x %= mod;
		if (b%2)
		{
			x *= a;
			x %= mod;
		}
		return x;
	}
}

ll n, a, b, v[110000];
vector< vector<int> > graph(110000);
ll negans = 0, posans = 0;
pl solve(int index, int par)
{
	ll neg = 0, pos = 0;
	for (int i = 0; i < graph[index].size(); i++)
	{
		int node = graph[index][i];
		if (node == par)
			continue;

		pl temp = solve(node, index);
		if (v[node] < 0)
		{
			pos = max(pos, -v[node]+temp.first);
			neg = max(neg, temp.second);
		}
		else
		{
			neg = max(neg, v[node]+temp.second);
			pos = max(pos, temp.first);
		}
	}
	v[index] += (pos-neg);
	negans = max(negans, neg);
	posans = max(posans, pos);
	return mp(pos, neg);
}

int main()
{
	fastio;		
	cin>>n;
	for (int i = 0; i < n-1; i++)
	{
		cin>>a>>b;
		graph[a].pb(b);
		graph[b].pb(a);
	}

	for (int i = 1; i <= n; i++)
		cin>>v[i];

	solve(1, -1);
	ll ans = negans+posans;
	if (v[1] > 0)
		ans += v[1];
	else
		ans += (-v[1]);
	cout<<ans<<endl;
	return 0;
}
