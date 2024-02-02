#  使用规则
1.  导入所有相关静态库文件(.a后缀文件)
2.  在building setting中Library search path中链接这些静态库的地址
3.  在building setting中Headers search path中链接这些静态库的头文件地址
4.  导入platform.cpp头文件放在im目录下，同时 在building setting中Headers search path中链接platform.cpp头文件地址
5.  编译执行

