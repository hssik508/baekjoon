// 파일 읽기+주소 저장(문법 오류 뜰시 파일 생성 안하고 재입력 받는 예외처리는 아직 안함)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int reg[32] = {0};
int pc = 1000; // 시작주소

// 벡터(c++ 처럼 관리) 관리 구조체 -> vector<string> Vector 과 동일한 기능
typedef struct
{
    char **data;     // 문자열 포인터 배열
    size_t size;     // 현재 저장된 문자열 개수
    size_t capacity; // 배열의 총 용량
} Vector;

Vector *inst;  // 파일에 적혀있는 문자열 저장할 벡터
Vector *parse; // 파싱한 문자열 저장할 벡터 선언

// 각 명령어의 주소 저장(라벨 저장 겸용)
typedef struct
{
    char instruction[1024];
    int address;
} Juso;

// Juso 벡터
typedef struct
{
    Juso *data;      // 동적 배열
    size_t size;     // 현재 요소 개수
    size_t capacity; // 현재 용량
} JusoVector;

JusoVector *juso;  // 명령어와 그 명령어가 위치한 주소 저장용
JusoVector *label; // 라벨 이름 및 주소 저장용
JusoVector *trace; // 코드가 실행되면서 나타나는 실제 주소 추적용

size_t I; // trace할때 사용

// 함수 선언부
int get_register(char *reg);
void clean_input(char *input, char *cleaned);

void operation_R_type(char *str);
void operation_I1_type(char *str);
void operation_I2_type(char *str);
void operation_S_type(char *str);
void operation_SB_type(char *str);
void operation_UJ_type(char *str);
void operation_exit(char *str);

void uppercase(char *str);
void lowercase(char *str);
int is_num(char *str);

void init_vector(Vector *vec);
void push_back(Vector *vec, const char *str);
void free_vector(Vector *vec);
void init_juso_vector(JusoVector *vec);
void push_back_juso(JusoVector *vec, const char *inst, int address);
void free_juso_vector(JusoVector *vec);
void init_register();

void trace_pc();

void file_read(char *name);
void print_address(JusoVector *vec);

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

// JusoVector 초기화
void init_juso_vector(JusoVector *vec)
{
    vec->data = (Juso *)malloc(30 * sizeof(Juso)); // 초기 용량 30
    vec->size = 0;
    vec->capacity = 30;
}

// JusoVector에 Juso 추가
void push_back_juso(JusoVector *vec, const char *inst, int address)
{
    if (vec->size == vec->capacity)
    { // 용량 초과 시 크기 확장
        vec->capacity *= 2;
        vec->data = (Juso *)realloc(vec->data, vec->capacity * sizeof(Juso));
    }
    strncpy(vec->data[vec->size].instruction, inst, sizeof(vec->data[vec->size].instruction) - 1);
    vec->data[vec->size].instruction[sizeof(vec->data[vec->size].instruction) - 1] = '\0';
    vec->data[vec->size].address = address;
    vec->size++;
}

// JusoVector 메모리 해제
void free_juso_vector(JusoVector *vec)
{
    free(vec->data);
}

void file_read(char *name)
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
        char ch[12345];
        res = fgets(ch, sizeof(ch), fp);
        if (res == NULL)
            break;
        size_t len = strlen(ch);
        if (len > 0 && ch[len - 1] == '\n')
        {
            ch[len - 1] = '\0';
        }

        char cleaned[1000]; // 공백, 쉼표, 탭 제거된 깔끔한 형태로 저장할 배열
        clean_input(res, cleaned);

        // 입력 내용이 비었거나 유효하지 않다면 건너뜀
        if (strlen(cleaned) == 0)
        {
            continue;
        }

        push_back(inst, cleaned);
        char op[100];
        sscanf(cleaned, "%s", op);
        uppercase(op); // 대문자 변환(라벨인 경우에 대문자로 바꾸기 위함)
        if (op[strlen(op) - 1] == ':')
        {
            char lb[100];
            strncpy(lb, op, strlen(op) - 1);
            lb[strlen(op) - 1] = '\0';
            push_back_juso(label, lb, pc); // 라벨인 경우 라벨 벡터에 라벨 이름 및 주소 삽입
            continue;
        }
        push_back_juso(juso, cleaned, pc);
        pc += 4;
    }
    fclose(fp);
}

