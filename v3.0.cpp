#include<bits/stdc++.h>
#include<windows.h> 
using namespace std;
struct Card{
	int num;
	int color;
	int cardno;
}card[5][40],nowCardSeq[28];
struct Record{
	int tot;//卡牌数量 
	Card seq[28];//卡牌序列 
	int type;//牌型 
}record;
const int iniCardno[16]={0,12,13,1,2,3,4,5,6,7,8,9,10,11,14,15};//初始卡牌大小 
int cardno[3][16];//每个队伍卡牌大小 
int remain[5]={0,27,27,27,27};//剩余卡牌数 
int playerrank[5]={0,0,0,0,0};//排名 
int level[3]={0,2,2};//每队等级 
int player=1;//本回合出牌玩家 
int players=4;//剩余玩家 
int nowCardId[28];//现在剩余牌所在数组下标 
int backtotwo[3];//A打三不过 
int gong=0;//进贡方式 

bool cmp(const Card &x,const Card &y){//排序判断 
	return x.cardno>y.cardno || (x.cardno==y.cardno && x.color<y.color);
}
void numprint(int num)//输出数字 
{
	if (num==1) printf("A  ");
	else if (num==11) printf("J  ");
	else if (num==12) printf("Q  ");
	else if (num==13) printf("K  ");
	else printf("%d  ",num);
}
void print(int player,Card c[],int tot)//输出卡牌，玩家序号不为0输出玩家 
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
					if(c[j].num==14) printf("%d.小王    ",i);
					else if (c[j].num==15)printf("%d.大王    ",i);
					break;
				default:
					break;
			}
		}
	}
	printf("\n");
}
void setCardno()//设定卡牌大小 
{
	for (int i=1;i<=15;++i)
	{
		cardno[1][i]=iniCardno[i];
		cardno[2][i]=iniCardno[i];
	}
	if (level[1]==13) cardno[1][1]=13;
	else
	for (int j=3;j<=level[1];++j)
	{
		swap(cardno[1][j],cardno[1][j-1]);
	}
	if (level[2]==13) cardno[2][1]=13;
	else
	for (int j=3;j<=level[2];++j)
	{
		swap(cardno[2][j],cardno[2][j-1]);
	}
}
void randomcard() //随机发牌 
{
	int sep,num;//花色和数字，花色五种对应四种基本花色和鬼，鬼数字为1或2 
	int yes[200]={0};//未发卡牌 
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
		sort(card[i]+1,card[i]+28,cmp);//卡牌排序 
	}
}
bool comp(Card a[],int alen,int type)
{
	if (type!=record.type)//牌型不同时只有炸弹和同花需要比较，较小牌型直接炸 
	{
		if (record.type<type) return 1;
		if (record.tot<=5) return 1;
		else return 0;
	}
	else 
	{
		if (type==9) 
		{
			if (alen>record.tot) return 1;
			else if (alen<record.tot) return 0;
			else if (alen==record.tot)
			{
				if (a[alen].num>record.seq[record.tot].num) return 1;
				else return 0;
			}
		}
		else 
		{
			if (a[alen].num>record.seq[record.tot].num) return 1;
			else return 0;
		}
	}
}
bool duizi(Card a[],int tot)//判断对子，若有逢人配则修改 
{
	int i=1;
	int team=player>2?player-2:player;
	if (a[1].num==a[2].num) return true;//如果两个数值相等则是 
	while(i<tot && a[i].num==level[team] && a[i].color==1) ++i;//不相等判断逢人配 
	if (i==1) 
	{
		a[1].num=a[2].num;
		a[1].cardno=cardno[team][a[1].num];//逢人配与另一张牌数值相同8 
		return 1;
	}
	else return 0;
}
bool pd(Card c[],int tot) //判断牌型1:单牌2:对子3:三顺4:三带二5:钢板6:连对 
						  //7:顺子8:同花顺9:炸
{
	sort(c+1,c+1+tot,cmp);
	/*if (tot<=1) return tot;
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
	return -1;*/
	return 1;
}
bool isRoundEnd()//判断回合结束，双下时按玩家序号大小确定名次 
{
	if (players==1) 
	{
		for (int i=1;i<=4;++i) if (remain[i]) playerrank[4]=i;
		return 1;
	}
	else if(players==2)
	{
		if (remain[1]==0&&remain[3]==0)
		{
			playerrank[3]=2;
			playerrank[4]=4;
			return 1;
		}
		if (remain[2]==0&&remain[4]==0)
		{
			playerrank[3]=1;
			playerrank[4]=3;
			return 1;
		}
	}
	return 0;
}

