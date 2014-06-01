/*
	[ 2014학년도 1학기 ] 프로그래밍 연습 - 기말과제
	제  목 : 회원 관리 프로그램
	작성자 : 경규일, 김강원
	※ 최종 수정일 : 2014년 5월 31일 토요일(Ver. 0.1.0.)
*/


/* 헤더 파일 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

#include "UserManagement.h"
#include "UserManagement_Func.h" // 함수 선언


// 메인 함수
int main(void){

	//변수 선언부
	int userCount;
	int option;

	UserInfo userInfo[User_MAX];
	FILE *readFile;
	FILE *writeFile;

	struct tm *t;
	time_t timer;

	// 콘솔창 크기 조정
	system("mode con lines=32 cols=105");

	// 데이터 파일 읽어오기
	readFile = fopen("data.txt", "rt");
	if (readFile == NULL){
		puts("data.txt file error. \n");
		return -1;
	}

	writeFile = fopen("out.txt", "wt");
	if (writeFile == NULL){
		puts("data.txt file error. \n");
		return -1;
	}

	userCount = initData(userInfo, readFile);

	/* 메인 화면 반복 */
	while (1){

		/* 시간 설정 관련 */
		timer = time(NULL);    // 현재 시각을 초 단위로 얻기
		t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기

		/* 0. 메인 페이지 */
		system("cls");

		// 0-(1) 상단부
		RED;
		printf("\n	   NHN NEXT FITNESS CENTER			");
		SKY;
		printf("		 %s\n", timeToString(t));
		YELLOW;
		printf("     ┌─────────────────────────────────────────────┐\n");
		printf("     │                             회원 관리 프로그램 (ver. 0.1.0.)                             │\n");
		printf("     └─────────────────────────────────────────────┘\n\n");
		WHITE;

		// 0-(2) 메뉴 출력부
		printf("		다음 중 사용하실 기능을 선택해주세요. \n\n");
		printf("		   1. 전체 회원 명단 보기 \n");
		printf("		   2. 신규 회원 등록하기 \n");
		printf("		   3. 기존 회원 삭제하기 \n");
		printf("		   4. 기존 회원 정보 수정하기 \n");
		printf("		   5. 기존 회원 검색하기 \n");
		printf("		   6. 변경 내용 저장 및 종료하기 \n");
		printf("		   7. 개발자 정보 보기 \n\n");
		printf("        ────────────────────────────────────────────\n");


		// 0-(3) 메뉴 선택부

		printf("         ◈ 숫자 입력으로 간편하게 이용하실 수 있습니다. : ");
		while (1)
		{
			if (_kbhit())
			{
				option = (getche() - 48); //아스키 코드 값을 정수로 변환 

				switch (option){
				case 1:
					system("cls");
					mainfunc_List(userInfo, readFile, userCount);
					break;
				case 2:
					fclose(readFile);
					system("cls");
					mainfunc_Enroll(userInfo, &userCount);

					readFile = fopen("data.txt", "rt");
					if (readFile == NULL){
						puts("data.txt file error. \n");
						return -1;
					}
					break;
				case 3:
					system("cls");
					mainfunc_Delete();
					break;
				case 4:
					system("cls");
					mainfunc_Modify();
					break;
				case 5:
					system("cls");
					mainfunc_Search();
					break;
				case 6:
					system("cls");
					mainfunc_SaveExit();
					break;
				case 7:
					system("cls");
					mainfunc_Info();
					break;
				default:
					printf("\n\n	    잘못된 입력입니다!");
					printf("\n	    아무 키나 입력하시면 다시 선택하실 수 있습니다. ");
					getche();
				}
				break;
			}
		}

		// 메인 화면 반복 종료
	}

	// file close
	fclose(readFile);
	fclose(writeFile);

	// 리턴 함수
	return 0;
}