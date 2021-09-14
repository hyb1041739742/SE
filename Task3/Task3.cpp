#include<bits/stdc++.h>
using namespace std;
const int maxn = 20000+10;
int prime[maxn];
int visit[maxn];
void Prime(){
    memset(visit,0,sizeof(visit));
    memset(prime, 0, sizeof(prime));
    for (int i = 2;i <= maxn; i++) {
        if (!visit[i]) {
            prime[++prime[0]] = i;      //纪录素数， 这个prime[0] 相当于 cnt，用来计数
        }
        for (int j = 1; j <=prime[0] && i*prime[j] <= maxn; j++) {
//            cout<<"  j = "<<j<<" prime["<<j<<"]"<<" = "<<prime[j]<<" i*prime[j] = "<<i*prime[j]<<endl;
            visit[i*prime[j]] = 1;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}


int main()
{
	Prime();
	int count = 0;
	for(int i = 2; i <= maxn-10; i++)
	{
		if(!visit[i]) printf("%d ", i),count++;
		if(count == 5) printf("\n"), count = 0;
	}
	
} 
