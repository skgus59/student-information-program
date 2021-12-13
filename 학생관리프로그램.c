#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct struct_student{
	int std_id;
	char name[20];
	int year;
	struct struct_student *link;
	struct struct_major *m_link;
	struct struct_address *a_link;
	struct struct_postcode *p_link;
}STUDENT;//����ü����
typedef struct struct_major{
	char major[30];
	struct struct_major *link;
}MAJOR;//����ü����
typedef struct struct_address{
	char address[20];
	struct struct_address *link;
}ADDRESS;//����ü����
typedef struct struct_postcode{
	int postcode;
	struct struct_postcode *link;
}POSTCODE;//����ü����

void insert(STUDENT *s_head, MAJOR *m_head, ADDRESS *a_head, POSTCODE *p_head);
void delete(STUDENT *s_head, MAJOR *m_head, ADDRESS *a_head, POSTCODE *p_head, int n);
void search_neighbor(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head, char name[], int n);
void search_family(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head, char name[], int n);
void search_friend(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head, char name[], int n);
void search_major(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head, char name[], int n);
void change_structure(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head);
void swap(STUDENT* s1, STUDENT* s2, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head);
void change_major(STUDENT* s_head, MAJOR* m_head, char name[], int n, char m[]);

int main(void){
	STUDENT *shead = NULL;//����ü ������ head
	MAJOR *mhead = NULL;
	ADDRESS *ahead = NULL;
	POSTCODE *phead = NULL;
	FILE *fa, *fm, *fp, *fs;//���������
	fa=fopen("address.txt", "r");
	if (fa==NULL){//���� ����
		printf("input address file open error!\n");
		return 1;
	}
	fm=fopen("major.txt","r");
	if (fm==NULL){//���� ����
		printf("input major file open error!\n");
		return 1;
	}
	fp=fopen("postcode.txt", "r");
	if (fp==NULL){//���� ����
		printf("input postcode file open error!\n");
	}
	fs=fopen("student.txt", "r");
	if (fs==NULL){//���� ����
		printf("input student file open error!\n");
	}
	while(!feof(fm)){//major.txt���� ���������� �ݺ�
		MAJOR *ptr;//ptr ������
		MAJOR *new;//new ������
		new=(MAJOR*)malloc(sizeof(MAJOR));//�����Ҵ�
		fscanf(fm, "%s\n", new->major);//���� scanf�ؼ� new�� major�� �ֱ�
		if (mhead==NULL){//���� ù ���� ��
			mhead=new;
			new->link=NULL;
		}
		else{
			ptr=mhead;//ptr�� MAJOR�� head�� ����Ŵ
			while(ptr->link!=NULL) ptr=ptr->link;//ptr�� MAJOR�� ���� ���� ����Ŵ
			new->link=NULL;
			ptr->link=new;//new�� MAJOR�� ���� ���� ���δ�
		}
	}
	while(!feof(fa)){
		ADDRESS *ptr;//ptr ������
		ADDRESS *new;//new ������
		new=(ADDRESS*)malloc(sizeof(ADDRESS));//�����Ҵ�
		fscanf(fa, "%s\n", new->address);//���� scanf�ؼ� new�� address�� �ֱ�
		if (ahead==NULL){//���� ù ���� ��
			ahead=new;
			new->link=NULL;
		}
		else{
			ptr=ahead;//ptr�� ADDRESS�� head�� ����Ŵ
			while(ptr->link!=NULL) ptr=ptr->link;//ptr�� ADDRESS�� ���� ���� ����Ŵ
			new->link=NULL;
			ptr->link=new;//new�� ADDRESS�� ���� ���� ���δ�
		}
	}
	while(!feof(fp)){//postcode.txt���� ���������� �ݺ�
		POSTCODE *ptr;//ptr������
		POSTCODE *new;//new ������
		new=(POSTCODE*)malloc(sizeof(POSTCODE));//�����Ҵ�
		fscanf(fp, "%d\n",&(new->postcode));//���� scanf�ؼ� new�� postcode�� �ֱ�
		if (phead==NULL){//���� ù ���� ��
			phead=new;
			new->link=NULL;
		}
		else{
			ptr=phead;//ptr�� POSTCODE�� head�� ����Ŵ
			while (ptr->link!=NULL) ptr=ptr->link;//ptr�� POSTCODE�� ���� ���� ����Ŵ
			new->link=NULL;
			ptr->link=new;//new�� POSTCODE�� ���� ���� ���δ�
		}
	}
	while(!feof(fs)){
		STUDENT *ptr;//ptr ������
		STUDENT *new;//new ������
		new=(STUDENT*)malloc(sizeof(STUDENT));//�����Ҵ�
		char* Major, * Address;//Major�� Address ������
		Major = (char*)malloc(sizeof(char)*30);//�����Ҵ�
		Address = (char*)malloc(sizeof(char)*20);//�����Ҵ�
		int Postcode;
		fscanf(fs,"%d %s %d %s %s %d\n", &(new->std_id),new->name,&(new->year), Major, Address, &Postcode);
		//���Ͽ��� scanf�ؼ� new�� std_id, name,year�� �ְ� Major, Address, Postcode�� �ֱ�
		MAJOR *m;//������
		m=mhead;//m�� MAJOR�� head�� ����Ŵ
		while(1){
			new->m_link=m;//new�� m_link�� MAJOR�� m�� ����Ŵ
			if (strcmp(Major, m->major) == 0) {//���Ͽ��� �޾ƿ� Major�� m->major�� ��ġ�� ��
				free(Major);//�Ҵ���� �޸� ��ȯ
				break;
			}
			else{
				m=m->link;//m�� �״��� m�� ����Ŵ
				new->m_link=m;//new->m_link�� MAJOR�� m�� ����Ŵ
			}
		}
		ADDRESS *a;
		a=ahead;//a�� ADDRESS�� head�� ����Ŵ
		while(1){
			new->a_link=a;//new->a_link�� ADDRESS�� a�� ����Ŵ
			if (strcmp(Address, a->address) == 0) {//���Ͽ��� �޾ƿ� Address�� a->address�� ��ġ�� ��
				free(Address);//�Ҵ���� �޸� ��ȯ
				break;
			}
			else{
				a=a->link;//a�� �״��� a�� ����Ŵ
				new->a_link=a;//new->a_link�� ADDRESS�� a�� ����Ŵ
			}
		}
		POSTCODE *p;
		p=phead;//p�� POSTCODE�� head�� ����Ŵ
		while(1){
			new->p_link=p;//new->p_link�� POSTCODE�� p�� ����Ŵ
			if (Postcode==p->postcode) break;//���Ͽ��� �޾ƿ� Postcode�� p->postcode�� ��ġ�� ��
			else{	   
				p=p->link;//p�� �״��� p�� ����Ŵ
				new->p_link=p;//new->p_link�� POSTCODE�� p�� ����Ŵ
			}
		}	 
		if (shead==NULL){//ù��° ���� ��
			shead=new;
			new->link=NULL;
		}
		else{
			ptr=shead;//ptr�� STUDENT�� head�� ����Ŵ
			while (ptr->link!=NULL) ptr=ptr->link;//ptr�� STUDENT�� ���� ����Ŵ
			new->link=NULL;
			ptr->link=new;//new�� STUDENT�� ���� ���� ���δ�
		}
	}
	while(1){//����ڿ��� ������ �޴� Ʋ
		printf("\n<Select number>\n");
		printf("1-insert 2-delete 3-search_neighbor 4-search_family\n");
		printf("5-search_friend 6-search_major 7-change_major 8-exit\n");
		printf("\nSelect > ");
		int a;
		scanf("%d",&a);//�����Է¹ޱ�
		if (a==1) insert(shead,mhead,ahead,phead);//���ο� �л��� �߰��ϴ� �Լ�
		else if (a==2){//���� �л��� �����ϴ� �Լ�
			int id;
			printf("insert student id : ");
			scanf("%d", &id);
			delete(shead,mhead,ahead,phead,id);
		}
		else if (a==3){//�̿��� ã�Ƽ� ����ϴ� �Լ�
			int id;
			char *nm;
			nm = (char*)malloc(sizeof(char) * 20);//�����Ҵ�
			printf("insert student id : ");
			scanf("%d", &id);
			printf("insert student name : ");
			scanf("%s", nm);
			search_neighbor(shead, mhead, ahead, phead, nm, id);
		}
		else if (a==4){//������ ã�Ƽ� ����ϴ� �Լ�
			int id;
			char *nm;
			nm = (char*)malloc(sizeof(char) * 20);//�����Ҵ�
			printf("insert student id : ");
			scanf("%d", &id);
			printf("insert student name : ");
			scanf("%s", nm);
			search_family(shead, mhead, ahead, phead, nm, id);
		}
		else if (a==5){//���̰� ���� �л��� ã�Ƽ� ����ϴ� �Լ�
			int id;
			char *nm;
			nm = (char*)malloc(sizeof(char) * 20);//�����Ҵ�
			printf("insert student id : ");
			scanf("%d", &id);
			printf("insert student name : ");
			scanf("%s",nm);
			search_friend(shead, mhead, ahead, phead, nm, id);
		}
		else if (a==6){//������ ���� �л��� ã�Ƽ� ����ϴ� �Լ�
			int id;
			char *nm;
			nm = (char*)malloc(sizeof(char) * 20);//�����Ҵ�
			printf("insert student id : ");
			scanf("%d", &id);
			printf("insert student name : ");
			scanf("%s", nm);
			search_major(shead, mhead, ahead, phead, nm, id);
		}
		else if (a==7){//�ش��л��� ������ �������ִ� �Լ�
			int id;
			char* nm;
			nm = (char*)malloc(sizeof(char) * 20);//�����Ҵ�
			char* mj;
			mj = (char*)malloc(sizeof(char) * 30);//�����Ҵ�
			printf("insert student id : ");
			scanf("%d", &id);
			printf("insert student name : ");
			scanf("%s", nm);
			printf("insert new major : ");
			scanf("%s", mj);
			change_major(shead,mhead,nm,id,mj);
		}
		else if (a==8) exit(1);//���α׷� ����
		else{//�߸��� ���ڸ� �Է��� ���
			printf("wrong number\n");
			printf("\n");
		}
	}
	return 0;
	fclose(fm);//��������� ����//
	fclose(fp);
	fclose(fa);
	fclose(fs); 
}

