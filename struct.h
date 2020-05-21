

#ifndef STUDENTMANAGESYSTEM_STRUCT_H
#define STUDENTMANAGESYSTEM_STRUCT_H

typedef struct student{
    int no;
    char name[20];
    char sex[5];
    char date[20];
    char address[100];
    float score;
    struct student * next;
}listnode,*listlink;

#endif //STUDENTMANAGESYSTEM_STRUCT_H
