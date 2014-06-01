#include "UserManagement.h"
#include "UserManagement_Func.h"

/* ���������� ����ϴ� �Լ� */

// ������ �ð��� ����ϴ� �Լ�
char* timeToString(struct tm *t) {
	static char s[20];

	sprintf(s, "%04d-%02d-%02d %02d:%02d:%02d",
		t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
		t->tm_hour, t->tm_min, t->tm_sec
		);

	return s;
}

int initData(UserInfo userInfo[], FILE* fp)
{
	int i = 0;
	int count = 0;
	char buffer[256];

	while ((fgets(buffer, sizeof(buffer), fp)) != NULL)
	{
		if (count == 0)
		{
			count++;
			continue;
		}
		setUserInfo(buffer, &userInfo[count]);
		count++;
	}

	return count;
}

void setUserInfo(char *buffer, UserInfo *userInfo)
{
	char id[10];
	char name[30];
	char address[128];
	char cellphone[20];
	int i = 0;

	while (*buffer != '\t'){	//id
		id[i++] = *buffer;
		buffer++;
	}
	id[i] = '\0';
	userInfo->userId = atoi(id);


	i = 0;
	buffer++;
	while (*buffer != '\t'){	//name
		name[i++] = *buffer;
		buffer++;
	}
	name[i] = '\0';
	strcpy(userInfo->UserName, name);

	i = 0;
	buffer++;
	while (*buffer != '\t'){	//address
		address[i++] = *buffer;
		buffer++;
	}
	address[i] = '\0';
	strcpy(userInfo->userAddress, address);

	i = 0;
	buffer++;
	while (*buffer != '\n'){	//cellphone
		cellphone[i++] = *buffer;
		buffer++;
	}
	cellphone[i] = '\0';
	strcpy(userInfo->cellphone, cellphone);
}

/* [�ֿ� ���] ��ü ȸ�� ��� ���� */
void mainfunc_List(UserInfo userInfo[], FILE *readFile, int count){
	int pageNum = 0, ListLine = 0;
	int userViewUnit = 15;
	int finalPage;
	char input;

	struct tm *t;
	time_t timer;

	// finalPage ����
	if (count%userViewUnit == 0){
		finalPage = count / userViewUnit;
	}
	else{
		finalPage = (count / userViewUnit) + 1;
	}

	// ������ �� ���
	for (pageNum = 0; pageNum < finalPage;)
	{
		timer = time(NULL);    // ���� �ð��� �� ������ ���
		t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

		// ��޴� ��� ��º�
		RED;
		printf("\n	   NHN NEXT FITNESS CENTER			");
		SKY;
		printf("		 %s\n", timeToString(t));
		YELLOW;
		printf("     ����������������������������������������������������������������������������������������������\n");
		printf("     ��                         ȸ�� ���� ���α׷� : ��ü ȸ�� ��� ����                         ��\n");
		printf("     ����������������������������������������������������������������������������������������������\n\n");
		WHITE;

		if (pageNum < 0)
			pageNum++;

		// ����, ���� ������ ��º�
		printf("	�� ���� (���� ����Ű)		     ");
		printf("[ Page : %d / %d ]", pageNum + 1, finalPage);
		printf("		    (���� ����Ű) ���� ��\n");

		// �޴� ���� ��ܺ�
		YELGREEN;
		printf("	����������������������������������������������������������������������������������������\n");
		printf("	       ��  ��  \t     ��  �� \t\t ��  ��\t\t\t\t   �� �� ó  \n");
		printf("	����������������������������������������������������������������������������������������\n");

		WHITE;
		if (pageNum == 0){
			for (ListLine = 0; ListLine <= userViewUnit; ListLine++)
			{
				if (pageNum * userViewUnit + ListLine >= count)
				{
					break;
				}
				if (pageNum == 0 && ListLine == 0)
					continue;
				printf("	       %-8d\t    %-7s \t %-35s\t%-10s\n", userInfo[pageNum * userViewUnit + ListLine].userId, userInfo[pageNum * userViewUnit + ListLine].UserName, userInfo[pageNum * userViewUnit + ListLine].userAddress, userInfo[pageNum * userViewUnit + ListLine].cellphone);
			}
		}
		else{
			for (ListLine = 0; ListLine < userViewUnit; ListLine++)
			{
				if (pageNum * userViewUnit + ListLine >= (count - 1))
				{
					break;
				}
				printf("	       %-8d\t    %-7s \t %-35s\t%-10s\n", userInfo[pageNum * userViewUnit + ListLine + 1].userId, userInfo[pageNum * userViewUnit + ListLine + 1].UserName, userInfo[pageNum * userViewUnit + ListLine + 1].userAddress, userInfo[pageNum * userViewUnit + ListLine + 1].cellphone);
			}
		}

		YELGREEN;
		printf("	����������������������������������������������������������������������������������������\n\n");
		WHITE;
		printf("	�� ���� �������� ���÷��� ESC Ű�� �Է����ּ���. \n");
		printf("	   ����, ���� ���������� �̵��� ���� BackSpaceŰ, EnterŰ�ε� �����մϴ�. ");

		while (1)
		{
			if (_kbhit())
			{
				input = _getch();
				switch (input)
				{
				case LEFT:
					pageNum--;
					system("cls");
					break;
				case RIGHT:
					if (pageNum != (finalPage - 1)) pageNum++; // lastpage
					system("cls");
					break;
				case 8: // BackSpace Key
					pageNum--;
					system("cls");
					break;
				case 13: // Enter Key
					if (pageNum != (finalPage - 1)) pageNum++;
					system("cls");
					break;
				case 27: // ESC Key
					return;
				default:
					break;
				}
				if (input == LEFT || input == RIGHT || input == 8 || input == 13)
				{
					input = 0;
					break;
				}
				else
				{
					input = 0;
					continue;
				}
			}
		}
	}
}

