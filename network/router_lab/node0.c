#include <stdio.h>

extern struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table 
{
  int costs[4][4];
} dt0;


/* students to write the following two routines, and maybe some others */

void rtinit0() 
{
  // 初始化节点0中的距离表, 按题目要求为1,2,3的成本分别为1,3,7
  // 节点0的向量表中[i,j]是节点0通过节点j连接到节点i所需的成本
  int i, j;
  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      dt0.costs[i][j] = 999;
  dt0.costs[0][0] = 0;
  dt0.costs[1][1] = 1;
  dt0.costs[2][2] = 3;
  dt0.costs[3][3] = 7;
}


void rtupdate0(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
  int i;
  int source_id = rcvdpkt->sourceid;
  for(i=0; i<4; i++){
    // 更新路由表
    dt0.costs[source_id][i] =  dt0.costs[0][source_id] + rcvdpkt->mincost[i];
  }
  printdt0(dt0);
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

