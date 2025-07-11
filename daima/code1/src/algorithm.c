/*
 * algorithm.c
 *
 *  Created on: Mar 16, 2025
 *      Author: Administrator
 */


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "algorithm.h"
#include "agi.h"
#include "link.h"

typedef struct {
    int row, col;
    u8 *pData;
    u8 k;
} Pair;

typedef struct {
    Pair rc;
    int iterationTimes;
} AnsStru;

//第2个参数是观众指定的牌，在魔术师不断收牌重排的过程中位置会不断变化，最后稳定下来
void rcAdd(Pair *pStart, Pair *pSim, int c) {
    int lastRow;

    //第一次增量是start+row/c+(1')-row = Δ
    //第二次增量是start+(row+Δ)/c+(1'')-(start+row/c+(1'))

    /*
     * 三点保证：
     * 1.start+(row+Δ)/c+(1)存在上限
     * 2.row在迭代过程中是单调递增的
     * 3.一旦Δ=0，此后迭代中row都不会改变
     */

    //当取最后一列时，start的行最大取r*(c-1)/c，此时列为r*(c-1)%c
    //start+(row+Δ)/c<=(r*(c-1)+r)/c=r,只要证明<=取到=r时，(1)只能取0，就完成了上限的证明
    //从操作上知道无论怎么迭代都是row+Δ<r，但是操作到形式的转换没想明白
    //一开始选定牌所在的row<r,重排时前面最多放(c-1)*r+row<c*r
    //所以这张牌所在行<c*r/c = r,应该这样证明

    lastRow = pSim->row;//记下上一次pSim的row
    //start <= (c-1*r)/c
    //这次row = start + 上次row/c = (start*c+row)/c < (c-1*r)/c + r/c = r
    //注意到lastRow是上次pSim->row，初始<r，上一次小于r，更新后<r，那就一直<r,不可能取到等号
    pSim->row = pStart->row+lastRow/c;//每数c个相当于把这张牌往下移动一行
    pSim->col = pStart->col+lastRow%c;//每数c个相当于这张牌的位置不变，看还多出来几个
    if (pSim->col>=c) {
        pSim->col %= c;
        pSim->row += 1;//这里还要+1，这里加的是lastRow取整后剩下的，看剩下的是不是能填充满这张牌所在行的右边空位
    }

}

// 计算第p列起始位置
void pthStart(Pair *pStart,long p, long r, long c) {
    //如果p=2，也就是做为第3列被收起了，前面收了2列,假设是7行3列，那么前面收了14个数字
    //重排后，收到的那一列的起始位置位于第14号位置（从0开始数起）
    //即第14/3=4行，第14%3=2列
    pStart->row = (r * p) / c;
    pStart->col = (r * p) % c;
    pStart->k = p;//这个k现在没用到吧？
}

// 计算距离中心点位置的最小距离
long calDist(Pair rc, long r, long c) {
    long mr = r / 2, mc = c / 2;
    long minr = labs(rc.row - mr);
    long minc = labs(rc.col - mc);
    //偶数时中间有2个点，还要计算另一个点的距离，取最小的
    if (r % 2 == 0 && labs(rc.row - (mr - 1)) < minr)
        minr = labs(rc.row - (mr - 1));
    if (c % 2 == 0 && labs(rc.col - (mc - 1)) < minc)
        minc = labs(rc.col - (mc - 1));
    return minr + minc;
}

