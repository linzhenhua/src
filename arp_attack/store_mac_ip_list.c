/******************************************************************************
*    > File Name: store_mac_ip_list.c
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2014年04月26日 星期六 22时16分10秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include "arp.h"

/******************************************************************************
 *功能：初始化链表
 *参数：待初始化的链表
 *****************************************************************************/
status linklist_init(linklist *l)
{
    l->head = (position *)malloc(sizeof(struct list_node));
    if(NULL == l->head)
    {
        printf("Memory allocation failure\n");
        return ERROR;
    }
    l->rear = l->head;
    l->rear->next = NULL;
    l->length = 0;

    return OK;
}
/******************************************************************************
 *功能：向链表插入元素
 *参数1：待插入的链表
 *参数2：待插入的元素
 *****************************************************************************/
status linklist_add(linklist *l, const attack_target *x)
{
    position *s;

    s = (position *)malloc(sizeof(struct list_node));
    if(NULL == s)
    {  
        printf("Memory allocation failure\n");
        return ERROR;
    }

    l->length++;

    s->data.flag = l->length;
    memcpy(s->data.mac, x->mac, sizeof(x->mac));
    memcpy(&s->data.ip, &x->ip, sizeof(x->ip));
    s->next = NULL;

    l->rear->next = s;
    l->rear = s;

    return OK;
}
/******************************************************************************
 *功能：遍历链表
 *参数：待遍历的链表
 *****************************************************************************/
status linklist_show(const linklist *l)
{
    position *s = l->head->next;

    while(NULL != s)
    {
        printf("第%d个:\n", s->data.flag);
        printf("mac: %s\n", s->data.mac);
        printf("ip: %s\n", inet_ntoa(s->data.ip));

        s = s->next;
    }

    //printf("链表的当前长度为%d\n", l->length);

    return OK;
}

/******************************************************************************
 *功能：销毁链表
 *参数: 待销毁的链表
 *****************************************************************************/
void linklist_destroy(linklist *l)
{
    position *s = l->head->next;
    position *tmp;

    l->head->next = NULL;
    while(NULL != s)
    {
        tmp = s->next;
        free(s);
        s = tmp;
    }
}

