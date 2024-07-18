# 博客地址

[C++实现迷宫](http://mywhp.cn/blog/#/blog/37)

# 视频演示

## 迷宫生成

<video src="/file/maze/generate.mp4" controls="controls" style="max-width:100%;"></video>

## 迷宫解密

<video src="/file/maze/decrypt.mp4" controls="controls" style="max-width:100%;"></video>

## 玩家操作

<video src="/file/maze/play.mp4" controls="controls" style="max-width:100%;"></video>

# 算法讲解

## 迷宫生成算法

这里主要使用深度优先的方式来生成迷宫

将地图考虑成一个全是格子的二维数组

初始情况下, 地图上所有全是墙, 可以将生成的过程考虑成一个砸墙游戏

## 迷宫解密

使用深度优先的方式来解密, 

# 可执行文件

- windows: [maze.exe](/file/maze/maze.exe)

# EXT 图形界面

前面的是基于控制台实现的(也就是大家刚学C语言时的那个黑框框), 比较原始, 我们可以将利用这个算法的思想写一个带图形界面的迷宫

> 由于笔者这里实现的图形界面是用的C语言一个比较小众的库(libgraphics), 而且当时我才大一, 代码写的比较抽象, 所以这里源代码就不开源了。

## 迷宫生成

<video src="/file/maze/generateUI.mp4" controls="controls" style="max-width:100%;"></video>

## 迷宫解密

<video src="/file/maze/decryptUI.mp4" controls="controls" style="max-width:100%;"></video>

> ## 参考文献
> 
> - 
