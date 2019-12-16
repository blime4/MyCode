#include<stdio.h>
#include<math.h>
void main()	
{
	/*G：生成矩阵  H：监督矩阵  HT：监督矩阵对应的转置矩阵*/
	/*M：输入信息序列  C：编码输出序列  Input：输入接收码序列  B：译码输出序列  S：伴随式*/
	int Q,N;/*定义开始*/
	int i,j,s,r,k,t,p,u,m;
    int G[4][7]={{1,0,0,0,1,1,1},{0,1,0,0,1,1,0},{0,0,1,0,1,0,1},{0,0,0,1,0,1,1}};
	int IR[3][3]={{1,0,0,},{0,1,0},{0,0,1}};
	int H[3][7], C[10][7],M[10][4],B[20][7],Input[100],HT[7][3],P[10],S[100][3];/*定义结束*/
	printf("\n您好！欢迎使用线性分组码编译器！\n");
	printf("\n\n本编译器针对（7，4）码，所采用的生成矩阵G=\n");
	for(i=0;i<4;i++)                                    //生成矩阵的建立          
	{
		for(j=0;j<7;j++)
			printf(" %d",G[i][j]);
		printf("\n");
	}
	printf("编译码过程都是针对二进制码组，除了系统要求选择功能，其他情况下禁止输入除0，1以外的数。请在使用的过程中严格按照编译器要求的格式输入数据。\n\n");
	printf("现在请输入您所选择的编译器所对应的序号,按回车键继续:\n");
	printf("\n1.编码器  2.译码器  3.退出\n");
	printf("\n我选择：");
	scanf("%d",&Q);
	if(Q==0)
		Q+=4;
	while(Q)
	{
	if(Q==1||Q==2||Q==3)break;     //判 断输入是否有误
	else
	{
		printf("对不起，您输入有误，请重新输入");
		scanf("%d",&Q);
	}
	}
	while(Q==1||Q==2||Q==3)
		{
			if(Q==1)/*编码程序*/
				{printf("\n请输入您需要编码的信息组数");
				scanf("%d",&N);
				printf("\n\n请输入您需要编码的%d组四位二进制信息组,码组间用空格分开，按回车键确认。\n",N);/*输入信息码*/
				printf("\n信息组m=");
				for(i=0;i<N;i++)
				scanf("%1d%1d%1d%1d",&M[i][3],&M[i][2],&M[i][1],&M[i][0]);
/*求监督码*/
				for(i=0;i<N;i++)
				{
				C[i][2]=M[i][3]^M[i][2]^M[i][1];    //a2=a6^a5^a4
				C[i][1]=M[i][3]^M[i][2]^M[i][0];    //a1=a6^a5^a3
				C[i][0]=M[i][3]^M[i][1]^M[i][0];    //a0=a6^a4^a3
				}
				for(j=0;j<N;j++)
				for (i=6;i>2;i--)/*输出编码结果*/
				C[j][i]=M[j][i-3];
				printf("\n您所输入的信息组编码结果c=");
				for(j=0;j<N;j++)
				{for(i=6;i>=0;i--)
					printf("%d",C[j][i]);  //输出编码结果
					printf("\n");          //换行  
				}
				printf("\n\n");
				printf("\n接下来您想：\n\n");/*选择功能*/
				printf("1.用编码器 2.用译码器 3.退出\n\n");
				printf("我想：");
				scanf("%d",&Q);
			}
			else if(Q==2)/*译码程序*/
			{
				for(i=0;i<3;i++)/*求监督矩阵*/
				{
					for(j=0;j<4;j++)
						H[i][j]=G[j][i+4];   
					for(j=4;j<7;j++)
						H[i][j]=IR[i][j-4];  //单位矩阵
				}
				printf("\n监督矩阵H=\n");/*输出监督矩阵*/
				for(i=0;i<3;i++)
				{
					for(j=0;j<7;j++)
					printf(" %d",H[i][j]);
					printf("\n");
				}
				t=1;
				while(t!=2)/*输入接收码组*/
				{
					p=1;
					printf("\n请输入总位数为7的倍数的接收码组,每位用空格隔开，每组位数为7的倍数,以十进制2作为结束标志!按回车键确认\n");
					while(p)
					{
						for(i=0;;i++)
						{
							scanf("%d",&Input[i]);
							if(Input[i]==2)break;   
						}
						k=i%7;      //判断是否为7的倍数
						if(k==0){p=0;t=2;}
						else
						{
							p=1;
							k=-k+7;    //计算丢失了几位
							printf("您接收到的码组丢失了%d位,系统不能判断丢失位的具体位置，请重新输入\n",k);
						}
					}
				}
				u=i/7; //接收到的码组分成u组
				i=0;
				for(r=0;r<u;r++)
				{	for(j=6;j>=0;j--,i++)
						B[r][j]=Input[i];     
				}
				printf("\n将接收码组每七位分为一个码组，如下：\n");
			    	for(i=0;i<u;i++)
					{
						for(j=0;j<7;j++)
							printf(" %1d",B[i][6-j]);    //显示分好的码组
						printf("\n");
					}
				for(i=0;i<3;i++)/*求监督矩阵H的转置矩阵*/
					for(j=0;j<7;j++)
						HT[j][i]=H[i][j];
					for(i=0;i<u;i++)              //计算伴随式
					{
						for(m=0;m<3;m++)
						{
							for(j=0;j<7;j++)
							{
								s+=(B[i][6-j]*HT[j][m]); 
							}
							if (s%2==1)s=1;
							else 
								s=0;
							S[i][2-m]=s;
							s=0;
						}
					}
					printf("\n\n伴随式S=\n");/*输出伴随式*/
				for(j=0;j<u;j++)
				{for(i=2;i>=0;i--)
					printf(" %1d",S[j][i]);
				printf("\n");}
				printf("\n");
				for(i=0;i<u;i++)
				{
				P[i]=4*S[i][2]+2*S[i][1]+S[i][0]+1;
				switch(P[i])/*根据伴随式判断接收码，并译码*/
				{
				case 1:
					{
						printf("\n\n您所接收的第%d个码组正确，它是：",++i);
						i--;
						for(j=6;j>=0;j--)
							printf("%1d",B[i][j]);
						printf("请您再次确认！");
							printf("译出的信息序列为：");
						    for(j=6;j>2;j--)
							printf("%d",B[i][j]);break;
					}
				case 2:
					{
						B[i][0]=1^B[i][0];
						printf("\n\n您接收的第%d个码组有错误，正确的码组应为：",++i);
						i--;
						for(j=6;j>=0;j--)
							printf("%1d",B[i][j]);
						printf("译出的信息序列为：");
						for(j=6;j>2;j--)
							printf("%d",B[i][j]);break;
					}
				case 3:
					{
						B[i][1]=1^B[i][1];
					printf("\n\n您接收的第%d个码组有错误，正确的码组应为：",++i);
						i--;
						for(j=6;j>=0;j--)
							printf("%1d",B[i][j]);
							printf("译出的信息序列为：");
						for(j=6;j>2;j--)
							printf("%d",B[i][j]);break;
					}
				case 4:
					{
						B[i][3]=1^B[i][3];
					printf("\n\n您接收的第%d个码组有错误，正确的码组应为：",++i);
						i--;
						for(j=6;j>=0;j--)
							printf("%1d",B[i][j]);
							printf("译出的信息序列为：");
						for(j=6;j>2;j--)
							printf("%d",B[i][j]);break;
					}
				case 5:
					{
						B[i][2]=1^B[i][2];
					printf("\n\n您接收的第%d个码组有错误，正确的码组应为：",++i);
						i--;
						for(j=6;j>=0;j--)
							printf("%1d",B[i][j]);
							printf("译出的信息序列为：");
						    for(j=6;j>2;j--)
							printf("%d",B[i][j]);break;
					}
				case 6:
					{
						B[i][4]=1^B[i][4];
					printf("\n\n您接收的第%d个码组有错误，正确的码组应为：",++i);
						i--;
						for(j=6;j>=0;j--)
						printf("%1d",B[i][j]);
						printf("译出的信息序列为：");
						for(j=6;j>2;j--)
						printf("%d",B[i][j]);break;
					}
				case 7:
					{
						B[i][5]=1^B[i][5];
					printf("\n\n您接收的第%d个码组有错误，正确的码组应为：",++i);
						i--;
						for(j=6;j>=0;j--)
						printf("%1d",B[i][j]);
						printf("译出的信息序列为：");
						for(j=6;j>2;j--)
						printf("%d",B[i][j]);break;
					}
				case 8:
					{
						B[i][6]=1^B[i][6];
					printf("\n\n您接收的第%d个码组有错误，正确的码组应为：",++i);
						i--;
						for(j=6;j>=0;j--)
						printf("%1d",B[i][j]);
						printf("译出的信息序列为：");
						for(j=6;j>2;j--)
						printf("%d",B[i][j]);break;
					}
				}
				}
				printf("\n\n总的译码结果为：");
				for(i=0;i<u;i++)
					for(j=6;j>2;j--)
					printf("%1d",B[i][j]);
				printf("\n\n接下来您想：\n\n");/*继续选择功能*/
				printf("1.用编码器 2.用译码器 3.退出\n\n");
				printf("我想：");
				scanf("%d",&Q);
				if(Q==0)
					Q=Q+4;
				while(Q)
				{
					if(Q==1||Q==2||Q==3)break;
					else
					{
						printf("对不起，您输入有误，请重新输入");
						scanf("%d",&Q);
					}
				}
			}
			else if(Q==3)/*退出程序*/
			{
				printf("\n谢谢您的使用，欢迎再次使用！\n");	Q=0;
			}
		}
}
