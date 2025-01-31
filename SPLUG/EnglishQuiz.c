#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_login = 0;  // 로그인/로그아웃 상태 체크
int terminate = 0; // 메인뷰에서 6 입력시 프로그램 종료
char myID[31];
char myPW[31];
char myName[31];

typedef struct Node // 회원 정보 저장용 연결리스트
{
    char *id;
    char *pw;
    char *name;
    struct Node *prev;
    struct Node *next;
} Node;

Node *head = NULL; // 리스트 맨 앞 가리키는 포인터
Node *tail = NULL; // 리스트 맨 뒤 가리키는 포인터

typedef struct Dictionary // 사전 정보 저장용 연결리스트(영어 단어 사전순으로 정렬)
{
    char *eng;
    char *kor;
    struct Dictionary *prev;
    struct Dictionary *next;
} Dictionary;

Dictionary *first = NULL;
Dictionary *last = NULL;

void add(char *id, char *pw, char *name);
void rmv(char *id);
void dicAdd(char *eng, char *kor);
int searchID(char *id);
int searchIDPW(char *id, char *pw);
void join();
void login();
void logout();
void quiz();
void withdrawal();
void call_memberlist();
void call_diclist();
void write_new_memberlist();
void freeNodeList();
void freeDictionaryList();
void print_logout();
void print_login();

void add(char *id, char *pw, char *name) // 회원가입 시 노드 추가
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    // 동적 메모리 할당 후 문자열 복사
    newNode->id = strdup(id); // 원본 문자열과 독립된 메모리 생성(strdup 안쓰면 매개변수들이 참조하는 외부 데이터가 바뀌거나 사라지면 문제생김)
    newNode->pw = strdup(pw);
    newNode->name = strdup(name);
    newNode->prev = NULL;
    newNode->next = NULL;
    // 리스트 노드 맨 뒤에 삽입
    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void rmv(char *id) // 회원탈퇴시 노드 제거
{
    Node *iter = head;
    while (1)
    {
        if (strcmp(iter->id, id) == 0)
            break;
        iter = iter->next;
    }
    Node *deleteNode = iter;
    if (deleteNode->prev == NULL && deleteNode->next == NULL) // 노드 1개밖에 없을 때
    {
        head = NULL;
        tail = NULL;
    }
    else if (deleteNode->prev == NULL) // 맨 앞 노드 삭제
    {
        head = deleteNode->next;
        head->prev = NULL;
    }
    else if (deleteNode->next == NULL) // 맨 뒤 노드 삭제
    {
        tail = deleteNode->prev;
        tail->next = NULL;
    }
    else // 중간 노드 삭제
    {
        deleteNode->prev->next = deleteNode->next;
        deleteNode->next->prev = deleteNode->prev;
    }
    free(deleteNode);
}

void dicAdd(char *eng, char *kor) // 영어단어와 한글 뜻 세트로 사전에 저장
{
    Dictionary *newNode = (Dictionary *)malloc(sizeof(Dictionary));

    // 동적 메모리 할당 및 문자열 복사
    newNode->eng = strdup(eng);
    newNode->kor = strdup(kor);
    newNode->prev = NULL;
    newNode->next = NULL;

    if (first == NULL)
    {
        first = newNode;
        last = newNode;
    }
    else // 사전 순으로 삽입해야함
    {
        Dictionary *iter = first;
        while (iter != NULL)
        {
            if (strcmp(eng, iter->eng) < 0)
                break;
            iter = iter->next;
        }

        if (iter == NULL) // 리스트 맨 뒤에 삽입해야 하는 경우
        {
            last->next = newNode;
            newNode->prev = last;
            last = newNode;
        }
        else if (iter == first) // 리스트 맨 앞에 삽입해야 하는 경우
        {
            first->prev = newNode;
            newNode->next = first;
            first = newNode;
        }
        else // 리스트 중앙에 삽입해야 하는 경우
        {
            newNode->next = iter;
            newNode->prev = iter->prev;
            iter->prev->next = newNode;
            iter->prev = newNode;
        }
    }
}

int searchID(char *id) // 아이디 입력시 아이디 존재 여부 확인
{
    Node *iter = head;
    int exist = 0;
    while (iter != NULL)
    {
        if (strcmp(iter->id, id) == 0)
        {
            exist = 1;
            break;
        }
        iter = iter->next;
    }
    if (exist == 0) // 중복되는거 없으면 0 리턴
        return 0;
    return 1; // 중복되는거 있으면 1 리턴
}

