#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAMELENGTH 25

typedef struct sub_node{
    char f_name [NAMELENGTH];
    int w_count;
    struct sub_node *link;
}sub_node_t;


typedef struct node{
    char word [NAMELENGTH];
    struct node *link;
    sub_node_t *sub_link;
    int f_count; 
}main_node_t;


typedef struct file_node{
    char f_name[NAMELENGTH];
    struct file_node *link;
}file_node_t;

typedef enum{
    e_success,
    e_failure
}Status;
