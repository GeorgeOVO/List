#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int 

//封装双链表


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

//设计双向链表结构
typedef struct DoubleList
{
	Node* head;  //头指针
	size_t size;  //节点数量
}DoubleList;

// _开头的都是依赖函数  在n1与n2之间插入data节点
static void _addr_node(Node* n1,Node* n2,TYPE data)
{
	Node* node=create_node(data);
	node->next=n2;
	node->prev=n1;
	n1->next=node;
	n2->prev=node;
}

//删除某个节点  依赖函数
static void _del_node(Node* node)
{
	node->prev->next=node->next;
	node->next->prev=node->prev;
	free(node);
}

//在链表中找index位置的节点  依赖函数
Node* _index_list(DoubleList* list,size_t index)
{
	if(index>=list->size)	return NULL;
	if(index<list->size/2)
	{
		//从前往后
		Node* n=list->head->next;
		while(index--) n=n->next;
		return n;
	}
	else
	{
		//从后往前
		Node* n=list->head->prev;
		while(++index < list->size) n=n->prev;
		return n;
	}
}

// 按值访问节点 依赖函数
Node* _value_list(DoubleList* list,TYPE data)
{
	if(0 == list->size) return NULL;
	for(Node* n = list->head->next;n != list->head;n = n->next)
	{
		if(data == n->data) return n;
	}
	return NULL;
}

//创建双链表结构
DoubleList* create_double_list(void)
{
	DoubleList* list=malloc(sizeof(DoubleList));
	list->head=create_node(0);
	list->size=0;
	return list;
}


//头添加
void add_head_list(DoubleList* list,TYPE data)
{
	_addr_node(list->head,list->head->next,data);
	list->size++;
}
//尾添加
void add_tail_list(DoubleList* list,TYPE data)
{
	_addr_node(list->head->prev,list->head,data);
	list->size++;
}
//插入
bool insert_list(DoubleList* list,size_t index,TYPE data)
{
	if(index>list->size) return false;
	Node* n=list->head;
	for(int i=0;i<index;i++,n=n->next);
	_addr_node(n,n->next,data);
	list->size++;
	return true;
}
//按位置删除
bool del_index_list(DoubleList* list,size_t index)
{
	Node* n=_index_list (list,index);
	if(NULL==n) return false;
	_del_node(n);
	list->size--;
	return true;
}
//按值删除
bool del_value_list(DoubleList* list,TYPE data)
{
	/*for(Node* n=list->head->next;n!=list->head;n=n->next)
	{
		if(data==n->data)
		{
			_del_node(n);
			list->size--;
			return true;
		}
	}
	return false;*/
	Node* n =_value_list(list,data);
	if(NULL = n) return false;
	_del_node(n);
	list->size--;
	return true;
}
//按位置修改
bool modify_index_list(DoubleList* list,size_t index,TYPE data)
{
	Node* n=_index_list(list,index);
	if(NULL==n) return false;
	n->data=data;
	return true;
}
//按值全部修改
int modify_value_list(DoubleList* list,TYPE old,TYPE data)
{	
	int cnt=0;
	for(Node* n=list->head->next;n!=list->head;n=n->next)
	{
		if(old==n->data)
		{
			n->data=data;
			cnt++;
		}
	}
	return cnt;
}
//访问
bool access_list(DoubleList* list,size_t index,TYPE* val)
{
	Node* n=_index_list(list,index);
	if(NULL==n) return false;
	*val=n->data;
	return true;
}
//查询
int query_list(DoubleList* list,TYPE data)
{
	int cnt=0;
	for(Node* n=list->head->next;n!=list->head;n=n->next)
	{
		if(data==n->data) cnt++;
	}
	return cnt;
}
//排序
void sort_list(DoubleList* list)
{
	for(Node* i=list->head->next;i=list->head->prev->prev;i=i->next)
	{
		for(Node* j=i->next;j!=list->head;j=j->next)
		{
			if(i->data>j->data)
			{
				int temp=i->data;
				i->data=j->data;
				j->data=temp;
			}
		}
	}
}
//遍历
void show_list(DoubleList* list)
{
	for(Node* n=list->head->next;n!=list->head;n=n->next)
	{
		printf("%d ",n->data);
	}
	printf("\n");
}
//清空
void clear_list(DoubleList* list)
{
	list->size=0;
}
//销毁
void destroy_list(DoubleList* list)
{
	while(list->head) free(list->head);
	free(list);
}

int main(int argc,const char* argv[])
{
	DoubleList* list=create_double_list();
	for(int i=0;i<10;i++)
	{
		int num=rand()%100;
		printf("%d ",num);
		add_head_list(list,num);
	}
	printf("\n--------------------------\n");
	show_list(list);
	return 0;
}