int searchIDPW(char *id, char *pw) // 아이디 존재할 시 비번이 일치하는지 확인
{
    Node *iter = head;
    int exist = 0;
    while (iter != NULL)
    {
        if (strcmp(iter->id, id) == 0)
        {
            exist = 1;
            break;
        }
        iter = iter->next;
    }
    if (exist == 0) // 아이디가 존재하지 않는 경우
    {
        printf("입력하신 아이디가 존재하지 않습니다.\n");
        return 0;
    }
    else if (exist == 1 && strcmp(iter->pw, pw) != 0) // 아이디는 맞았으나 비번이 틀린경우
    {
        printf("비밀번호가 틀렸습니다.\n");
        return 0;
    }
    strcpy(myID, id);
    strcpy(myPW, pw);
    strcpy(myName, iter->name);
    return 1; // 맞게 입력한 경우 아이디, 비번, 이름 전역변수 초기화 후 1 리턴
}

void join() // 회원가입
{
    printf("회원가입 페이지 (입력창에 'q' 입력시 모든 행위 취소하고 메인화면으로 이동)\n");
    char id[12345];

    while (1)
    {
        printf("아이디: ");
        scanf("%s", id);
        if (strcmp(id, "q") == 0)
            return;
        if (strlen(id) > 30)
        {
            printf("아이디는 30글자 이하여야 합니다.\n");
            continue;
        }
        if (strlen(id) < 2)
        {
            printf("아이디는 2글자 이상이어야 합니다.\n");
            continue;
        }
        if (searchID(id) == 0)
        {
            printf("사용 가능한 아이디 입니다.\n");
            break;
        }
        else
        {
            printf("이미 존재하는 아이디 입니다.\n");
            continue;
        }
    }

    char pw[12345];
    while (1)
    {
        printf("비밀번호: ");
        scanf("%s", pw);
        if (strcmp(pw, "q") == 0)
            return;
        if (strlen(pw) > 30)
        {
            printf("비밀번호는 30글자 이하여야 합니다.\n");
            continue;
        }
        if (strlen(pw) < 2)
        {
            printf("비밀번호는 2글자 이상이어야 합니다.\n");
            continue;
        }
        break;
    }

    char name[12345];
    while (1)
    {
        printf("이름: ");
        scanf("%s", name);
        if (strcmp(name, "q") == 0)
            return;
        if (strlen(name) < 2)
        {
            printf("이름은 2글자 이상이어야 합니다.\n");
            continue;
        }
        if (strlen(name) > 30)
        {
            printf("이름은 30글자 이하여야 합니다.\n");
            continue;
        }
        break;
    }

    add(id, pw, name);
}

void login() // 로그인
{
    printf("로그인 (입력창에 'q' 입력시 모든 행위 취소하고 메인화면으로 이동)\n");
    char id[12345], pw[12345];
    while (1)
    {
        printf("아이디: ");
        scanf("%s", id);
        if (strcmp(id, "q") == 0)
            break;
        printf("비밀번호: ");
        scanf("%s", pw);
        if (strcmp(pw, "q") == 0)
            break;
        int success = searchIDPW(id, pw);
        if (success == 0)
            continue;
        else
        {
            is_login = 1;
            break;
        }
    }
}

void logout() // 로그아웃
{
    printf("정말 로그아웃 하시겠습니까? [y/n]: ");
    char c[111]; // char* c 이렇게 선언하면 메모리 할당이 안된 상태이므로 잘못된 결과가 나옴
    scanf("%s", c);
    if (strcmp(c, "y") == 0)
        is_login = 0;
}

void quiz() // 영어 단어 맞히기
{
    printf(">> 영어 단어 맞히기 프로그램 <<\n");
    printf("1. 영어 단어 맞히기 2. 프로그램 종료\n");
    printf("번호를 선택하세요: ");
    int num;
    scanf("%d", &num);
    if (num != 1)
        return;
    Dictionary *iter = first;
    int cnt = 0, correctCnt = 0;
    while (iter != NULL)
    {
        char k[111];
        printf("%s -> ", iter->eng);
        scanf("%s", k);
        if (strcmp(k, ".quit") == 0)
            break;
        cnt++;
        if (strcmp(k, iter->kor) == 0)
        {
            printf("correct!\n");
            correctCnt++;
        }
        else
            printf("incorrect!\n");
        iter = iter->next;
    }
    float score = (correctCnt / (float)cnt) * 100;
    printf("%s님의 점수는 %.2f점 입니다.\n", myName, score);
}