void insert(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head) {
	STUDENT* new;
	new = (STUDENT*)malloc(sizeof(STUDENT));//�����Ҵ�
	char* Major, * Address;
	Major = (char*)malloc(sizeof(char)*30);//�����Ҵ�
	Address = (char*)malloc(sizeof(char)*20);//�����Ҵ�
	int Postcode;
	printf("insert student information >\n");
	printf("id name year major address postcode: ");
	scanf("%d %s %d %s %s %d", &(new->std_id), new->name, &(new->year), Major, Address, &Postcode);
	//���Ͽ��� scanf�ؼ� new�� std_id, name, year�� Major,Address, Postcode�� ���� �ֱ�
	STUDENT* s;
	s = s_head;//s�� STUDENT�� head�� ����Ŵ
	while (1) {
		if (s->std_id == new->std_id) {//�̹� ���� std_id�� �����ϴ� ���
			printf("same student id exist\n");
			free(Major);//�Ҵ���� �޸� ��ȯ
			free(Address);//�Ҵ���� �޸� ��ȯ
			return;
		}
		else {
			s = s->link;//s�� ���� s�� ����Ŵ
			if (s == NULL) break;//������ ���
		}
	}
	free(s);
	MAJOR* m;//m�� MAJOR�� head�� ����Ŵ
	m = m_head;
	while (1) {
		new->m_link = m;
		if (strcmp(Major, m->major) == 0) break;//���� �Է¹��� �л��� Major�� ���� MAJOR�� �ִ� ���
		else {
			m = m->link;//m�� ���� m�� ����Ŵ
			new->m_link = m;//new->m_link�� m�� ����Ŵ
			if (m == NULL) {//���� �Է¹��� �л��� Major�� ���� MAJOR�� ���� ���
				printf("wrong major\n");
				free(Major);//�Ҵ���� �޸� ��ȯ
				free(Address);//�Ҵ���� �޸� ��ȯ
				return;
			}
		}
	}
	ADDRESS* a;
	a = a_head;//a�� ADDRESS�� head�� ����Ŵ
	while (1) {
		new->a_link = a;
		if (strcmp(Address, a->address) == 0) break;//���� �Է¹��� �л��� Address�� ���� ADDRESS�� �ִ� ��� 
		else {
			a = a->link;//a�� ���� a�� ����Ŵ
			new->a_link = a;//new->m_link�� a�� ����Ŵ
			if (a == NULL) {//���� �Է¹��� �л��� Address�� ���� ADDRESS�� ���� ���
				printf("wrong address\n");
				free(Major);//�Ҵ���� �޸� ��ȯ
				free(Address);//�Ҵ���� �޸� ��ȯ
				return;
			}
		}
	}
	POSTCODE* p;
	p = p_head;//p�� POSTCODE�� head�� ����Ŵ
	while (1) {
		new->p_link = p;
		if (Postcode == p->postcode) break;//���� �Է¹��� �л��� Postcode�� ���� POSTCODE�� �ִ� ���
		else {
			p = p->link;//p�� ���� p�� ����Ŵ
			new->p_link = p;//new->p_link�� p�� ����Ŵ
			if (p == NULL) {//���� �Է¹��� �л��� Postcode�� ���� POSTCODE�� ���� ���
				printf("wrong postcode\n");
				free(Major);//�Ҵ���� �޸� ��ȯ
				free(Address);//�Ҵ���� �޸� ��ȯ
				return;
			}
		}
	}
	free(Major);//�Ҵ���� �޸� ��ȯ
	free(Address);//�Ҵ���� �޸� ����
	STUDENT* ptr;
	ptr = s_head;//ptr�� STUDENT�� head�� ����Ŵ
	while (ptr->link != NULL) ptr = ptr->link;//ptr�� STUDENT�� ���� ����Ŵ
	new->link = NULL;
	ptr->link = new;//new�� STUDENT�� ���� ���δ�
}

