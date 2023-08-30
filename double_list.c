#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int 

//演示带头节点的双链表
typedef struct Node
{
	struct Node* prev;  //前驱指针
	TYPE data;
	struct Node* next;  //后继指针
}Node;

Node* create_node(TYPE data)
{
	Node* node=malloc(sizeof(Node));
	node->data=data;
	node->prev=node;
	node->next=node;
	return node;
}

// _开头的都是依赖函数  在n1与n2之间插入data节点
static void _addr_list(Node* n1,Node* n2,TYPE data)
{
	Node* node=create_node(data);
	node->next=n2;
	node->prev=n1;
	n1->next=node;
	n2->prev=node;
}


//头添加
void add_head_list(Node* head,TYPE data)
{
	_addr_list(head,head->next,data);
}
//尾添加
void add_tail_list(Node* head,TYPE data)
{
	_addr_list(head->prev,head,data);
}
//插入
bool insert_list(Node* head,size_t index,TYPE data)
{
	Node* n=head;
	for(int i=0;i<index;i++)
	{
		if(n==head) return false;
		n=n->next;
	}
	_addr_list(n,n->next,data);
	return true;
}

// 删除某一个节点  依赖函数
static void _del_list(Node* node)
{
	node->prev->next=node->next;
	node->next->prev=node->prev;
	free(node);
}
		
//按值删除
bool del_value_list(Node* head,TYPE data)
{
	for(Node* n=head->next;n!=head;n=n->next)
	{
		if(data==n->data)
		{
			_del_list(n);
			return true;
		}
	}
	return false;
}

//按位置删除
bool del_index_list(Node* head,size_t index)
{
	Node* n=head->next;
	if(n==head) return false;
	for(int i=0;i<index;i++)
	{
		n=n->next;
		if(n==head) return false;
	}
	_del_list(n);
	return true;
}

//遍历
void show_list(Node* head)
{
	for(Node* n=head->next;n!=head;n=n->next)
	{
		printf("%d ",n->data);
	}
	printf("\n");
}


int main(int argc,const char* argv[])
{
	Node* head=create_node(0);  //带头节点的
	for(int i=0;i<10;i++)
	{	
		int num=rand()%100;
		printf("%d ",num);
		add_head_list(head,num);
	}
	printf("\n------------------------------\n");
	show_list(head);
	insert_list(head,10,88);
	show_list(head);
	del_value_list(head,88);
	show_list(head);
	return 0;
}
