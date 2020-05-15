#include <stdio.h>

extern struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };
extern void creatertpkt(struct rtpkt * initrtpkt, int srcid, int destid, int mincosts[]);   
extern void tolayer2(struct rtpkt packet);
extern int TRACE;
extern int YES;
extern int NO;

int connectcosts3[4] = {7, 999, 2, 0};
int minicosts3[4] = {7, 999, 2, 0};

struct distance_table 
{
  int costs[4][4];
} dt3;

/* students to write the following two routines, and maybe some others */

void rtinit3() 
{
  // 初始化节点3中的距离表
  // 节点3的向量表中[i,j]是节点3通过节点j连接到节点i所需的成本
  int i, j;
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      dt3.costs[i][j] = 999;  // 首先默认全部初始化为999
  dt3.costs[0][0] = connectcosts3[0];  dt3.costs[0][3] = connectcosts3[0];
  dt3.costs[1][1] = connectcosts3[1];  dt3.costs[1][3] = connectcosts3[1];
  dt3.costs[2][2] = connectcosts3[2];  dt3.costs[2][3] = connectcosts3[2];
  dt3.costs[3][3] = 0;
  // 向其他结点发送自己的最小代价信息
  struct rtpkt* update_ptr = (struct rtpkt*)malloc(1*sizeof(struct rtpkt));
  creatertpkt(update_ptr, 3, 0, minicosts3);
  tolayer2(*update_ptr);
  creatertpkt(update_ptr, 3, 2, minicosts3);
  tolayer2(*update_ptr);
  free(update_ptr);

  printf("......init node3......\n");
  printdt3(&dt3);
}


void rtupdate3(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{
  int source = rcvdpkt->sourceid;
  int i, j , min_cost, flag=0;
  for(i = 0; i<4; i++){
    // 更新路由表
    if(i == 3) continue;
    dt3.costs[i][source] = dt3.costs[source][0] + rcvdpkt->mincost[i];
  }
  for(i=0; i<4; i++){
    if(i == 3) continue;
    // 检查(对每个目的地)是否有更短路径，如果有，应该通知相邻结点
    min_cost = 999;
    for(j=0; j<4; j++){
      min_cost = min_cost < dt3.costs[i][j] ? min_cost : dt3.costs[i][j];
    }
    if(minicosts3[i] > min_cost){
      minicosts3[i] = min_cost;
      flag = 1; // 发送标志
    }
  }
  if(flag == 1){
    struct rtpkt* update_ptr = (struct rtpkt*)malloc(1*sizeof(struct rtpkt));
    creatertpkt(update_ptr, 1, 0, minicosts3);
    tolayer2(*update_ptr);
    creatertpkt(update_ptr, 1, 2, minicosts3);
    tolayer2(*update_ptr);
    free(update_ptr);
  }

  printf("......update node3......\n");
  printdt3(&dt3);
}


printdt3(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}