void delete(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head, int n) {
	STUDENT* ptr;
	ptr = s_head;//ptr�� STUDENT�� head�� ����Ŵ
	int count = 0;
	while (1) {
		if (ptr->std_id == n) {//ptr->std_id�� n�� ��ġ�ϴ� ���
			break;
		}
		else {
			ptr = ptr->link;//ptr�� ���� ptr�� ����Ŵ
			count++;//count ����
			if (ptr == NULL) {//ptr->std_id�� n�� ��ġ���� �ʴ� ���
				printf("student id not exist\n");
				return;
			}
		}
	}
	STUDENT* pPrev;
	pPrev = s_head;//pPrev�� STUDENT�� head�� ����Ŵ
	if (count == 0) s_head = ptr->link;//ù��°�� ���
	for (int i = 0; i < count - 1; i++) pPrev = pPrev->link;//pPrev�� ã�� student �ٷ� ���� ����Ŵ
	pPrev->link = ptr->link;//pPrev�� ptr�� �ǳʶٰ� ptr->link�� ����Ŵ ���� ����
	free(ptr);//�Ҵ���� �޸� ��ȯ
}

void search_neighbor(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head, char name[], int n) {
	STUDENT* ptr;
	ptr = s_head;//ptr�� STUDENT�� head�� ����Ŵ
	while (1) {
		if (strcmp(ptr->name, name) == 0) break;//ptr->name�� name�� ��ġ�ϴ� ���
		else {
			ptr = ptr->link;//ptr�� ���� ptr�� ����Ŵ
			if (ptr == NULL) {
				printf("student name not exist\n");//ptr->name�� name�� ��ġ�ϴ� ���� �ƹ��͵� ���� ���
				return;
			}
		}
	}
	ptr = s_head;//ptr�� STUDENT�� head�� ����Ŵ
	while (1) {
		if (n == ptr->std_id) break; //ptr->std_id�� n�� ��ġ�ϴ� ���
		else {
			ptr = ptr->link;//ptr�� ���� ptr�� ����Ŵ
			if (ptr == NULL) {
				printf("student id not exist\n");//ptr->std_id�� n�� ��ġ�ϴ� ���� �ƹ��͵� ���� ���
				return;
			}
		}
	}
	if (strcmp(name, ptr->name) != 0) {//�Է¹��� �л��� �й��� �̸��� ��ġ���� �ʴ� ���
		printf("student id & name not same\n");
		return;
	}
	int Postcode;
	Postcode = (ptr->p_link)->postcode;//Postcode�� �Է¹��� �л��� postcode ����ֱ�
	char* Address;
	Address = (char*)malloc(sizeof(char)*20);//�����Ҵ�
	strcpy(Address, (ptr->a_link)->address);//Address�� �Է¹��� �л��� �ּ� ����ֱ�

	STUDENT* search;
	search = s_head;//search�� STUDENT�� head�� ����Ŵ
	change_structure(search, m_head, a_head, p_head);//STUDENT ������ ������� ���� ������ �ٲٴ� �Լ�
	printf("<neighbor>\n");
	while (search != NULL) {//postcode�� ��ġ�ϳ� address�� �ٸ� ��츦 ã��
		if ((Postcode == (search->p_link)->postcode) && (strcmp(Address, (search->a_link)->address) != 0)) {
			printf("%d %s 0%d %s %s %d\n", search->std_id, search->name, search->year, search->m_link->major, search->a_link->address, search->p_link->postcode);
			search = search->link;//search�� ���� search�� ����Ŵ
		}
		else {
			search = search->link;//search�� ���� search�� ����Ŵ
		}
	}
	free(search);//�Ҵ���� �޸𸮸� ��ȯ
	free(Address);//�Ҵ���� �޸𸮸� ��ȯ
}

