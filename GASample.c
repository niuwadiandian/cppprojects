// GASample.c

#include "stdafx.h"
#include "math.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- ����
#define  MAX_GEN 500    // 最大迭代代数
#define  POP_SIZE 10    // 种群大小
float fPC = 0.6;        // 交叉率
float fPM = 0.02;       // 变异率
int t = 0;              // 当前迭代代数

float xU[2] = {5.0, 5.0};   // 变量x1,x2上界
float xL[2] = {-5.0, -5.0}; // 变量x1,x2下界

float fPop[2][3*POP_SIZE];  // 种群大小，数组的数组，预留空间，用于保存交叉、变异的子代
float fEval[3*POP_SIZE];    // 适值函数，和染色体对应

int iChildNum = 0;               // 交叉、变异产生的子代个数
float fResults[MAX_GEN+1];       // 保存每一代的最好值
float x[2][MAX_GEN+1];         //  保存每一代的最好解
char mk[2][POP_SIZE];       // 染色体交叉变异标志，仅仅为了显示

// ---- 函数
float objFunc(float x1, float x2)   // 目标函数，用函数的形式表示
{
    return -20 * exp(-0.2 * sqrt(0.5 * (pow(x1, 2) + pow(x2, 2))))-exp(0.5 * (cos(2 * 3.1415926 * x1) + cos(2 * 3.1415926 * x1))) + 20 + 2.71828;
}

float random(float a1, float a2)    //  产生 a1 到 a2 之间的随机数，经常用到
{
    return  a1 + (a2 - a1) * rand()/RAND_MAX;
}

void initPop()           // 种群初始化，在变量上下限之间随机产生
{
    for (int i = 0; i < POP_SIZE; i++)
    {
        fPop[0][i] = random(xL[0], xU[0]);
        fPop[1][i] = random(xL[1], xU[1]);
    }
}

void evaluat(int aType)  // 评价，计算适值。aType = 0-初始种群，1-子代
{
    float C = 15.0;
    for (int i = 0 + aType * POP_SIZE; i < POP_SIZE + aType * iChildNum; i++)
    {
        fEval[i] = C - objFunc(fPop[0][i], fPop[1][i]);     // 目标函数到适值的映射
    }
}

void crossover()        // 交叉操作，算术交叉
{
    int iCross[POP_SIZE];       // 用于记录哪些父代被选作交叉

    for (int j = 0, i = 0; i < POP_SIZE; i++)
    {
        iCross[i] = -1;         // 数组初始化为 -1，便于判断
        mk[0][i] = '-';
        if (random(0, 1) < fPC) //  满足交叉条件
        {
            iCross[j] = i;      // 记录染色体编号
            j++;
            mk[0][i] = '*';     // 记录哪个染色体用于交叉，仅为了显示
        }
    }
    
    for (int i = 0; i < POP_SIZE && (iCross[i] != -1) && (iCross[i + 1] != -1); i = i + 2)     // 有两个染色体满足条件
    {
        fPop[0][POP_SIZE + iChildNum] = 0.7 * fPop[0][iCross[i]] + 0.3 *  fPop[0][iCross[i + 1]];
        fPop[1][POP_SIZE + iChildNum] = 0.7 * fPop[1][iCross[i]] + 0.3 *  fPop[1][iCross[i + 1]];
        iChildNum ++;
        
        fPop[0][POP_SIZE + iChildNum] = 0.7 * fPop[0][iCross[i + 1]] + 0.3 *  fPop[0][iCross[i]];
        fPop[1][POP_SIZE + iChildNum] = 0.7 * fPop[1][iCross[i + 1]] + 0.3 *  fPop[1][iCross[i]];
        iChildNum ++;
    }
}

void mutation()     // 变异操作，均匀变异
{
    for (int i = 0; i < POP_SIZE; i++)
    {
        mk[1][i] = '-';
        int iFlag = 0;          // 染色体是否变异的标志
        for (int j = 0; j < 2; j++)
        {
            if (random(0, 1) < fPM)     // 满足变异条件
            {
                 iFlag++;
                 if (iFlag == 1)        // 染色体中第一个基因发生变异时，复制染色体
                 {
                    fPop[0][POP_SIZE + iChildNum] = fPop[0][i];
                    fPop[1][POP_SIZE + iChildNum] = fPop[1][i];
                 }

				 if (random(0, 1)<=0.5) 
				 {
					fPop[j][POP_SIZE + iChildNum] = random(fPop[j][POP_SIZE + iChildNum], xU[j])  / (t + 1);     // t+1 避免除0
					//fPop[j][POP_SIZE + iChildNum] = random(fPop[j][POP_SIZE + iChildNum], xU[j]);
				 } else{
					fPop[j][POP_SIZE + iChildNum] = random(xL[j], fPop[j][POP_SIZE + iChildNum])  / (t + 1);     // t+1 避免除0
					//fPop[j][POP_SIZE + iChildNum] = random(xL[j], fPop[j][POP_SIZE + iChildNum]);
				 }
                 // 随着迭代代数的增加、变异幅值减小，是否除以t， 对收敛性影响很大
				 
                 mk[1][i] = '*';        // 染色体变异标志，仅用于显示ʾ
            }
        }
        if (iFlag > 0)         // 一个染色体有基因发生变异的话，下一代的个数+1
        {
            iChildNum++;
        }
    }
}

