#include <stdio.h>
#include "demo.h"
#include <stdlib.h>
#include <string.h>
#include<stdio.h>


void input(stu_info *stu,int len)
{

	for(int i=0;i<len;i++)
	{
		fflush(stdin);
		gets(stu[i].no);
		fflush(stdin);
		gets(stu[i].name);
		fflush(stdin);
		stu[i].gender=getchar();
		scanf("%d%d%d",&stu[i].birthday.year,&stu[i].birthday.month,&stu[i].birthday.day);
	}
}


void output(stu_info *stu,int len)
{

	for(int i=0;i<len;i++)
	{	
		puts((stu+i)->no);	
		puts((stu+i)->name);		
		putchar((stu+i)->gender);
		putchar('\n');
		printf("%d\t%d\t%d\n",stu[i].birthday.year,stu[i].birthday.month,stu[i].birthday.day);
	}
}
void writeFile(stu_info *p,int len)
{
	FILE *fp;
	
	fp=fopen("test.txt","w");

	for(int i=0;i<len;i++)
		fwrite(p,sizeof(stu_info),1,fp);
//	fwrite(p,sizeof(stu_info),len,fp);
	fclose(fp);
}

//将没有头结点的链表写入文件
void saveList(node *head)
{
	FILE *fp=NULL;	
	fp=fopen("list.txt","w");

	if(fp==NULL)
	{
		printf("file open failed,write file failed\n");
		return ;
	}
	while(head!=NULL)
	{
		fwrite(head,sizeof(node),1,fp);
		head = head->next;
	}
	fclose(fp);
}
//从文件中读取数据，用头插法组建没有头结点的新链表
struct node * loadList()
{
	FILE *fp;	
	fp=fopen("list.txt","r");
	struct node *head=NULL;
	struct node *p=NULL;

	if(fp==NULL)
	{
		printf("file open failed,create list failed\n");
		return NULL;
	}

	while(!feof(fp))
	{	
		p=(struct node *) malloc(sizeof(node));
		memset(p,0,sizeof(node));
		if(fread(p,sizeof(node),1,fp)!=0)
		{			
			p->next=head;
			head = p;
		}else
			free(p);
	}
	fclose(fp);

	return head;
}

void modify(struct node *head,char *no)
{
	while(head!=NULL)
	{
		if(strcmp(head->no,no)==0)
		{
			printf("input new name:\n");
			gets(head->name);
		}

		head=head->next;
	}
}



void deleteNode(struct node *head,char *no)
{
	struct node *p=head;
	struct node *p1=NULL;

	while(p!=NULL&&strcmp(p->no,no)==0)
	{
		p1=p->next;	
		free(p);
		p=p1;
	}
	
	while(p->next!=NULL)
	{
		if(strcmp(p->next->no,no)==0)
		{
			p1=p->next;
			p->next=p->next->next;
			free(p1);
		}
		p=p->next;
	}
}

//从文件中读取数据，用尾插法组建新链表
struct node * loadList2()
{
	FILE *fp;	
	fp=fopen("list.txt","r");
	struct node *head=NULL;
	struct node *tail=NULL;
	struct node *p=NULL;
	while(!feof(fp))
	{	
		p=(struct node *) malloc(sizeof( struct node));
		memset(p,0,sizeof( struct node));
		if(fread(p,sizeof(node),1,fp)!=0)
		{
			p->next = NULL;

			if(head==NULL)
			{
				head = p;
				tail = p;
			}else
			{
				tail->next = p;
				tail = p;
			}		
		}else
			free(p);
	}
	fclose(fp);

	return head;
}

void freeList(struct node *head)
{
	struct node *p;
	while(head!=NULL)
	{
		p=head->next;
		free(head);
		head=p;
	}
}
//头插法插入新节点
struct node *insert(struct node *head,struct node *newNode)
{
	newNode->next=head;
	head = newNode;
	return head;
}

//新节点插入有序链表
struct node *insert2(struct node *head,struct node *newNode)
{
	struct node *p=head;

	if(head==NULL)
		return newNode;

	if(strcmp(newNode->no,head->no)<0)
	{
		newNode->next=head;
		return newNode;
	}else
		while(p->next!=NULL)
		{
			if(strcmp(p->next->no,newNode->no)>0)
				break;
				p=p->next;
		}

		newNode->next=p->next;
		p->next=newNode;

	return head;
}



struct node *create()
{
	node *head=NULL;
	node *p=NULL;

	while(1)
	{
		p=(node *)malloc(sizeof(node));

		memset(p,0,sizeof(node));
		printf("please input no:\n");
		fflush(stdin);
		gets(p->no);
		fflush(stdin);
		printf("please input name:\n");
		gets(p->name);

		if(strcmp(p->no,"0")!=0)
		{
			p->next = head;
			head=p;
		}else
		{	
			free(p);
			break;
		}
	}

	return head;
	
}


void inputList(struct node *head)
{
	while(head!=NULL)
	{
		fflush(stdin);
		printf("please input no\n:");
		gets(head->no);
		printf("please input name\n:");
		fflush(stdin);
		gets(head->name);
		head = head->next;
	}
}


void outputList(struct node *head)
{
	while(head!=NULL)
	{
		puts(head->no);
		puts(head->name);
		head = head->next;
	}
}

void readFile(stu_info *p,int len)
{
	FILE *fp;
	
	fp=fopen("test.txt","r");

	while(!feof(fp))
		if(fread(p,sizeof(stu_info),1,fp)!=0)
			p++;

//	fwrite(p,sizeof(stu_info),len,fp);

	fclose(fp);
}



void main()
{
	struct node *list=NULL;

	list = loadList();

	outputList(list);
	
//	saveList(list);

	freeList(list);	
}
