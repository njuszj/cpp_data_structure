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
} dt0;
int connectcosts0[4] = {0, 1, 3, 7};  // node0到0/1/2/3结点的直连距离
int minicosts0[4] = {0, 1, 3, 7};


/* students to write the following two routines, and maybe some others */
void rtinit0() {
  // 初始化节点0中的距离表, 按题目要求为1,2,3的成本分别为1,3,7
  // 节点0的向量表中[i,j]是节点0通过节点j连接到节点i所需的成本
  int i, j;
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      dt0.costs[i][j] = 999;  // 首先默认全部初始化为999
  dt0.costs[0][0] = 0;        // 初始化到直连结点的距离
  dt0.costs[1][1] = connectcosts0[1];  dt0.costs[1][0] = connectcosts0[1];
  dt0.costs[2][2] = connectcosts0[2];  dt0.costs[2][0] = connectcosts0[2];
  dt0.costs[3][3] = connectcosts0[3];  dt0.costs[3][0] = connectcosts0[3];
  // 向其他结点发送自己的最小代价信息
  struct rtpkt* update_ptr = (struct rtpkt*)malloc(1*sizeof(struct rtpkt));
  creatertpkt(update_ptr, 0, 1, minicosts0);
  tolayer2(*update_ptr);
  creatertpkt(update_ptr, 0, 2, minicosts0);
  tolayer2(*update_ptr);
  creatertpkt(update_ptr, 0, 3, minicosts0);
  tolayer2(*update_ptr);
  free(update_ptr);

  printf("......init node0......\n");
  printdt0(&dt0);
}


void rtupdate0(struct rtpkt *rcvdpkt) {
  int source = rcvdpkt->sourceid;
  int i, j , min_cost, flag=0;
  for(i = 0; i<4; i++){
    // 更新路由表
    if(i == 0) continue;
    dt0.costs[i][source] = dt0.costs[source][0] + rcvdpkt->mincost[i];
  }
  for(i=0; i<4; i++){
    if(i == 0) continue;
    // 检查(对每个目的地)是否有更短路径，如果有，应该通知相邻结点
    min_cost = 999;
    for(j=0; j<4; j++){
      min_cost = min_cost < dt0.costs[i][j] ? min_cost : dt0.costs[i][j];
    }
    if(minicosts0[i] > min_cost){
      minicosts0[i] = min_cost;
      flag = 1; // 发送标志
    }
  }
  if(flag == 1){
    struct rtpkt* update_ptr = (struct rtpkt*)malloc(1*sizeof(struct rtpkt));
    creatertpkt(update_ptr, 0, 1, minicosts0);
    tolayer2(*update_ptr);
    creatertpkt(update_ptr, 0, 2, minicosts0);
    tolayer2(*update_ptr);
    creatertpkt(update_ptr, 0, 3, minicosts0);
    tolayer2(*update_ptr);
    free(update_ptr);
  }

  printf("......update node0......\n");
  printdt0(&dt0);
}


printdt0(dtptr)
  struct distance_table *dtptr;
  
{
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}

linkhandler0(linkid, newcost)   
  int linkid, newcost;

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}

