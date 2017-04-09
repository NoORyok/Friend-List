
/*
 * Friend-List.c
 *
 *  Created on: 2017. 4. 5.
 *      Author: SEONGJAE LEE
 */


#include "Friend-List.h"


// ���� ��� PUSH
void push(char* name) {

	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	strcpy_s(newNode->sName, sizeof(newNode->sName), name);
	newNode->link = top;
	top = newNode;
}

// ���� ��� POP
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

// ���� ��� �Լ�
void printStack() {

	StackNode* pStackNode = top;
	printf(" ���� [ ");

	while (pStackNode != NULL)
	{
		printf(" %s ", pStackNode->sName);
		pStackNode = pStackNode->link;
	}

	printf("]\n");
}

// �׷��� ����
Graph* createGraph() {

	// �׷��� �ʱ�ȭ
	Graph* newGraph = (Graph*)malloc(sizeof(Graph));
	newGraph->nVertexCnt = 0;
	newGraph->pVertex = NULL;
	return newGraph;
}

/*
���� ���� �˻� �Լ� : Ž���� ������ �̸��� �Է��Ͽ� �� ������ �ּҸ� ��ȯ�Ѵ�.
���ϰ� 1. NULL(������ ���ų� Ž���� ������ ���) 2. Ž���� ������ �ּ�(Ž�� ����)
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
���� �߰� �Լ� : name�� ������ ������ �߰��Ѵ�.
���ϰ� 1. TRUE(���� �߰� ����) 2. FALSE(���� �߰� ����)
*/
int insertVertex(char* name) {


	VertexNode* vNode;											// �߰��� ������ ������
	VertexNode* pVertex;										// ������ ��ȸ�ϴ� ������

	if (findVertex(name))
		return FALSE;

	// ���� �ʱ�ȭ
	vNode = (VertexNode*)malloc(sizeof(VertexNode));
	graph->nVertexCnt++;

	vNode->visited = FALSE;
	strcpy_s(vNode->vName, sizeof(vNode->vName), name);
	vNode->pEdgeHead = NULL;
	vNode->pNextNode = NULL;

	// ���� ����Ʈ�� �߰�
	if (graph->pVertex == NULL)
		graph->pVertex = vNode;

	// ���� ����Ʈ�� �������� �߰�
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
���� ���� �˻� �Լ� : from�� target ���̿� ���� ������ �˻��Ѵ�.
���ϰ� 1. NULL(������ ���ų� ������ ���� ���) 2. ������ �ּ�(������ �����ϴ� ���)
*/
EdgeNode* findEdge(char* fName, char* tName) {


	VertexNode* pFrom = findVertex(fName);						// from�� ���� �ּ�
	VertexNode* pTarget = findVertex(tName);					// target�� ���� �ּ�
	EdgeNode* pEdge;

	// ���� Ȯ��
	if (!pFrom || !pTarget)
		return NULL;

	// ���� Ȯ��
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
���� �߰� �Լ� : from�� target ���� ���̿� ������ �߰��Ѵ�.
���ϰ� 1. FALSE(������ ���ų� ������ �̹� �����ϴ� ���) 2. TRUE(���� �߰� ����)
*/
int insertEdge(char* fName, char* tName) {

	EdgeNode* pAddEdge;											// �߰��� ������ ������
	VertexNode* pFrom;											// ������ �߰��� from ������ ������
	EdgeNode* pEdge;


	if (findEdge(fName, tName))
		return FALSE;


	// ���� �ʱ�ȭ
	pAddEdge = (EdgeNode*)malloc(sizeof(EdgeNode));
	pAddEdge->pFromVertex = findVertex(fName);
	pAddEdge->pTargetVertex = findVertex(tName);
	pAddEdge->pNextNode = NULL;



	pFrom = pAddEdge->pFromVertex;

	// from ������ ���� ����Ʈ�� �߰�
	if (!pFrom->pEdgeHead)
		pFrom->pEdgeHead = pAddEdge;

	// ���� ����Ʈ�� �������� �߰�
	else
	{
		pEdge = pFrom->pEdgeHead;

		while (pEdge->pNextNode != NULL)
			pEdge = pEdge->pNextNode;

		pEdge->pNextNode = pAddEdge;

	}

	return TRUE;
}


// �׷��� ��� �Լ� : ��� ������ �� ������ ���� ����Ʈ�� ����Ѵ�.
void printGraph() {

	VertexNode* pV = NULL;
	EdgeNode* pE = NULL;

	if (!graph->pVertex)
		printf("�� ���� ����Ʈ\n");

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


// ����� ģ�� push
void pushFriendList(char* uName) {

	VertexNode* uVertex;
	EdgeNode* uEdge;

	// ����� Ž��
	uVertex = findVertex(uName);

	if (uVertex == NULL)
		return;

	// ����� ���� Ž��
	uEdge = uVertex->pEdgeHead;

	// ģ�� ����Ʈ push
	while (uEdge)
	{
		push(uEdge->pTargetVertex->vName);
		uEdge = uEdge->pNextNode;
	}

	// ����� �湮 ǥ��
	uVertex->visited = TRUE;

}

void printFriendList(char* pName) {

	VertexNode* pVertex;
	EdgeNode* pEdge;

	// ����� Ž��
	pVertex = findVertex(pName);


	if (pVertex == NULL) {
		printf("���� ����� �Դϴ�\n\n");
		exit(1);										// ���α׷� ����
	}

	pEdge = pVertex->pEdgeHead;

	// ģ�� ��� ���
	while (pEdge)
	{
		if (pEdge->pTargetVertex->visited == FALSE)		// ���
		{
			printf("\n%s", pEdge->pTargetVertex->vName);
			pEdge->pTargetVertex->visited = TRUE;
		}
		pEdge = pEdge->pNextNode;
	}


}
