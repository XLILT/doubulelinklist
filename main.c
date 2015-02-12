#include <stdio.h>
#include <stdlib.h>

#define PRINTMEMALLOCERR printMemoryAllocateError(__FILE__, __func__, __LINE__)

static void printMemoryAllocateError(const char *file_name, const char *func_name, const int line)
{
	printf("Allocate memory failed in function:%s line:%d!!!\n", file_name, func_name, line);
}

typedef struct Node
{
	float x;
	struct Node *next, *ant;
}Node_t, *Node_p, **List_t;

void printList(Node_p head)
{
	Node_p cur_node = head->next;
	while(cur_node != head)
	{
		printf("%f, ", cur_node->x);
		cur_node = cur_node->next;
	}
}

Node_p populateList(char *file_name)
{
	Node_p head = (Node_p)malloc(sizeof(Node_t));
	if(NULL != head)
	{
		head->x = 0;
		head->next = head;
		head->ant = head;
	}
	else
	{
		PRINTMEMALLOCERR;
		return NULL;
	}
	
	if(NULL == file_name)
	{
		return head;
	}

	FILE *f = fopen(file_name, "rt");
	if(NULL == f)
	{       
		printf("cannot open file %s\n", file_name);
		return head;
	}

	float nf = 0;
	Node_p cur_node = head;
	while(fscanf(f, "%f", &nf) == 1)
	{
		cur_node->next = (Node_p)malloc(sizeof(Node_t));
		if(NULL != cur_node->next)
		{
			cur_node->next->x = nf;
			cur_node->next->ant = cur_node;
			cur_node->next->next = head;
			
			cur_node = cur_node->next;
		}
		else
		{
			PRINTMEMALLOCERR;
			break;
		}		
	}

	if(NULL != f)
	{
		fclose(f);
	}

	return head;
}

void destoryList(Node_p head)
{
	if(NULL == head)
	{
		return;
	}

	Node_p cur_node = head->next;
	while(cur_node != head)
	{
		Node_p tmp_node = cur_node->next;
		free(cur_node);
		cur_node = tmp_node;
	}

	free(head);
	head = NULL;
}

void main()
{
	Node_p head = populateList("test.txt");
	printList(head);
	destoryList(head);
}