int get_register(char *reg)
{
    if (strcmp(reg, "x0") == 0)
        return 0;
    if (strcmp(reg, "x1") == 0)
        return 1;
    if (strcmp(reg, "x2") == 0)
        return 2;
    if (strcmp(reg, "x3") == 0)
        return 3;
    if (strcmp(reg, "x4") == 0)
        return 4;
    if (strcmp(reg, "x5") == 0)
        return 5;
    if (strcmp(reg, "x6") == 0)
        return 6;
    if (strcmp(reg, "x7") == 0)
        return 7;
    if (strcmp(reg, "x8") == 0)
        return 8;
    if (strcmp(reg, "x9") == 0)
        return 9;
    if (strcmp(reg, "x10") == 0)
        return 10;
    if (strcmp(reg, "x11") == 0)
        return 11;
    if (strcmp(reg, "x12") == 0)
        return 12;
    if (strcmp(reg, "x13") == 0)
        return 13;
    if (strcmp(reg, "x14") == 0)
        return 14;
    if (strcmp(reg, "x15") == 0)
        return 15;
    if (strcmp(reg, "x16") == 0)
        return 16;
    if (strcmp(reg, "x17") == 0)
        return 17;
    if (strcmp(reg, "x18") == 0)
        return 18;
    if (strcmp(reg, "x19") == 0)
        return 19;
    if (strcmp(reg, "x20") == 0)
        return 20;
    if (strcmp(reg, "x21") == 0)
        return 21;
    if (strcmp(reg, "x22") == 0)
        return 22;
    if (strcmp(reg, "x23") == 0)
        return 23;
    if (strcmp(reg, "x24") == 0)
        return 24;
    if (strcmp(reg, "x25") == 0)
        return 25;
    if (strcmp(reg, "x26") == 0)
        return 26;
    if (strcmp(reg, "x27") == 0)
        return 27;
    if (strcmp(reg, "x28") == 0)
        return 28;
    if (strcmp(reg, "x29") == 0)
        return 29;
    if (strcmp(reg, "x30") == 0)
        return 30;
    if (strcmp(reg, "x31") == 0)
        return 31;
    else // 잘못된 값이 들어왔을 경우
        return 999;
}

void clean_input(char *input, char *cleaned) // 문자열 예외처리
{
    int i = 0, j = 0; // i: 입력 문자열 순회용, j: 결과 문자열에 글자 저장용
    while (input[i] != '\0')
    {
        if (!isspace(input[i]) && input[i] != ',') // 공백, 탭, 쉼표인경우 스킵
            cleaned[j++] = input[i];
        else if (j > 0 && cleaned[j - 1] != ' ') // 단어 간 공백 하나만 추가
            cleaned[j++] = ' ';
        i++;
    }
    // 마지막 공백 제거
    if (j > 0 && cleaned[j - 1] == ' ')
    {
        j--;
    }
    cleaned[j] = '\0'; // 문자열 끝 처리
}

void operation_R_type(char *str)
{
    char op[100], rd[100], rs1[100], rs2[100];
    sscanf(str, "%s %s %s %s", op, rd, rs1, rs2);

    uppercase(op);
    lowercase(rd);
    lowercase(rs1);
    lowercase(rs2);

    int rd_num = get_register(rd);
    int rs1_num = get_register(rs1);
    int rs2_num = get_register(rs2);

    if (rd_num == 999 || rs1_num == 999 || rs2_num == 999) // 예외처리: 잘못된 레지스터 번호
    {
        printf("Syntax Error!!\n");
        return;
    }

    if (strcmp(op, "ADD") == 0)
    {
        reg[rd_num] = reg[rs1_num] + reg[rs2_num];
    }
    else if (strcmp(op, "SUB") == 0)
    {
        reg[rd_num] = reg[rs1_num] - reg[rs2_num];
    }
    else if (strcmp(op, "AND") == 0)
    {
        reg[rd_num] = reg[rs1_num] & reg[rs2_num];
    }
    else if (strcmp(op, "OR") == 0)
    {
        reg[rd_num] = reg[rs1_num] | reg[rs2_num];
    }
    else if (strcmp(op, "XOR") == 0)
    {
        reg[rd_num] = reg[rs1_num] ^ reg[rs2_num];
    }
    else if (strcmp(op, "SLL") == 0)
    {
        reg[rd_num] = reg[rs1_num] << reg[rs2_num];
    }
    else if (strcmp(op, "SRL") == 0)
    {
        reg[rd_num] = (unsigned int)reg[rs1_num] >> reg[rs2_num];
    }
    else if (strcmp(op, "SRA") == 0)
    {
        reg[rd_num] = reg[rs1_num] >> reg[rs2_num];
    }

    pc += 4;
}

