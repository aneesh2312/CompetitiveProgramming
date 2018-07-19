/*
	Do coordinate compression on (c, d) pairs. Check for each contiguous range of compressed coordinates of ids - like (1, 2), (2, 3), (3,4) ...
	One case to take care of is when (i-1, i) and (i, i+1) don't reach but (i, i) can reach.
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
ll n, m, k, visit[1100], a, b, c, d, s, t, cnt = 1, rev[11000], done[11000], ans = 0;
map<int, int> m1;
set<int> pts;
vector< vector< pii > > graph(1100);

void solve(int beg, int end, int index)
{
	if (visit[index])
		return;
	visit[index] = 1;
	for (int i = 0; i < graph[index].size(); i++)
	{
		pii temp = graph[index][i];
		if (beg >= temp.second.first and end <= temp.second.second)
			solve(beg, end, temp.first);
	}
}

int main()
{
	fastio;		
	cin>>n>>m>>k;

	cin>>s>>t;

	for (int i = 0; i < m; i++)
	{
		cin>>a>>b>>c>>d;
		graph[a].pb(mp(b, mp(c, d)));
		pts.insert(c);
		pts.insert(d);
	}

	set<int>::iterator iter = pts.begin();
	while (iter != pts.end())
	{
		m1[*iter] = cnt;
		rev[cnt++] = *iter;
		iter++;
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < graph[i].size(); j++)
		{
			graph[i][j].second.first = m1[graph[i][j].second.first];
			graph[i][j].second.second = m1[graph[i][j].second.second];
		}
	}

	for (int i = 1; i < cnt-1; i++)
	{
		memset(visit, 0, sizeof(visit));
		solve(i, i+1, s);
		if (visit[t] == 1)
		{
			ans += (rev[i+1]-rev[i]+1-done[i]);
			done[i] = done[i+1] = 1; 
		}
		if (!done[i])
		{
			memset(visit, 0, sizeof(visit));
			solve(i, i, s);
			if (visit[t])
			{
				ans++;
				done[i] = 1;
			}
		}
	}

	cout<<ans<<endl;

	return 0;
}
