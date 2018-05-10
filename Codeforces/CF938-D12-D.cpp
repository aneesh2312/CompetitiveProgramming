/*
	Easy problem. Do a dijkstra based on total cost of attending concert. Start with node with minimum a[i], update the cost
	for other nodes. Select node with minimum cost among those not selected yet, so on..	
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

ll n, m, a[210000], done[210000], u, v, w;
vector< vector< pl > > graph(210000);

int main()
{
	fastio;		
	cin>>n>>m;
	for (int i = 0; i < m; i++)
	{
		cin>>u>>v>>w;
		graph[u].pb(mp(v, w));
		graph[v].pb(mp(u, w));
	}

	priority_queue< pl > pq;
	for (int i = 1; i <= n; i++)
	{
		cin>>a[i];
		pq.push(mp(-a[i], i));
	}

	while (!pq.empty())
	{
		pl temp = pq.top(); pq.pop();
		if (done[temp.second])
			continue;
		done[temp.second] = 1;
		int node = temp.second;
		for (int i = 0; i < graph[node].size(); i++)
		{
			pl t = graph[node][i];
			if (2*t.second-temp.first < a[t.first])
			{
				a[t.first] = 2*t.second - temp.first;
				pq.push(mp((temp.first - 2*t.second), t.first));
			}
		}
	}

	for (int i = 1; i <= n; i++)
		cout<<a[i]<<" ";
	cout<<endl;

	return 0;
}