void roundend()//回合结束加等级及A打三次不过回退功能 
{
	int winner=playerrank[1];
	player=winner;
	if (playerrank[3]==1&&playerrank[4]==3) 
	{
		if (level[2]>=13)
		{
			printf("本局结束！赢家为玩家2和玩家4！");
			Sleep(5000);
			exit(0);
		}
		level[2]+=3;
		gong=1;
	}
	if (playerrank[3]==2&&playerrank[4]==4) 
	{
		if (level[1]>=13)
		{
			printf("本局结束！赢家为玩家1和玩家3！");
			Sleep(5000);
			exit(0);
		}
		level[1]+=3;
		gong=2;
	}
	if ((playerrank[1]==1||playerrank[1]==3)&&(playerrank[2]==2||playerrank[2]==4)&&(playerrank[3]==1||playerrank[3]==3)&&(playerrank[4]==2||playerrank[4]==4)) 
	{
		level[1]+=2;
		gong=3;
	}
	if ((playerrank[1]==2||playerrank[1]==4)&&(playerrank[2]==1||playerrank[2]==3)&&(playerrank[3]==2||playerrank[3]==4)&&(playerrank[4]==1||playerrank[4]==3)) 
	{
		level[2]+=2;
		gong=3;
	}
	if ((playerrank[1]==1||playerrank[1]==3)&&(playerrank[2]==2||playerrank[2]==4)&&(playerrank[3]==2||playerrank[3]==4)&&(playerrank[4]==1||playerrank[4]==3)) level[1]+=1;
	if ((playerrank[1]==2||playerrank[1]==4)&&(playerrank[2]==1||playerrank[2]==3)&&(playerrank[3]==1||playerrank[3]==3)&&(playerrank[4]==2||playerrank[4]==4)) level[2]+=1;
	printf("本局结束，头家为%d，末流为%d\n",playerrank[1],playerrank[4]);
	if (level[1]>=13)
	{
		level[1]=13;
		++backtotwo[1];
		if (backtotwo[1]>3) 
		{
			backtotwo[1]=0;
			level[1]=2;
			printf("玩家1玩家3打三次A不过回退至2\n");
		}
	}
	if (level[2]>=13)
	{
		level[2]=13;
		++backtotwo[2];
		if (backtotwo[2]>3) 
		{
			backtotwo[2]=0;
			level[2]=2;
			printf("玩家2玩家4打三次A不过回退至2\n");
		}
	}
	Sleep(3000);
}

void give(int player1,int player2)//锟斤拷锟狡伙拷锟斤拷 
{
	int number1,number2;
	print(player1,card[player1],27);
	printf("玩家%d输入进贡卡牌编号，不得大于10且不得选择主牌红桃\n",player1);
	scanf("%d",&number1);
	while(card[player1][number1].num<10||(card[player1][number1].color==1 && card[player1][number1].cardno==13)){
		printf("不得大于10且不得选择主牌红桃！\n");
		scanf("%d",&number1);
	}
	print(player2,card[player2],27);
	printf("玩家%d输入返还卡牌编号，不得大于10\n",player2);
	scanf("%d",&number2);
	while(card[player2][number2].num<10){ 
		printf("不得大于10！\n");
		scanf("%d",&number2);
	}
	swap(card[player1][number1],card[player2][number2]);
	sort(card[player1]+1,card[player1]+28,cmp);
	sort(card[player2]+1,card[player2]+28,cmp);
	system("cls");
}

