#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* possible events: */

struct event
{
    float evtime;       /* event time */
    int evtype;         /* event type code */
    int eventity;       /* entity where event occurs */
    struct pkt *pktptr; /* ptr to packet (if any) assoc w/ this event */
    struct event *prev;
    struct event *next;
};
struct event *evlist = NULL; /* the event list */

#define TIMER_INTERRUPT 0
#define FROM_LAYER5 1
#define FROM_LAYER3 2

#define OFF 0
#define ON 1
#define A 0
#define B 1

int TRACE = 1;   /* for my debugging */
int nsim = 0;    /* number of messages from 5 to 4 so far */
int nsimmax = 0; /* number of msgs to generate, then stop */
float time = 0.000;
float lossprob;    /* probability that a packet is dropped  */
float corruptprob; /* probability that one bit is packet is flipped */
float lambda;      /* arrival rate of messages from layer 5 */
int ntolayer3;     /* number sent into layer 3 */
int nlost;         /* number lost in media */
int ncorrupt;      /* number corrupted by media*/

#define BIDIRECTIONAL 0 // change to 1 if you're doing extra credit and write a routine called B_output

typedef struct msg
{
    char data[20];
} msg;


typedef struct pkt
{
    int seqnum;
    int acknum;
    int checksum;
    char payload[20];
} pkt;

void starttimer(int AorB, float increment);
void stoptimer(int AorB);
void tolayer3(int AorB, struct pkt packet);
void tolayer5(int AorB, char datasent[20]);

/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/

#define WINDOW_SIZE 10    // 发送窗口长度
#define BUFFER_SIZE 500   // 缓冲区大小

int A_tail;      // 发送窗口尾部指针
int A_head;       // 发送窗口头部指针
int A_nextseq;   // 要发送的序号
int A_seq;   // 序号
int A_ack;   // 确认号
pkt A_buffer_zone[BUFFER_SIZE];   // A的缓冲区, 是一个储存pkt的数组
char ACK[20] = "ACK";
char NAK[20] = "NAK";

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init(void)
{
    A_tail = 0;
    A_nextseq = 0;
    A_head = 0;
    srand(24);
    A_seq = rand() % BUFFER_SIZE;
    A_ack = rand() % BUFFER_SIZE;
}

/* Note that with simplex transfer from a-to-B, there is no B_output() */

void GetCheckSum(pkt* packet){
    // 计算校验和
    // 把每一部分都加起来(seq ack payload)
    packet->checksum = packet->seqnum + packet->acknum;
    int i;
    for(i=0; i<20; i+=4){
        int tmp1 = (int)packet->payload[i];
        int tmp2 = (int)packet->payload[i + 1];
        int tmp3 = (int)packet->payload[i + 2];
        int tmp4 = (int)packet->payload[i + 3];
        tmp2 << 8;  // 移位
        tmp3 << 16;
        tmp4 << 24;
        packet->checksum += (tmp1 + tmp2 + tmp3 + tmp4);
     }
     packet->checksum = ~ packet->checksum;
}

int VerifyCheckSum(pkt* packet){
    // 校验checksum
    int check = packet->checksum;
    check += (packet->seqnum + packet->acknum);
    int i;
    for(i = 0;i < 20;i += 4){
        int tmp1 = (int)packet->payload[i];
        int tmp2 = (int)packet->payload[i + 1];
        int tmp3 = (int)packet->payload[i + 2];
        int tmp4 = (int)packet->payload[i + 3];
        tmp2 << 8;
        tmp3 << 16;
        tmp4 << 24;
        check += (tmp1 + tmp2 + tmp3 + tmp4);
    }
    return check;  // 如果没有差错应该得到-1(全1序列)
}


