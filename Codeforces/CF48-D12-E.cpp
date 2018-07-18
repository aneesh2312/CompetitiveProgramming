/*
	Do dijkstra to check for a win, and find minimum number of moves. If found, print it.
	Next do a dp to find draw or loss. To find draw, use visit array (kind of like DFS). 
	For loss, maintain the maximum number of moves possible. 
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

ll h, t, r, dp1[410][410], dp2[410][410], h1[210], t1[210], h2[210], t2[210], n, m, visit[410][410], dist[410][410];

pl solve(ll heads, ll tails, ll curr)
{
	if (heads == 0 and tails == 0)
	{
		return mp(2, curr);
	}
	if (heads+tails > r)
		return mp(0, curr);
	if (visit[heads][tails])
		return mp(1, -1);
	if (dp1[heads][tails] != -1)
	{
		return mp(dp1[heads][tails], dp2[heads][tails]+curr);
	}
	visit[heads][tails] = 1;
	ll best = -1, maxmoves = 0;
	for (int i = 1; i <= min(n, heads); i++)
	{
		ll temph = heads-i+h1[i];
		ll tempt = tails+t1[i];
		pl temp = solve(temph, tempt, curr+1);
		if (temp.first > best)
		{
			best = temp.first;
			maxmoves = temp.second;
		}
		else if (temp.first == best)
		{
			if (best == 0)
				maxmoves = max(maxmoves, temp.second);
			else if (best == 2)
				maxmoves = min(maxmoves, temp.second);
		}
	}

	for (int i = 1; i <= min(m, tails); i++)
	{
		ll temph = heads+h2[i];
		ll tempt = tails-i+t2[i];
		pl temp = solve(temph, tempt, curr+1);
		if (temp.first > best)
		{
			best = temp.first;
			maxmoves = temp.second;
		}
		else if (temp.first == best)
		{
			if (best == 0)
				maxmoves = max(maxmoves, temp.second);
			else if (best == 2)
				maxmoves = min(maxmoves, temp.second);
		}
	}
	visit[heads][tails] = 0;
	dp1[heads][tails] = best;
	dp2[heads][tails] = maxmoves-curr;
	return mp(dp1[heads][tails], dp2[heads][tails]+curr);
}

void djikstra(ll heads, ll tails)
{
	priority_queue< pll > pq;
	pq.push(mp(0, mp(heads, tails)));
	dist[heads][tails] = 0;
	while (!pq.empty())
	{
		pll temp = pq.top(); pq.pop();
		heads = temp.second.first, tails = temp.second.second;
		if (heads+tails > r)
			continue;
		if (-temp.first != dist[heads][tails])
		{
			pq.push(mp(-dist[heads][tails], mp(heads, tails)));
			continue;
		}
		if (heads == 0 and tails == 0)
			break;

		for (int i = 1; i <= min(m, tails); i++)
		{
			ll temph = heads+h2[i];
			ll tempt = tails-i+t2[i];
			if (temph == heads and tempt == tails)
				continue;
			if (dist[temph][tempt] == -1)
			{
				pq.push(mp(-dist[heads][tails]-1, mp(temph, tempt)));
				dist[temph][tempt] = dist[heads][tails]+1;
			}
		}

		for (int i = 1; i <= min(n, heads); i++)
		{
			ll temph = heads-i+h1[i];
			ll tempt = tails+t1[i];
			if (temph == heads and tempt == tails)
				continue;
			if (dist[temph][tempt] == -1)
			{
				pq.push(mp(-dist[heads][tails]-1, mp(temph, tempt)));
				dist[temph][tempt] = dist[heads][tails]+1;
			}
		}
	}
}

int main()
{
	fastio;		
	cin>>h>>t>>r;
	memset(dp1, -1, sizeof(dp1));
	memset(dp2, -1, sizeof(dp2));
	memset(dist, -1, sizeof(dist));
	cin>>n;
	for (int i = 1; i <= n; i++)
		cin>>h1[i]>>t1[i];

	cin>>m;
	for (int i = 1; i <= m; i++)
		cin>>h2[i]>>t2[i];

	djikstra(h, t);
	if (dist[0][0] != -1)
	{
		cout<<"Ivan"<<endl<<dist[0][0]<<endl;
		return 0;
	}

	pi temp = solve(h, t, 0);

	if (temp.first == 0)
	{
		cout<<"Zmey"<<endl<<temp.second<<endl;
	}
	else if (temp.first == 1)
	{
		cout<<"Draw"<<endl;
	}

	return 0;
}
