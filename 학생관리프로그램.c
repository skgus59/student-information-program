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
}STUDENT;//구조체정의
typedef struct struct_major{
	char major[30];
	struct struct_major *link;
}MAJOR;//구조체정의
typedef struct struct_address{
	char address[20];
	struct struct_address *link;
}ADDRESS;//구조체정의
typedef struct struct_postcode{
	int postcode;
	struct struct_postcode *link;
}POSTCODE;//구조체정의

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
	STUDENT *shead = NULL;//구조체 포인터 head
	MAJOR *mhead = NULL;
	ADDRESS *ahead = NULL;
	POSTCODE *phead = NULL;
	FILE *fa, *fm, *fp, *fs;//파일입출력
	fa=fopen("address.txt", "r");
	if (fa==NULL){//파일 오류
		printf("input address file open error!\n");
		return 1;
	}
	fm=fopen("major.txt","r");
	if (fm==NULL){//파일 오류
		printf("input major file open error!\n");
		return 1;
	}
	fp=fopen("postcode.txt", "r");
	if (fp==NULL){//파일 오류
		printf("input postcode file open error!\n");
	}
	fs=fopen("student.txt", "r");
	if (fs==NULL){//파일 오류
		printf("input student file open error!\n");
	}
	while(!feof(fm)){//major.txt파일 끝날때까지 반복
		MAJOR *ptr;//ptr 포인터
		MAJOR *new;//new 포인터
		new=(MAJOR*)malloc(sizeof(MAJOR));//동적할당
		fscanf(fm, "%s\n", new->major);//파일 scanf해서 new의 major에 넣기
		if (mhead==NULL){//제일 첫 값일 때
			mhead=new;
			new->link=NULL;
		}
		else{
			ptr=mhead;//ptr은 MAJOR의 head를 가리킴
			while(ptr->link!=NULL) ptr=ptr->link;//ptr은 MAJOR의 가장 끝을 가리킴
			new->link=NULL;
			ptr->link=new;//new를 MAJOR의 가장 끝에 붙인다
		}
	}
	while(!feof(fa)){
		ADDRESS *ptr;//ptr 포인터
		ADDRESS *new;//new 포인터
		new=(ADDRESS*)malloc(sizeof(ADDRESS));//동적할당
		fscanf(fa, "%s\n", new->address);//파일 scanf해서 new의 address에 넣기
		if (ahead==NULL){//제일 첫 값일 때
			ahead=new;
			new->link=NULL;
		}
		else{
			ptr=ahead;//ptr은 ADDRESS의 head를 가리킴
			while(ptr->link!=NULL) ptr=ptr->link;//ptr은 ADDRESS의 가장 끝을 가리킴
			new->link=NULL;
			ptr->link=new;//new를 ADDRESS의 가장 끝에 붙인다
		}
	}
	while(!feof(fp)){//postcode.txt파일 끝날때까지 반복
		POSTCODE *ptr;//ptr포인터
		POSTCODE *new;//new 포인터
		new=(POSTCODE*)malloc(sizeof(POSTCODE));//동적할당
		fscanf(fp, "%d\n",&(new->postcode));//파일 scanf해서 new의 postcode에 넣기
		if (phead==NULL){//제일 첫 값일 때
			phead=new;
			new->link=NULL;
		}
		else{
			ptr=phead;//ptr은 POSTCODE의 head를 가리킴
			while (ptr->link!=NULL) ptr=ptr->link;//ptr은 POSTCODE의 가장 끝을 가리킴
			new->link=NULL;
			ptr->link=new;//new를 POSTCODE의 가장 끝에 붙인다
		}
	}
	while(!feof(fs)){
		STUDENT *ptr;//ptr 포인터
		STUDENT *new;//new 포인터
		new=(STUDENT*)malloc(sizeof(STUDENT));//동적할당
		char* Major, * Address;//Major와 Address 포인터
		Major = (char*)malloc(sizeof(char)*30);//동적할당
		Address = (char*)malloc(sizeof(char)*20);//동적할당
		int Postcode;
		fscanf(fs,"%d %s %d %s %s %d\n", &(new->std_id),new->name,&(new->year), Major, Address, &Postcode);
		//파일에서 scanf해서 new의 std_id, name,year에 넣고 Major, Address, Postcode에 넣기
		MAJOR *m;//포인터
		m=mhead;//m은 MAJOR의 head를 가리킴
		while(1){
			new->m_link=m;//new의 m_link는 MAJOR의 m을 가리킴
			if (strcmp(Major, m->major) == 0) {//파일에서 받아온 Major와 m->major가 일치할 때
				free(Major);//할당받은 메모리 반환
				break;
			}
			else{
				m=m->link;//m은 그다음 m을 가리킴
				new->m_link=m;//new->m_link는 MAJOR의 m을 가리킴
			}
		}
		ADDRESS *a;
		a=ahead;//a는 ADDRESS의 head를 가리킴
		while(1){
			new->a_link=a;//new->a_link는 ADDRESS의 a을 가리킴
			if (strcmp(Address, a->address) == 0) {//파일에서 받아온 Address와 a->address가 일치할 때
				free(Address);//할당받은 메모리 반환
				break;
			}
			else{
				a=a->link;//a는 그다음 a를 가리킴
				new->a_link=a;//new->a_link는 ADDRESS의 a를 가리킴
			}
		}
		POSTCODE *p;
		p=phead;//p는 POSTCODE의 head를 가리킴
		while(1){
			new->p_link=p;//new->p_link는 POSTCODE의 p를 가리킴
			if (Postcode==p->postcode) break;//파일에서 받아온 Postcode와 p->postcode가 일치할 때
			else{	   
				p=p->link;//p는 그다음 p를 가리킴
				new->p_link=p;//new->p_link는 POSTCODE의 p를 가리킴
			}
		}	 
		if (shead==NULL){//첫번째 값일 때
			shead=new;
			new->link=NULL;
		}
		else{
			ptr=shead;//ptr은 STUDENT의 head를 가리킴
			while (ptr->link!=NULL) ptr=ptr->link;//ptr은 STUDENT의 끝을 가리킴
			new->link=NULL;
			ptr->link=new;//new를 STUDENT의 가장 끝에 붙인다
		}
	}
	while(1){//사용자에게 선택을 받는 틀
		printf("\n<Select number>\n");
		printf("1-insert 2-delete 3-search_neighbor 4-search_family\n");
		printf("5-search_friend 6-search_major 7-change_major 8-exit\n");
		printf("\nSelect > ");
		int a;
		scanf("%d",&a);//정수입력받기
		if (a==1) insert(shead,mhead,ahead,phead);//새로운 학생을 추가하는 함수
		else if (a==2){//기존 학생을 제거하는 함수
			int id;
			printf("insert student id : ");
			scanf("%d", &id);
			delete(shead,mhead,ahead,phead,id);
		}
		else if (a==3){//이웃을 찾아서 출력하는 함수
			int id;
			char *nm;
			nm = (char*)malloc(sizeof(char) * 20);//동적할당
			printf("insert student id : ");
			scanf("%d", &id);
			printf("insert student name : ");
			scanf("%s", nm);
			search_neighbor(shead, mhead, ahead, phead, nm, id);
		}
		else if (a==4){//가족을 찾아서 출력하는 함수
			int id;
			char *nm;
			nm = (char*)malloc(sizeof(char) * 20);//동적할당
			printf("insert student id : ");
			scanf("%d", &id);
			printf("insert student name : ");
			scanf("%s", nm);
			search_family(shead, mhead, ahead, phead, nm, id);
		}
		else if (a==5){//나이가 같은 학생을 찾아서 출력하는 함수
			int id;
			char *nm;
			nm = (char*)malloc(sizeof(char) * 20);//동적할당
			printf("insert student id : ");
			scanf("%d", &id);
			printf("insert student name : ");
			scanf("%s",nm);
			search_friend(shead, mhead, ahead, phead, nm, id);
		}
		else if (a==6){//전공이 같은 학생을 찾아서 출력하는 함수
			int id;
			char *nm;
			nm = (char*)malloc(sizeof(char) * 20);//동적할당
			printf("insert student id : ");
			scanf("%d", &id);
			printf("insert student name : ");
			scanf("%s", nm);
			search_major(shead, mhead, ahead, phead, nm, id);
		}
		else if (a==7){//해당학생의 전공을 변경해주는 함수
			int id;
			char* nm;
			nm = (char*)malloc(sizeof(char) * 20);//동적할당
			char* mj;
			mj = (char*)malloc(sizeof(char) * 30);//동적할당
			printf("insert student id : ");
			scanf("%d", &id);
			printf("insert student name : ");
			scanf("%s", nm);
			printf("insert new major : ");
			scanf("%s", mj);
			change_major(shead,mhead,nm,id,mj);
		}
		else if (a==8) exit(1);//프로그램 종료
		else{//잘못된 숫자를 입력한 경우
			printf("wrong number\n");
			printf("\n");
		}
	}
	return 0;
	fclose(fm);//파일입출력 종료//
	fclose(fp);
	fclose(fa);
	fclose(fs); 
}