void operation_I1_type(char *str) // 일반적인 I타입
{
    char op[100], rd[100], rs1[100], imm[100];
    sscanf(str, "%s %s %s %s", op, rd, rs1, imm);

    uppercase(op);
    lowercase(rd);
    lowercase(rs1);

    if (!is_num(imm)) // 숫자 맞는지 체크
    {
        printf("Syntax Error!!\n");
        return;
    }

    int rd_num = get_register(rd);
    int rs1_num = get_register(rs1);
    int immValue = atoi(imm);

    if (rd_num == 999 || rs1_num == 999)
    {
        printf("Syntax Error!!\n");
        return;
    }
    else if (strcmp(op, "SLLI") == 0 || strcmp(op, "SRLI") == 0 || strcmp(op, "SRAI") == 0)
    {
        if (immValue < 0 || immValue > 31) // SR시리즈는 5비트 값 (0 ~ 31)
        {
            printf("Syntax Error!!\n");
            return;
        }
    }
    else
    {
        if (immValue < -pow(2, 11) || immValue > pow(2, 11) - 1) // immValue는 12비트 부호 있는 값 (-2048 ~ 2047)
        {
            printf("Syntax Error!!\n");
            return;
        }
    }

    if (strcmp(op, "ADDI") == 0)
    {
        reg[rd_num] = reg[rs1_num] + immValue;
    }
    else if (strcmp(op, "ANDI") == 0)
    {
        reg[rd_num] = reg[rs1_num] & immValue;
    }
    else if (strcmp(op, "ORI") == 0)
    {
        reg[rd_num] = reg[rs1_num] | immValue;
    }
    else if (strcmp(op, "XORI") == 0)
    {
        reg[rd_num] = reg[rs1_num] ^ immValue;
    }
    else if (strcmp(op, "SLLI") == 0)
    {
        reg[rd_num] = reg[rs1_num] << immValue;
    }
    else if (strcmp(op, "SRLI") == 0)
    {
        reg[rd_num] = (unsigned int)reg[rs1_num] >> immValue;
    }
    else if (strcmp(op, "SRAI") == 0)
    {
        reg[rd_num] = reg[rs1_num] >> immValue;
    }

    pc += 4;
}

void operation_I2_type(char *str) // LW, JALR
{
    char op[100], rd[100], tmp[100], rs1[100], imm[100]; // tmp: 괄호 분리해서 rs1과 imm값 추출하기 위한 임시배열
    sscanf(str, "%s %s %s", op, rd, tmp);

    int i = 0, error = 1;
    while (tmp[i] != '\0')
    {
        if (tmp[i] == ')')
        {
            error = 0;
            break;
        }
        else if (tmp[i] == '(')
            tmp[i] = ' ';
        i++;
    }
    tmp[i] = '\0';

    if (error == 1)
    {
        printf("Syntax Error!!\n");
        return;
    }

    sscanf(tmp, "%s %s", imm, rs1);

    if (!is_num(imm))
    {
        printf("Syntax Error!!\n");
        return;
    }

    uppercase(op);
    lowercase(rd);
    lowercase(rs1);

    int rd_num = get_register(rd);
    int rs1_num = get_register(rs1);
    int immValue = atoi(imm);

    if (rd_num == 999 || rs1_num == 999)
    {
        printf("Syntax Error!!\n");
        return;
    }
    else
    {
        if (immValue < -pow(2, 11) || immValue > pow(2, 11) - 1)
        {
            printf("Syntax Error!!\n");
            return;
        }
    }

    if (strcmp(op, "LW") == 0)
    {
        reg[rd_num] = 0;
        pc += 4;
        I++;
    }
    else if (strcmp(op, "JALR") == 0)
    {
        if (rd_num != 0)
        {
            reg[rd_num] = pc + 4;
        }

        // 점프 주소 계산
        int target_address = (reg[rs1_num] + immValue) & ~1;
        if (target_address < 0) // 예외 처리: 잘못된 주소
        {
            printf("Syntax Error!!\n");
            return;
        }
        // 점프 대상 주소가 juso 벡터에 존재하는지 확인
        int found = 0;
        for (size_t i = 0; i < juso->size; i++)
        {
            if (juso->data[i].address == target_address)
            {
                pc = target_address; // PC 갱신
                I = i;               // 인덱스 갱신
                found = 1;
                break;
            }
        }
        // 점프 대상 명령어를 찾지 못한 경우
        if (!found)
        {
            printf("Syntax Error!!\n");
            return;
        }
    }
}

