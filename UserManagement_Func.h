/* �Լ�(�ֿ� ���) ����� */
void mainfunc_List(UserInfo userInfo[], FILE *writeFile, int count); // ��ü ȸ�� ��� ����
void mainfunc_Enroll(UserInfo * userInfo, int * count); // �ű� ȸ�� ����ϱ�
void mainfunc_Delete(void); // ���� ȸ�� �����ϱ�
void mainfunc_Modify(void); // ���� ȸ�� ���� �����ϱ�
void mainfunc_Search(void); // ���� ȸ�� �˻��ϱ�
void mainfunc_SaveExit(void); // ���� ���� ���� �� �����ϱ�
void mainfunc_Info(void); // ������ ���� ����

// �Լ�(���� ���) �����
char* timeToString(struct tm *t);
int initData(UserInfo userInfo[], FILE* fp);
void setUserInfo(char *buffer, UserInfo *userInfo);