void insert(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head) {
	STUDENT* new;
	new = (STUDENT*)malloc(sizeof(STUDENT));//동적할당
	char* Major, * Address;
	Major = (char*)malloc(sizeof(char)*30);//동적할당
	Address = (char*)malloc(sizeof(char)*20);//동적할당
	int Postcode;
	printf("insert student information >\n");
	printf("id name year major address postcode: ");
	scanf("%d %s %d %s %s %d", &(new->std_id), new->name, &(new->year), Major, Address, &Postcode);
	//파일에서 scanf해서 new의 std_id, name, year와 Major,Address, Postcode에 값을 넣기
	STUDENT* s;
	s = s_head;//s는 STUDENT의 head를 가리킴
	while (1) {
		if (s->std_id == new->std_id) {//이미 같은 std_id가 존재하는 경우
			printf("same student id exist\n");
			free(Major);//할당받은 메모리 변환
			free(Address);//할당받은 메모리 변환
			return;
		}
		else {
			s = s->link;//s는 다음 s를 가리킴
			if (s == NULL) break;//성공한 경우
		}
	}
	free(s);
	MAJOR* m;//m은 MAJOR의 head를 가리킴
	m = m_head;
	while (1) {
		new->m_link = m;
		if (strcmp(Major, m->major) == 0) break;//새로 입력받은 학생의 Major가 기존 MAJOR에 있는 경우
		else {
			m = m->link;//m은 다음 m을 가리킴
			new->m_link = m;//new->m_link은 m을 가리킴
			if (m == NULL) {//새로 입력받은 학생의 Major가 기존 MAJOR에 없는 경우
				printf("wrong major\n");
				free(Major);//할당받은 메모리 반환
				free(Address);//할당받은 메모리 반환
				return;
			}
		}
	}
	ADDRESS* a;
	a = a_head;//a는 ADDRESS의 head를 가리킴
	while (1) {
		new->a_link = a;
		if (strcmp(Address, a->address) == 0) break;//새로 입력받은 학생의 Address가 기존 ADDRESS에 있는 경우 
		else {
			a = a->link;//a는 다음 a를 가리킴
			new->a_link = a;//new->m_link은 a를 가리킴
			if (a == NULL) {//새로 입력받은 학생의 Address가 기존 ADDRESS에 없는 경우
				printf("wrong address\n");
				free(Major);//할당받은 메모리 반환
				free(Address);//할당받은 메모리 반환
				return;
			}
		}
	}
	POSTCODE* p;
	p = p_head;//p는 POSTCODE의 head를 가리킴
	while (1) {
		new->p_link = p;
		if (Postcode == p->postcode) break;//새로 입력받은 학생의 Postcode가 기존 POSTCODE에 있는 경우
		else {
			p = p->link;//p는 다음 p를 가리킴
			new->p_link = p;//new->p_link는 p를 가리킴
			if (p == NULL) {//새로 입력받은 학생의 Postcode가 기존 POSTCODE에 없는 경우
				printf("wrong postcode\n");
				free(Major);//할당받은 메모리 반환
				free(Address);//할당받은 메모리 반환
				return;
			}
		}
	}
	free(Major);//할당받은 메모리 반환
	free(Address);//할당받은 메모리 반한
	STUDENT* ptr;
	ptr = s_head;//ptr은 STUDENT의 head를 가리킴
	while (ptr->link != NULL) ptr = ptr->link;//ptr은 STUDENT의 끝을 가리킴
	new->link = NULL;
	ptr->link = new;//new를 STUDENT의 끝에 붙인다
}

