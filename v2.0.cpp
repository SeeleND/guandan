#include<bits/stdc++.h>
#include<windows.h> 
using namespace std;
struct Card{
	int num;
	int color;
	int cardno;
}card[5][40],nowCardSeq[28];
struct Record{
	int tot;//出牌数 
	Card seq[10];//出牌序列 
	int type;//牌型 
}record;
const int iniCardno[16]={0,12,13,1,2,3,4,5,6,7,8,9,10,11,14,15};//第一局卡牌大小 
int 
int remain[5]={0,27,27,27,27};//剩余手牌 
int rank[5];//名次 
int level[3]={0,2,2};//玩家1玩家2所在队伍初始等级 
int player=1;//玩家序号
int players=4;//剩余没有出完牌的玩家 
int nowCardId[28];

bool cmp(const Card &x,const Card &y){//排序判断 
	return x.cardno>y.cardno || (x.cardno==y.cardno && x.color<y.color);
}
void numprint(int num)//输出数字 
{
	if (num==1) printf("A ");
	else if (num==11) printf("J ");
	else if (num==12) printf("Q ");
	else if (num==13) printf("K ");
	else printf("%d ",num);
}
void print(int player,Card c[],int tot)//输出手牌序列，玩家序号不为0输出玩家序号 
{
	if (player) printf("玩家%d\n",player);
	int i=0;
	for (int j=1;j<=tot;++j)
	{
		if (c[j].color==0) continue;
		else
		{
			++i;nowCardId[i]=j;
			switch(c[j].color)
			{
				case 1:
					printf("%d.红桃",i);
					numprint(c[j].num);
					break;
				case 2:
					printf("%d.黑桃",i);
					numprint(c[j].num);
					break;
				case 3:
					printf("%d.方块",i);
					numprint(c[j].num);
					break;
				case 4:
					printf("%d.梅花",i);
					numprint(c[j].num);
					break;
				case 5:
					if(c[j].num==14) printf("%d.小鬼 ",i);
					else if (c[j].num==15)printf("%d.大鬼 ",i);
					break;
				default:
					break;
			}
		}
	}
}
void randomcard() 
{
	int sep,num;//花色和数字，花色五种对应四种基本花色和鬼，鬼数字为1或2 
	int yes[200]={0};//标记剩余卡片 
	for (int i=1;i<=4;++i)
	{
		int team=i>2?i-2:i;
		for (int j=1;j<=27;++j)
		{
			int id=rand()%108+1;
			while (yes[id]) id=rand()%108+1;
			sep=(id-1)/26,num=id-sep*26;
			yes[id]=1;
			num=(num+1)/2;
			if ((sep+1)==5) num+=13;
			card[i][j].color=sep+1;
			card[i][j].num=num;
			card[i][j].cardno=cardno[team][num];
		}
		sort(card[i]+1,card[i]+28,cmp);//手牌排序 
	}
}
bool comp(Card &a[],int alen,int type)
{
	if (type!=record.type)//如果牌型不同只需同花和炸弹的比较 
	{
		if (record.tot<=5) return 0;
		else return 1;
	}
	else 
	{
		if (type==9) 
		{
			if (alen>record.tot) return 1;
			else if (alen<record.tot) return 0;
			else if (alen==record.tot)
			{
				if (a[tot].num>record.seq[tot].num) return 1;
				else return 0;
			}
		}
		else 
		{
			if (a[tot].num>record.seq[tot].num) return 1;
			else return 0;
		}
	}
}
bool duizi(Card &a[],int tot)//判断并根据逢人配修改对子 
{
	int i=1;
	int team=player>2?player-2:player;
	if (a[1].num==a[2].num) return true;//若相等则是 
	while(i<tot && a[i].num==level[team] && a[i].color==1) ++i;//不相等检查逢人配 
	if (i==1) 
	{
		a[1].num=a[2].num;
		a[1].cardno=cardno[a[1].num];//逢人配数值与另一张牌相同 
		return 1;
	}
	else return 0;
}
bool pd(Card &c[],int tot) //牌型判断1:单牌2:对子3:三顺4:三带二5:钢板6:连对
						  //7:顺子8:同花9:炸
{
	sort(c+1,c+1+tot,cmp);
	if (tot<=1) return tot;
	else if (tot==2) 
	{
		if (duizi(c,tot)) return 2;
	}
	else if (tot==3) 
	{
		if (szp(c,tot)) return 3;
	}
	else if (tot==5)
	{
		int temp=0;
		if (sandaier(c,tot)) return 4;
		temp=shunzi(c,tot);
		if (temp) return temp;
	}
	else if (tot==6)
	{
		if (gangban(c,tot)) return 5;
		if (liandui(c,tot)) return 6;
	}
	else if (tot>=4)
	{
		if (bomb(c,tot)) return 9;
	}
	return -1;
}
void roundend()
{
	if (rank[3]==1&&rank[4]==3) level[2]+=3;
	if (rank[3]==2&&rank[4]==4) level[1]+=3;
	if ((rank[1]==1||rank[1]==3)&&(rank[2]==2||rank[2]==4)&&(rank[3]==1||rank[3]==3)&&(rank[4]==2||rank[4]==4)) level[1]+=2;
	if ((rank[1]==2||rank[1]==4)&&(rank[2]==1||rank[2]==3)&&(rank[3]==2||rank[3]==4)&&(rank[4]==1||rank[4]==3)) level[2]+=2;
	if ((rank[1]==1||rank[1]==3)&&(rank[2]==2||rank[2]==4)&&(rank[3]==))
}
int main(){
	srand((unsigned)time(NULL));//初始化随机种子 
	int tot,serialnum[28],round=0,turn=0; 
	int flag;//判定牌型 
	bool roundstart=1;//一局开始 
	while (1)
	{
		tot=0;
		system("cls");
		if (roundstart) //一局开始初始化 
		{
			memset(rank,0,sizeof(rank));
			randomcard();//发牌
			roundstart=0;
			player=1;
			players=4;
			++round;
			turn=0;
			printf("第%d局开始，玩家1、3主牌为%d，玩家2、4主牌为%d",round,level1,level2);
		}
		if (remain[player]==0) 
		{
			player++;
			if (player>4) player-=4;
			continue;
		}
		if (turn++) {
			printf("上一个出牌：");
			print(0,record.seq,record.tot);
		}
		print(player,card[player],remain[player]);
		printf("请输入出牌序号，以0作为结尾，用空格隔开，不出直接输入0：");
		while (scanf("%d",serialnum[++tot])!=0);
		for (int i=1,--tot;i<=tot;++i)
			nowCardSeq[i]=card[player][serialnum[i]];
		flag=pd(nowCardSeq,tot);
		while (flag==-1 || (flag<8 && flag!=record.type && record.type!=0) 
			|| ((flag>=8 || flag==record.type) && !comp(nowCardSeq,tot,flag))
		//牌型不合法或与上次出牌不同或小于上次出牌大小 
		{
			tot=0;
			printf("出牌不合法，请重新输入：");
			while (scanf("%d",serialnum[++tot])!=0);
			for (int i=1,--tot;i<=tot;++i)
				nowCardSeq[i]=card[player][nowCardId[serialnum[i]]];
			flag=pd(nowCardSeq,tot);
		}
		remain[player]-=tot;//减手牌数 
		if (tot == 0) jiefeng++;
		else jiefeng=0;
		if (flag==0 && jiefeng) ++jiefeng;
		if (remain[player]==0) //手牌出完 
		{
			if (players==4) 
			{
				jiefeng=1;//接风计数
				jiefengplayer=player+2;
				if (jiefengplayer>4) jiefengplayer-=4;
			}
			--players;//剩余玩家-1
			rank[4-players]=player;
			if (players==1) 
			{
				roundend();
				roundstart=1;
			}
		}
		record.seq=nowCardSeq;
		record.tot=tot;
		record.type=flag;//记录出牌 
		for (int i=1;i<=tot;++i) 
			card[player][nowCardId[serialnum[i]]].color=0;//已经出过的牌标记 
		if (jiefeng==4)
		{
			player=jiefengplayer;
			jiefeng=0;
		}else
		{
			++player;//下一家 
			if (player>4) player-=4; 
		}
	}
	return 0;
}
