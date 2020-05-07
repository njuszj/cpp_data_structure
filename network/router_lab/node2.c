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
} dt2;


/* students to write the following two routines, and maybe some others */

void rtinit2() 
{
  dt2.costs[0][0] = 3;
  dt2.costs[1][1] = 1;
  dt2.costs[2][2] = 0;
  dt2.costs[3][3] = 2;
}


void rtupdate2(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{
  int i;
  int source_id = rcvdpkt->sourceid;
  for(i=0; i<4; i++){
    // 更新路由表
    dt2.costs[source_id][i] =  dt2.costs[0][source_id] + rcvdpkt->mincost[i];
  }
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