void delete(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head, int n) {
	STUDENT* ptr;
	ptr = s_head;//ptr은 STUDENT의 head를 가리킴
	int count = 0;
	while (1) {
		if (ptr->std_id == n) {//ptr->std_id가 n과 일치하는 경우
			break;
		}
		else {
			ptr = ptr->link;//ptr은 다음 ptr을 가리킴
			count++;//count 세기
			if (ptr == NULL) {//ptr->std_id가 n과 일치하지 않는 경우
				printf("student id not exist\n");
				return;
			}
		}
	}
	STUDENT* pPrev;
	pPrev = s_head;//pPrev은 STUDENT의 head를 가리킴
	if (count == 0) s_head = ptr->link;//첫번째인 경우
	for (int i = 0; i < count - 1; i++) pPrev = pPrev->link;//pPrev은 찾는 student 바로 앞을 가리킴
	pPrev->link = ptr->link;//pPrev은 ptr을 건너뛰고 ptr->link을 가리킴 삭제 성공
	free(ptr);//할당받은 메모리 반환
}

void search_neighbor(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head, char name[], int n) {
	STUDENT* ptr;
	ptr = s_head;//ptr은 STUDENT의 head를 가리킴
	while (1) {
		if (strcmp(ptr->name, name) == 0) break;//ptr->name과 name이 일치하는 경우
		else {
			ptr = ptr->link;//ptr은 다음 ptr을 가리킴
			if (ptr == NULL) {
				printf("student name not exist\n");//ptr->name과 name이 일치하는 것이 아무것도 없는 경우
				return;
			}
		}
	}
	ptr = s_head;//ptr은 STUDENT의 head를 가리킴
	while (1) {
		if (n == ptr->std_id) break; //ptr->std_id와 n이 일치하는 경우
		else {
			ptr = ptr->link;//ptr은 다음 ptr을 가리킴
			if (ptr == NULL) {
				printf("student id not exist\n");//ptr->std_id와 n이 일치하는 것이 아무것도 없는 경우
				return;
			}
		}
	}
	if (strcmp(name, ptr->name) != 0) {//입력받은 학생의 학번과 이름이 일치하지 않는 경우
		printf("student id & name not same\n");
		return;
	}
	int Postcode;
	Postcode = (ptr->p_link)->postcode;//Postcode에 입력받은 학생의 postcode 집어넣기
	char* Address;
	Address = (char*)malloc(sizeof(char)*20);//동적할당
	strcpy(Address, (ptr->a_link)->address);//Address에 입력받은 학생의 주소 집어넣기

	STUDENT* search;
	search = s_head;//search는 STUDENT의 head를 가리킴
	change_structure(search, m_head, a_head, p_head);//STUDENT 순서를 생년월일 빠른 순서로 바꾸는 함수
	printf("<neighbor>\n");
	while (search != NULL) {//postcode는 일치하나 address가 다른 경우를 찾기
		if ((Postcode == (search->p_link)->postcode) && (strcmp(Address, (search->a_link)->address) != 0)) {
			printf("%d %s 0%d %s %s %d\n", search->std_id, search->name, search->year, search->m_link->major, search->a_link->address, search->p_link->postcode);
			search = search->link;//search는 다음 search를 가리킴
		}
		else {
			search = search->link;//search는 다음 search를 가리킴
		}
	}
	free(search);//할당받은 메모리를 반환
	free(Address);//할당받은 메모리를 반환
}

