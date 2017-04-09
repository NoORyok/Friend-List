
/*
 * Friend-List.c
 *
 *  Created on: 2017. 4. 5.
 *      Author: SEONGJAE LEE
 */


#include "Friend-List.h"


// 스택 노드 PUSH
void push(char* name) {

	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	strcpy_s(newNode->sName, sizeof(newNode->sName), name);
	newNode->link = top;
	top = newNode;
}

// 스택 노드 POP
char* pop() {

	static char pName[22];
	StackNode* popNode = top;

	if (top == NULL)
		return NULL;
	else
	{
		strcpy_s(pName, sizeof(pName), popNode->sName);
		top = top->link;
		free(popNode);
	}

	return pName;
}

// 스택 출력 함수
void printStack() {

	StackNode* pStackNode = top;
	printf(" 스택 [ ");

	while (pStackNode != NULL)
	{
		printf(" %s ", pStackNode->sName);
		pStackNode = pStackNode->link;
	}

	printf("]\n");
}

// 그래프 생성
Graph* createGraph() {

	// 그래프 초기화
	Graph* newGraph = (Graph*)malloc(sizeof(Graph));
	newGraph->nVertexCnt = 0;
	newGraph->pVertex = NULL;
	return newGraph;
}

/*
정점 유무 검사 함수 : 탐색할 정점의 이름을 입력하여 그 정점의 주소를 반환한다.
리턴값 1. NULL(정점이 없거나 탐색을 실패할 경우) 2. 탐색할 정점의 주소(탐색 성공)
*/
VertexNode* findVertex(char* name) {


	VertexNode* v = graph->pVertex;

	if (!v)	return NULL;

	while (v)
	{
		if (!strcmp(v->vName, name))
			break;
		else v = v->pNextNode;
	}


	return v;
}

/*
정점 추가 함수 : name을 가지는 정점을 추가한다.
리턴값 1. TRUE(정점 추가 성공) 2. FALSE(정점 추가 실패)
*/
int insertVertex(char* name) {


	VertexNode* vNode;											// 추가할 정점의 포인터
	VertexNode* pVertex;										// 정점을 순회하는 포인터

	if (findVertex(name))
		return FALSE;

	// 정점 초기화
	vNode = (VertexNode*)malloc(sizeof(VertexNode));
	graph->nVertexCnt++;

	vNode->visited = FALSE;
	strcpy_s(vNode->vName, sizeof(vNode->vName), name);
	vNode->pEdgeHead = NULL;
	vNode->pNextNode = NULL;

	// 정점 리스트에 추가
	if (graph->pVertex == NULL)
		graph->pVertex = vNode;

	// 정점 리스트의 마지막에 추가
	else
	{
		pVertex = graph->pVertex;


		while (pVertex->pNextNode != NULL)
			pVertex = pVertex->pNextNode;

		pVertex->pNextNode = vNode;
	}

	return TRUE;
}

/*
간선 유무 검사 함수 : from과 target 사이에 간선 유무를 검사한다.
리턴값 1. NULL(정점이 없거나 간선이 없는 경우) 2. 간선의 주소(간선이 존재하는 경우)
*/
EdgeNode* findEdge(char* fName, char* tName) {


	VertexNode* pFrom = findVertex(fName);						// from의 정점 주소
	VertexNode* pTarget = findVertex(tName);					// target의 정점 주소
	EdgeNode* pEdge;

	// 정점 확인
	if (!pFrom || !pTarget)
		return NULL;

	// 간선 확인
	pEdge = pFrom->pEdgeHead;
	while (pEdge)
	{
		if ((!strcmp(pEdge->pFromVertex->vName, fName)) && (!strcmp(pEdge->pTargetVertex->vName, tName)))
			return pEdge;
		else pEdge = pEdge->pNextNode;
	}

	return NULL;
}

/*
간선 추가 함수 : from과 target 정점 사이에 간선을 추가한다.
리턴값 1. FALSE(정점이 없거나 간선이 이미 존재하는 경우) 2. TRUE(간선 추가 성공)
*/
int insertEdge(char* fName, char* tName) {

	EdgeNode* pAddEdge;											// 추가할 간선의 포인터
	VertexNode* pFrom;											// 간선을 추가할 from 정점의 포인터
	EdgeNode* pEdge;


	if (findEdge(fName, tName))
		return FALSE;


	// 간선 초기화
	pAddEdge = (EdgeNode*)malloc(sizeof(EdgeNode));
	pAddEdge->pFromVertex = findVertex(fName);
	pAddEdge->pTargetVertex = findVertex(tName);
	pAddEdge->pNextNode = NULL;



	pFrom = pAddEdge->pFromVertex;

	// from 정점의 간선 리스트에 추가
	if (!pFrom->pEdgeHead)
		pFrom->pEdgeHead = pAddEdge;

	// 간선 리스트의 마지막에 추가
	else
	{
		pEdge = pFrom->pEdgeHead;

		while (pEdge->pNextNode != NULL)
			pEdge = pEdge->pNextNode;

		pEdge->pNextNode = pAddEdge;

	}

	return TRUE;
}


// 그래프 출력 함수 : 모든 정점과 그 정점의 간선 리스트를 출력한다.
void printGraph() {

	VertexNode* pV = NULL;
	EdgeNode* pE = NULL;

	if (!graph->pVertex)
		printf("빈 정점 리스트\n");

	pV = graph->pVertex;

	while (pV)
	{
		printf("%s : ", pV->vName);
		pE = pV->pEdgeHead;

		while (pE)
		{
			printf("%s ", pE->pTargetVertex->vName);
			pE = pE->pNextNode;
		}
		printf("\n");
		pV = pV->pNextNode;
	}
}


// 사용자 친구 push
void pushFriendList(char* uName) {

	VertexNode* uVertex;
	EdgeNode* uEdge;

	// 사용자 탐색
	uVertex = findVertex(uName);

	if (uVertex == NULL)
		return;

	// 사용자 간선 탐색
	uEdge = uVertex->pEdgeHead;

	// 친구 리스트 push
	while (uEdge)
	{
		push(uEdge->pTargetVertex->vName);
		uEdge = uEdge->pNextNode;
	}

	// 사용자 방문 표시
	uVertex->visited = TRUE;

}

void printFriendList(char* pName) {

	VertexNode* pVertex;
	EdgeNode* pEdge;

	// 사용자 탐색
	pVertex = findVertex(pName);


	if (pVertex == NULL) {
		printf("없는 사용자 입니다\n\n");
		exit(1);										// 프로그램 종료
	}

	pEdge = pVertex->pEdgeHead;

	// 친구 목록 출력
	while (pEdge)
	{
		if (pEdge->pTargetVertex->visited == FALSE)		// 출력
		{
			printf("\n%s", pEdge->pTargetVertex->vName);
			pEdge->pTargetVertex->visited = TRUE;
		}
		pEdge = pEdge->pNextNode;
	}


}