void select()       // 选择操作，最好种群选择法。
{
    // 对父代+子代的染色体进行排序, 排序后，前POP_SIZE个染色体，即为要选择的染色体。
    int iFlag = POP_SIZE + iChildNum;       // 冒泡排序
	while (iFlag > 0)
	{
		int k = iFlag;
		iFlag = 0;
		for (int j = 0; j < k; j++)
		{
			if (fEval[j] < fEval[j + 1])	// 不满足顺序
			{
				float eval = fEval[j + 1];
                float x1 = fPop[0][j + 1];
                float x2 = fPop[1][j + 1];

				fEval[j + 1] = fEval[j];
                fPop[0][j +1] = fPop[0][j];
                fPop[1][j +1] = fPop[1][j];

				fEval[j] = eval;
                fPop[0][j] = x1;
                fPop[1][j] = x2;

				iFlag = j;		// 最后一次交换的位置
			}
		}
	}

    // 保存最好解，第一个就是。便于打印输出看趋势。
    fResults[t] = fEval[0];
    x[0][t] = fPop[0][0];
    x[1][t] = fPop[1][0];

    // 随机打乱排序顺序。增加染色体交叉的随机性，没有也可以。
    for (int i = 0; i < POP_SIZE / 2; i++)
    {
        int j = (int)(random(0, POP_SIZE - 1) + 0.5);
        int k = (int)(random(0, POP_SIZE - 1) + 0.5);
        if (j != k)
        {
            float eval = fEval[j];
            float x1 = fPop[0][j];
            float x2 = fPop[1][j];

			fEval[j] = fEval[k];
            fPop[0][j] = fPop[0][k];
            fPop[1][j] = fPop[1][k];

			fEval[k] = eval;
            fPop[0][k] = x1;
            fPop[1][k] = x2;
        }
    }
}


void dspPop()            // 显示种群信息
{
    if (t > 5) return;     // 仅显示前5代。

    printf("\n第 %i 代，父代", t);
    printf("\n  No [ x1       x2    ]   eval    交叉  变异");  // 打印输出每次迭代的最好解
    for (int i = 0; i < POP_SIZE; i++)
        printf("\n%4i [%+7.4f  %+7.4f]  %7.4f   %c     %c", i, fPop[0][i], fPop[1][i], fEval[i], mk[0][i], mk[1][i]);

    printf("\n第 %i 代，子代", t);
    for (int i = POP_SIZE; i < POP_SIZE + iChildNum; i++)
        printf("\n%4i [%+7.4f  %+7.4f]  %7.4f", i, fPop[0][i], fPop[1][i], fEval[i]);

    printf("\n press any key to continue");
    char c = getch();
}
// --- 主函数
int _tmain(int argc, _TCHAR* argv[])
{
    srand((unsigned)time(NULL));
    // 在调用rand()函数产生随机数前，必须先利用srand()设好随机数种子。
    // 若不设随机数种子，rand()每次执行时产生的随机数都是相同的。

    initPop();              // 种群初始化
    evaluat(0);             // 计算初始种群适值
    while (t <= MAX_GEN)
    {
        iChildNum = 0;      // 交叉变异前、子代数清零
        crossover();
		mutation();
		evaluat(1);         // 计算交叉、变异产生的子代的适值
        dspPop();           // 显示种群,便于查看交叉、变异的结果。
        select();
        t++;
    }

    printf("\n   t [ x1       x2    ]   eval");  // 打印输出每次迭代的最好解
    for (int i = 0; i <= MAX_GEN; i = i + 10)
        printf("\n%4i [%+7.4f  %+7.4f]  %7.4f", i, x[0][i], x[1][i], fResults[i]);
    printf("\n x1 = %2.4f,   x2 = %2.4f,     ObjFunc = %2.4f \n", x[0][MAX_GEN-1], x[1][MAX_GEN-1], objFunc(x[0][MAX_GEN-1], x[1][MAX_GEN-1]));
    printf("\n press any key to continue");
    char c = getch();
	return 0;
}