void withdrawal() // 회원탈퇴
{
    printf("정말 회원을 탈퇴하시겠습니까? [y/n]: ");
    char c[111];
    scanf("%s", c);
    if (strcmp(c, "y") == 0)
    {
        rmv(myID);
        is_login = 0;
        myID[0] = '\0';
        myPW[0] = '\0';
        myName[0] = '\0';
    }
}

void call_memberlist() // 회원 정보 불러와서 리스트에 저장
{
    FILE *fp = fopen("member.txt", "r");
    char id[33], pw[33], name[33];
    while (fscanf(fp, "%s %s %s", id, pw, name) == 3)
    {
        add(strdup(id), strdup(pw), strdup(name)); // strdup로 복사
    }
    fclose(fp);
}

void call_diclist() // 사전 정보 불러와서 리스트에 저장
{
    FILE *fp = fopen("dic.txt", "r");
    char eng[111], kor[111];
    while (fscanf(fp, "%s %s", eng, kor) == 2)
    {
        dicAdd(strdup(eng), strdup(kor)); // strdup로 복사
    }
    fclose(fp);
}

void write_new_memberlist() // 새롭게 바뀐 회원정보 파일에 기록
{
    FILE *fp = fopen("member.txt", "w");
    Node *iter = head;
    while (iter != NULL)
    {
        fprintf(fp, "%s %s %s\n", iter->id, iter->pw, iter->name); // 공백으로 구분
        iter = iter->next;
    }
    fclose(fp);
}

void freeNodeList()
{
    Node *current = head;
    while (current != NULL)
    {
        Node *temp = current;
        // 각 멤버 변수의 메모리를 해제
        free(temp->id);
        free(temp->pw);
        free(temp->name);
        current = current->next;
        // 노드 자체를 해제
        free(temp);
    }
}

void freeDictionaryList()
{
    Dictionary *current = first;
    while (current != NULL)
    {
        Dictionary *temp = current;
        // 각 멤버 변수의 메모리를 해제
        free(temp->eng);
        free(temp->kor);
        // 노드 자체를 해제
        current = current->next;
        free(temp);
    }
}

void print_logout() // 로그아웃 상태일 때 화면뷰
{
    printf("==================================\n");
    printf("=========== 2021 SPLUG ===========\n");
    printf("==================================\n");
    printf("==================================\n");
    printf("=              메뉴              =\n");
    printf("         1. 회원가입              \n");
    printf("         2. 로그인                \n");
    printf("         3. 로그아웃              \n");
    printf("         4. 영어 단어 맞히기      \n");
    printf("         5. 회원 탈퇴             \n");
    printf("         6. 프로그램 종료         \n");
    printf("==================================\n");
    printf(": ");
}

void print_login() // 로그인 상태일 때 화면뷰
{
    printf("==================================\n");
    printf("=========== 2021 SPLUG ===========\n");
    for (int i = 0; i < 33 - strlen(myID); i++)
        printf("=");
    printf(" ");
    printf("%s\n", myID);
    printf("==================================\n");
    printf("==================================\n");
    printf("=              메뉴              =\n");
    printf("         1. 회원가입              \n");
    printf("         2. 로그인                \n");
    printf("         3. 로그아웃              \n");
    printf("         4. 영어 단어 맞히기      \n");
    printf("         5. 회원 탈퇴             \n");
    printf("         6. 프로그램 종료         \n");
    printf("==================================\n");
    printf(": ");
}

int main()
{
    call_memberlist();
    call_diclist();
    while (1)
    {
        if (is_login == 0)
            print_logout();
        else
            print_login();

        char ch[123];
        scanf("%s", ch);
        if (ch[0] < '0' || ch[0] > '6' || ch[1] != '\0')
        {
            printf("잘못된 값을 입력하였습니다. 다시 입력해 주세요\n");
            continue;
        }
        int option = ch[0] - '0';

        switch (option)
        {
        case 1:
            join();
            break;
        case 2:
            login();
            break;
        case 3:
            if (is_login == 0)
                printf("로그인 되지 않았습니다. 다시 시도하세요.\n");
            else
                logout();
            break;
        case 4:
            if (is_login == 0)
                printf("로그인 후 이용해주세요.\n");
            else
                quiz();
            break;
        case 5:
            if (is_login == 0)
                printf("로그인 상태가 아닙니다.\n");
            else
                withdrawal();
            break;
        case 6:
            terminate = 1;
            printf("다음에 또 만나요!!");
            break;
        }

        if (terminate == 1)
        {
            write_new_memberlist();
            break;
        }
        printf("\n");
    }
    freeNodeList();
    freeDictionaryList();
    return 0;
}