void search_family(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head, char name[], int n) {
	STUDENT* ptr;
	ptr = s_head;//ptr�� STUDENT�� head�� ����Ŵ
	while (1) {
		if (strcmp(ptr->name, name) == 0) break;//ptr->name�� name�� ��ġ�ϴ� ���
		else {
			ptr = ptr->link;//ptr�� ���� ptr�� ����Ŵ
			if (ptr == NULL) {
				printf("student name not exist\n");//ptr->name�� name�� ��ġ�ϴ� ���� �ƹ��͵� ���� ���
				return;
			}
		}
	}
	ptr = s_head;//ptr�� STUDENT�� head�� ����Ŵ
	while (1) {
		if (n == ptr->std_id) break; //ptr->std_id�� n�� ��ġ�ϴ� ���
		else {
			ptr = ptr->link;//ptr�� ���� ptr�� ����Ŵ
			if (ptr == NULL) {
				printf("student id not exist\n");//ptr->std_id�� n�� ��ġ�ϴ� ���� �ƹ��͵� ���� ���
				return;
			}
		}
	}
	if (strcmp(name, ptr->name) != 0) {//�Է¹��� �л��� �й��� �̸��� ��ġ���� �ʴ� ���
		printf("student id & name not same\n");
		return;
	}
	int Postcode;
	Postcode = (ptr->p_link)->postcode;//Postcode�� �Է¹��� �л��� postcode ����ֱ�
	char* Address;
	Address = (char*)malloc(sizeof(char));//�����Ҵ�
	strcpy(Address, (ptr->a_link)->address);//Address�� �Է¹��� �л��� �ּ� ����ֱ�

	STUDENT* search;
	search = s_head;//search�� STUDENT�� head ����Ŵ
	change_structure(search, m_head, a_head, p_head);//STUDENT ������ ������� ���� ������ �ٲٴ� �Լ�
	printf("<family>\n");
	while (search != NULL) {//postcode�� ddress�� ��ġ�ϴ� ��츦 ã��
		if ((Postcode == (search->p_link)->postcode) && (strcmp(Address, (search->a_link)->address) == 0)) {
			printf("%d %s 0%d %s %s %d\n", search->std_id, search->name, search->year, search->m_link->major, search->a_link->address, search->p_link->postcode);
			search = search->link;//search�� ���� search�� ����Ŵ
		}
		else {
			search = search->link;//search�� ���� search�� ����Ŵ
		}
	}
	free(search);//�Ҵ���� �޸𸮸� ��ȯ
	free(Address);//�Ҵ���� �޸𸮸� ��ȯ
}

