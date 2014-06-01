#include "UserManagement.h"
#include "UserManagement_Func.h"

/* 奢鱔瞳戲煎 餌辨ж朝 л熱 */

// ⑷營曖 衛除擊 啗骯ж朝 л熱
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

/* [輿蹂 晦棟] 瞪羹 �蛾� 貲欽 爾晦 */
void mainfunc_List(UserInfo userInfo[], FILE *readFile, int count){
	int pageNum = 0, ListLine = 0;
	int userViewUnit = 15;
	int finalPage;
	char input;

	struct tm *t;
	time_t timer;

	// finalPage 薑曖
	if (count%userViewUnit == 0){
		finalPage = count / userViewUnit;
	}
	else{
		finalPage = (count / userViewUnit) + 1;
	}

	// む檜雖 滌 轎溘
	for (pageNum = 0; pageNum < finalPage;)
	{
		timer = time(NULL);    // ⑷營 衛陝擊 蟾 欽嬪煎 橢晦
		t = localtime(&timer); // 蟾 欽嬪曖 衛除擊 碟葬ж罹 掘褻羹縑 厥晦

		// 渠詭景 鼻欽 轎溘睡
		RED;
		printf("\n	   NHN NEXT FITNESS CENTER			");
		SKY;
		printf("		 %s\n", timeToString(t));
		YELLOW;
		printf("     忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
		printf("     弛                         �蛾� 婦葬 Щ煎斜極 : 瞪羹 �蛾� 貲欽 爾晦                         弛\n");
		printf("     戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n\n");
		WHITE;

		if (pageNum < 0)
			pageNum++;

		// 檜瞪, 棻擠 む檜雖 轎溘睡
		printf("	９ 檜瞪 (謝難 寞щ酈)		     ");
		printf("[ Page : %d / %d ]", pageNum + 1, finalPage);
		printf("		    (辦難 寞щ酈) 棻擠 Ⅱ\n");

		// 詭景 詭檣 鼻欽睡
		YELGREEN;
		printf("	式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n");
		printf("	       з  廓  \t     檜  葷 \t\t 輿  模\t\t\t\t   翱 塊 籀  \n");
		printf("	式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n");

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
		printf("	式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n\n");
		WHITE;
		printf("	≦ 詭檣 む檜雖煎 陛衛溥賊 ESC 酈蒂 殮溘п輿撮蹂. \n");
		printf("	   檜瞪, 棻擠 む檜雖煎曖 檜翕擎 陝陝 BackSpace酈, Enter酈煎紫 陛棟м棲棻. ");

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

/* [輿蹂 晦棟] 褐敘 �蛾� 蛔煙ж晦 */
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

	timer = time(NULL);    // ⑷營 衛陝擊 蟾 欽嬪煎 橢晦
	t = localtime(&timer); // 蟾 欽嬪曖 衛除擊 碟葬ж罹 掘褻羹縑 厥晦

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("     弛                         �蛾� 婦葬 Щ煎斜極 : 褐敘 �蛾� 蛔煙ж晦                          弛\n");
	printf("     戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n\n");
	WHITE;

	printf("		雖旎睡攪 褐敘 �蛾衋� 蛔煙м棲棻! \n");
	printf("1. з廓 : ");
	gets(id);
	printf("2. 檜葷 : ");
	gets(name);
	printf("3. 輿模 : ");
	gets(address);
	printf("4. 瞪�食醽� : ");
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
	printf("褐敘 蛔煙 諫猿\n嬴鼠 酈釭 揚楝 詭檣�飛橉虞� 陛衛螃");
	free(TempUser);
	fclose(writeData);
	getche();
}

/* [輿蹂 晦棟] 晦襄 �蛾� 餉薯ж晦 */
void mainfunc_Delete(void){
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // ⑷營 衛陝擊 蟾 欽嬪煎 橢晦
	t = localtime(&timer); // 蟾 欽嬪曖 衛除擊 碟葬ж罹 掘褻羹縑 厥晦

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("     弛                         �蛾� 婦葬 Щ煎斜極 : 晦襄 �蛾� 餉薯ж晦                          弛\n");
	printf("     戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n\n");
	WHITE;

	printf("		嬴霜 掘⑷腎雖 彊擎 晦棟殮棲棻! \n");
	printf("		嬴鼠 酈釭 殮溘ж衛賊 詭檣 �飛橉虞� 給嬴骨棲棻. \n\n		");
	getche();
}

/* [輿蹂 晦棟] 晦襄 �蛾� 薑爾 熱薑ж晦 */
void mainfunc_Modify(void){
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // ⑷營 衛陝擊 蟾 欽嬪煎 橢晦
	t = localtime(&timer); // 蟾 欽嬪曖 衛除擊 碟葬ж罹 掘褻羹縑 厥晦

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("     弛                       �蛾� 婦葬 Щ煎斜極 : 晦襄 �蛾� 薑爾 熱薑ж晦                       弛\n");
	printf("     戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n\n");
	WHITE;

	printf("		嬴霜 掘⑷腎雖 彊擎 晦棟殮棲棻! \n");
	printf("		嬴鼠 酈釭 殮溘ж衛賊 詭檣 �飛橉虞� 給嬴骨棲棻. \n\n		");
	getche();
}

/* [輿蹂 晦棟] 晦襄 �蛾� 匐儀ж晦 */
void mainfunc_Search(void){
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // ⑷營 衛陝擊 蟾 欽嬪煎 橢晦
	t = localtime(&timer); // 蟾 欽嬪曖 衛除擊 碟葬ж罹 掘褻羹縑 厥晦

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("     弛                         �蛾� 婦葬 Щ煎斜極 : 晦襄 �蛾� 匐儀ж晦                          弛\n");
	printf("     戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n\n");
	WHITE;

	printf("		嬴霜 掘⑷腎雖 彊擎 晦棟殮棲棻! \n");
	printf("		嬴鼠 酈釭 殮溘ж衛賊 詭檣 �飛橉虞� 給嬴骨棲棻. \n\n		");
	getche();
}

/* [輿蹂 晦棟] 滲唳 頂辨 盪濰 塽 謙猿ж晦 */
void mainfunc_SaveExit(void){
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // ⑷營 衛陝擊 蟾 欽嬪煎 橢晦
	t = localtime(&timer); // 蟾 欽嬪曖 衛除擊 碟葬ж罹 掘褻羹縑 厥晦

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("     弛                      �蛾� 婦葬 Щ煎斜極 : 滲唳 頂辨 盪濰 塽 謙猿ж晦                     弛\n");
	printf("     戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n\n");
	WHITE;

	printf("		嬴霜 掘⑷腎雖 彊擎 晦棟殮棲棻! \n");
	printf("		嬴鼠 酈釭 殮溘ж衛賊 詭檣 �飛橉虞� 給嬴骨棲棻. \n\n		");
	getche();
}

/* [輿蹂 晦棟] 偃嫦濠 薑爾 爾晦 */
void mainfunc_Info(void){
	struct tm *t;
	time_t timer;

	timer = time(NULL);    // ⑷營 衛陝擊 蟾 欽嬪煎 橢晦
	t = localtime(&timer); // 蟾 欽嬪曖 衛除擊 碟葬ж罹 掘褻羹縑 厥晦

	RED;
	printf("\n	   NHN NEXT FITNESS CENTER			");
	SKY;
	printf("		 %s\n", timeToString(t));
	YELLOW;
	printf("     忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("     弛                          �蛾� 婦葬 Щ煎斜極 : 偃嫦濠 薑爾 爾晦                           弛\n");
	printf("     戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n\n");
	WHITE;

	printf("		嬴霜 掘⑷腎雖 彊擎 晦棟殮棲棻! \n");
	printf("		嬴鼠 酈釭 殮溘ж衛賊 詭檣 �飛橉虞� 給嬴骨棲棻. \n\n		");
	getche();
}