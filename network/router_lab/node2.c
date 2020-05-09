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

struct distance_table 
{
  int costs[4][4];
} dt2;

int connectcosts2[4] = {3,  1,  0, 2};
int minicosts2[4] = {3, 1, 0, 2};


/* students to write the following two routines, and maybe some others */

void rtinit2() 
{
  // 初始化节点2中的距离表
  // 节点2的向量表中[i,j]是节点2通过节点j连接到节点i所需的成本
  int i, j;
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      dt2.costs[i][j] = 999;  // 首先默认全部初始化为999
  dt2.costs[0][0] = connectcosts2[0];  dt2.costs[0][2] = connectcosts2[0];
  dt2.costs[1][1] = connectcosts2[1];  dt2.costs[1][2] = connectcosts2[1];
  dt2.costs[2][2] = 0;
  dt2.costs[3][3] = connectcosts2[3];  dt2.costs[3][2] = connectcosts2[3];
  // 向其他结点发送自己的最小代价信息
  struct rtpkt* update_ptr = (struct rtpkt*)malloc(1*sizeof(struct rtpkt));
  creatertpkt(update_ptr, 1, 0, minicosts2);
  tolayer2(*update_ptr);
  creatertpkt(update_ptr, 1, 1, minicosts2);
  tolayer2(*update_ptr);
  creatertpkt(update_ptr, 1, 3, minicosts2);
  tolayer2(*update_ptr);
  free(update_ptr);

  printf("......init node2......\n");
  printdt2(&dt2);
}


void rtupdate2(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
  int source = rcvdpkt->sourceid;
  int i, j , min_cost, flag=0;
  for(i = 0; i<4; i++){
    // 更新路由表
    if(i == 2) continue;
    dt2.costs[i][source] = dt2.costs[source][0] + rcvdpkt->mincost[i];
  }
  for(i=0; i<4; i++){
    if(i == 2) continue;
    // 检查(对每个目的地)是否有更短路径，如果有，应该通知相邻结点
    min_cost = 999;
    for(j=0; j<4; j++){
      min_cost = min_cost < dt2.costs[i][j] ? min_cost : dt2.costs[i][j];
    }
    if(minicosts2[i] > min_cost){
      minicosts2[i] = min_cost;
      flag = 1; // 发送标志
    }
  }
  if(flag == 1){
    struct rtpkt* update_ptr = (struct rtpkt*)malloc(1*sizeof(struct rtpkt));
    creatertpkt(update_ptr, 1, 0, minicosts2);
    tolayer2(*update_ptr);
    creatertpkt(update_ptr, 1, 1, minicosts2);
    tolayer2(*update_ptr);
    creatertpkt(update_ptr, 1, 3, minicosts2);
    tolayer2(*update_ptr);
    free(update_ptr);
  }

  printf("......update node2......\n");
  printdt2(&dt2);
}


printdt2(dtptr)
  struct distance_table *dtptr;
  
{
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}