void search_friend(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head, char name[], int n) {
	STUDENT* ptr;
	ptr = s_head;//ptr�� STUDENT�� head�� ����Ŵ
	while (1) {
		if (strcmp(ptr->name, name) == 0) break;//ptr->name�� name�� ��ġ�ϴ� ���
		else {
			ptr = ptr->link;//ptr�� ���� ptr�� ����Ŵ
			if (ptr == NULL) {
				printf("student name not exist\n");//ptr->name�� name�� ��ġ�ϴ� ���� �ƹ��͵� ���� ���
				return;
			}
		}
	}
	ptr = s_head;//ptr�� STUDENT�� head�� ����Ŵ
	while (1) {
		if (n == ptr->std_id) break; //ptr->std_id�� n�� ��ġ�ϴ� ���
		else {
			ptr = ptr->link;//ptr�� ���� ptr�� ����Ŵ
			if (ptr == NULL) {
				printf("student id not exist\n");//ptr->std_id�� n�� ��ġ�ϴ� ���� �ƹ��͵� ���� ���
				return;
			}
		}
	}
	if (strcmp(name, ptr->name) != 0) {//�Է¹��� �л��� �й��� �̸��� ��ġ���� �ʴ� ���
		printf("student id & name not same\n");
		return;
	}
	int Year;
	Year = (ptr->year);//Year�� �Է¹��� �л��� year�� ����ֱ�

	STUDENT* search;
	search = s_head;//search�� STUDENT�� head�� ����Ŵ
	change_structure(search, m_head, a_head, p_head);//STUDENT ������ ������� ���� ������ �ٲٴ� �Լ�
	printf("<same year>\n");
	while (search != NULL) {//�Է¹��� �л��� ���̰� ���� �л� ã��
		if ((int)(search->year)/10000==(int)Year/10000) {
			printf("%d %s 0%d %s %s %d\n", search->std_id, search->name, search->year, search->m_link->major, search->a_link->address, search->p_link->postcode);
			search = search->link;//search�� ���� search�� ����Ŵ
		}
		else {
			search = search->link;//search�� ���� search�� ����Ŵ
		}
	}
	free(search);//�Ҵ���� �޸� ��ȯ
}