void operation_S_type(char *str)
{
    // char op[100], rs2[100], tmp[100], rs1[100], imm[100]; // tmp: 괄호 분리해서 rs1과 imm값 추출하기 위한 임시배열
    // sscanf(str, "%s %s %s", op, rs2, tmp);

    // int i = 0, error = 1;
    // while (tmp[i] != '\0')
    // {
    //     if (tmp[i] == ')')
    //     {
    //         error = 0;
    //         break;
    //     }
    //     else if (tmp[i] == '(')
    //         tmp[i] = ' ';
    //     i++;
    // }
    // tmp[i] = '\0';

    // if (error == 1)
    // {
    //     printf("Syntax Error!!\n");
    //     return;
    // }

    // sscanf(tmp, "%s %s", imm, rs1);

    // if (!is_num(imm))
    // {
    //     printf("Syntax Error!!\n");
    //     return;
    // }

    // uppercase(op);
    // lowercase(rs2);
    // lowercase(rs1);

    // int rs2_num = get_register(rs2);
    // int rs1_num = get_register(rs1);
    // int immValue = atoi(imm);

    // if (rs2_num == 999 || rs1_num == 999)
    // {
    //     printf("Syntax Error!!\n");
    //     return;
    // }
    // else
    // {
    //     if (immValue < -pow(2, 11) || immValue > pow(2, 11) - 1)
    //     {
    //         printf("Syntax Error!!\n");
    //         return;
    //     }
    // }
    pc += 4;
}

void operation_SB_type(char *str)
{
    char op[100], rs1[100], rs2[100], lb[100];
    sscanf(str, "%s %s %s %s", op, rs1, rs2, lb);

    uppercase(lb); // 라벨 대문자 변환
    lowercase(rs1);
    lowercase(rs2);

    int rs1_num = get_register(rs1);
    int rs2_num = get_register(rs2);

    if (rs1_num == 999 || rs2_num == 999)
    {
        printf("Syntax Error!!");
        return;
    }

    int target_address = -1;
    for (size_t i = 0; i < label->size; i++)
    {
        if (strcmp(label->data[i].instruction, lb) == 0)
        {
            target_address = label->data[i].address;
            break;
        }
    }

    if (target_address == -1)
    {
        printf("Syntax Error!!");
        return;
    }

    // 점프 조건 처리
    if ((strcmp(op, "BGE") == 0 && reg[rs1_num] >= reg[rs2_num]) ||
        (strcmp(op, "BEQ") == 0 && reg[rs1_num] == reg[rs2_num]) ||
        (strcmp(op, "BNE") == 0 && reg[rs1_num] != reg[rs2_num]) ||
        (strcmp(op, "BLT") == 0 && reg[rs1_num] < reg[rs2_num]))
    {
        // 조건 만족 시 라벨로 점프
        pc = target_address;
        for (size_t i = 0; i < juso->size; i++)
        {
            if (juso->data[i].address == pc)
            {
                I = i;
                return;
            }
        }
    }
    else
    {
        // 조건 불만족 시 다음 명령어로 이동
        pc += 4;
        I++;
    }
}

void operation_UJ_type(char *str)
{
    char op[100], rd[100], lb[100];
    sscanf(str, "%s %s %s", op, rd, lb);

    uppercase(lb); // 라벨 대문자 변환
    uppercase(op);
    lowercase(rd);

    int rd_num = get_register(rd);

    if (rd_num == 999)
    {
        printf("Syntax Error!!\n");
        return;
    }

    int target_address = -1;
    for (size_t i = 0; i < label->size; i++)
    {
        if (strcmp(label->data[i].instruction, lb) == 0)
        {
            target_address = label->data[i].address;
            break;
        }
    }

    if (target_address == -1)
    {
        printf("Syntax Error!!\n");
        return;
    }

    reg[rd_num] = pc + 4; // 리턴 주소 저장
    pc = target_address;  // 점프할 주소로 PC 갱신

    for (size_t i = 0; i < juso->size; i++) // 어차피 JAL 하나밖에 없음
    {
        if (juso->data[i].address == pc)
        {
            I = i;
            return;
        }
    }
}

void operation_exit(char *str)
{
    I = juso->size;
}

void uppercase(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = toupper((unsigned char)str[i]);
    }
}