/* [�ֿ� ���] �ű� ȸ�� ����ϱ� */
void mainfunc_Enroll(UserInfo * userInfo, int * count){
	struct tm *t;
	time_t timer;
	UserInfo * TempUser=(UserInfo*)malloc(sizeof(UserInfo));
	FILE * writeData;

	char id[10];
	char name[30];
	char address[128];
	char cellphone[20];

	writeData = fopen("data.txt", "at");
	if (writeData == NULL)
	{
		puts("data.txt file error. \n");
		return -1;
	}

	timer = time(NULL);    // ���� �ð��� �� ������ ���
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     ����������������������������������������������������������������������������������������������\n");
	printf("     ��                         ȸ�� ���� ���α׷� : �ű� ȸ�� ����ϱ�                          ��\n");
	printf("     ����������������������������������������������������������������������������������������������\n\n");
	WHITE;

	printf("		���ݺ��� �ű� ȸ���� ����մϴ�! \n");
	printf("1. �й� : ");
	gets(id);
	printf("2. �̸� : ");
	gets(name);
	printf("3. �ּ� : ");
	gets(address);
	printf("4. ��ȭ��ȣ : ");
	gets(cellphone);

	printf("%s\t%s\t%s\t%s\n", id, name, address, cellphone);

	userInfo[*count].userId = atoi(id);
	strcpy(userInfo[*count].UserName, name);
	strcpy(userInfo[*count].userAddress, address);
	strcpy(userInfo[*count].cellphone, cellphone);
	(*count)++;

	fputs(id, writeData);
	fputs("\t", writeData);
	fputs(name, writeData);
	fputs("\t", writeData);
	fputs(address, writeData);
	fputs("\t", writeData);
	fputs(cellphone, writeData);
	fputs("\n", writeData);
	printf("�ű� ��� �Ϸ�\n�ƹ� Ű�� ���� ����ȭ������ ���ÿ�");
	free(TempUser);
	fclose(writeData);
	getche();
}

/* [�ֿ� ���] ���� ȸ�� �����ϱ� */
void mainfunc_Delete(void){
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // ���� �ð��� �� ������ ���
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     ����������������������������������������������������������������������������������������������\n");
	printf("     ��                         ȸ�� ���� ���α׷� : ���� ȸ�� �����ϱ�                          ��\n");
	printf("     ����������������������������������������������������������������������������������������������\n\n");
	WHITE;

	printf("		���� �������� ���� ����Դϴ�! \n");
	printf("		�ƹ� Ű�� �Է��Ͻø� ���� ȭ������ ���ư��ϴ�. \n\n		");
	getche();
}

/* [�ֿ� ���] ���� ȸ�� ���� �����ϱ� */
void mainfunc_Modify(void){
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // ���� �ð��� �� ������ ���
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     ����������������������������������������������������������������������������������������������\n");
	printf("     ��                       ȸ�� ���� ���α׷� : ���� ȸ�� ���� �����ϱ�                       ��\n");
	printf("     ����������������������������������������������������������������������������������������������\n\n");
	WHITE;

	printf("		���� �������� ���� ����Դϴ�! \n");
	printf("		�ƹ� Ű�� �Է��Ͻø� ���� ȭ������ ���ư��ϴ�. \n\n		");
	getche();
}

/* [�ֿ� ���] ���� ȸ�� �˻��ϱ� */
void mainfunc_Search(void){
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // ���� �ð��� �� ������ ���
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     ����������������������������������������������������������������������������������������������\n");
	printf("     ��                         ȸ�� ���� ���α׷� : ���� ȸ�� �˻��ϱ�                          ��\n");
	printf("     ����������������������������������������������������������������������������������������������\n\n");
	WHITE;

	printf("		���� �������� ���� ����Դϴ�! \n");
	printf("		�ƹ� Ű�� �Է��Ͻø� ���� ȭ������ ���ư��ϴ�. \n\n		");
	getche();
}

/* [�ֿ� ���] ���� ���� ���� �� �����ϱ� */
void mainfunc_SaveExit(void){
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // ���� �ð��� �� ������ ���
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     ����������������������������������������������������������������������������������������������\n");
	printf("     ��                      ȸ�� ���� ���α׷� : ���� ���� ���� �� �����ϱ�                     ��\n");
	printf("     ����������������������������������������������������������������������������������������������\n\n");
	WHITE;

	printf("		���� �������� ���� ����Դϴ�! \n");
	printf("		�ƹ� Ű�� �Է��Ͻø� ���� ȭ������ ���ư��ϴ�. \n\n		");
	getche();
}

/* [�ֿ� ���] ������ ���� ���� */
void mainfunc_Info(void){
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // ���� �ð��� �� ������ ���
	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     ����������������������������������������������������������������������������������������������\n");
	printf("     ��                          ȸ�� ���� ���α׷� : ������ ���� ����                           ��\n");
	printf("     ����������������������������������������������������������������������������������������������\n\n");
	WHITE;

	printf("		���� �������� ���� ����Դϴ�! \n");
	printf("		�ƹ� Ű�� �Է��Ͻø� ���� ȭ������ ���ư��ϴ�. \n\n		");
	getche();
}