void search_major(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head, char name[], int n) {
	STUDENT* ptr;
	ptr = s_head;//ptr�� STUDENT�� head�� ����Ŵ
	while (1) {
		if (strcmp(ptr->name, name) == 0) break;//ptr->name�� name�� ��ġ�ϴ� ���
		else {
			ptr = ptr->link;//ptr�� ���� ptr�� ����Ŵ
			if (ptr == NULL) {
				printf("student name not exist\n");//ptr->name�� name�� ��ġ�ϴ� ���� �ƹ��͵� ���� ���
				return;
			}
		}
	}
	ptr = s_head;//ptr�� STUDENT�� head�� ����Ŵ
	while (1) {
		if (n == ptr->std_id) break; //ptr->std_id�� n�� ��ġ�ϴ� ���
		else {
			ptr = ptr->link;//ptr�� ���� ptr�� ����Ŵ
			if (ptr == NULL) {
				printf("student id not exist\n");//ptr->std_id�� n�� ��ġ�ϴ� ���� �ƹ��͵� ���� ���
				return;
			}
		}
	}
	if (strcmp(name, ptr->name)!= 0) {//�Է¹��� �л��� �й��� �̸��� ��ġ���� �ʴ� ���
		printf("student id & name not same\n");
		return;
	}
	char *Major;
	Major = (char*)malloc(sizeof(char)*30);//�����Ҵ�
	strcpy(Major, (ptr->m_link)->major);//Major�� �Է¹��� �л��� major ����ֱ�

	STUDENT* search;
	search = s_head;//search�� STUDENT�� head ����Ŵ
	change_structure(search, m_head, a_head, p_head);//STUDENT ������ ������� ���� ������ �ٲٴ� �Լ�
	printf("<same major>\n");
	while (search != NULL) {//�Է¹��� �л��� ������ ���� �л� ã��
		if (strcmp(Major, (search->m_link)->major) == 0) {
			printf("%d %s 0%d %s %s %d\n", search->std_id, search->name, search->year, search->m_link->major, search->a_link->address, search->p_link->postcode);
			search = search->link;//search�� ���� search ����Ŵ
		}
		else {
			search = search->link;//search�� ���� search ����Ŵ
		}
	}
	free(search);//�Ҵ���� �޸� ��ȯ
	free(Major);//�Ҵ���� �޸� ��ȯ
}

void change_structure(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head) {
	STUDENT* Count;
	Count = s_head;//Count�� STUDENT�� head ����Ŵ
	int count = 0;
	while (Count != NULL) {//STUDENT �ȿ� �л��� ������� Ȯ���ϱ�
		count++;//count ����
		Count = Count->link;//Count�� ���� Count�� ����Ŵ
	}
	free(Count);//�Ҵ���� �޸� ��ȯ
	STUDENT* ptr;//ptr�� STUDENT�� head ����Ŵ
	for (int i = 0; i < count; i++) {//�� count��ŭ �ݺ�
		for (int j = 0; j < count - 1; j++) {//�տ������� �ΰ��� count-1 ���ϱ�
			ptr = s_head;//ptr�� STUDENT�� head ����Ŵ
			for (int k = 0; k < j; k++) ptr = ptr->link; //ptr�� �տ������� 1�� ����
			if ((ptr->year) > ((ptr->link)->year)) {
				swap(ptr, ptr->link, m_head, a_head, p_head);//ptr�� ptr->link���� ��� ������ �±�ȯ
			}
		}
	}
}

