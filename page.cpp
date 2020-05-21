#include "function.h"

void mainPage(sqlite3 *db, listlink H){
    system("clear");
    printf("--------------------------------------------------------------\n");
    printf("|                       学生管理系统                         |\n");
    printf("|                      按提示选择功能                        |\n");
    printf("|                       1.创建班级                           |\n");
    printf("|                       2.查看班级                           |\n");
    printf("|                       3.退出                               |\n");
    printf("--------------------------------------------------------------\n");
    int n;
    while(1){
        printf("请选择：");
        scanf("%d",&n);
        switch(n){
            case 1:createPage(db,H);break;
            case 2:readPage(db,H);break;
            case 3:exit(0);
            default:printf("不是正确选项！请重新选择:");
                scanf("%d",&n);break;
        }
    }
}
//创建班级
void createPage(sqlite3 * db,listlink H){
    system("clear");
    int classmatesNum;//功能选择器,同学人数,录入状态
    printf("请输入班级人数:");
    scanf("%d",&classmatesNum);
    if(insertMore(H,classmatesNum) != 0){
        fprintf(stderr,"信息插入失败!\n");
        return ;
    }else{
        fprintf(stdout,"信息插入成功!请输入要保存的班级名称:");
    }
    char className[20];
    scanf("%s",className);
    if(savaDatabase(db,H,className) == 0){
        fprintf(stdout,"所有记录保存成功!\n");
    }else{
        fprintf(stderr,"记录保存失败!请注意警示信息!\n");
    }
    transit(db,H,mainPage);
}
//班级读取
void readPage(sqlite3 *db,listlink H){
    system("clear");
    int Selector,total;
    printf("--------------------------------------------------------------\n");
    printf("|                已创建班级如下,按序号查看                   |\n");
    total = getTable(db);
    printf("|                       %d.返回                               |\n",total);
    printf("--------------------------------------------------------------\n");
    printf("请输入:");
    //按下序号获取到指定的班级数据表内容,然后对应着给链表填入信息
    scanf("%d",&Selector);
    if(Selector == total){
        mainPage(db,H);
        exit(0);    }
    if(Selector > total){fprintf(stderr,"不是正确选项.\n");transit(db,H,mainPage);return ;}
    char * className = getNumTable(db,H,&Selector);
    if(className == NULL){
        fprintf(stderr,"读取失败,请注意警示信息!\n");
        return;
    }
    sort(H);
    show(H);
    printf("你可以进行如下的表操作(按键进入):\n");
    tableOperte(db,H,className);
    transit(db,H,mainPage);
}
//表操作
void tableOperte(sqlite3 * db,listlink H,char * className){
    printf("1.添加信息 2.删除信息 3.查找信息 4.返回上级 '任意键'退出\n");
    char selector = 49;
    char sl = 49;
    printf("请选择:");
    fflush(stdin);
    getchar();
    scanf("%c",&selector);
    if(selector == '1'){
        if(insertOne(H) == 0) {
            fprintf(stdout, "添加成功!记录如下:\n");
            sort(H);
            show(H);
            printf("默认或按1覆盖,其他则否,是否覆盖:");
            fflush(stdin);
            getchar();
            scanf("%c",&sl);
            if (sl == '1' || sl == '\n') {
                if (savaDatabase(db, H, className) == 0) {
                    fprintf(stdout, "覆盖成功!\n");
                    transit(db,H,readPage);
                } else {
                    fprintf(stderr, "覆盖失败!注意警示信息!\n");
                    return;
                }
            }else{
                fprintf(stdout,"不覆盖,信息即被丢弃!\n");
                return ;
            }
        }
    }else if(selector == '2'){
        printf("目前仅支持提供学号进行删除,请输入要删除的学号:");
        int no;
        scanf("%d",&no);
        if(deleteNo(H,no) == 0){
            fprintf(stdout,"删除成功!记录如下\n");
            sort(H);
            show(H);
            printf("默认或按1覆盖,其他则否,是否覆盖:");
            fflush(stdin);
            getchar();
            sl = getchar();
            if (sl == '1' || sl == '\n') {
                if (savaDatabase(db, H, className) == 0) {
                    fprintf(stdout, "覆盖成功!\n");
                    transit(db,H,readPage);
                } else {
                    fprintf(stderr, "覆盖失败!注意警示信息!\n");
                    return;
                }
            }
        }
    }else if(selector == '3'){
        printf("1.学号查找(默认) 2.姓名查找 3.分数条件查找 '任意键'退出\n请选择:");
        char innersele = 49;
        fflush(stdin);
        getchar();
        innersele = getchar();
        if(innersele == 49 || innersele == '\n'){
            printf("请输入学号:");
            int no;
            scanf("%d",&no);
            listlink node = selectNo(H,no);
            if(node){
                inModi(db,H,className,node,1);
                transit(db,H,readPage);
            }else{
                fprintf(stderr,"查找失败!未找到记录!\n");
                return ;
            }
        }else if(innersele == 50){
            printf("请输入姓名:");
            char name[10];
            scanf("%s",name);
            listlink node = selectName(H,name);
            if(node){
                inModi(db,H,className,node,1);
                transit(db,H,readPage);
            }else{
                fprintf(stderr,"查找失败!未找到记录!\n");
                return ;
            }
        }else if(innersele == 51){
            printf("1.大于 2.大于等于 3.小于 4.小于等于 5.完全等 6.介于 7.两边站  '任意键'退出\n请选择:");
            char x;
            fflush(stdin);
            getchar();
            x = getchar();
            float num1,num2;
            listlink link;
            if(x >= '6'){
                printf("请输入两个数确定查找的范围:");
                scanf("%f%f",&num1,&num2);
                link = selectScoreRequirement(H,num1,num2,x);
                if(link){
                    inModi(db,H,className,link,0);
                    transit(db,H,readPage);
                }else{
                    fprintf(stderr,"查找失败!未找到记录!");
                    return ;
                }
            }else if (x >= '1' && x <= '5'){
                printf("请输入一个数确定查找的界值:");
                scanf("%f",&num1);
                link = selectScoreRequirement(H,num1,0,x);
                if(link){
                    inModi(db,H,className,link,0);
                    transit(db,H,readPage);
                }else{
                    fprintf(stderr,"查找失败!未找到记录!");
                    return ;
                }
            }
        }else{
            printf("选择退出\n");
            return;
        }
    }else if(selector == '4') {
        readPage(db, H);
        return;
    }else{
        printf("选择退出\n");
        return;
    }
}

