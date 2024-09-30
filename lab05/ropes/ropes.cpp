#include <bits/stdc++.h>

using namespace std;

// The main function that returns
// the minimum cost to connect n
// ropes of lengths stored in len[0..n-1]

int minCost(int len[], int n)
{
	if (n==0) { return 0 ; }
	if (n==1) { return len[0]; }
	if(n==2)  { return len[0] + len[1]; }

 	std :: priority_queue<int, vector<int>, std :: less<int>> Q;
	for (int i = 0; i<n; i++)
	{
		Q.push(len[i]) ;
	}
	int cost = 0;
	while(Q.size()>1)
	{
		int a = Q.top() ;
		Q.pop();
		a+=Q.top() ;
		Q.pop();
		Q.push(a) ;
		cost+=a;
	}
	return cost;
}