void swap(STUDENT* s1, STUDENT* s2, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head) {
	int tempid;
	tempid = s1->std_id;//tempid�� s1�� �й��� ����
	s1->std_id = s2->std_id;//s1->std_id�� s2�� �й� ����
	s2->std_id = tempid;//s2->std_id�� s1�� �й� ����
	int tempy;
	tempy = s1->year;//tempy�� s1�� ������� ����
	s1->year = s2->year;//s1->year�� s2�� ������� ����
	s2->year = tempy;//s2->year�� s1�� ������� ����
	char* nm1, * nm2;
	nm1 = (char*)malloc(sizeof(char) * 20);//�����Ҵ�
	strcpy(nm1, s1->name);//nm1�� s1�� �̸� ����
	nm2 = (char*)malloc(sizeof(char) * 20);//�����Ҵ�
	strcpy(nm2, s2->name);//nm2�� s2�� �̸� ����
	strcpy(s1->name, nm2);//s1->name�� nm2 ����
	strcpy(s2->name, nm1);//s2->name�� nm1 ����
	char* mj1, * mj2;
	mj1 = (char*)malloc(sizeof(char)*30);//�����Ҵ�
	strcpy(mj1, s1->m_link->major);//mj1�� s1�� ���� ����
	mj2 = (char*)malloc(sizeof(char)*30);//�����Ҵ�
	strcpy(mj2, s2->m_link->major);//mj2�� s2�� ���� ����
	MAJOR* m1;
	m1 = m_head;//m1�� MAJOR�� head ����Ŵ
	while (1) {//s1�� major�� s2�� major�� �ٲٴ� �۾�
		s1->m_link = m1;//s1->m_link�� m1�� ����Ŵ
		if (strcmp(mj2, m1->major) == 0) {//s2�� major�� m1->major�� ��ġ�ϴ� ��� ã��
			free(mj2);//�Ҵ���� �޸� ��ȯ
			break;
		}
		else {
			m1 = m1->link;//m1�� ���� m1�� ����Ŵ
			s1->m_link = m1;//s1->m_link�� m1�� ����Ŵ
		}
	}
	MAJOR* m2;
	m2 = m_head;//m2�� MAJOR�� head ����Ŵ
	while (1) {//s2�� major�� s1�� major�� �ٲٴ� �۾�
		s2->m_link = m2;//s2->m_link�� m2�� ����Ŵ
		if (strcmp(mj1, m2->major) == 0) {//s2�� major�� m1->major�� ��ġ�ϴ� ��� ã��
			free(mj1);//�Ҵ���� �޸� ��ȯ
			break;
		}
		else {
			m2 = m2->link;//m2�� ���� m2�� ����Ŵ
			s2->m_link = m2;//s2->m_link�� m2�� ����Ŵ
		}
	}
	char* ad1, * ad2;
	ad1 = (char*)malloc(sizeof(char)*20);//�����Ҵ�
	strcpy(ad1, s1->a_link->address);//ad1�� s1�� �ּ� �ֱ�
	ad2 = (char*)malloc(sizeof(char)*20);//�����Ҵ�
	strcpy(ad2, s2->a_link->address);//ad2�� s2�� �ּ� �ֱ�
	ADDRESS* a1;
	a1 = a_head;//a1�� ADRESS�� head ����Ŵ
	while (1) {//s1�� address�� s2�� address�� �ٲٴ� �۾�
		s1->a_link = a1;//s1->a_link�� a1�� ����Ŵ
		if (strcmp(ad2, a1->address) == 0) {//s2�� address�� a1->address�� ��ġ�ϴ� ��� ã��
			free(ad2);//�Ҵ���� �޸� ��ȯ
			break;
		}
		else {
			a1 = a1->link;//a1�� ���� a1 ����Ŵ
			s1->a_link = a1;//s1->a_link�� a1�� ����Ŵ
		}
	}
	ADDRESS* a2;
	a2 = a_head;//a2�� ADDRESS�� head�� ����Ŵ
	while (1) {//s2�� address�� s1�� address�� �ٲٴ� �۾�
		s2->a_link = a2;//s2->a_link�� a2�� ����Ŵ
		if (strcmp(ad1, a2->address) == 0) {//s1�� address�� a2->address�� ��ġ�ϴ� ��� ã��
			free(ad1);//�Ҵ���� �޸� ��ȭ
			break;
		}
		else {
			a2 = a2->link;//a2�� ���� a2 ����Ŵ
			s2->a_link = a2;//s2->a_link�� a2�� ����Ŵ
		}
	}
	int pc1, pc2;
	pc1 = s1->p_link->postcode;//pc1�� s1�� �ּ� ����ֱ�
	pc2 = s2->p_link->postcode;//pc2�� s2�� �ּ� ����ֱ�
	POSTCODE* p1;
	p1 = p_head;//p1�� POSTCODE�� head ����Ŵ
	while (1) {//s1�� postcode�� s2�� postcode�� �ٲٴ� �۾�
		s1->p_link = p1;//s1->p_link�� p1�� ����Ŵ
		if (pc2 == p1->postcode) {//s2�� postcode�� p1->postcode�� ��ġ�ϴ� ��� ã��
			break;
		}
		else {
			p1 = p1->link;//p1�� ���� p1�� ����Ŵ
			s1->p_link = p1;//s1->p_link�� p1�� ����Ŵ
		}
	}
	POSTCODE* p2;
	p2 = p_head;//p2�� POSTCODE�� head ����Ŵ
	while (1) {//s2�� postcode�� s1�� postcode�� �ٲٴ� �۾�
		s2->p_link = p2;//s2->p_link�� p2�� ����Ŵ
		if (pc1 == p2->postcode) {//s1�� postcode�� p2->postcode�� ��ġ�ϴ� ��� ã��
			break;
		}
		else {
			p2 = p2->link;//p2�� ���� p2�� ����Ŵ
			s2->p_link = p2;//s2->p_link�� p2�� ����Ŵ
		}
	}
}

