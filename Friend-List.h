
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

// 정점 노드 구조체
typedef struct vertexNode {

	char vName[22];					// 정점 데이터
	int visited;
	struct vertexNode* pNextNode;	// 다음 정점을 가리키는 포인터
	struct edgeNode* pEdgeHead;		// 간선 리스트의 헤드 포인터

} VertexNode;

// 간선 노드 구조체
typedef struct edgeNode {

	VertexNode* pFromVertex;		// 간선 리스트의 from 정점 포인터
	VertexNode* pTargetVertex;		// 간선 리스트의 target 정점 포인터

	struct edgeNode* pNextNode;		// 간선 노드 포인터

} EdgeNode;

// 그래프 구조체
typedef struct {

	int nVertexCnt;					// 정점 개수
	VertexNode* pVertex;			// 정점 리스트의 포인터

} Graph;

// 스택 노드 구조체
typedef struct StackNode {
	char sName[22];
	struct StackNode* link;
} StackNode;

// 전역 변수
Graph* graph;
StackNode* top;

// 함수 헤더
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
