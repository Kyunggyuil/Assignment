#include "UserManagement.h"
#include "UserManagement_Func.h"

/* °øÅëÀûÀ¸·Î »ç¿ëÇÏ´Â ÇÔ¼ö */

// ÇöÀçÀÇ ½Ã°£À» °è»êÇÏ´Â ÇÔ¼ö
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

/* [ÁÖ¿ä ±â´É] ÀüÃ¼ È¸¿ø ¸í´Ü º¸±â */
void mainfunc_List(UserInfo userInfo[], FILE *readFile, int count){
	int pageNum = 0, ListLine = 0;
	int userViewUnit = 15;
	int finalPage;
	char input;

	struct tm *t;
	time_t timer;

	// finalPage Á¤ÀÇ
	if (count%userViewUnit == 0){
		finalPage = count / userViewUnit;
	}
	else{
		finalPage = (count / userViewUnit) + 1;
	}

	// ÆäÀÌÁö º° Ãâ·Â
	for (pageNum = 0; pageNum < finalPage;)
	{
		timer = time(NULL);    // ÇöÀç ½Ã°¢À» ÃÊ ´ÜÀ§·Î ¾ò±â
		t = localtime(&timer); // ÃÊ ´ÜÀ§ÀÇ ½Ã°£À» ºÐ¸®ÇÏ¿© ±¸Á¶Ã¼¿¡ ³Ö±â

		// ´ë¸Þ´º »ó´Ü Ãâ·ÂºÎ
		RED;
		printf("\n	   NHN NEXT FITNESS CENTER			");
		SKY;
		printf("		 %s\n", timeToString(t));
		YELLOW;
		printf("     ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
		printf("     ¦¢                         È¸¿ø °ü¸® ÇÁ·Î±×·¥ : ÀüÃ¼ È¸¿ø ¸í´Ü º¸±â                         ¦¢\n");
		printf("     ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n\n");
		WHITE;

		if (pageNum < 0)
			pageNum++;

		// ÀÌÀü, ´ÙÀ½ ÆäÀÌÁö Ãâ·ÂºÎ
		printf("	¢¸ ÀÌÀü (ÁÂÃø ¹æÇâÅ°)		     ");
		printf("[ Page : %d / %d ]", pageNum + 1, finalPage);
		printf("		    (¿ìÃø ¹æÇâÅ°) ´ÙÀ½ ¢º\n");

		// ¸Þ´º ¸ÞÀÎ »ó´ÜºÎ
		YELGREEN;
		printf("	¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡\n");
		printf("	       ÇÐ  ¹ø  \t     ÀÌ  ¸§ \t\t ÁÖ  ¼Ò\t\t\t\t   ¿¬ ¶ô Ã³  \n");
		printf("	¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡\n");

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
		printf("	¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡\n\n");
		WHITE;
		printf("	¡Ø ¸ÞÀÎ ÆäÀÌÁö·Î °¡½Ã·Á¸é ESC Å°¸¦ ÀÔ·ÂÇØÁÖ¼¼¿ä. \n");
		printf("	   ÀÌÀü, ´ÙÀ½ ÆäÀÌÁö·ÎÀÇ ÀÌµ¿Àº °¢°¢ BackSpaceÅ°, EnterÅ°·Îµµ °¡´ÉÇÕ´Ï´Ù. ");

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

/* [ÁÖ¿ä ±â´É] ½Å±Ô È¸¿ø µî·ÏÇÏ±â */
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

	timer = time(NULL);    // ÇöÀç ½Ã°¢À» ÃÊ ´ÜÀ§·Î ¾ò±â
	t = localtime(&timer); // ÃÊ ´ÜÀ§ÀÇ ½Ã°£À» ºÐ¸®ÇÏ¿© ±¸Á¶Ã¼¿¡ ³Ö±â

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
	printf("     ¦¢                         È¸¿ø °ü¸® ÇÁ·Î±×·¥ : ½Å±Ô È¸¿ø µî·ÏÇÏ±â                          ¦¢\n");
	printf("     ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n\n");
	WHITE;

	printf("		Áö±ÝºÎÅÍ ½Å±Ô È¸¿øÀ» µî·ÏÇÕ´Ï´Ù! \n");
	printf("1. ÇÐ¹ø : ");
	gets(id);
	printf("2. ÀÌ¸§ : ");
	gets(name);
	printf("3. ÁÖ¼Ò : ");
	gets(address);
	printf("4. ÀüÈ­¹øÈ£ : ");
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
	printf("½Å±Ô µî·Ï ¿Ï·á\n¾Æ¹« Å°³ª ´­·¯ ¸ÞÀÎÈ­¸éÀ¸·Î °¡½Ã¿À");
	free(TempUser);
	fclose(writeData);
	getche();
}

/* [ÁÖ¿ä ±â´É] ±âÁ¸ È¸¿ø »èÁ¦ÇÏ±â */
void mainfunc_Delete(void){
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // ÇöÀç ½Ã°¢À» ÃÊ ´ÜÀ§·Î ¾ò±â
	t = localtime(&timer); // ÃÊ ´ÜÀ§ÀÇ ½Ã°£À» ºÐ¸®ÇÏ¿© ±¸Á¶Ã¼¿¡ ³Ö±â

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
	printf("     ¦¢                         È¸¿ø °ü¸® ÇÁ·Î±×·¥ : ±âÁ¸ È¸¿ø »èÁ¦ÇÏ±â                          ¦¢\n");
	printf("     ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n\n");
	WHITE;

	printf("		¾ÆÁ÷ ±¸ÇöµÇÁö ¾ÊÀº ±â´ÉÀÔ´Ï´Ù! \n");
	printf("		¾Æ¹« Å°³ª ÀÔ·ÂÇÏ½Ã¸é ¸ÞÀÎ È­¸éÀ¸·Î µ¹¾Æ°©´Ï´Ù. \n\n		");
	getche();
}

/* [ÁÖ¿ä ±â´É] ±âÁ¸ È¸¿ø Á¤º¸ ¼öÁ¤ÇÏ±â */
void mainfunc_Modify(void){
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // ÇöÀç ½Ã°¢À» ÃÊ ´ÜÀ§·Î ¾ò±â
	t = localtime(&timer); // ÃÊ ´ÜÀ§ÀÇ ½Ã°£À» ºÐ¸®ÇÏ¿© ±¸Á¶Ã¼¿¡ ³Ö±â

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
	printf("     ¦¢                       È¸¿ø °ü¸® ÇÁ·Î±×·¥ : ±âÁ¸ È¸¿ø Á¤º¸ ¼öÁ¤ÇÏ±â                       ¦¢\n");
	printf("     ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n\n");
	WHITE;

	printf("		¾ÆÁ÷ ±¸ÇöµÇÁö ¾ÊÀº ±â´ÉÀÔ´Ï´Ù! \n");
	printf("		¾Æ¹« Å°³ª ÀÔ·ÂÇÏ½Ã¸é ¸ÞÀÎ È­¸éÀ¸·Î µ¹¾Æ°©´Ï´Ù. \n\n		");
	getche();
}

/* [ÁÖ¿ä ±â´É] ±âÁ¸ È¸¿ø °Ë»öÇÏ±â */
void mainfunc_Search(void){
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // ÇöÀç ½Ã°¢À» ÃÊ ´ÜÀ§·Î ¾ò±â
	t = localtime(&timer); // ÃÊ ´ÜÀ§ÀÇ ½Ã°£À» ºÐ¸®ÇÏ¿© ±¸Á¶Ã¼¿¡ ³Ö±â

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
	printf("     ¦¢                         È¸¿ø °ü¸® ÇÁ·Î±×·¥ : ±âÁ¸ È¸¿ø °Ë»öÇÏ±â                          ¦¢\n");
	printf("     ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n\n");
	WHITE;

	printf("		¾ÆÁ÷ ±¸ÇöµÇÁö ¾ÊÀº ±â´ÉÀÔ´Ï´Ù! \n");
	printf("		¾Æ¹« Å°³ª ÀÔ·ÂÇÏ½Ã¸é ¸ÞÀÎ È­¸éÀ¸·Î µ¹¾Æ°©´Ï´Ù. \n\n		");
	getche();
}

/* [ÁÖ¿ä ±â´É] º¯°æ ³»¿ë ÀúÀå ¹× Á¾·áÇÏ±â */
void mainfunc_SaveExit(void){
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // ÇöÀç ½Ã°¢À» ÃÊ ´ÜÀ§·Î ¾ò±â
	t = localtime(&timer); // ÃÊ ´ÜÀ§ÀÇ ½Ã°£À» ºÐ¸®ÇÏ¿© ±¸Á¶Ã¼¿¡ ³Ö±â

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
	printf("     ¦¢                      È¸¿ø °ü¸® ÇÁ·Î±×·¥ : º¯°æ ³»¿ë ÀúÀå ¹× Á¾·áÇÏ±â                     ¦¢\n");
	printf("     ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n\n");
	WHITE;

	printf("		¾ÆÁ÷ ±¸ÇöµÇÁö ¾ÊÀº ±â´ÉÀÔ´Ï´Ù! \n");
	printf("		¾Æ¹« Å°³ª ÀÔ·ÂÇÏ½Ã¸é ¸ÞÀÎ È­¸éÀ¸·Î µ¹¾Æ°©´Ï´Ù. \n\n		");
	getche();
}

/* [ÁÖ¿ä ±â´É] °³¹ßÀÚ Á¤º¸ º¸±â */
void mainfunc_Info(void){
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // ÇöÀç ½Ã°¢À» ÃÊ ´ÜÀ§·Î ¾ò±â
	t = localtime(&timer); // ÃÊ ´ÜÀ§ÀÇ ½Ã°£À» ºÐ¸®ÇÏ¿© ±¸Á¶Ã¼¿¡ ³Ö±â

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
	printf("     ¦¢                          È¸¿ø °ü¸® ÇÁ·Î±×·¥ : °³¹ßÀÚ Á¤º¸ º¸±â                           ¦¢\n");
	printf("     ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n\n");
	WHITE;

	printf("		¾ÆÁ÷ ±¸ÇöµÇÁö ¾ÊÀº ±â´ÉÀÔ´Ï´Ù! \n");
	printf("		¾Æ¹« Å°³ª ÀÔ·ÂÇÏ½Ã¸é ¸ÞÀÎ È­¸éÀ¸·Î µ¹¾Æ°©´Ï´Ù. \n\n		");
	getche();
}