


/*
 * main.c
 *
 *  Created on: 2017. 4. 5.
 *      Author: SEONGJAE LEE
 */

#include "Friend-List.h"

int main(void) {


	FILE* fp;				// ���� ������

	char fName[22];			// from ������ �̸��� �����ϴ� �迭
	char tName[22];			// target ������ �̸��� �����ϴ� �迭
	char uName[22];			// ����� �̸��� �����ϴ� �迭
	char FName[22];			// ģ�� �̸��� �����ϴ� �迭


	// ���� ����(�б�����)
	if((fp =  fopen(FILENAME, "r")) == NULL) {
		perror(FILENAME);
		system("pause");
		return 0;	
	}

	// �׷��� ����
	graph = createGraph();

	// ���� ���� �б�
	while (!feof(fp))
	{

		fscanf(fp, "%s %s", fName, tName);

		// ���� �߰�(from)(target)
		insertVertex(fName);
		insertVertex(tName);

		// ���� �߰�(from, target), (target, from)
		insertEdge(fName, tName);
		insertEdge(tName, fName);

	}
	fclose(fp);

	// �׷��� ���
	printf("\n<��ü ģ�� ���>\n\n");
	printGraph();
	printf("\n<����� �ο� : %d>\n\n", graph->nVertexCnt);


	printf("����� �̸� : ");
	gets(uName);

	pushFriendList(uName);

	printf("\n<�� ģ�� ���>\n");
	printFriendList(uName);

	printf("\n\n<�� ģ���� ģ�� ���>\n");

	while (top != NULL)
	{
		strcpy_s(FName, sizeof(FName), pop());
		printFriendList(FName);
	}

	printf("\n\n");
	
	system("pause");
	return 0;

}






