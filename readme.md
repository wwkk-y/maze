# 项目信息

- 博客: [C++实现迷宫](http://mywhp.cn/blog/#/blog/37)
- 可执行文件: [maze.exe](http://mywhp.cn/file/maze/maze.exe) (windows)

# 算法讲解

## 迷宫生成算法

这里主要使用深度优先的方式来生成迷宫

将地图考虑成一个全是格子的二维数组

初始情况下, 地图上所有全是墙, 可以将生成的过程考虑成一个砸墙游戏

1. 随机选一个位置方向开始
2. 随机选一个方向开始砸墙, 每次都砸两格
   1. 如果不是墙就换个方向
   2. 如果所有方向都不行, 就往回走砸其它可以砸的墙
3. 如果到了终点, 就往回走继续砸其它可以砸的墙
4. 如果回到了起点, 算法结束

核心代码如下:

```cpp
    vector<Pos> con; // 栈用来存走过的路径
    Pos pos = {
        (rand() % ((int)plat.size() - 3) + 1),
        (rand() % ((int)plat.back().size() - 3) + 1)
    }; // 用来表示当前的位置
    if (!(pos.i % 2)) pos.i += 1;
    if (!(pos.j % 2)) pos.j += 1;

    con.push_back(pos);
    plat[con.back().i][con.back().j]=SPACE;
    while (!con.empty()) {
        random_shuffle(drc.begin(), drc.end(), [](int i) {return rand() % i; }); // 随机选取一个方向
        int i;
        for (i = 0; i < drc.size(); ++i) {
            Pos& pos = con.back(); // 当前位置
            Pos np = { pos.i + 2 * drc[i][0],pos.j + 2 * drc[i][1] };
            // 砸两个格子
            if (np.i >= 0 && np.i < plat.size() && np.j >= 0 && np.j < plat.back().size()) {
                if (plat[np.i][np.j] == WALL) {
                    plat[pos.i + drc[i][0]][pos.j + drc[i][1]] = SPACE;
                    plat[np.i][np.j] = SPACE;
                    con.push_back(np);
                    break;
                }
            }
        }
        if (i == drc.size()) con.pop_back();
    }
    plat[1][0] = SPACE; // 起点
    plat[plat.size() - 2][plat.back().size() - 1] = SPACE; // 终点
```

## 迷宫解密

使用深度优先的方式来解密

初始情况从起点开始走

1. 在所有可选的方向里选一个方向开始走
   - 如果没有可以走的方向, 就往回走
2. 如果到达终点, 算法结束

核心代码如下:

```cpp
    vector<Pos> con; // 栈用来存走过的路径
    const Pos end = { plat.size() - 2,plat.back().size() - 2 }; // 终点
    Pos pos = { 1,1 }; // 当前位置
    setPlat(pos.left(), PATH);
    setPlat(end.right(), PATH);
    while (pos != end) { // 如果到达终点, 算法结束
        con.push_back(pos);
        setPlat(pos, WALK);
        // 在所有可选的方向里选一个方向开始走
        if (getPlat(pos.right()) == SPACE) pos = pos.right();
        else if (getPlat(pos.down()) == SPACE) pos = pos.down();
        else if (getPlat(pos.left()) == SPACE) pos = pos.left();
        else if(getPlat(pos.up()) == SPACE) pos = pos.up();
        else {
            // 如果没有可以走的方向, 就往回走
            con.pop_back();
            con.pop_back();
            pos = con.back();
        }
    }
```

> 参考文献
> 
> - [bilibili-从迷宫生成到创意编程](https://www.bilibili.com/video/BV1tK4y1W777)
