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

int initData(UserInfo userInfo[], FILE* readFile)
{
	int i = 0;
	int count = 0;

	fscanf(readFile, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", &userInfo[count].userId, &userInfo[count].UserName, &userInfo[count].userAddress, &userInfo[count].cellphone); // 羅 廓簞 等檜攪 檗擎 菴 棻衛 檗橫憮 雖錶幗萵 匙歜

	for (count = 0; fscanf(readFile, "%d\t%[^\t]\t%[^\t]\t%[^\n]\n", &userInfo[count].userId, &userInfo[count].UserName, &userInfo[count].userAddress, &userInfo[count].cellphone) != EOF; count++);

	return count;
}

int verifyId(int id)
{
	if (id >= 100000 && id <= 999999)
		return 1;
	else
		return 0;
}

int verifyName(char *name)
{
	int idx;

	if (strlen(name) == 0 || strlen(name) > 8)
		return 0;
	
	else
	{
		for (idx = 0 ; idx < strlen(name) ; idx++)
			if (*(name + idx) >= 48 && *(name + idx) <= 57)
				return 0;
	}

	return 1;
}

int verifyPhone(char *phone)
{
	int idx;

	if (strlen(phone) == 0 || strlen(phone) < 12 || strlen(phone) > 13)
		return 0;

	for (idx = 0; idx < strlen(phone); idx++)
	{
		if (*(phone + idx) < '0' || *(phone + idx) > '9')
		{
			if ((idx == 3 || idx == 8) && *(phone + idx) == '-')
				continue;
			else
				return 0;
		}
	}

	return 1;
}

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);

}