void search_family(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head, char name[], int n) {
	STUDENT* ptr;
	ptr = s_head;//ptr은 STUDENT의 head를 가리킴
	while (1) {
		if (strcmp(ptr->name, name) == 0) break;//ptr->name과 name이 일치하는 경우
		else {
			ptr = ptr->link;//ptr은 다음 ptr을 가리킴
			if (ptr == NULL) {
				printf("student name not exist\n");//ptr->name과 name이 일치하는 것이 아무것도 없는 경우
				return;
			}
		}
	}
	ptr = s_head;//ptr은 STUDENT의 head를 가리킴
	while (1) {
		if (n == ptr->std_id) break; //ptr->std_id와 n이 일치하는 경우
		else {
			ptr = ptr->link;//ptr은 다음 ptr을 가리킴
			if (ptr == NULL) {
				printf("student id not exist\n");//ptr->std_id와 n이 일치하는 것이 아무것도 없는 경우
				return;
			}
		}
	}
	if (strcmp(name, ptr->name) != 0) {//입력받은 학생의 학번과 이름이 일치하지 않는 경우
		printf("student id & name not same\n");
		return;
	}
	int Postcode;
	Postcode = (ptr->p_link)->postcode;//Postcode에 입력받은 학생의 postcode 집어넣기
	char* Address;
	Address = (char*)malloc(sizeof(char));//동적할당
	strcpy(Address, (ptr->a_link)->address);//Address에 입력받은 학생의 주소 집어넣기

	STUDENT* search;
	search = s_head;//search는 STUDENT의 head 가리킴
	change_structure(search, m_head, a_head, p_head);//STUDENT 순서를 생년월일 빠른 순서로 바꾸는 함수
	printf("<family>\n");
	while (search != NULL) {//postcode와 ddress가 일치하는 경우를 찾기
		if ((Postcode == (search->p_link)->postcode) && (strcmp(Address, (search->a_link)->address) == 0)) {
			printf("%d %s 0%d %s %s %d\n", search->std_id, search->name, search->year, search->m_link->major, search->a_link->address, search->p_link->postcode);
			search = search->link;//search는 다음 search를 가리킴
		}
		else {
			search = search->link;//search는 다음 search를 가리킴
		}
	}
	free(search);//할당받은 메모리를 반환
	free(Address);//할당받은 메모리를 반환
}

