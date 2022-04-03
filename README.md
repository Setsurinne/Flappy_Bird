# Flappy_Bird
 

本项目意在使用C++ easyx库复现flappy bird, 故完成版本将尽力朝原版靠齐

目前version1已经完成，主要使用结构体实现，且所有代码均在一个.cpp内，推荐初学者理清项目逻辑使用

后续版本将使用class实现，目标是自主实现一个2D游戏的开发框架（即基类），希望能够应用于其他简单的2D游戏内
 
基础逻辑： 加载资源 （图片）==> 初始化（数值） ==> 绘图 <<====>> 更新资源 ==> 结束

项目主要资源：背景；地面；小鸟；管道；分数；文字及图标; 背景音乐

## 实现效果
<div><img src="https://github.com/Setsurinne/Flappy_Bird/blob/main/trial.gif" width="250px"></div>

## [version 1](https://github.com/Setsurinne/Flappy_Bird/blob/main/version1/Flappy_Bird/Flappy_Bird.cpp) 涉及知识点： 
1. **easyx 基础函数: 载入图片，绘（多帧）图，旋转图片...**
2. **graphics 基础函数（鼠标点击事件）**
3. **透明贴图：掩码图的绘制 及 原理**
4. **C++ 结构体 及 基础数据类型使用**
5. **使用mmsystem播放背景音乐**
6. ...
     
## [version 2](https://github.com/Setsurinne/Flappy_Bird/tree/main/version2/2D_gaming) （咕咕咕开发中）涉及：
1. **C++ 类的继承；多态；虚函数**
2. ...




This is a project intends to build game flappy-bird in C++ with library easyx
The finished version shoule be an exact reproduct of the original version.
The basic reproduction has been finished in version 1, and latter versions will focus on refractoring & module building

Basic Logic: Load Resources ==> Initialize ==> Draw Images <<====>> Update Resources ==> End
Main Componennts: Background; Ground; Bird; Pipes; Score; Texts; Buttons; Background Music