void change_major(STUDENT* s_head, MAJOR* m_head, char name[], int n, char m[]) {
	STUDENT* ptr;
	ptr = s_head;//ptr�� STUDENT�� head�� ����Ŵ
	while (1) {
		if (strcmp(ptr->name, name) == 0) break;//ptr->name�� name�� ��ġ�ϴ� ���
		else {
			ptr = ptr->link;//ptr�� ���� ptr�� ����Ŵ
			if (ptr == NULL) {
				printf("student name not exist\n");//ptr->name�� name�� ��ġ�ϴ� ���� �ƹ��͵� ���� ���
				return;
			}
		}
	}
	ptr = s_head;//ptr�� STUDENT�� head�� ����Ŵ
	while (1) {
		if (n == ptr->std_id) break; //ptr->std_id�� n�� ��ġ�ϴ� ���
		else {
			ptr = ptr->link;//ptr�� ���� ptr�� ����Ŵ
			if (ptr == NULL) {
				printf("student id not exist\n");//ptr->std_id�� n�� ��ġ�ϴ� ���� �ƹ��͵� ���� ���
				return;
			}
		}
	}
	if (strcmp(name,ptr->name)!=0) {//�Է¹��� �л��� �й��� �̸��� ��ġ���� �ʴ� ���
		printf("student id & name not same\n");
		return;
	}
	MAJOR* mj;
	mj = m_head;//mj�� MAJOR�� head�� ����Ŵ
	while (1) {
		if (strcmp(mj->major, m) == 0) break;//mj->major�� �Է¹��� ������ ���� ��� ������ ���
		else {
			mj = mj->link;//mj�� ���� mj�� ����Ŵ
			if (mj == NULL) {
				printf("major not exist\n");//�Է¹��� ������ MAJOR�� ���� ��� ������ ���
				return;
			}
		}
	}
	MAJOR* search;
	search = m_head;//search�� MAJOR�� head�� ����Ŵ
	while (1) {
		ptr->m_link = search;//ptr->m_link�� search�� ����Ŵ
		if (strcmp(search->major, m) == 0) break;//�Է¹��� m�� search->major�� ���� ���
		else {
			search = search->link;//search�� ���� search�� ����Ŵ
			ptr->m_link = search;//ptr->m_link�� search�� ����Ŵ
		}
	}
}