void lowercase(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int is_num(char *str)
{
    int i = 0, error = 0;
    if (str[i] == '-') // 음수 처리를 위해 첫 번째 문자가 '-'일 수 있는 경우 처리
    {
        i++;
    }
    while (str[i] != '\0') // 숫자인지 확인
    {
        if (str[i] < '0' || str[i] > '9')
        {
            error = 1;
            break;
        }
        i++;
    }
    if (error == 1 || i == 0) // 숫자가 전혀 없거나 에러인 경우
        return 0;
    else
        return 1;
}

void trace_pc() // 명령어 실행 후 PC 추적
{
    pc = 1000; // PC 초기화
    I = 0;

    while (I < juso->size)
    {
        char *instruction = juso->data[I].instruction; // 현재 명령어
        char op[100];                                  // 명령어 구분
        sscanf(instruction, "%s", op);
        uppercase(op);

        // PC와 명령어 저장
        push_back_juso(trace, instruction, pc);

        if (strcmp(op, "ADD") == 0 || strcmp(op, "SUB") == 0 || strcmp(op, "AND") == 0 ||
            strcmp(op, "OR") == 0 || strcmp(op, "XOR") == 0 || strcmp(op, "SLL") == 0 ||
            strcmp(op, "SRL") == 0 || strcmp(op, "SRA") == 0)
        {
            operation_R_type(instruction);
            I++;
        }
        else if (strcmp(op, "ADDI") == 0 || strcmp(op, "ANDI") == 0 || strcmp(op, "ORI") == 0 ||
                 strcmp(op, "XORI") == 0 || strcmp(op, "SLLI") == 0 || strcmp(op, "SRLI") == 0 ||
                 strcmp(op, "SRAI") == 0)
        {
            operation_I1_type(instruction);
            I++;
        }
        else if (strcmp(op, "LW") == 0 || strcmp(op, "JALR") == 0)
        {
            operation_I2_type(instruction);
        }
        else if (strcmp(op, "SW") == 0)
        {
            operation_S_type(instruction);
            I++;
        }
        else if (strcmp(op, "BEQ") == 0 || strcmp(op, "BNE") == 0 || strcmp(op, "BGE") == 0 || strcmp(op, "BLT") == 0)
        {
            operation_SB_type(instruction);
        }
        else if (strcmp(op, "JAL") == 0)
        {
            operation_UJ_type(instruction);
        }
        else if (strcmp(op, "EXIT") == 0)
        {
            operation_exit(instruction);
        }
        // * 실제 구현 시 is_error가 1이면 trace함수로 돌아왔을 시 함수 종료하는 코드 만들기(안그럼 syntax error가 무한 출력됨)
    }
}

void print_address(JusoVector *vec)
{
    for (size_t i = 0; i < vec->size; i++) // 명령어 및 명령어가 위치한 주소 출력
    {
        printf("%s\n", vec->data[i].instruction);
        printf("%d\n", vec->data[i].address);
    }
}

void init_register() // 레지스터 초기화
{
    for (int i = 0; i < 32; i++)
    {
        reg[i] = 0;
    }
    reg[1] = 1;
    reg[2] = 2;
    reg[3] = 3;
    reg[4] = 4;
    reg[5] = 5;
    reg[6] = 6;
}

int main()
{
    // 벡터 포인터 공간 할당(Vector 구조체 접근하는 용도)
    inst = (Vector *)malloc(sizeof(Vector));
    parse = (Vector *)malloc(sizeof(Vector));
    juso = (JusoVector *)malloc(sizeof(JusoVector));
    label = (JusoVector *)malloc(sizeof(JusoVector));
    trace = (JusoVector *)malloc(sizeof(JusoVector));
    while (1)
    {
        init_vector(inst); // 벡터 초기화('vector<string> data' 역할 하고있는 char** data의 공간 할당)
        init_vector(parse);
        init_juso_vector(juso);
        init_juso_vector(label);
        init_juso_vector(trace);
        init_register();

        char name[1024];
        printf(">> Enter Input File Name: ");
        scanf("%s", name);
        if (strcmp(name, "terminate") == 0) // 파일 이름 대신 terminate가 입력되면 종료
            break;
        pc = 1000; 
        file_read(name);

        trace_pc();
        print_address(trace);
        // print_address(juso);
        // print_address(label);
        free_vector(inst); // 메모리 해제
        free_vector(parse);
        free_juso_vector(juso);
        free_juso_vector(label);
        free_juso_vector(trace);
    }
    return 0;
}
