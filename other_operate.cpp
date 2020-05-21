
#include "function.h"
//字符串逆置配合int_to_str使用
void str_reverse(char  *str){
    char ch;
    int i,len = strlen(str);
    for(i = 0; i < len/2; i++){
        ch = *(str+i);
        *(str+i) = *(str+len-i-1);
        *(str+len-i-1) = ch;
    }
}
//数字转字符串
void int_to_str(int x, char str[]) {
    int a, i = 0;
    while (x) {
        a = x % 10;
        str[i++] = a + '0';
        x = x / 10;
    }
    str_reverse(str);
}

//node元素转换字符集
void node_to_str(listlink node,char classString[]){
    char str[120] = "";
    char str1[5];
    if(node->no != 0){
        int_to_str(node->no,str1);
        strcat(str,str1);
    }
    strcat(str,",");
    strcat(str,"'");
    strcat(str,node->name);
    strcat(str,"'");
    strcat(str,",");
    strcat(str,"'");
    strcat(str,node->sex);
    strcat(str,"'");
    strcat(str,",");
    strcat(str,"'");
    strcat(str,node->date);
    strcat(str,"'");
    strcat(str,",");
    strcat(str,"'");
    strcat(str,node->address);
    strcat(str,"'");
    strcat(str,",");
    if(node->score != 0) {
        char str2[10];
        sprintf(str2, "%.2f", node->score);
        strcat(str, str2);
    }
    strcpy(classString,str);
}