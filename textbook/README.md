
### 《C++数据结构与算法》部分代码
我在学习此书时实现了书中的一些代码，并添加了一些注释

### 目录
+ 编译后的可执行文件 bin/
+ 第一章案例: 随机访问文件 RandomFileIO/
+ 第三章: 单向链表 IntSLList/
+ 第三章: 跳跃链表 GenSkipList/
+ 第三章案例: 图书馆系统 Library/
+ 第四章案例: 迷宫问题　Maze/
+ 第五章: 斐波那契数列的三种表示 Fibonacci.cpp
+ 第五章案例:　递归下降解释器 Interpreter/
+ 第六章: 二叉查找树 GenBST/

### 递归下降解释器
+ 使用递归的方式调用解释器
+ 表达式分解成项(term), 项分解成因子
+ 因子(factor): 标识符、数、圆括号
+ 表达式类维护了一个字符型变量 ch, 用以逐字符读入
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200314110212253.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2JhaWR1XzQxNzQzMTk1,size_1,color_FFFFFF,t_70)