// 该函数被上层调用，向下层传递字符串消息
void A_output(msg message)
{
    if(A_nextseq < (A_tail+WINDOW_SIZE)){
        // 如果在窗口中
        strncpy(A_buffer_zone[A_nextseq].payload, message.data, 20);
        A_buffer_zone[A_nextseq].seqnum = A_seq + (A_nextseq - A_tail);
        A_buffer_zone[A_nextseq].acknum = A_ack + (A_nextseq - A_tail);
        GetCheckSum(&A_buffer_zone[A_nextseq]);    // 计算校验和
        tolayer3(0,A_buffer_zone[A_nextseq]);
        if(A_nextseq == A_tail) starttimer(0,lambda);  // 窗口内的包已经发送完毕
        {
            // 打印日志
            printf("***************************************\n");
            printf("A-> has sent\n");
            printf("A-> seq: %d,  ack: %d,  checksum: %d \n", A_buffer_zone[A_nextseq].seqnum, A_buffer_zone[A_nextseq].acknum, A_buffer_zone[A_nextseq].checksum);
            printf("A-> messages: %s\n", A_buffer_zone[A_nextseq].payload);
            printf("***************************************\n");
        }
        A_nextseq = (A_nextseq + 1) % BUFFER_SIZE;  // 发送序号+1
        A_head = (A_head + 1) % BUFFER_SIZE;   // 发送窗口+1
    }
    else{
        // 如果加上窗口值之后等于下一期望的序号
        // 即需要添加发送的pkt
        if(A_head % BUFFER_SIZE == A_tail){
            // 如果顶部指针与底部指针重合
            printf("缓冲区已经满了!\n");
            return;
        }
        else{
            strncpy(A_buffer_zone[A_head].payload, message.data, 20);   // 向pkt中拷贝消息
            A_head = (A_head + 1) % BUFFER_SIZE;  // 窗口数据填充
        }
    }
}

/* need be completed only for extra credit */
void B_output(struct msg message)
{
    printf("  B_output: uni-directional. ignore.\n");
}

// 下层调用， 向上层传递 layer3->layer5
void A_input(struct pkt packet)
{
    if(A_ack != packet.seqnum){
        printf("错误的确认号\n");
        return;
    }   
    if(VerifyCheckSum(&packet) == -1){
        // 校验成功
        stoptimer(0);
        if(strcmp(packet.payload, ACK) == 0){
            // 消息是ACK
            A_seq++;
            A_ack++;
            A_tail = (A_tail + 1) % BUFFER_SIZE;
            if(A_head != A_nextseq){
                // 如果窗口头部不是下一序号
                // 发送消息
                A_buffer_zone[A_nextseq].seqnum = A_seq + (A_nextseq - A_tail);
                A_buffer_zone[A_nextseq].acknum = A_ack + (A_nextseq - A_tail);
                GetCheckSum(&A_buffer_zone[A_nextseq]);
                tolayer3(0, A_buffer_zone[A_nextseq]);  // 发送下一条消息
                A_nextseq = (A_nextseq + 1) % BUFFER_SIZE;
            }
        }
        else{
            printf("消息没有收到应答，NAK");
            tolayer3(0,A_buffer_zone[A_tail]);  // 重传
            starttimer(0, lambda);
        }
    }
    else{
        // 校验和出错
        printf("错误的校验号");
        return;
    }
}

/* called when A's timer goes off */
void A_timerinterrupt(void)
{
    // 调用这个函数重传所有没被确认的序号，后退n步
    int i,j;
    for(j = A_tail;j < A_nextseq; j++){
        tolayer3(0, A_buffer_zone[j]);  // 重传
        {
            printf("***************************************\n");
            printf("A-> sending:\n");
            printf("A-> seq:%d, ack:%d, check:%X\n",A_buffer_zone[j].seqnum,A_buffer_zone[j].acknum,A_buffer_zone[j].checksum);
            printf("A-> message: %s", A_buffer_zone[j].payload);
            printf("\n\n");
            printf("***************************************\n");
        }

    }
    starttimer(0, lambda);
}   

void send_ack(int AorB, int ack)
{
    return;
}


pkt B_packet;                   /* packet buffer */
int B_first_or_not;
int B_seq_looking_for;
int B_ack;

/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init(void)
{
    B_first_or_not = 1;
    B_packet.seqnum = -1;
    B_packet.acknum = -1;
    strncpy(B_packet.payload,NAK,20);
}