void search_friend(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head, char name[], int n) {
	STUDENT* ptr;
	ptr = s_head;//ptr은 STUDENT의 head를 가리킴
	while (1) {
		if (strcmp(ptr->name, name) == 0) break;//ptr->name과 name이 일치하는 경우
		else {
			ptr = ptr->link;//ptr은 다음 ptr을 가리킴
			if (ptr == NULL) {
				printf("student name not exist\n");//ptr->name과 name이 일치하는 것이 아무것도 없는 경우
				return;
			}
		}
	}
	ptr = s_head;//ptr은 STUDENT의 head를 가리킴
	while (1) {
		if (n == ptr->std_id) break; //ptr->std_id와 n이 일치하는 경우
		else {
			ptr = ptr->link;//ptr은 다음 ptr을 가리킴
			if (ptr == NULL) {
				printf("student id not exist\n");//ptr->std_id와 n이 일치하는 것이 아무것도 없는 경우
				return;
			}
		}
	}
	if (strcmp(name, ptr->name) != 0) {//입력받은 학생의 학번과 이름이 일치하지 않는 경우
		printf("student id & name not same\n");
		return;
	}
	int Year;
	Year = (ptr->year);//Year에 입력받은 학생의 year를 집어넣기

	STUDENT* search;
	search = s_head;//search는 STUDENT의 head를 가리킴
	change_structure(search, m_head, a_head, p_head);//STUDENT 순서를 생년월일 빠른 순서로 바꾸는 함수
	printf("<same year>\n");
	while (search != NULL) {//입력받은 학생과 나이가 같은 학생 찾기
		if ((int)(search->year)/10000==(int)Year/10000) {
			printf("%d %s 0%d %s %s %d\n", search->std_id, search->name, search->year, search->m_link->major, search->a_link->address, search->p_link->postcode);
			search = search->link;//search는 다음 search를 가리킴
		}
		else {
			search = search->link;//search는 다음 search를 가리킴
		}
	}
	free(search);//할당받은 메모리 반환
}

