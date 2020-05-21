

#ifndef STUDENTMANAGESYSTEM_FUNCTION_H_
#define STUDENTMANAGESYSTEM_FUNCTION_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"struct.h"
#include "sqlite3.h"

//视图过渡类型
typedef  void (*method)(sqlite3 *,listlink);

//链表操作
extern listlink createClass();  //创建初始化班级
extern int insertOne(listlink); //单记录插入
extern int insertMore(listlink,int);    //多记录插入
extern listlink selectNo(listlink,int); //以学号选择
extern listlink selectName(listlink,char *);    //以姓名选择
extern listlink selectScoreRequirement(listlink,float,float,int);   //按分数条件选择
extern int deleteNo(listlink,int);  //按学号删除
extern int modifyInformation(listlink);     //修改学生信息
extern int sort(listlink);  //排序
extern int show(listlink);  //打印
extern void shownode(listlink node);   //节点打印
extern void print(int pos,listlink node);  //选择打印方式
extern int release(listlink);   //释放链表

//数据库存储
extern sqlite3* openDatabase(sqlite3 *);    //打开数据库
extern int createTable(sqlite3 *, char *);  //创建表
extern int insertRecord(sqlite3 *,listlink,char classname[]);   //记录插入
extern int savaDatabase(sqlite3 *,listlink , char *);  //链表保存入表
extern int getRecord(sqlite3 *, char className[],listlink); //获取全部记录
extern int sqlite_callback(void *, int, char **, char **);  //获取记录的回调函数
extern int table_back(void *, int, char **, char **);   //获取库中表的回调函数
extern int getTable(sqlite3 *);     //获取库中表
extern char* getNumTable(sqlite3 *, listlink, int*); //获取库中第几张表的内容
extern int tableName_back(void *, int, char **, char **);//获取库中第几张表的回调函数

//页面函数
extern void mainPage(sqlite3 *, listlink);  //主页面
extern void createPage(sqlite3 *,listlink);  //创建班级页面
extern void readPage(sqlite3 *, listlink);    //获取班级页面
extern void tableOperte(sqlite3*,listlink,char *);   //班级操作页面
extern void inModi(sqlite3 *,listlink,char *,listlink,int);    //进入修改 pos参数:1为打印节点 2为打印链表

//转换操作
extern void int_to_str(int , char * );  //数字转字符串
extern void node_to_str(listlink,char *);   //结构转字符串
extern void str_reverse(char *);    //字符串转数字
extern void transit(sqlite3 *, listlink,method);    //页面过渡
#endif //STUDENTMANAGESYSTEM_FUNCTION_H
