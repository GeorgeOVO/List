#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int

typedef struct ArrayStack
{
	TYPE* ptr;	//存储元素首地址
	size_t cal; //容量
	size_t top; //栈顶位置
}ArrayStack;

// 创建
ArrayStack* create_array_stack(size_t cal)
{
	ArrayStack* stack=malloc(sizeof(ArrayStack));
	stack->ptr=malloc(sizeof(TYPE)*cal);
	stack->cal=cal;
	stack->top=0;
	return stack;
}

//栈满
bool full_array_stack(ArrayStack* stack)
{
	return stack->top==stack->cal;
}

//栈空
bool empty_array_stack(ArrayStack* stack)
{
	return 0==stack->top;
}

//入栈
bool push_array_stack(ArrayStack* stack,TYPE data)
{
	if(full_array_stack(stack)) return false;
	stack->ptr[stack->top++]=data;
	return true;
}

//查看栈顶元素
TYPE top_array_stack(ArrayStack* stack)
{
   if(!empty_array_stack(stack)) return stack->ptr[stack->top-1];
}

//出栈
bool pop_array_stack(ArrayStack* stack)
{
	if(empty_array_stack(stack)) return false;
	stack->top--;
	return true;
}

//销毁
void destroy_array_stack(ArrayStack* stack)
{
	free(stack->ptr);
	free(stack);
}

//判断是否出栈顺序
bool is_pop_stack(const int* a,const int* b,size_t len)
{
	//创建栈
	ArrayStack* stack=create_array_stack(len);
	//按照a的顺序入栈
	for(int i=0,j=0;i<len;i++)
	{
		push_array_stack(stack,a[i]);
		//按照b的顺序尝试出栈
		while(!empty_array_stack(stack)&&b[j]==top_array_stack(stack))
		{
			pop_array_stack(stack);
			j++;
		}
	}
	bool flag=empty_array_stack(stack);
	destroy_array_stack(stack);
	return flag;
}

/*使用两个栈 模拟队列功能*/
typedef struct Queue
{
	ArrayStack* s1;
	ArrayStack* s2;
}Queue;

//创建队列
Queue* create_queue(size_t cal)
{
	Queue* queue=malloc(sizeof(Queue));
	queue->s1=create_array_stack(cal);
	queue->s2=create_array_stack(cal);
	return queue;
}

//入队
bool push_queue(Queue* queue,TYPE val)
{
	if(full_array_stack(queue->s1))
	{
		if(!empty_array_stack(queue->s2)) return false;

		while(!empty_array_stack(queue->s1))
		{
			TYPE top=top_array_stack(queue->s1);
			pop_array_stack(queue->s1);
			push_array_stack(queue->s2,top);
		}
	}
	printf("rear:%d\n",val);
	return push_array_stack(queue->s1,val);	
	/*if(!full_array_stack(queue->s1)) return push_array_stack(queue->s1,val);
	if(full_array_stack(queue->s1))
	{
		if(!empty_array_stack(queue->s2)) return false;
		else
		{
			while(!empty_array_stack(queue->s1))
			{
				TYPE res = top_array_stack(queue->s1);
				pop_array_stack(queue->s1);
				push_array_stack(queue->s2,res);
			}
		}
		return push_array_stack(queue->s1,val);
	}*/
}

//出队
bool pop_queue(Queue* queue)
{
	if(empty_array_stack(queue->s2))
	{
		if(empty_array_stack(queue->s1)) return false;

		while(!empty_array_stack(queue->s1))
		{
			TYPE top=top_array_stack(queue->s1);
			pop_array_stack(queue->s1);
			push_array_stack(queue->s2,top);
		}
	}
	TYPE top=top_array_stack(queue->s2);
	printf("front:%d\n",top);
	return pop_array_stack(queue->s2);
	/*if(!empty_array_stack(queue->s2)) return pop_array_stack(queue->s2);
	if(empty_array_stack(queue->s2))
	{
		if(empty_array_stack(queue->s1)) return false;
		else
		{
			while(!empty_array_stack(queue->s1))
			{
				TYPE res = top_array_stack(queue->s1);
				pop_array_stack(queue->s1);
				push_array_stack(queue->s2,res);
			}
		}
		return pop_array_stack(queue->s2);
	}*/
}

int main(int argc,const char* argv[])
{
	Queue* queue=create_queue(5);
	for(int i=0;i<10;i++)
	{
		push_queue(queue,i+1);
	}
	for(int i=0;i<10;i++)
	{
		pop_queue(queue);
	}
	return 0;
}