void search_major(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head, char name[], int n) {
	STUDENT* ptr;
	ptr = s_head;//ptr은 STUDENT의 head를 가리킴
	while (1) {
		if (strcmp(ptr->name, name) == 0) break;//ptr->name과 name이 일치하는 경우
		else {
			ptr = ptr->link;//ptr은 다음 ptr을 가리킴
			if (ptr == NULL) {
				printf("student name not exist\n");//ptr->name과 name이 일치하는 것이 아무것도 없는 경우
				return;
			}
		}
	}
	ptr = s_head;//ptr은 STUDENT의 head를 가리킴
	while (1) {
		if (n == ptr->std_id) break; //ptr->std_id와 n이 일치하는 경우
		else {
			ptr = ptr->link;//ptr은 다음 ptr을 가리킴
			if (ptr == NULL) {
				printf("student id not exist\n");//ptr->std_id와 n이 일치하는 것이 아무것도 없는 경우
				return;
			}
		}
	}
	if (strcmp(name, ptr->name)!= 0) {//입력받은 학생의 학번과 이름이 일치하지 않는 경우
		printf("student id & name not same\n");
		return;
	}
	char *Major;
	Major = (char*)malloc(sizeof(char)*30);//동적할당
	strcpy(Major, (ptr->m_link)->major);//Major에 입력받은 학생의 major 집어넣기

	STUDENT* search;
	search = s_head;//search는 STUDENT의 head 가리킴
	change_structure(search, m_head, a_head, p_head);//STUDENT 순서를 생년월일 빠른 순서로 바꾸는 함수
	printf("<same major>\n");
	while (search != NULL) {//입력받은 학생과 전공이 같은 학생 찾기
		if (strcmp(Major, (search->m_link)->major) == 0) {
			printf("%d %s 0%d %s %s %d\n", search->std_id, search->name, search->year, search->m_link->major, search->a_link->address, search->p_link->postcode);
			search = search->link;//search는 다음 search 가리킴
		}
		else {
			search = search->link;//search는 다음 search 가리킴
		}
	}
	free(search);//할당받은 메모리 반환
	free(Major);//할당받은 메모리 반환
}

void change_structure(STUDENT* s_head, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head) {
	STUDENT* Count;
	Count = s_head;//Count는 STUDENT의 head 가리킴
	int count = 0;
	while (Count != NULL) {//STUDENT 안에 학생이 몇명인지 확인하기
		count++;//count 세기
		Count = Count->link;//Count는 다음 Count를 가리킴
	}
	free(Count);//할당받은 메모리 반환
	STUDENT* ptr;//ptr은 STUDENT의 head 가리킴
	for (int i = 0; i < count; i++) {//총 count만큼 반복
		for (int j = 0; j < count - 1; j++) {//앞에서부터 두개씩 count-1 비교하기
			ptr = s_head;//ptr은 STUDENT의 head 가리킴
			for (int k = 0; k < j; k++) ptr = ptr->link; //ptr은 앞에서부터 1씩 증가
			if ((ptr->year) > ((ptr->link)->year)) {
				swap(ptr, ptr->link, m_head, a_head, p_head);//ptr과 ptr->link안의 모든 데이터 맞교환
			}
		}
	}
}

