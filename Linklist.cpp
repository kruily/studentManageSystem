
/*
	链表操作
*/
#include "struct.h"
#include "function.h"

//创建空班级
listlink createClass(){
    listlink H;
    if((H = (listlink)malloc(sizeof(listnode))) == NULL){
        printf("malloc failed!\n");
    }
    H->next = NULL;
    return H;
}
//单条信息插入
int insertOne(listlink H){
    listlink head,node;
    head = H;
    if((node = (listlink)malloc(sizeof(listnode))) == NULL){
        printf("malloc failed!\n");
        return -1;
    }
    printf("请按提示输入信息：\n");
    printf("请输入学号：");
    scanf("%d",&node->no);
    printf("请输入姓名：");
    scanf("%s",node->name);
    printf("请输入性别：");
    scanf("%s",node->sex);
    printf("请输入出生日期(以xxxx/xx/xx): ");
    scanf("%s",node->date);
    printf("请输入籍贯：");
    scanf("%s",node->address);
    printf("请输入入学成绩：");
    scanf("%f",&node->score);
    node->next = head->next;
    head->next= node;
    return 0;
}
//插入多条信息
int insertMore(listlink H, int num){
    listlink head;
    head = H;
    int i;
    for(i = 0; i < num; i++){
        if(insertOne(head) == -1){
            printf("插入失败\n");
            return -1;
        }
        head = head->next;
    }
    if(i >= num){
        printf("数据输入完成！\n");
        return 0;
    }else{
        printf("数据插入误差！\n");
        return -1;
    }
}

//按学号查找
listlink selectNo(listlink H,int No){
    listlink head;
    head = H;
    if(head == NULL || head->next == NULL){
        printf("不是正确的查找班级！\n");
        return NULL;
    }
    head = head->next;
    while(head){
        if(head->no == No){
            return head;
        }
        head = head->next;
    }
    if(head->next == NULL){
        printf("未查找到该信息，查找条件可能有误！\n");
        return NULL;
    }
    return NULL;
}
//按姓名查找
listlink selectName(listlink H, char * Name){
    listlink head;
    head = H;
    if(head == NULL){
        printf("不是正确的查找班级!\n");
        return NULL;
    }
    head = head->next;
    while(head){
        if(strcmp(head->name,Name) == 0){
            return head;
        }
        head = head->next;
    }
    if(head->next == NULL){
        printf("未查找到该信息，查找条件可能有误！\n");
        return NULL;
    }
    return NULL;
}
//按分数条件查找
listlink selectScoreRequirement(listlink H,float s1,float s2,int req){
    listlink head,link,node;
    head = H->next;
    if((link = (listlink)malloc(sizeof(listnode))) == NULL){
        printf("malloc failed!\n");
        return NULL;
    }
    link->next = NULL;
    switch(req){
        case '1':while(head){//大于
                if(head->score > s1){
                    if((node = (listlink)malloc(sizeof(listnode))) == NULL){
                        printf("malloc faied!\n");
                        return link;
                    }
                    node->no = head->no;
                    strcpy(node->name,head->name);
                    strcpy(node->sex,head->sex);
                    strcpy(node->date,head->date);
                    strcpy(node->address,head->address);
                    node->score = head->score;
                    node->next = link->next;
                    link->next = node;
                }
                head = head->next;
            }
            if(head == NULL && link->next == NULL){
                printf("没有查找到信息, 查找条件可能过大！\n");
                return link;
            }else{
                return link;
            }
            break;
        case '2':while(head){//大于等于
                if(head->score >= s1){
                    if((node = (listlink)malloc(sizeof(listnode))) == NULL){
                        printf("malloc failed!\n");
                        return link;
                    }
                    node = head;
                    node->next = link->next;
                    link->next = node;
                }
                head = head->next;
            }
            if(head == NULL && link->next == NULL){
                printf("没有查找到信息, 查找条件可能过大！\n");
                return link;
            }else{
                return link;
            }
            break;
        case '3':while(head){//小于
                if(head->score < s1){
                    if((node = (listlink)malloc(sizeof(listnode))) == NULL){
                        printf("malloc failed!\n");
                        return link;
                    }
                    node = head;
                    node->next= link->next;
                    link->next = node;
                }
                head = head->next;
            }
            if(head == NULL && link->next == NULL){
                printf("没有查找到信息，查找条件可能过小！\n");
                return link;
            }else{
                return link;
            }
            break;
        case '4':while(head){//小于等于
                if(head->score <= s1){
                    if((node = (listlink)malloc(sizeof(listnode))) == NULL){
                        printf("malloc failed!\n");
                        return link;
                    }
                    node = head;
                    node->next= link->next;
                    link->next = node;
                }
                head = head->next;
            }
            if(head == NULL && link->next == NULL){
                printf("没有查找到信息，查找条件可能过小！\n");
                return link;
            }else{
                return link;
            }
            break;
        case '6':while(head){//介于
                if(s1 > s2){
                    s1 = s1+s2;
                    s2 = s1-s2;
                    s1 = s1-s2;
                }
                if(head->score>s1 && head->score<s2){
                    if((node = (listlink)malloc(sizeof(listnode))) == NULL){
                        printf("malloc failed!\n");
                        return link;
                    }
                    node = head;
                    node->next = link->next;
                    link->next = node;
                }
                head = head->next;
            }
            if(head == NULL&&link->next == NULL){
                printf("没有查找到信息，条件范围可能有误！\n");
                return link;
            }else{
                return link;
            }
            break;
        case '7':while(head){//两边站
                if(s1 > s2){
                    s1 = s1+s2;
                    s2 = s1-s2;
                    s1 = s1-s2;
                }
                if(head->score<s1 || head->score>s2){
                    if((node = (listlink)malloc(sizeof(listnode))) == NULL){
                        printf("malloc failed!\n");
                        return link;
                    }
                    node = head;
                    node->next = link->next;
                    link->next = node;
                }
                head = head->next;
            }
            if(head == NULL && link->next == NULL){
                printf("没有查找到信息，条件取值可能是分数极！\n");
                return link;
            }else{
                return link;
            }
            break;
        case '5':while(head){//完全等
                if(head->score == s1){
                    if((node = (listlink)malloc(sizeof(listnode))) == NULL){
                        printf("malloc failed!\n");
                        return link;
                    }
                    node = head;
                    node->next = link->next;
                    link->next = node;
                }
                head = head->next;
            }
            if(head == NULL && link->next == NULL){
                printf("没有查找到信息，条件可能出现各种情况，请自行核实！\n");
                return link;
            }else{
                return link;
            }
            break;
    }
    return link;
}

