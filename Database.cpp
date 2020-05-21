#include "function.h"

int savaDatabase(sqlite3 *db, listlink H, char className[]){
    char *zErrMsg = 0;
    int rc;
    listlink  head = H->next;
    char sql[200]="select * from sqlite_master where name = '";
    //先查看是否有表,如果有则删除
    strcat(sql,className);
    strcat(sql,"'");
    rc = sqlite3_exec(db,sql,NULL,0,&zErrMsg);
    if(rc == SQLITE_OK){
        memset(sql,'\0',strlen(sql));
        strcpy(sql,"drop table ");
        strcat(sql,className);
        sqlite3_exec(db,sql,NULL,0,&zErrMsg);
    }
    if(head == NULL){
        fprintf(stdout,"无学生信息可存储!\n");
        return 0;
    }
    if(createTable(db,className) == 0){
        fprintf(stdout,"%s创建成功!\n",className);
    }else{
        fprintf(stderr,"创建失败!\n");
        sqlite3_free(zErrMsg);
        return -1;
    }
    while(head){
        rc = insertRecord(db,head,className);
        if(rc != SQLITE_OK){
            fprintf(stderr,"学号%d记录插入失败!\n",head->no);
            sqlite3_free(zErrMsg);
            return -1;
        }
        head = head->next;
    }
    sqlite3_free(zErrMsg);
    return 0;
}
//打开班级管理数据库
sqlite3 * openDatabase(sqlite3 *db){
    if(db != nullptr){
        printf("变量已指向一个数据库!\n");
        return NULL;
    }
    //打开数据库
    if(sqlite3_open("班级管理",&db)){
        fprintf(stderr,"不能打开数据库!\n");
        exit(0);
    }else{
        fprintf(stdout,"打开成功!\n");
    }
    return db;
}
//创建表
int createTable(sqlite3 * db, char  className[]){
    if(className == NULL){
        fprintf(stderr, "没有表名!\n");
        return -1;
    }
    int rc;
    char* zErrMsg = 0;
    char sql[200]="create table ";
    //创建班级表
    strcat(sql, className);
    strcat(sql," (id int primary key  not null, name text not null, sex char(10), birthday char(20), address text, score float)");
    rc = sqlite3_exec(db,sql,NULL,0,&zErrMsg);
    if(rc != SQLITE_OK){
        fprintf(stderr,"sql error!\n",zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }else{
        fprintf(stdout,"table created successfully\n");
    }
    sqlite3_free(zErrMsg);
    return 0;
}
//记录的插入
int insertRecord(sqlite3 *db,listlink node,char classname[]){
    char sql[200] = "insert into ",str[200];
    char *zErrMsg = 0;
    int rc;
    node_to_str(node,str);
    strcat(sql, classname);
    strcat(sql, " values(");
    strcat(sql,str);
    strcat(sql,")");
    rc = sqlite3_exec(db,sql,NULL,0,&zErrMsg);
    if(rc != SQLITE_OK){
        fprintf(stderr,"插入记录失败!\n");
        sqlite3_free(zErrMsg);
        return -1;
    }
    sqlite3_free(zErrMsg);
    return 0;
}
//记录的查询,获取所有的记录,传递给链表
int getRecord(sqlite3 *db, char className[],listlink head){
    char sql[200]="select * from ";
    strcat(sql,className);
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_exec(db,sql,sqlite_callback,head,&zErrMsg);
    if(rc != SQLITE_OK){
        fprintf(stderr,"获取记录失败!\n");
        sqlite3_free(zErrMsg);
        return -1;
    }else{
        fprintf(stdout,"获取记录成功!\n");
        sqlite3_free(zErrMsg);
        return 0;
    }
}
//回调函数
int sqlite_callback(void *fourarg, int argc, char **argv, char **collum){
    listlink head = NULL,node;
    head = (listlink)fourarg;
    if((node = (listlink)malloc(sizeof(listnode))) == NULL){
        fprintf(stderr,"malloc failed!\n");
        return -1;
    }
    node->no = atoi(argv[0]);
    strcpy(node->name, argv[1]);
    strcpy(node->sex, argv[2]);
    strcpy(node->date,argv[3]);
    strcpy(node->address,argv[4]);
    node->score = atof(argv[5]);
    node->next = head->next;
    head->next = node;
    return 0;
}


//获取库中所有表
int Index;
int getTable(sqlite3 *db){
    Index = 1;
    char *zErrMsg = 0;
    char sql[100] = "SELECT name FROM sqlite_master WHERE type ='table' ";
    int rc;
//    rc = sqlite3_get_table(db,sql,&result,&row,&col,&zErrMsg);
    rc = sqlite3_exec(db,sql,table_back,0,&zErrMsg);
    if(rc != SQLITE_OK){
        fprintf(stderr,"获取表名失败!\n");
        sqlite3_free(zErrMsg);
        return -1;
    }
    sqlite3_free(zErrMsg);
    return Index;
}
int table_back(void * pv, int argc, char ** argv, char ** collum){
    printf("|                       %d.%s                            |\n",Index++,argv[0]);
    return 0;
}
//获取第几张表:db数据库引用,H头,num第几张表
char Class[20];//保存获取到的表的名字
char * getNumTable(sqlite3 * db, listlink H, int *num){
    if(H == NULL || num == NULL){
        fprintf(stderr,"无读取空间或选取超出!\n");
        return NULL;
    }
    Index = 1;
    int rc;
    char sql[100] = "SELECT name FROM sqlite_master WHERE type ='table' ";
    char *zErrMsg = 0;
    rc = sqlite3_exec(db,sql,tableName_back,num,&zErrMsg);
    if(rc != SQLITE_OK){
        fprintf(stderr,"获取表名失败!\n");
        sqlite3_free(zErrMsg);
        return NULL;
    }
    getRecord(db,Class,H);

    return Class;
}
int tableName_back(void * pv, int argc, char ** argv, char ** collum){
    int * num = (int*)pv;
    if(*num == Index){
        strcpy(Class,argv[0]);
    }
    Index++;
    return 0;
}