/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(struct pkt packet)
{
    int i;

    printf("B <- receiving:\n");
    printf("B <- seq:%d, ack:%d check:%X\n",packet.seqnum,packet.acknum,packet.checksum);
    printf("B <- message: %s", packet.payload);
    printf("\n\n");

    if(VerifyCheckSum(&packet) == -1){ 
        //校验和正确
        if(B_first_or_not){
            B_seq_looking_for = packet.seqnum;
            B_ack = packet.acknum;
            B_first_or_not = 0;
        }
        printf("receive:%d,looking for:%d\n",packet.seqnum,B_seq_looking_for);
        if(packet.seqnum == B_seq_looking_for){
            // 向上层交付
            B_packet.seqnum = B_ack++;
            B_packet.acknum = ++B_seq_looking_for;               
            strncpy(B_packet.payload,ACK,20);
            msg receive;
            strncpy(receive.data,packet.payload,20);
            tolayer5(1, receive.data);
        }
        else{
            if(packet.seqnum > B_seq_looking_for){
                // 向A发送确认
                tolayer3(1, B_packet);
                {
                    // 打印日志
                    printf("***************************************\n");
                    printf("B ->  sending:\n");
                    printf("B ->  seq:%d, ack:%d check:%X\n",B_packet.seqnum,B_packet.acknum,B_packet.checksum);
                    printf("B ->  message: %s", B_packet.payload);
                    printf("\n\n");
                    printf("***************************************\n");
                }
            }
            else{
                pkt lost_or_corrputed_ACK;
                lost_or_corrputed_ACK.seqnum = packet.acknum;
                lost_or_corrputed_ACK.acknum = packet.seqnum + 1;
                strncpy(lost_or_corrputed_ACK.payload,ACK,20);
                GetCheckSum(&lost_or_corrputed_ACK);
                tolayer3(1,lost_or_corrputed_ACK);   // 发送反馈
                {
                    printf("***************************************\n");
                    printf("B -> sending:\n");
                    printf("B -> seq:%d, ack:%d ",lost_or_corrputed_ACK.seqnum,lost_or_corrputed_ACK.acknum);
                    printf("B -> check:%X\n",lost_or_corrputed_ACK.checksum);
                    printf("B ->  message:%s", lost_or_corrputed_ACK.payload);
                    printf("\n\n");
                    printf("***************************************\n");
                }
            }
        }       
    }
    else
        strncpy(B_packet.payload,NAK,20);        
    GetCheckSum(&B_packet);
    {
        printf("***************************************\n");
        printf("B -> sending:\n");
        printf("B -> seq:%d, ack:%d check:%X\n",B_packet.seqnum,B_packet.acknum,B_packet.checksum);
        printf("B -> message:%s", B_packet.payload);
        printf("\n\n");
        printf("***************************************\n");
    }
    tolayer3(1,B_packet);
}

/* called when B's timer goes off */
void B_timerinterrupt(void)
{
    printf("  B_timerinterrupt: B doesn't have a timer. ignore.\n");
}


void init(int argc, char **argv);
void generate_next_arrival(void);
void insertevent(struct event *p);

int main(int argc, char **argv)
{
    struct event *eventptr;
    struct msg msg2give;
    struct pkt pkt2give;

    int i, j;
    char c;

    init(argc, argv);
    A_init();
    B_init();

    while (1)
    {
        eventptr = evlist; /* get next event to simulate */
        if (eventptr == NULL)
            goto terminate;
        evlist = evlist->next; /* remove this event from event list */
        if (evlist != NULL)
            evlist->prev = NULL;
        if (TRACE >= 2)
        {
            printf("\nEVENT time: %f,", eventptr->evtime);
            printf("  type: %d", eventptr->evtype);
            if (eventptr->evtype == 0)
                printf(", timerinterrupt  ");
            else if (eventptr->evtype == 1)
                printf(", fromlayer5 ");
            else
                printf(", fromlayer3 ");
            printf(" entity: %d\n", eventptr->eventity);
        }
        time = eventptr->evtime; /* update time to next event time */
        if (eventptr->evtype == FROM_LAYER5)
        {
            if (nsim < nsimmax)
            {
                if (nsim + 1 < nsimmax)
                    generate_next_arrival(); /* set up future arrival */
                /* fill in msg to give with string of same letter */
                j = nsim % 26;
                for (i = 0; i < 20; i++)
                    msg2give.data[i] = 97 + j;
                msg2give.data[19] = 0;
                if (TRACE > 2)
                {
                    printf("          MAINLOOP: data given to student: ");
                    for (i = 0; i < 20; i++)
                        printf("%c", msg2give.data[i]);
                    printf("\n");
                }
                nsim++;
                if (eventptr->eventity == A)
                    A_output(msg2give);
                else
                    B_output(msg2give);
            }
        }
        else if (eventptr->evtype == FROM_LAYER3)
        {
            pkt2give.seqnum = eventptr->pktptr->seqnum;
            pkt2give.acknum = eventptr->pktptr->acknum;
            pkt2give.checksum = eventptr->pktptr->checksum;
            for (i = 0; i < 20; i++)
                pkt2give.payload[i] = eventptr->pktptr->payload[i];
            if (eventptr->eventity == A) /* deliver packet by calling */
                A_input(pkt2give);       /* appropriate entity */
            else
                B_input(pkt2give);
            free(eventptr->pktptr); /* free the memory for packet */
        }
        else if (eventptr->evtype == TIMER_INTERRUPT)
        {
            if (eventptr->eventity == A)
                A_timerinterrupt();
            else
                B_timerinterrupt();
        }
        else
        {
            printf("INTERNAL PANIC: unknown event type \n");
        }
        free(eventptr);
    }

terminate:
    printf(
        " Simulator terminated at time %f\n after sending %d msgs from layer5\n",
        time, nsim);
}

