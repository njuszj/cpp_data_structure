clc;
clear;
N=50;                         %信道数为50 
service_time=20;              %服务持续时间
call_nums=250;               %模拟的呼叫次数  
C=zeros(1,N);                 %信道初始化，全部为空闲   
rates=1:0.5:5;                %信号到达速率   
A=20*rates;                   %话务量

for m=1:length(rates)
    block_num=0;                %信道阻塞的次数清零    
    C=zeros(1,N);               %信道初始化，全部为空闲    
    g=rand(1,call_nums);        %随机生成呼叫次数
    for q=1:call_nums           %指数分布产生服务持续时间     
        services(q)=-service_time*log(g(q));
    end
    temp=0;
    for i=1:call_nums
        randomnum=rand;
        interval=-log(randomnum)/rates(m);      %指数分布产生信号时间间隔 
        arrival(i)=temp+interval;               %信号到达时间
        temp=arrival(i);
    end
    for i=1:call_nums
        access=0;
        for k=1:N
            if arrival(i) > C(k)
                C(k) = arrival(i)+services(i);   %如果信道空闲，就接入
                access = 1;
                break;
            end
        end
        if access == 0                            
            block_num = block_num + 1;                          %如果信道都忙，阻塞个数加一
        end
    end
    block_prob(m)=block_num/call_nums;                          %阻塞率
end

%计算理论堵塞率 
s_fact = factorial(N);
for j=1:length(rates)
    sum = 0;
    for i=1:N
        tmp = A(j)^i / factorial(i);
    	sum = sum + tmp;
    end
    b(j)=((A(j))^N)/(s_fact*sum);                %阻塞率B公式
end

figure(1);
plot(A,block_prob,'^g')
hold on;
plot(A,b,'ob')
xlabel('话务量');
ylabel('阻塞率');
legend('仿真曲线','理论曲线');


figure(2);