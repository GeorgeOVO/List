#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int

//封装带头节点的链表
typedef struct Node
{
	TYPE data;
	struct Node* next;
}Node;

Node* create_node(TYPE data)
{	
	Node* node=malloc(sizeof(Node));
	node->data=data;
	node->next=NULL;
	return node;
}

typedef struct List
{
	Node* head;  //头指针
	Node* tail; //尾指针
	size_t size;  //节点数量
}List;

//创建链表
List* create_list(void)
{
	List* list=malloc(sizeof(List));
	list->head=NULL;
	list->tail=NULL;
	list->size=0;
	return list;
}

//头添加
void add_head_list(List* list,TYPE data)
{
	Node* node=create_node(data);
	if(0==list->size)
	{
		list->tail=node;
	}
	node->next=list->head;
	list->head=node;
	list->size++;
}

//尾添加
void add_tail_list(List* list,TYPE data)
{
	Node* node=create_node(data);
	if(0==list->size)
	{
		list->head=node;
	}
	else
	{
		list->tail->next=node;
	}
	list->tail=node;
	list->size++;
}

//头删除
bool del_head_list(List* list)
{
	if(0==list->size) return false;
	Node* temp=list->head;
	list->head=temp->next;
	free(temp);
	if(1==list->size) list->tail=NULL;
	list->size--;
	return true;
}

//尾删除
bool del_tail_list(List* list)
{
	if(0==list->size) return false;
	if(1==list->size) 
	{
		free(list->tail);
		list->head=NULL;
		list->tail=NULL;
	}
	else
	{
		Node* prev=list->head;
		while(prev->next!=list->tail) prev=prev->next;
		free(list->tail);
		list->tail=prev;
		list->tail->next=NULL;
	}
	list->size--;
	return true;
}

//插入
bool insert_list(List* list,size_t index,TYPE data)
{
	if(index>list->size) return false;
	if(0==index)
	{
		add_head_list(list,data);
		return true;
	}
	if(index==list->size)
	{  	
		add_tail_list(list,data);
		return true;
	}
	Node* node=create_node(data);
	Node* prev=list->head;
	for(int i=1;i<index;i++,prev=prev->next);
	node->next=prev->next;
	prev->next=node;
	list->size++;
	return true;
}

//按值删除
bool del_value_list(List* list,TYPE data)
{
	if(0==list->size) return false;
	if(data==list->head->data) return del_head_list(list);
	if(data==list->tail->data) return del_tail_list(list);

	for(Node* prev=list->head;prev->next;prev=prev->next)
	{
		if(data==prev->next->data)
		{
			Node* temp=prev->next;
			prev->next=temp->next;
			free(temp);
			list->size--;
			return true;
		}
	}
	return false;
}

//按位置删除
bool del_index_list(List* list,size_t index)
{
	if(index>=list->size) return false;
   	if(0==index) return del_head_list(list);
	if(list->size-1==index) return del_tail_list(list);
	
	Node* prev=list->head;
	for(int i=1;i<index;i++,prev=prev->next);
	Node* temp=prev->next;
	prev->next=temp->next;
	free(temp);
	list->size--;
	return true;
}

//按位置修改
bool modify_index_list(List* list,size_t index,TYPE val)
{
	if(index>=list->size) return false;
	Node* node=list->head;
	for(int i=0;i<index;i++,node=node->next);
	node->data=val;
	return true;	
}

//按值全部修改  返回修改次数
int modify_value_list(List* list,TYPE old,TYPE val)
{
	Node* node=list->head;
	int cnt=0;
	while(old!=node->data&&node!=NULL)
	{
		node=node->next;
		if(old==node->data)
		{
			node->data=val;
			node=node->next;
			cnt++;
		}
	}
	return cnt;
}

//访问
bool access_list(List* list,size_t index,TYPE* val)
{
	if(index>=list->size) return false;
	Node* node=list->head;
	for(int i=0;i<index;i++,node=node->next);
	*val=node->data;
	return true;
}

//查询
int query_list(List* list,TYPE data)
{	
	int cnt=0;
	for(Node* node=list->head;node;node=node->next)
	{
		if(data==node->data) cnt++;
	}
	return cnt;
}

//排序
void sort_list(List* list)
{
	for(Node* i=list->head;NULL==i->next->next;i=i->next)
	{
		for(Node* j=i->next;j;j=j->next)
		{
			if(i->data>j->data)
			{
				TYPE temp=i->data;
				i->data=j->data;
				j->data=temp;
			}
		}
	}
}

//清空
void clear_list(List* list)
{
	Node* node=list->head;
	while(node!=NULL)
	{
		node->data=0;
		node=node->next;
	}
}

//销毁
void destroy_list(List* list)
{
	while(del_head_list(list));
	free(list);
}

//遍历
void show_list(List* list)
{
	for(Node* n=list->head;n;n=n->next)
	{
		printf("%d ",n->data);
	}
	printf("\n");
}

int main(int argc,const char* argv[])
{	
	List* list=create_list();
	for(int i=0;i<10;i++)
	{
		add_tail_list(list,i+1);
	}
	show_list(list);
	del_head_list(list);
	del_tail_list(list);
	show_list(list);
	return 0;
}