void swap(STUDENT* s1, STUDENT* s2, MAJOR* m_head, ADDRESS* a_head, POSTCODE* p_head) {
	int tempid;
	tempid = s1->std_id;//tempid에 s1의 학번을 저장
	s1->std_id = s2->std_id;//s1->std_id에 s2의 학번 저장
	s2->std_id = tempid;//s2->std_id에 s1의 학번 저장
	int tempy;
	tempy = s1->year;//tempy에 s1의 생년월일 저장
	s1->year = s2->year;//s1->year에 s2의 생년월일 저장
	s2->year = tempy;//s2->year에 s1의 생년월일 저장
	char* nm1, * nm2;
	nm1 = (char*)malloc(sizeof(char) * 20);//동적할당
	strcpy(nm1, s1->name);//nm1에 s1의 이름 저장
	nm2 = (char*)malloc(sizeof(char) * 20);//동적할당
	strcpy(nm2, s2->name);//nm2에 s2의 이름 저장
	strcpy(s1->name, nm2);//s1->name에 nm2 저장
	strcpy(s2->name, nm1);//s2->name에 nm1 저장
	char* mj1, * mj2;
	mj1 = (char*)malloc(sizeof(char)*30);//동적할당
	strcpy(mj1, s1->m_link->major);//mj1에 s1의 전공 저장
	mj2 = (char*)malloc(sizeof(char)*30);//동적할당
	strcpy(mj2, s2->m_link->major);//mj2에 s2의 전공 저장
	MAJOR* m1;
	m1 = m_head;//m1은 MAJOR의 head 가리킴
	while (1) {//s1의 major를 s2의 major로 바꾸는 작업
		s1->m_link = m1;//s1->m_link는 m1을 가리킴
		if (strcmp(mj2, m1->major) == 0) {//s2의 major와 m1->major가 일치하는 경우 찾기
			free(mj2);//할당받은 메모리 반환
			break;
		}
		else {
			m1 = m1->link;//m1은 다음 m1을 가리킴
			s1->m_link = m1;//s1->m_link은 m1을 가리킴
		}
	}
	MAJOR* m2;
	m2 = m_head;//m2는 MAJOR의 head 가리킴
	while (1) {//s2의 major를 s1의 major로 바꾸는 작업
		s2->m_link = m2;//s2->m_link는 m2를 가리킴
		if (strcmp(mj1, m2->major) == 0) {//s2의 major와 m1->major가 일치하는 경우 찾기
			free(mj1);//할당받은 메모리 반환
			break;
		}
		else {
			m2 = m2->link;//m2는 다음 m2를 가리킴
			s2->m_link = m2;//s2->m_link는 m2를 가리킴
		}
	}
	char* ad1, * ad2;
	ad1 = (char*)malloc(sizeof(char)*20);//동적할당
	strcpy(ad1, s1->a_link->address);//ad1에 s1의 주소 넣기
	ad2 = (char*)malloc(sizeof(char)*20);//동적할당
	strcpy(ad2, s2->a_link->address);//ad2에 s2의 주소 넣기
	ADDRESS* a1;
	a1 = a_head;//a1은 ADRESS의 head 가리킴
	while (1) {//s1의 address를 s2의 address로 바꾸는 작업
		s1->a_link = a1;//s1->a_link는 a1을 가리킴
		if (strcmp(ad2, a1->address) == 0) {//s2의 address와 a1->address가 일치하는 경우 찾기
			free(ad2);//할당받은 메모리 반환
			break;
		}
		else {
			a1 = a1->link;//a1은 다음 a1 가리킴
			s1->a_link = a1;//s1->a_link은 a1을 가리킴
		}
	}
	ADDRESS* a2;
	a2 = a_head;//a2는 ADDRESS의 head를 가리킴
	while (1) {//s2의 address를 s1의 address로 바꾸는 작업
		s2->a_link = a2;//s2->a_link는 a2를 가리킴
		if (strcmp(ad1, a2->address) == 0) {//s1의 address와 a2->address가 일치하는 경우 찾기
			free(ad1);//할당받은 메모리 반화
			break;
		}
		else {
			a2 = a2->link;//a2는 다음 a2 가리킴
			s2->a_link = a2;//s2->a_link는 a2를 가리킴
		}
	}
	int pc1, pc2;
	pc1 = s1->p_link->postcode;//pc1에 s1의 주소 집어넣기
	pc2 = s2->p_link->postcode;//pc2에 s2의 주소 집어넣기
	POSTCODE* p1;
	p1 = p_head;//p1은 POSTCODE의 head 가리킴
	while (1) {//s1의 postcode를 s2의 postcode로 바꾸는 작업
		s1->p_link = p1;//s1->p_link는 p1을 가리킴
		if (pc2 == p1->postcode) {//s2의 postcode와 p1->postcode가 일치하는 경우 찾기
			break;
		}
		else {
			p1 = p1->link;//p1은 다음 p1을 가리킴
			s1->p_link = p1;//s1->p_link은 p1을 가리킴
		}
	}
	POSTCODE* p2;
	p2 = p_head;//p2는 POSTCODE의 head 가리킴
	while (1) {//s2의 postcode를 s1의 postcode로 바꾸는 작업
		s2->p_link = p2;//s2->p_link는 p2를 가리킴
		if (pc1 == p2->postcode) {//s1의 postcode와 p2->postcode가 일치하는 경우 찾기
			break;
		}
		else {
			p2 = p2->link;//p2는 다음 p2를 가리킴
			s2->p_link = p2;//s2->p_link는 p2를 가리킴
		}
	}
}

