飞机大战
----
# 简介
一款用C语言写的小游戏，使用了easyX图形库。
# 玩法
鼠标移动控制飞机，单击左键发射子弹。
# 开发经验
1.新建项目时选择控制台程序。
2.在visual studio的项目/属性/常规中将unicode字符集改为多字节字符集。否则要在路径的引号前加上“L”。
3.用fabs代替abs。因为abs有多种参数类型，会导致不匹配。
4.为了防止访问越界，微软建议使用sprintf_s代替sprintf。但是推荐在项目/属性/C/C++/预处理器中添加以下宏：_CRT_SECURE_NO_DEPRECATE;_SCL_SECURE_NO_DEPRECATE。
5.使用BeginBatchDraw(),别忘了FlushBatchDraw();
6.文件路径要写完整。
# 游戏的不足
1.敌机只有一架，循环生成。
2.没有做敌机出下界的判断。
3.没有开始菜单，也没有结束界面。
4.不能显示最高分。
5.敌机不会攻击。
6.不能暂停。
7.不支持关闭音乐和音效。
8.玩法比较单一，没有补给包。
9.画面丑，音乐难听。
