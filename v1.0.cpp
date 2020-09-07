#include<bits/stdc++.h>
using namespace std;
struct Card{
	int num;
	int color;
}card[5][40];
bool cmp(const Card &x,const Card &y){
	return x.num>y.num || (x.num==y.num && x.color>y.color);
}
void print(int num)
{
	if (num==1) printf("A ");
	else if (num==11) printf("J ");
	else if (num==12) printf("Q ");
	else if (num==13) printf("K ");
	else printf("%d ",num);
}
void randomcard() 
{
	int sep,num;//花色和数字，花色五种对应四种基本花色和鬼，鬼数字为1或2 
	int yes[200]={0};//标记剩余卡片 
	srand((unsigned)time(NULL));//初始化随机种子 
	for (int i=1;i<=4;++i)
	{
		for (int j=1;j<=27;++j)
		{
			int id=rand()%108+1;
			while (yes[id]) id=rand()%108+1;
			sep=(id-1)/26,num=id-sep*26;
			yes[id]=1;
			num=(num+1)/2;
			card[i][j].color=sep+1;
			card[i][j].num=(sep+1)==5?num+13:num;
		}
		sort(card[i]+1,card[i]+28,cmp);//手牌排序 
	}
	for (int i=1;i<=4;++i)
	{
		printf("玩家%d\n",i);
		for (int j=1;j<=27;++j)
		{
			switch(card[i][j].color)
			{
				case 1:
					printf("黑桃");
					print(card[i][j].num);
					break;
				case 2:
					printf("红桃");
					print(card[i][j].num);
					break;
				case 3:
					printf("方块");
					print(card[i][j].num);
					break;
				case 4:
					printf("梅花");
					print(card[i][j].num);
					break;
				case 5:
					if(card[i][j].num==14) printf("小鬼 ");
					else if (card[i][j].num==15)printf("大鬼 ");
					break;
				default:
					break; 
			}
		}
		printf("\n");
	}
}
int main(){
	randomcard();
	
	return 0;
}