void change_major(STUDENT* s_head, MAJOR* m_head, char name[], int n, char m[]) {
	STUDENT* ptr;
	ptr = s_head;//ptr은 STUDENT의 head를 가리킴
	while (1) {
		if (strcmp(ptr->name, name) == 0) break;//ptr->name과 name이 일치하는 경우
		else {
			ptr = ptr->link;//ptr은 다음 ptr을 가리킴
			if (ptr == NULL) {
				printf("student name not exist\n");//ptr->name과 name이 일치하는 것이 아무것도 없는 경우
				return;
			}
		}
	}
	ptr = s_head;//ptr은 STUDENT의 head를 가리킴
	while (1) {
		if (n == ptr->std_id) break; //ptr->std_id와 n이 일치하는 경우
		else {
			ptr = ptr->link;//ptr은 다음 ptr을 가리킴
			if (ptr == NULL) {
				printf("student id not exist\n");//ptr->std_id와 n이 일치하는 것이 아무것도 없는 경우
				return;
			}
		}
	}
	if (strcmp(name,ptr->name)!=0) {//입력받은 학생의 학번과 이름이 일치하지 않는 경우
		printf("student id & name not same\n");
		return;
	}
	MAJOR* mj;
	mj = m_head;//mj는 MAJOR의 head를 가리킴
	while (1) {
		if (strcmp(mj->major, m) == 0) break;//mj->major와 입력받은 전공이 같은 경우 성공한 경우
		else {
			mj = mj->link;//mj는 다음 mj를 가리킴
			if (mj == NULL) {
				printf("major not exist\n");//입력받은 전공이 MAJOR에 없는 경우 실패한 경우
				return;
			}
		}
	}
	MAJOR* search;
	search = m_head;//search는 MAJOR의 head를 가리킴
	while (1) {
		ptr->m_link = search;//ptr->m_link는 search를 가리킴
		if (strcmp(search->major, m) == 0) break;//입력받은 m과 search->major가 같은 경우
		else {
			search = search->link;//search는 다음 search를 가리킴
			ptr->m_link = search;//ptr->m_link는 search를 가리킴
		}
	}
}