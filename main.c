


/*
 * main.c
 *
 *  Created on: 2017. 4. 5.
 *      Author: SEONGJAE LEE
 */

#include "Friend-List.h"

int main(void) {


	FILE* fp;				// 파일 포인터

	char fName[22];			// from 정점의 이름을 저장하는 배열
	char tName[22];			// target 정점의 이름을 저장하는 배열
	char uName[22];			// 사용자 이름을 저장하는 배열
	char FName[22];			// 친구 이름을 저장하는 배열


	// 파일 열기(읽기전용)
	if((fp =  fopen(FILENAME, "r")) == NULL) {
		perror(FILENAME);
		system("pause");
		return 0;	
	}

	// 그래프 생성
	graph = createGraph();

	// 파일 내용 읽기
	while (!feof(fp))
	{

		fscanf(fp, "%s %s", fName, tName);

		// 정점 추가(from)(target)
		insertVertex(fName);
		insertVertex(tName);

		// 간선 추가(from, target), (target, from)
		insertEdge(fName, tName);
		insertEdge(tName, fName);

	}
	fclose(fp);

	// 그래프 출력
	printf("\n<전체 친구 목록>\n\n");
	printGraph();
	printf("\n<사용자 인원 : %d>\n\n", graph->nVertexCnt);


	printf("사용자 이름 : ");
	gets(uName);

	pushFriendList(uName);

	printf("\n<내 친구 목록>\n");
	printFriendList(uName);

	printf("\n\n<내 친구의 친구 목록>\n");

	while (top != NULL)
	{
		strcpy_s(FName, sizeof(FName), pop());
		printFriendList(FName);
	}

	printf("\n\n");
	
	system("pause");
	return 0;

}






