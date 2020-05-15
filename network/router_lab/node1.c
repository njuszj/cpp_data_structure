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

int connectcosts1[4] = { 1,  0,  1, 999 };
int minicosts1[4] = {1, 0, 1, 999};

struct distance_table 
{
  int costs[4][4];
} dt1;


/* students to write the following two routines, and maybe some others */


rtinit1() 
{
  // 初始化节点1中的距离表
  // 节点1的向量表中[i,j]是节点1通过节点j连接到节点i所需的成本
  int i, j;
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      dt1.costs[i][j] = 999;  // 首先默认全部初始化为999
  dt1.costs[0][0] = connectcosts1[0];  dt1.costs[0][1] = connectcosts1[0];
  dt1.costs[1][1] = 0;
  dt1.costs[2][2] = connectcosts1[2];  dt1.costs[2][1] = connectcosts1[2];
  dt1.costs[3][3] = connectcosts1[3];  dt1.costs[3][1] = connectcosts1[3];
  // 向其他结点发送自己的最小代价信息
  struct rtpkt* update_ptr = (struct rtpkt*)malloc(1*sizeof(struct rtpkt));
  creatertpkt(update_ptr, 1, 0, minicosts1);
  tolayer2(*update_ptr);
  creatertpkt(update_ptr, 1, 2, minicosts1);
  tolayer2(*update_ptr);
  free(update_ptr);

  printf("......init node1......\n");
  printdt1(&dt1);
}


rtupdate1(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
  int source = rcvdpkt->sourceid;
  int i, j , min_cost, flag=0;
  for(i = 0; i<4; i++){
    // 更新路由表
    if(i == 1) continue;
    dt1.costs[i][source] = dt1.costs[source][0] + rcvdpkt->mincost[i];
  }
  for(i=0; i<4; i++){
    if(i == 1) continue;
    // 检查(对每个目的地)是否有更短路径，如果有，应该通知相邻结点
    min_cost = 999;
    for(j=0; j<4; j++){
      min_cost = min_cost < dt1.costs[i][j] ? min_cost : dt1.costs[i][j];
    }
    if(minicosts1[i] > min_cost){
      minicosts1[i] = min_cost;
      flag = 1; // 发送标志
    }
  }
  if(flag == 1){
    struct rtpkt* update_ptr = (struct rtpkt*)malloc(1*sizeof(struct rtpkt));
    creatertpkt(update_ptr, 1, 0, minicosts1);
    tolayer2(*update_ptr);
    creatertpkt(update_ptr, 1, 2, minicosts1);
    tolayer2(*update_ptr);
    free(update_ptr);
  }

  printf("......update node1......\n");
  printdt1(&dt1);
}


printdt1(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}



linkhandler1(linkid, newcost)   
int linkid, newcost;   
/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
    int i,j;   
    int cost = 999;   
    int changed = 0;   
    dt1.costs[linkid][1] = newcost;   
    for(i=0; i<4; i++){   
        dt1.costs[i][linkid] = dt1.costs[i][linkid] + newcost - connectcosts1[linkid];   
    }   
    connectcosts1[linkid] = newcost;   
    for(i=0; i<4; i++){   
        cost = 999;   
        for(j=0; j<4; j++){   
            if(cost > dt1.costs[i][j]){   
                cost = dt1.costs[i][j];   
                   
            }   
        }   
        minicosts1[i] = cost;   
    }
    struct rtpkt* update_ptr = (struct rtpkt*)malloc(1*sizeof(struct rtpkt));
    creatertpkt(update_ptr, 1, 0, minicosts1);
    tolayer2(*update_ptr);
    creatertpkt(update_ptr, 1, 2, minicosts1);
    tolayer2(*update_ptr);
    free(update_ptr);
}


