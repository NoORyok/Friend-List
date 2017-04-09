
/*
 * Friend-List.h
 *
 *  Created on: 2017. 4. 5.
 *      Author: SEONGJAE LEE
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define vsprintf_s(buf, size, fmt, ...)  vsprintf(buf, fmt, ##__VA_ARGS__)
#define strcpy_s(dst, size, src)         strcpy(dst, src)
#define scanf_s(fmt, size, ...)          scanf(fmt, ##__VA_ARGS__)
#define memmove_s(dst, size, src, count) memmove(dst, src, count)
#define gets_s(buf, size)                gets(buf)

#define printf_s  printf
#define fprintf_s fprintf
#define fscanf_s fscanf
#define sprintf_s snprintf
#define _strdup   strdup

errno_t fopen_s(FILE** fileHandle, const char* fileName, const char *mode);


#define FILENAME "friends.txt"
#define TRUE 1
#define FALSE 0

// ���� ��� ����ü
typedef struct vertexNode {

	char vName[22];					// ���� ������
	int visited;
	struct vertexNode* pNextNode;	// ���� ������ ����Ű�� ������
	struct edgeNode* pEdgeHead;		// ���� ����Ʈ�� ��� ������

} VertexNode;

// ���� ��� ����ü
typedef struct edgeNode {

	VertexNode* pFromVertex;		// ���� ����Ʈ�� from ���� ������
	VertexNode* pTargetVertex;		// ���� ����Ʈ�� target ���� ������

	struct edgeNode* pNextNode;		// ���� ��� ������

} EdgeNode;

// �׷��� ����ü
typedef struct {

	int nVertexCnt;					// ���� ����
	VertexNode* pVertex;			// ���� ����Ʈ�� ������

} Graph;

// ���� ��� ����ü
typedef struct StackNode {
	char sName[22];
	struct StackNode* link;
} StackNode;

// ���� ����
Graph* graph;
StackNode* top;

// �Լ� ���
void push(char* name);
char* pop();
void printStack();
Graph* createGraph();
VertexNode* findVertex(char* name);
int insertVertex(char* name);
EdgeNode* findEdge(char* fName, char* tName);
int insertEdge(char* fName, char* tName);
void printGraph();
void pushFriendList(char* uName);
void printFriendList(char* pName);