//按学号删除
int deleteNo(listlink H, int No){
    if(H == NULL){
        printf("不是正确的信息源！\n");
        return -1;
    }
    listlink head, node;
    node = selectNo(H,No);
    head = H;
    while(head){
        if(head->next->no == No){
            break;
        }
        head = head->next;
    }
    head->next = node->next;
    free(node);
    return 0;
}
//修改信息
int modifyInformation(listlink node){
    if(node == NULL){
        printf("节点为空,无法更改!\n");
        return -1;
    }
    char x;
    union{
        int No;
        char Name[20];
        char Sex[5];
        char date[20];
        char Address[100];
        float Score;
    }UN;
    printf("可以对该条信息进行如下操作:");
    printf("请选择你要修改的信息：1.学号 2.姓名 3.性别 4.出生日期 5.籍贯 6.入学成绩 '其他任意键'退出\n请选择：");
    fflush(stdin);
    getchar();
    x = getchar();
    switch(x){
        case 49:printf("请输入需更新数据：");
            scanf("%d",&UN.No);
            node->no = UN.No;
            return 0;
        case 50:printf("请输入需更新数据：");
            scanf("%s",UN.Name);
            strcpy(node->name,UN.Name);
            return 0;
        case 51:printf("请输入需更新数据：");
            scanf("%s",UN.Sex);
            strcpy(node->sex,UN.Sex);
            return 0;
        case 52:printf("请输入需更新数据：");
            scanf("%s",UN.date);
            strcpy(node->date,UN.date);
            return 0;
        case 53:printf("请输入需更新数据：");
            scanf("%s",UN.Address);
            strcpy(node->address,UN.Address);
            return 0;
        case 54:printf("请输入需更新数据：");
            scanf("%f",&UN.Score);
            node->score = UN.Score;
            return 0;
        default:printf("未选择操作!退出\n");
            return -1;
    }
}

//排序
int sort(listlink H){
    if(H == NULL){
        printf("非正常班级！请确认班级是否含有信息！\n");
        return -1;
    }
    listlink head,node,transit;
    node = H->next;
    H->next = NULL;
    while(node){
        transit = node;
        node = node->next;
        head = H;
        while(head->next && head->next->no < transit->no){
            head = head->next;
        }
        transit->next = head->next;
        head->next = transit;
    }
    return 0;
}
//打印信息
int show(listlink H){
    if(H == NULL){
        printf("非正确班级！请检查班级是否含有信息！\n");
        return -1;
    }
    listlink head;
    head = H->next;
    printf("学号    姓名    性别    出生日期	        籍贯               入学成绩\n");
    printf("------------------------------------------------------------------------------\n");
    while(head){
        printf("%-6d\t%-8s\t%-5s\t%-16s\t%-20s\t%.2f\n",head->no,head->name,head->sex,head->date,head->address,head->score);
        printf("------------------------------------------------------------------------------\n");
        head = head->next;
    }
    if(head == NULL){
        printf("信息打印成功！\n");
    }
    return 0;
}
//节点打印
void shownode(listlink node){
    printf("学号    姓名    性别    出生日期	        籍贯               入学成绩\n");
    printf("------------------------------------------------------------------------------\n");
    printf("%-6d\t%-8s\t%-5s\t%-16s\t%-20s\t%.2f\n",node->no,node->name,node->sex,node->date,node->address,node->score);
    printf("------------------------------------------------------------------------------\n");
}
//链表的释放
int release(listlink H){
    if(H == NULL){
        fprintf(stderr,"链表为空,无需释放!\n");
        return -1;
    }
    listlink node;
    while(H){
        node = H->next;
        if(node == NULL){
            H->next =NULL;
            break;
        }
        H->next = H->next->next;
        free(node);
    }
    return 0;
}