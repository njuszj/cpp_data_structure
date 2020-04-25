/*
 * linux cp 功能
*/


# include "sys/types.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define BUFSIZE 4096
# define OUTPUT_MODE 0700

int main(int argc, char* argv[]){
    int in_fd, out_fd, rd_cnt, wt_cnt;
    char buffer[BUFSIZE];

    if(argc != 3){
        printf("参数错误：数量不是3个\n");
        exit(1);
    }
    in_fd = open(argv[1], O_RDONLY);  // 以只读形式打开文件
    if(in_fd < 0) exit(2);   // 读取失败
    out_fd = creat(argv[2], OUTPUT_MODE);  // 创建文件
    if(out_fd < 0) exit(3);  // 创建失败

    while(1){
        // 循环复制
        rd_cnt = read(in_fd, buffer, BUFSIZE);  // 读数据
        if(rd_cnt <= 0) break;
        wt_cnt = write(out_fd, buffer, rd_cnt);  // 写数据
        if(wt_cnt <= 0) exit(4);
    }
    close(in_fd);
    close(out_fd);
    if(rd_cnt == 0)
        exit(0);
    else
    {
        exit(5);
    }
}