void Cardiology1(int r, int c)
{
    AnsStru* stablePos;
    Pair aEle[2];
    Pair start = {0, 0};
    int j,i;
    int iterationTime = 0;
    Pair aPre[2];
   // u8 aBuf[21];

    //为什么程序崩溃，加个link.h头文件就好了？
    stablePos = (AnsStru*)RawMalloc(sizeof(AnsStru) * c);



    for(j=0;j<c;j++)
    {
        iterationTime = 0;

        //当c=1时，此时j只能取0，只有一列，重排不变，start必然是0，0
        //start指的是这张牌所在列的第一张牌的位置，这张牌前面收了j列张牌（每列有r张）
        pthStart(&start,j, r, c);

        //为什么要选择开头和结尾这两个数字模拟，原题似乎要求把这一列中的所有数字都模拟一遍
        //只用一个数字模拟行不行
        //总共有0~r*c张牌可以模拟，每张牌初始位置都满足row<r
        aEle[0].row = 0;
        aEle[0].col = 0;
        aEle[1].row = r-1;
        aEle[1].col = c-1;

      //  log_a("restart:%d %d",start.row,start.col);

        while (1) {
            aPre[0] = aEle[0];
            aPre[1] = aEle[1];

            //j指的是第p列被收走，每次while循环都是前面收走了p列按行重排
            //所以第p列的第一张牌，即start的位置是不变的，被收走这张牌在这一列中属于第几行
            //决定了重排时相对start的偏移
            rcAdd(&start, &aEle[0], c);
            rcAdd(&start, &aEle[1], c);

            if (aPre[0].row == aEle[0].row && aPre[0].col == aEle[0].col &&
                aPre[1].row == aEle[1].row && aPre[1].col == aEle[1].col)
            {
                //6 2不是在中央啊
             //   log_a("");//在6 2结束循环？
                break;//这个循环一定会结束吗？
            }
            //最大迭代次数为什么只需加个endst判断就可以了，而不用把这列的数字都模拟一遍
            iterationTime++;
        }
        if (aEle[0].row == aEle[1].row && aEle[0].col == aEle[1].col) {
            //记录first最后稳定的坐标，感觉是对于不同的j，first不一定收敛到中央
            //出题人是想让你找出收敛到中央的那个j
            //看错了，他这个判断是first和endst收敛到同一个坐标
            stablePos[j].rc = aEle[0];
          //  log_a("j %d end same %d %d",j,aEle[0].row,aEle[0].col);
        } else {
            stablePos[j].rc.row = -1;
            stablePos[j].rc.col = -1;
            log_a("j %d not same %d %d %d %d",j,
                    aEle[0].row,aEle[0].col,aEle[1].row,aEle[1].col);
        }
        stablePos[j].iterationTimes = iterationTime;
    }

    int ans = -1;
    long minDist = LONG_MAX;

    for (i=0;i<c;i++) {
        Pair pi = stablePos[i].rc;
        if (pi.row != -1 && pi.col != -1) {
            long dist = calDist(pi, r, c);
            if(dist == minDist && i < ans){
                assert(0);//这个条件不知道是什么意思，应该也不会进的吧
            }
            if (dist < minDist || (dist == minDist && i < ans)) {
                minDist = dist;
                ans = i;
            }
        }
    }

    if (ans != -1) {
        log_a("%d %d %d %d",
            ans + 1,
            stablePos[ans].rc.row + 1,
            stablePos[ans].rc.col + 1,
            stablePos[ans].iterationTimes);
    } else {
        log_a("No stable position found.");//c=1的时候会进这里
    }

    RawFree(stablePos);
}



#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

int Cardiology2(int R, int C) {
        // ret = {距离, p, i, j, 迭代次数s}
        int ret[5] = {100000, 0, 0, 0, 0};

        for (int64_t p = 0; p < C; p++) {
            int64_t i = -1, j = -1, s1 = -1, s2 = 0;
            int64_t x = 0, y = 0;

            // 第一次迭代，从(0,0)开始
            do {
                j = x;
                i = y;
                x = (y + p * R) % C;
                y = (y + p * R) / C;
                s1++;
            } while (x != j || y != i);

            if ((i > 0 && j == 0) || (i < R - 1 && j == C - 1))
                continue;

            x = C - 1;
            y = R - 1;
            s2 = 0;

            // 第二次迭代，从(R-1,C-1)开始
            while (x != j || y != i) {
                x = (y + p * R) % C;
                y = (y + p * R) / C;
                s2++;
            }

            int64_t d = MIN(llabs((C - 1) / 2 - j), llabs(C / 2 - j)) +
                        MIN(llabs((R - 1) / 2 - i), llabs(R / 2 - i));

            int64_t cur[5] = {d, p + 1, i + 1, j + 1, MAX(s1, s2)};

            // 比较cur和ret，cur<ret则更新ret
            int is_smaller = 0;
            for (int idx = 0; idx < 5; idx++) {
                if (cur[idx] < ret[idx]) {
                    is_smaller = 1;
                    break;
                } else if (cur[idx] > ret[idx]) {
                    is_smaller = 0;
                    break;
                }
            }
            if (is_smaller)
                for (int idx = 0; idx < 5; idx++)
                    ret[idx] = cur[idx];
        }
        log_a("%d %d %d %d",ret[1], ret[2], ret[3], ret[4]);

    return 0;
}