void init(int argc, char **argv) /* initialize the simulator */
{
    int i;
    float sum, avg;
    float jimsrand();

    if (argc != 6)
    {
        printf("usage: %s  num_sim  prob_loss  prob_corrupt  interval  debug_level\n", argv[0]);
        exit(1);
    }

    nsimmax = atoi(argv[1]);
    lossprob = atof(argv[2]);
    corruptprob = atof(argv[3]);
    lambda = atof(argv[4]);
    TRACE = atoi(argv[5]);
    printf("-----  Stop and Wait Network Simulator Version 1.1 -------- \n\n");
    printf("the number of messages to simulate: %d\n", nsimmax);
    printf("packet loss probability: %f\n", lossprob);
    printf("packet corruption probability: %f\n", corruptprob);
    printf("average time between messages from sender's layer5: %f\n", lambda);
    printf("TRACE: %d\n", TRACE);

    srand(9999); /* init random number generator */
    sum = 0.0;   /* test random number generator for students */
    for (i = 0; i < 1000; i++)
        sum = sum + jimsrand(); /* jimsrand() should be uniform in [0,1] */
    avg = sum / 1000.0;
    if (avg < 0.25 || avg > 0.75)
    {
        printf("It is likely that random number generation on your machine\n");
        printf("is different from what this emulator expects.  Please take\n");
        printf("a look at the routine jimsrand() in the emulator code. Sorry. \n");
        exit(1);
    }

    ntolayer3 = 0;
    nlost = 0;
    ncorrupt = 0;

    time = 0.0;              /* initialize time to 0.0 */
    generate_next_arrival(); /* initialize event list */
}

/****************************************************************************/
/* jimsrand(): return a float in range [0,1].  The routine below is used to */
/* isolate all random number generation in one location.  We assume that the*/
/* system-supplied rand() function return an int in therange [0,mmm]        */
/****************************************************************************/
float jimsrand(void)
{
    double mmm = RAND_MAX;
    float x;          /* individual students may need to change mmm */
    x = rand() / mmm; /* x should be uniform in [0,1] */
    return (x);
}

/********************* EVENT HANDLINE ROUTINES *******/
/*  The next set of routines handle the event list   */
/*****************************************************/

void generate_next_arrival(void)
{
    double x, log(), ceil();
    struct event *evptr;
    float ttime;
    int tempint;

    if (TRACE > 2)
        printf("          GENERATE NEXT ARRIVAL: creating new arrival\n");

    x = lambda * jimsrand() * 2; /* x is uniform on [0,2*lambda] */
                                 /* having mean of lambda        */
    evptr = (struct event *)malloc(sizeof(struct event));
    evptr->evtime = time + x;
    evptr->evtype = FROM_LAYER5;
    if (BIDIRECTIONAL && (jimsrand() > 0.5))
        evptr->eventity = B;
    else
        evptr->eventity = A;
    insertevent(evptr);
}

void insertevent(struct event *p)
{
    struct event *q, *qold;

    if (TRACE > 2)
    {
        printf("            INSERTEVENT: time is %lf\n", time);
        printf("            INSERTEVENT: future time will be %lf\n", p->evtime);
    }
    q = evlist; /* q points to header of list in which p struct inserted */
    if (q == NULL)
    { /* list is empty */
        evlist = p;
        p->next = NULL;
        p->prev = NULL;
    }
    else
    {
        for (qold = q; q != NULL && p->evtime > q->evtime; q = q->next)
            qold = q;
        if (q == NULL)
        { /* end of list */
            qold->next = p;
            p->prev = qold;
            p->next = NULL;
        }
        else if (q == evlist)
        { /* front of list */
            p->next = evlist;
            p->prev = NULL;
            p->next->prev = p;
            evlist = p;
        }
        else
        { /* middle of list */
            p->next = q;
            p->prev = q->prev;
            q->prev->next = p;
            q->prev = p;
        }
    }
}

void printevlist(void)
{
    struct event *q;
    int i;
    printf("--------------\nEvent List Follows:\n");
    for (q = evlist; q != NULL; q = q->next)
    {
        printf("Event time: %f, type: %d entity: %d\n", q->evtime, q->evtype,
               q->eventity);
    }
    printf("--------------\n");
}

/********************** Student-callable ROUTINES ***********************/

