// 파일 입력받아서 벡터에 저장 후 출력 코드
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 벡터(c++ 처럼 관리) 관리 구조체 -> vector<string> Vector 과 동일한 기능
typedef struct
{
    char **data;     // 문자열 포인터 배열
    size_t size;     // 현재 저장된 문자열 개수
    size_t capacity; // 배열의 총 용량
} Vector;

// 벡터 초기화
void init_vector(Vector *vec)
{
    vec->data = (char **)malloc(30 * sizeof(char *)); // 행의 개수 초기화
    vec->size = 0;
    vec->capacity = 30; // 초기 용량: 30
}

// 벡터에 문자열 추가
void push_back(Vector *vec, const char *str)
{
    if (vec->size == vec->capacity) // 벡터 크기 확장
    {
        vec->capacity *= 2;
        vec->data = (char **)realloc(vec->data, vec->capacity * sizeof(char *));
    }
    vec->data[vec->size] = strdup(str); // 문자열 복사 및 저장
    vec->size++;
}

// 벡터 메모리 해제
void free_vector(Vector *vec)
{
    for (size_t i = 0; i < vec->size; i++)
    {
        free(vec->data[i]); // 각 문자열 메모리 해제
    }
    free(vec->data); // 배열 자체 해제
}

void file_read(char *name, Vector *vec)
{
    FILE *fp;
    char *s = name;
    fp = fopen(s, "r");
    if (fp == NULL)
    {
        printf("Input file does not exist!!\n");
        return;
    }
    char *res;
    while (1)
    {
        char ch[1024];
        res = fgets(ch, sizeof(ch), fp);
        if (res == NULL)
            break;
        size_t len = strlen(ch);
        if (len > 0 && ch[len - 1] == '\n')
        {
            ch[len - 1] = '\0';
        }
        push_back(vec, res);
    }
    fclose(fp);
}

int main()
{
    while (1)
    {
        Vector line;   // 파일에 적혀있는 문자열 저장할 벡터 선언
        init_vector(&line); // 벡터 초기화

        char name[1024];
        printf("Enter Input File Name: ");
        scanf("%s", name);
        if (strcmp(name, "terminate") == 0) // 파일 이름 대신 terminate가 입력되면 종료
            break;
        file_read(name, &line);

        // 내용 출력
        for (size_t i = 0; i < line.size; i++)
        {
            printf("%s\n", line.data[i]);
        }
        free_vector(&line); // 메모리 해제
    }
    return 0;
}

// fgetc: 파일에서 한 문자씩 입력받음
// fputc: 파일에 한 문자씩 출력함
// fgets: 파일에서 한 줄씩 입력받음
// fputs: 파일에서 한 줄씩 출력함
// 미션 - 일단 파일에서 문자열 한줄 받아와서 조건에 맞게 문자열을 분리하여 후 저장