/* [輿蹂 晦棟] 瞪羹 �蛾� 貲欽 爾晦 */
void mainfunc_List(UserInfo userInfo[], int count){
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
				if (userInfo[pageNum + userViewUnit + ListLine].userId == 0)
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
				if (userInfo[pageNum + userViewUnit + ListLine].userId == 0)
					continue;
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
				case BACKSPACE:
					pageNum--;
					system("cls");
					break;
				case ENTER:
					if (pageNum != (finalPage - 1)) pageNum++;
					system("cls");
					break;
				case ESC:
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
	UserInfo * TempUser = (UserInfo*)malloc(sizeof(UserInfo));

	char id[10];
	char name[30];
	char address[128];
	char cellphone[20];

	char input;

	timer = time(NULL);    // ⑷營 衛陝擊 蟾 欽嬪煎 橢晦
	t = localtime(&timer); // 蟾 欽嬪曖 衛除擊 碟葬ж罹 掘褻羹縑 厥晦

	RED;
	printf("\n      NHN NEXT FITNESS CENTER         ");
	SKY;
	printf("       %s\n", timeToString(t));
	YELLOW;
	printf("     忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("     弛                         �蛾� 婦葬 Щ煎斜極 : 褐敘 �蛾� 蛔煙ж晦                          弛\n");
	printf("     戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n\n");
	WHITE;

	printf("\n      Ⅱ 雖旎睡攪 ");
	YELGREEN;
	printf("%d喇 %d錯曖 褐敘 �蛾�", t->tm_year + 1900, t->tm_mon + 1);
	WHITE;
	printf("擊 蛔煙м棲棻! (蛔煙 氬渡濠 : ");
	GRAY;
	printf("Admin");
	WHITE;
	printf(") \n\n");


	printf("          旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf("          早                                                                      早\n");
	printf("          早     Ⅹ з廓 :                                                        早\n");
	printf("          早                                                                      早\n");
	printf("          早     Ⅹ 檜葷(4濠 檜頂) :                                              早\n");
	printf("          早                                                                      早\n");
	printf("          早     Ⅹ 輿模(嗥橫噙晦 んл 20濠 檜頂) :                               早\n");
	printf("          早                                                                      早\n");
	printf("          早                                                                      早\n");
	printf("          早     Ⅹ 瞪�食醽�(- んл 11濠 檜頂) :                                  早\n");
	printf("          早                                                                      早\n");
	printf("          曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭\n\n");
	printf("");

	printf("   式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n\n");
	printf("     ≦ 殮溘 紫醞 蛔煙擊 醞雖ж堅 談棻賊,\n        酈爾萄曖 ESC 酈蒂 殮溘ж衛賊 詭檣 �飛橉虞� 給嬴骨棲棻.\n\n\n");

	while (1)
	{
		if (_kbhit())
		{
			input = _getch();
			switch (input)
			{
			case 27: // ESC Key
				return;
			default:
				break;
			}
		}
	}
	do{
		gets(name);
	} while (verifyName == 0);
	gets(address);
	do{
		printf("Ⅹ 瞪�食醽� : ");
		gets(cellphone);
	} while (verifyPhone == 0);
	printf("%s\t%s\t%s\t%s\n", id, name, address, cellphone);

	userInfo[*count].userId = userInfo[*(count - 1)].userId>151000 ? userInfo[*(count - 1)].userId+1:151001;
	strncpy(userInfo[*count].UserName, name, sizeof(name));
	strncpy(userInfo[*count].userAddress, address, sizeof(address));
	strncpy(userInfo[*count].cellphone, cellphone, sizeof(cellphone));
	(*count)++;

	printf("褐敘 蛔煙 諫猿\n嬴鼠 酈釭 揚楝 詭檣�飛橉虞� 陛衛螃");
	free(TempUser);
	getche();
}

/* [輿蹂 晦棟] 晦襄 �蛾� 餉薯ж晦 */
void mainfunc_Delete(UserInfo * userInfo, int * count, int searchResult[], int targetData){
	struct tm *t;
	time_t timer;
	char deleteSelect;

	timer = time(NULL);    // ⑷營 衛陝擊 蟾 欽嬪煎 橢晦
	t = localtime(&timer); // 蟾 欽嬪曖 衛除擊 碟葬ж罹 掘褻羹縑 厥晦

	while (1)
	{
		RED;
		printf("\n	   NHN NEXT FITNESS CENTER			");
		SKY;
		printf("		 %s\n", timeToString(t));
		YELLOW;
		printf("     忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
		printf("     弛                         �蛾� 婦葬 Щ煎斜極 : 晦襄 �蛾� 餉薯ж晦                          弛\n");
		printf("     戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n\n");
		WHITE;

		printf("ID\t:\t%d\n檜葷\t:\t%s\n輿模\t:\t%s\n瞪�食醽αt:\t%s\n嬪曖 濠猿蒂 薑蜓煎 餉薯ж衛啊蝗棲梱?", userInfo[searchResult[targetData]].userId, userInfo[searchResult[targetData]].UserName, userInfo[searchResult[targetData]].userAddress, userInfo[searchResult[targetData]].cellphone);
		while (1)
		{
			if (_kbhit())
			{
				deleteSelect = getch();
				switch (deleteSelect)
				{
				case 'y':
				case 'Y':
					userInfo[searchResult[targetData]].userId = 0;
					(*count)--;
					printf("餉薯陛 諫猿 腎歷蝗棲棻. 嬴鼠酈釭 揚楝 啗樓ж褊衛螃.");
					return;
				case 'n':
				case 'N':
					return;
				default:
					printf("澀跤 摹鷗ж樟蝗棲棻. 嬴鼠 酈釭 揚楝憮 棻衛 衛濛й 熱 氈蝗棲棻.");
					getch();
				}
				break;
			}
		}
	}
}

/* [輿蹂 晦棟] 晦襄 �蛾� 薑爾 熱薑ж晦 */
void mainfunc_Modify(UserInfo * userInfo, int * searchResult, int targetData){
	struct tm *t;
	time_t timer;
	int userSelection = 0;
	char name[30];
	char address[128];
	char cellphone[20];

	while (1)
	{
		system("cls");
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
		printf("熱薑й 等檜攪 摹鷗\n1.\t檜葷\n2.\t輿模\n3.\t瞪�食醽αn");
		while (1)
		{
			if (_kbhit())
			{
				userSelection = getch();
				if (userSelection<ONE || userSelection>THREE)
				{
					printf("澀跤脹 摹鷗殮棲棻. 棻衛 殮溘ж晦嬪п憮朝 嬴鼠酈釭 揚楝輿褊衛螃.");
					getch();
					continue;
				}
				else
				{
					switch (userSelection)
					{
					case ONE:
						printf("晦襄 檜葷\t:\t%s\n褐敘 檜葷\t:\t", userInfo[searchResult[targetData]].UserName);
						while (1)
						{
							gets(name);
							if (verifyName(name) == 0)
							{
								printf("澀跤脹 檜葷殮棲棻. 棻衛 殮溘п 輿撮蹂.\n");
								getch();
								continue;
							}
							else
							{
								break;
							}
						}
						strncpy(userInfo[searchResult[targetData]].UserName, name, sizeof(name));
						break;
					case TWO:
						printf("晦襄 輿模\t:\t%s\n褐敘 輿模\t:\t", userInfo[searchResult[targetData]].userAddress);
						gets(address);
						strncpy(userInfo[searchResult[targetData]].userAddress, address, sizeof(address));
						break;
					case THREE:
						printf("晦襄 瞪�食醽αt:\t%s\n褐敘 瞪�食醽αt:\t", userInfo[searchResult[targetData]].cellphone);
						while (1)
						{
							gets(cellphone);
							if (verifyPhone(cellphone) == 0)
							{
								printf("澀跤脹 瞪�食醽� 殮棲棻. 棻衛 殮溘п 輿撮蹂.\n");
								getch();
								continue;
							}
							else
							{
								break;
							}
						}
						strncpy(userInfo[searchResult[targetData]].cellphone, cellphone, sizeof(cellphone));
						break;
					}
				}
			}
		}
	}


	getche();
}

/* [輿蹂 晦棟] 晦襄 �蛾� 匐儀ж晦 */
void mainfunc_Search(UserInfo * userInfo, int * count, int searchResult[]){
	struct tm *t;
	time_t timer;
	int searchSelect;
	int idx;
	char continueSelect=0;
	int resultCount = 0;
	int dataChange=0;
	int dataControlSelect = 0;

	timer = time(NULL);    // ⑷營 衛陝擊 蟾 欽嬪煎 橢晦
	t = localtime(&timer); // 蟾 欽嬪曖 衛除擊 碟葬ж罹 掘褻羹縑 厥晦

	int id;
	char name[30];
	char cellphone[20];

	while (1)
	{
		searchSelect = 0;
		continueSelect = 0;
		resultCount = 0;

		system("cls");
		RED;
		printf("\n	   NHN NEXT FITNESS CENTER			");
		SKY;
		printf("		 %s\n", timeToString(t));
		YELLOW;
		printf("     忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
		printf("     弛                         �蛾� 婦葬 Щ煎斜極 : 晦襄 �蛾� 匐儀ж晦                          弛\n");
		printf("     戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n\n");
		WHITE;

		printf("\t1.\tid蒂 檜辨п 瓊晦\n\t2.\t檜葷擊 檜辨п 瓊晦\n\t3.\t瞪�食醽ㄧ� 檜辨п 瓊晦\n\tESC.\t詭檣詭景煎 給嬴陛晦\n");
		
		searchSelect = getch();

		switch (searchSelect)
		{
		case ONE: // id煎 瓊晦
			while (1)
			{
				printf("\nID蒂 殮溘п 輿褊衛螃 : ");
				scanf(" %d", &id);
				if (verifyId(id) == 0) // 嶸�褲� id陛 嬴棋 唳辦
				{
					printf("\n嶸�褲狫� 彊擎 id殮棲棻. 棻衛 殮溘ж衛啊蝗棲梱?(Y/N) : ");
					do
					{
						if (_kbhit())
						{
							continueSelect = getche();
							switch (continueSelect)
							{
							case 'y':
							case 'Y':
								break;
							case 'n':
							case 'N':
								return;
							default:
								printf("\n澀跤脹 殮溘殮棲棻. 嬴鼠 酈釭 揚楝輿褊衛螃.\n");
								getch();
								printf("嶸�褲狫� 彊擎 id殮棲棻. 棻衛 殮溘ж衛啊蝗棲梱?(Y/N) : ");
								break;
							}
						}
					} while (continueSelect == 'y'||continueSelect == 'Y');
				}

				else // 嶸�褲� id檣 唳辦
				{
					break;
				}
			}
			
			for (idx = 0; idx < count; idx++)
			{
				if (userInfo[idx].userId == id)
				{
					printf("	       %-8d\t    %-7s \t %-35s\t%-10s\n", userInfo[idx].userId, userInfo[idx].UserName, userInfo[idx].userAddress, userInfo[idx].cellphone);
					searchResult[resultCount] = idx;
					resultCount++;
				}
			}

			break;
		case TWO:
			while (1)
			{
				printf("\n檜葷擊 殮溘п 輿褊衛螃 : ");
				gets(name);
				if (verifyName(name) == 0) // 嶸�褲� 檜葷檜 嬴棋 唳辦
				{
					printf("\n嶸�褲狫� 彊擎 檜葷殮棲棻. 棻衛 殮溘ж衛啊蝗棲梱?(Y/N) : ");
					do
					{
						if (_kbhit())
						{
							continueSelect = getche();
							switch (continueSelect)
							{
							case 'y':
							case 'Y':
								break;
							case 'n':
							case 'N':
								return (int)NULL;
							default:
								printf("\n澀跤脹 殮溘殮棲棻. 嬴鼠 酈釭 揚楝輿褊衛螃.\n");
								getch();
								printf("\n嶸�褲狫� 彊擎 檜葷殮棲棻. 棻衛 殮溘ж衛啊蝗棲梱?(Y/N) : ");
								break;
							}
						}
					} while (continueSelect != 'y'&&continueSelect != 'Y');
				}

				else // 嶸�褲� 檜葷檣 唳辦
				{
					break;
				}
			}

			for (idx = 0; idx < count; idx++)
			{
				if (!strcmp(userInfo[idx].UserName, name))
				{
					printf("	       %-8d\t    %-7s \t %-35s\t%-10s\n", userInfo[idx].userId, userInfo[idx].UserName, userInfo[idx].userAddress, userInfo[idx].cellphone);
					searchResult[resultCount] = idx;
					resultCount++;
				}
			}
			break;
		case THREE:
			while (1)
			{
				printf("\n瞪�食醽ㄧ� 殮溘п 輿褊衛螃 : ");
				gets(cellphone);
				if (verifyPhone(cellphone) == 0) // 嶸�褲� 瞪�食醽ㄟ� 嬴棋 唳辦
				{
					printf("\n嶸�褲狫� 彊擎 瞪�食醽�殮棲棻. 棻衛 殮溘ж衛啊蝗棲梱?(Y/N) : ");
					do
					{
						if (_kbhit())
						{
							continueSelect = getche();
							switch (continueSelect)
							{
							case 'y':
							case 'Y':
								break;
							case 'n':
							case 'N':
								return (int)NULL;
							default:
								printf("澀跤脹 殮溘殮棲棻. 嬴鼠 酈釭 揚楝輿褊衛螃.\n");
								getch();
								printf("嶸�褲狫� 彊擎 瞪�食醽�殮棲棻. 棻衛 殮溘ж衛啊蝗棲梱?(Y/N) : ");
								break;
							}
						}
					} while (continueSelect != 'y'&&continueSelect != 'Y');
				}

				else // 嶸�褲� 瞪�食醽�檣 唳辦
				{
					break;
				}
			}

			for (idx = 0; idx < count; idx++)
			{
				if (strcmp(userInfo[idx].cellphone, cellphone)==0)
				{
					printf("%d\t:\t	       %-8d\t    %-7s \t %-35s\t%-10s\n", idx+1, userInfo[idx].userId, userInfo[idx].UserName, userInfo[idx].userAddress, userInfo[idx].cellphone);
					searchResult[resultCount] = idx;
					resultCount++;
				}
			}

			break;
		case ESC:
			return resultCount;
		default:
			printf("澀跤脹 殮溘殮棲棻.\n");
			searchSelect = 0;
		}

		if (resultCount == 0)
			printf("橾纂ж朝 匐儀 唸婁陛 橈蝗棲棻. \n");
		else
		{
			printf("等檜攪蒂 熱薑 傳朝 餉薯ж衛溥賊 п渡ж衛朝 廓�ㄧ� ж雖 彊戲衛堅 謙猿ж衛溥賊 0擊 殮溘ж衛賊 腌棲棻 : ");
			while (1)
			{
				if (_kbhit)
				{
					dataChange = getch();

					if (dataChange <= resultCount || dataChange > 0)
					{
						while (1)
						{
							printf("等檜攪蒂 熱薑ж溥賊 1, 餉薯ж溥賊 2, 謙猿ж溥賊 0 : ");
							dataControlSelect = getch();
							if (dataControlSelect == '1')
							{
								mainfunc_Modify(userInfo, searchResult, dataChange);
								break;
							}
							else if (dataControlSelect == '2')
							{
								mainfunc_Delete(userInfo, count, searchResult, dataChange);
								break;
							}
							else if (dataControlSelect == '0')
							{
								break;
							}
							else
							{
								printf("澀跤脹 殮溘殮棲棻. 棻衛 ж晦 嬪п憮朝 嬴鼠酈釭 揚腦衛賊 腌棲棻.\n");
								getch();
							}
						}
					}
					else if (dataChange == '0')
						return;
				}
				if (dataChange == '0')
			}
		}

		continueSelect = 0;
		printf("\t棻衛 匐儀ж衛啊蝗棲梱?(Y/N)\t:\t");
		fflush(stdin);
		do
		{
			if (_kbhit())
			{
				continueSelect = getch();
				switch (continueSelect)
				{
				case 'y':
				case 'Y':
					continueSelect = 0;
					resultCount = 0;
					dataChange = 0;
					dataControlSelect = 0;
					searchSelect = 0;
					break;
				case 'n':
				case 'N':
					return resultCount;
				default:
					printf("澀跤脹 殮溘殮棲棻. 嬴鼠 酈釭 揚楝輿褊衛螃.\n");
					getche();
					continueSelect = 0;
				}
			}
		} while (continueSelect == 'y'&&continueSelect == 'Y');
	}

	return resultCount;
}

/* [輿蹂 晦棟] 滲唳 頂辨 盪濰 塽 謙猿ж晦 */
void mainfunc_SaveExit(UserInfo * userInfo, FILE * writeFile, int count){
	struct tm *t;
	time_t timer;
	int idx;

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

	fprintf(writeFile, "�蛾� 嬴檜蛤\t檜葷\t輿模\t瞪�食醽αn");

	for (idx = 0; idx < count; idx++)
	{
		if (userInfo[idx].userId == 0)
		{
			count++;
			continue;
		}
		fprintf(writeFile, "%d\t%s\t%s\t%s\n", userInfo[idx].userId, userInfo[idx].UserName, userInfo[idx].userAddress, userInfo[idx].cellphone);
	}

	printf("盪濰 諫猿. 嬴鼠酈釭 殮溘ж罹 Щ煎斜極 謙猿");
	getch();
	return;
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

	printf("		141007 : 梯鬼錳 \n");
	printf("		141001 : 唳敘橾 \n\n		");
	getche();
}