//修改选项
void inModi(sqlite3 * db,listlink H,char * className,listlink node,int pos){
    char sl = 49;
    fprintf(stdout,"找到了!记录如下:\n");
    print(pos,node);
    if(pos == 0){
        fprintf(stdout,"仅可查询出结果,无法进行修改!\n");
        transit(db,H,readPage);
        return ;
    }
    if(modifyInformation(node) == 0){
        fprintf(stdout,"修改成功!记录如下:\n");
       print(pos,node);
        printf("默认或按1覆盖,其他则否,是否覆盖:");
        fflush(stdin);
        getchar();
        sl = getchar();
        if (sl == '1' || sl =='\n') {
            if (savaDatabase(db, H, className) == 0) {
                fprintf(stdout, "覆盖成功!\n");
                return;
            } else {
                fprintf(stderr, "覆盖失败!注意警示信息!\n");
                return;
            }
        }
    }else{
        fprintf(stderr,"未选择修改\n");
        return ;
    }
}
//打印方式
void print(int pos,listlink node){
    if(pos == 1){
        shownode(node);
    }else{
        show(node);
    }
}
//页面过渡
void transit(sqlite3 *db, listlink H,method p){
    if(release(H) == 0){
        fprintf(stdout,"空间释放完毕!\n");
    }else{
        fprintf(stderr,"空间释放失败!\n");
    }
    printf("1.回到主界面 2.回到上一级 3. 退出程序\n请选择:");
    int x;
    scanf("%d",&x);
    while(true){
        if(x == 1){
            mainPage(db,H);
        }else if(x == 2){
            p(db,H);
        }else if(x == 3){
            exit(0);
        }else{
            fprintf(stderr,"不是正确的选项,请重选:");
            scanf("%d",&x);
        }
    }
}