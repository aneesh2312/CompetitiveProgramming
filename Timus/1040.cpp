/*
	Hint is gcd(x, x+1) = 1. Then it is just plain dfs.
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

int gcd(int a, int b)
{
   	if (b == 0)
   		return a;
   	a %= b;
   	return gcd(b, a);
}

ll n, m, mat[100][100], cost[100][100], u, v, revu[3000], revv[3000], done[100], curr = 1;
vector<pi> g;

int currgcd(int index, int pos)
{
	int ans = -1;
	for (int i = 1; i <= n; i++)
	{
		if (i == pos)
			continue;
		if (cost[i][index] != 0)
		{
			if (ans == -1)
				ans = cost[i][index];
			else
				ans = gcd(ans, cost[i][index]);
		}
	}
	if (ans == -1)
		return 1;
	return ans;
}

void dfs(int index, int par)
{
	done[index] = 1;
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		if (!done[i] and mat[i][index] and cost[index][i] == 0)
		{
			cost[i][index] = cost[index][i] = curr++;
			dfs(i, index);
			cnt++;
		}
	}

	for (int i = 1; i <= n; i++)
	{
		if (mat[i][index] and i != par and cost[index][i] == 0)
		{
			cost[i][index] = cost[index][i] = curr++;
			break;
		}
	}
}

int main()
{
	fastio;		
	cin>>n>>m;
	for (int i = 0; i < m; i++)
	{
		cin>>u>>v;
		mat[u][v] = mat[v][u] = 1;
		g.pb(mp(u, v));
	}

	for (int i = 1; i <= n; i++)
	{
		if (!done[i])
		{
			dfs(i, -1);
		}
	}

	cout<<"YES\n";
	for (int i = 0; i < m; i++)
	{
		u = g[i].first, v = g[i].second;
		if (cost[u][v] == 0)
		{
			cout<<curr<<" ";
			curr++;
		}
		else
			cout<<cost[u][v]<<" ";
	}
	cout<<endl;

	return 0;
}