/* called by students routine to cancel a previously-started timer */
void stoptimer(int AorB /* A or B is trying to stop timer */)
{
    struct event *q, *qold;

    if (TRACE > 2)
        printf("          STOP TIMER: stopping timer at %f\n", time);
    /* for (q=evlist; q!=NULL && q->next!=NULL; q = q->next)  */
    for (q = evlist; q != NULL; q = q->next)
        if ((q->evtype == TIMER_INTERRUPT && q->eventity == AorB))
        {
            /* remove this event */
            if (q->next == NULL && q->prev == NULL)
                evlist = NULL;        /* remove first and only event on list */
            else if (q->next == NULL) /* end of list - there is one in front */
                q->prev->next = NULL;
            else if (q == evlist)
            { /* front of list - there must be event after */
                q->next->prev = NULL;
                evlist = q->next;
            }
            else
            { /* middle of list */
                q->next->prev = q->prev;
                q->prev->next = q->next;
            }
            free(q);
            return;
        }
    printf("Warning: unable to cancel your timer. It wasn't running.\n");
}

void starttimer(int AorB /* A or B is trying to stop timer */, float increment)
{
    struct event *q;
    struct event *evptr;

    if (TRACE > 2)
        printf("          START TIMER: starting timer at %f\n", time);
    /* be nice: check to see if timer is already started, if so, then  warn */
    /* for (q=evlist; q!=NULL && q->next!=NULL; q = q->next)  */
    for (q = evlist; q != NULL; q = q->next)
        if ((q->evtype == TIMER_INTERRUPT && q->eventity == AorB))
        {
            printf("Warning: attempt to start a timer that is already started\n");
            return;
        }

    /* create future event for when timer goes off */
    evptr = (struct event *)malloc(sizeof(struct event));
    evptr->evtime = time + increment;
    evptr->evtype = TIMER_INTERRUPT;
    evptr->eventity = AorB;
    insertevent(evptr);
}

/************************** TOLAYER3 ***************/
void tolayer3(int AorB /* A or B is trying to stop timer */, struct pkt packet)
{
    struct pkt *mypktptr;
    struct event *evptr, *q;
    float lastime, x;
    int i;

    ntolayer3++;

    /* simulate losses: */
    if (jimsrand() < lossprob)
    {
        nlost++;
        if (TRACE > 0)
            printf("          TOLAYER3: packet being lost\n");
        return;
    }

    /* make a copy of the packet student just gave me since he/she may decide */
    /* to do something with the packet after we return back to him/her */
    mypktptr = (struct pkt *)malloc(sizeof(struct pkt));
    mypktptr->seqnum = packet.seqnum;
    mypktptr->acknum = packet.acknum;
    mypktptr->checksum = packet.checksum;
    for (i = 0; i < 20; i++)
        mypktptr->payload[i] = packet.payload[i];
    if (TRACE > 2)
    {
        printf("          TOLAYER3: seq: %d, ack %d, check: %d ", mypktptr->seqnum,
               mypktptr->acknum, mypktptr->checksum);
        for (i = 0; i < 20; i++)
            printf("%c", mypktptr->payload[i]);
        printf("\n");
    }

    /* create future event for arrival of packet at the other side */
    evptr = (struct event *)malloc(sizeof(struct event));
    evptr->evtype = FROM_LAYER3;      /* packet will pop out from layer3 */
    evptr->eventity = (AorB + 1) % 2; /* event occurs at other entity */
    evptr->pktptr = mypktptr;         /* save ptr to my copy of packet */
                                      /* finally, compute the arrival time of packet at the other end.
                                         medium can not reorder, so make sure packet arrives between 1 and 10
                                         time units after the latest arrival time of packets
                                         currently in the medium on their way to the destination */
    lastime = time;
    /* for (q=evlist; q!=NULL && q->next!=NULL; q = q->next) */
    for (q = evlist; q != NULL; q = q->next)
        if ((q->evtype == FROM_LAYER3 && q->eventity == evptr->eventity))
            lastime = q->evtime;
    evptr->evtime = lastime + 1 + 9 * jimsrand();

    /* simulate corruption: */
    if (jimsrand() < corruptprob)
    {
        ncorrupt++;
        if ((x = jimsrand()) < .75)
            mypktptr->payload[0] = 'Z'; /* corrupt payload */
        else if (x < .875)
            mypktptr->seqnum = 999999;
        else
            mypktptr->acknum = 999999;
        if (TRACE > 0)
            printf("          TOLAYER3: packet being corrupted\n");
    }

    if (TRACE > 2)
        printf("          TOLAYER3: scheduling arrival on other side\n");
    insertevent(evptr);
}

void tolayer5(int AorB, char datasent[20])
{
    int i;
    if (TRACE > 2)
    {
        printf("          TOLAYER5: data received: ");
        for (i = 0; i < 20; i++)
            printf("%c", datasent[i]);
        printf("\n");
    }
}