void jingong()
{
	if (gong==1) 
	{
		printf("玩家1玩家3需要进贡\n");
		bool little=0,big=0;
		print(1,card[1],27);
		print(3,card[3],27);
		for (int j=1;j<=4;++j) 
		{
			if (card[1][j].cardno==15 || card[3][j].cardno==15) ++big;
		}
		if (big==2) 
		{
			int confirm;
			printf("队伍有两张大王，是否抗贡？是1，否0\n");
			scanf("%d",&confirm);
			if (confirm==1)
			{
				printf("抗贡成功!\n");
				Sleep(1500);
				system("cls");
				gong=0;
				return;
			}
		}
		system("cls");
		give(1,playerrank[1]);
		give(3,playerrank[2]);
		player=1;
		return;
	}
	if (gong==2)
	{
		printf("玩家2玩家4需要进贡\n");
		bool little=0,big=0;
		print(2,card[2],27);
		print(4,card[4],27);
		for (int j=1;j<=4;++j) 
		{
			if (card[2][j].cardno==15 || card[4][j].cardno==15) ++big;
		}
		if (big==2) 
		{
			int confirm;
			printf("队伍有两张大王，是否抗贡？是1，否0\n");
			scanf("%d",confirm);
			if (confirm==1)
			{
				printf("抗贡成功!\n");
				Sleep(1500);
				system("cls");
				gong=0;
				return;
			}
		}
		give(2,playerrank[1]);
		give(4,playerrank[2]);
		player=2;
		return;
	}
	if (gong==3)
	{
		printf("玩家%d需要进贡\n",playerrank[4]);
		bool little=0,big=0;
		print(playerrank[4],card[playerrank[4]],27);
		for (int j=1;j<=4;++j) 
		{
			if (card[playerrank[4]][j].cardno==15) ++big;
		}
		if (big==2) 
		{
			int confirm;
			printf("有两张大王，是否抗贡？是1，否0\n");
			scanf("%d",&confirm);
			if (confirm==1)
			{
				printf("抗贡成功!\n");
				Sleep(1500);
				system("cls");
				gong=0;
				return;
			}
		}
		give(playerrank[4],playerrank[1]);
		player=playerrank[4];
		return;
	}
}

int main(){
	srand((unsigned)time(NULL));//初始化随机种子 
	int tot,serialnum[28],round=0,turn=0; 
	int flag;//牌型
	bool roundstart=1;//一局开始 
	int jiefeng=0;//接风计数 
	int jiefengplayer=0;//接风玩家 
	while (1)
	{
		tot=0;
		//system("cls");
		if (roundstart) //一锟街匡拷始锟斤拷始锟斤拷 
		{
			++round;
			setCardno();
			randomcard();//锟斤拷锟斤拷
			if (gong) jingong();//锟斤拷锟斤拷 
			memset(playerrank,0,sizeof(playerrank));
			for (int i=1;i<=4;++i) remain[i]=27;
			roundstart=0;
			players=4;
			turn=0;
			printf("第%d局开始！玩家1玩家3主牌为%d，玩家2玩家4主牌为%d\n",round,level[1],level[2]);
			Sleep(2000);
			//system("cls");
		}
		
		if (remain[player]==0) 
		{
			player++;
			if (player>4) player-=4;
			continue;
		}
		
		if (turn++) {
			printf("上一次出牌：\n");
			print(0,record.seq,record.tot);
		}
		
		print(player,card[player],27);
		printf("输入出牌序号，用空格隔开，0结尾，不出牌输入0:\n");
		
		while (scanf("%d",&serialnum[++tot])) if (serialnum[tot]==0) break;
		--tot;
		for (int i=1;i<=tot;++i)
			nowCardSeq[i]=card[player][serialnum[i]];
		flag=pd(nowCardSeq,tot);
		
		/*while (flag==-1 || (flag<8 && flag!=record.type && record.type!=0) 
			|| (flag>=8 || flag==record.type) && !comp(nowCardSeq,tot,flag))
		//牌型不合法活比上一次牌小 
		{
			tot=0;
			printf("出牌不合法，请重新输入：\n");
			while (scanf("%d",&serialnum[++tot]))if (serialnum[tot]!=0) break;
			--tot;
			for (int i=1;i<=tot;++i)
				nowCardSeq[i]=card[player][nowCardId[serialnum[i]]];
			flag=pd(nowCardSeq,tot);
		}*/
		remain[player]-=tot;//减手牌数 
		if (flag==0 && jiefeng) ++jiefeng;
		else jiefeng=0;
		if (remain[player]==0) //手牌出完 
		{
			if (players==4) 
			{
				jiefeng=1;//接风计数 
				jiefengplayer=player+2;
				if (jiefengplayer>4) jiefengplayer-=4;
			}
			--players;//剩余玩家-1
			playerrank[4-players]=player;
			if (isRoundEnd()) 
			{
				roundend();
				roundstart=1;
			}
		}
		for (int i=1;i<=tot;++i)
		{
			record.seq[i]=nowCardSeq[i];
		}
		record.tot=tot;
		record.type=flag;//记录这一次出牌 
		for (int i=1;i<=tot;++i) 
			card[player][nowCardId[serialnum[i]]].color=0;//标记出过的牌 
		if (jiefeng==players)//其他玩家放弃出牌 
		{
			player=jiefengplayer;
			jiefeng=0;
		}else
		{
			++player;//下一个玩家 
			if (player>4) player-=4;
		}
	}
	return 0;
}
