/*
	Construct a bipartite graph. The graph will have edges between bf and gf, and 2*x and (2*x+1)%(2*n). Such construction ensures that
	there will be no odd length cycle, therefore the graph will be bipartite. Then do dfs on graph starting with 1 kind of food.
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
ll n, u, v, ans[210000], b[110000], g[110000];
vector< vector<int> > graph(210000);

void dfs(int index, int col)
{
	ans[index] = col;
	for (int i = 0; i < graph[index].size(); i++)
	{
		int node = graph[index][i];
		if (ans[node] == 0)
		{
			if (col == 1)
				dfs(node, 2);
			else
				dfs(node, 1);
		}
	}
}

int main()
{
	fastio;		
	cin>>n;
	for (int i = 1; i <= n; i++)
	{
		cin>>b[i]>>g[i];
		u = b[i]; v = g[i];
		graph[u].pb(v);
		graph[v].pb(u);
		graph[2*i].pb((2*i+1)%(2*n));
		graph[(2*i+1)%(2*n)].pb(2*i);
	}

	for (int i = 1; i <= 2*n; i++)
	{
		if (ans[i] == 0)
		{
			dfs(i, 1);
		}
	}

	for (int i = 1; i <= n; i++)
	{
		cout<<ans[b[i]]<<" "<<ans[g[i]]<<endl;
	}

	return 0;
}
