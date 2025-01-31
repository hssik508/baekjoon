#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeToFile(const char* inputFilename, char** stringArray, int stringCount, int* intArray, int intCount) {
    // 파일 이름을 생성하기 위한 버퍼
    char baseFilename[256];
    strcpy(baseFilename, inputFilename);
    // 확장자 제거
    char* dotPosition = strrchr(baseFilename, '.');
    if (dotPosition != NULL) {
        *dotPosition = '\0'; // 확장자 제거
    }
    // .o 파일 생성
    char oFilename[256];
    sprintf(oFilename, "%s.o", baseFilename);
    FILE* oFile = fopen(oFilename, "w");
    if (oFile == NULL) {
        perror("fileopen failed (.o)");
        exit(1);
    }
    // 문자열 배열 내용 쓰기
    for (int i = 0; i < stringCount; i++) {
        fprintf(oFile, "%s\n", stringArray[i]);
    }
    fclose(oFile);
    // .trace 파일 생성
    char traceFilename[256];
    sprintf(traceFilename, "%s.trace", baseFilename);
    FILE* traceFile = fopen(traceFilename, "w");
    if (traceFile == NULL) {
        perror("fileopen failed (.trace)");
        exit(1);
    }
    // 정수 배열 내용 쓰기
    for (int i = 0; i < intCount; i++) {
        fprintf(traceFile, "%d\n", intArray[i]);
    }
    fclose(traceFile);
}

int main() {
    // 문자열 배열 초기화
    char* strings[] = {
        "Hello, world!",
        "Welcome to C programming",
        "File I/O is fun!",
        "ex"
    };
    int stringCount = sizeof(strings) / sizeof(strings[0]);

    // 정수 배열 초기화
    int numbers[] = {10, 20, 30, 40, 50, 1424};
    int intCount = sizeof(numbers) / sizeof(numbers[0]);

    // 사용자로부터 파일 이름 입력받기
    char inputFilename[256];
    printf("input filename: ");
    scanf("%s", inputFilename);

    // 파일 생성 함수 호출
    writeToFile(inputFilename, strings, stringCount, numbers, intCount); 
    // (파일이름 저장한 문자열, char** 배열, char**배열 사이즈, int 배열, int 배열 크기)
    // 실제 합칠 때는 int형 배열 대신 구조체 배열형으로 넣어야할듯?
    return 0;
}
