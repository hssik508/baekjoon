// 파일 읽기+문자열 파싱(문법 오류 뜰시 파일 생성 안하고 재입력 받는 예외처리는 아직 안함)

// 실제 파싱할 때는 juso 벡터 활용해서 파싱할듯?
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// RISC-V 명령어 구조 정의
// R타입
#define ADD_OPCODE 0x33
#define SUB_OPCODE 0x33
#define AND_OPCODE 0x33
#define OR_OPCODE 0x33
#define XOR_OPCODE 0x33
#define SLL_OPCODE 0x33
#define SRL_OPCODE 0x33
#define SRA_OPCODE 0x33

#define ADD_FUNCT3 0x0
#define SUB_FUNCT3 0x0
#define AND_FUNCT3 0x7
#define OR_FUNCT3 0x6
#define XOR_FUNCT3 0x4
#define SLL_FUNCT3 0x1
#define SRL_FUNCT3 0x5
#define SRA_FUNCT3 0x5

#define ADD_FUNCT7 0x0
#define SUB_FUNCT7 0x20
#define AND_FUNCT7 0x0
#define OR_FUNCT7 0x0
#define XOR_FUNCT7 0x0
#define SLL_FUNCT7 0x0
#define SRL_FUNCT7 0x0
#define SRA_FUNCT7 0x20

// I타입
#define ADDI_OPCODE 0x13
#define ANDI_OPCODE 0x13
#define ORI_OPCODE 0x13
#define XORI_OPCODE 0x13
#define SLLI_OPCODE 0x13
#define SRLI_OPCODE 0x13
#define SRAI_OPCODE 0x13
#define LW_OPCODE 0x03
#define JALR_OPCODE 0x67

#define ADDI_FUNC3 0x0
#define ANDI_FUNC3 0x7
#define ORI_FUNC3 0x6
#define XORI_FUNC3 0x4
#define SLLI_FUNC3 0x1
#define SRLI_FUNC3 0x5
#define SRAI_FUNC3 0x5
#define LW_FUNC3 0x2
#define JALR_FUNC3 0x0

#define SLLI_FUNC7 0x0
#define SRLI_FUNC7 0x0
#define SRAI_FUNC7 0x20

// S타입
#define SW_OPCODE 0x23

#define SW_FUNC3 0x2

// SB타입
#define BEQ_OPCODE 0x63
#define BNE_OPCODE 0x63
#define BGE_OPCODE 0x63
#define BLT_OPCODE 0x63

#define BEQ_FUNC3 0x0
#define BNE_FUNC3 0x1
#define BGE_FUNC3 0x5
#define BLT_FUNC3 0x4

// UJ타입
#define JAL_OPCODE 0x6F

// EXIT
#define EXIT 0xFFFFFFFF

// 벡터(c++ 처럼 관리) 관리 구조체 -> vector<string> Vector 과 동일한 기능
typedef struct
{
    char **data;     // 문자열 포인터 배열
    size_t size;     // 현재 저장된 문자열 개수
    size_t capacity; // 배열의 총 용량
} Vector;

Vector *inst;  // 파일에 적혀있는 문자열 저장할 벡터
Vector *parse; // 파싱한 문자열 저장할 벡터 선언

// 함수 선언부
int get_register(char *reg);
void clean_input(char *input, char *cleaned);
void type_check(char *str);
void handle_R_type(char *str);
void handle_I1_type(char *str);
void handle_I2_type(char *str);
void handle_S_type(char *str);
void handle_SB_type(char *str);
void handle_UJ_type(char *str);
void handle_exit(char *str);
void uppercase(char *str);
void lowercase(char *str);
void print_binary(int num);
int is_num(char *str);
void init_vector(Vector *vec);
void push_back(Vector *vec, const char *str);
void free_vector(Vector *vec);
void file_read(char *name);

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
        char ch[1024];
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

void type_check(char *str) // 무슨 타입 명령어인지 확인 후 그 타입에 맞는 함수 호출
{
    char op[100]; // operation(명령어 저장)
    sscanf(str, "%s", op);
    uppercase(op); // 대문자 변환
    // 명령어에 따라 분류하고 나머지 인수를 처리하는 함수 호출
    if (strcmp(op, "ADD") == 0 || strcmp(op, "SUB") == 0 || strcmp(op, "AND") == 0 || strcmp(op, "OR") == 0 ||
        strcmp(op, "XOR") == 0 || strcmp(op, "SLL") == 0 || strcmp(op, "SRL") == 0 || strcmp(op, "SRA") == 0)
        handle_R_type(str);
    else if (strcmp(op, "ADDI") == 0 || strcmp(op, "ANDI") == 0 || strcmp(op, "ORI") == 0 || strcmp(op, "XORI") == 0 ||
             strcmp(op, "SLLI") == 0 || strcmp(op, "SRLI") == 0 || strcmp(op, "SRAI") == 0)
        handle_I1_type(str);
    else if (strcmp(op, "LW") == 0 || strcmp(op, "JALR") == 0)
        handle_I2_type(str);
    else if (strcmp(op, "SW") == 0)
        handle_S_type(str);
    else if (strcmp(op, "BEQ") == 0 || strcmp(op, "BNE") == 0 || strcmp(op, "BGE") == 0 || strcmp(op, "BLT") == 0)
        handle_SB_type(str);
    else if (strcmp(op, "JAL") == 0)
        handle_UJ_type(str);
    else if (strcmp(op, "EXIT") == 0)
        handle_exit(str);
    else if (op[strlen(op) - 1] == ':')
    {
        return; // 라벨인 경우 함수 종료 후 다음 명령어 입력받도록 함
    }
    else // 예외처리: 잘못된 명령어
    {
        printf("Syntax Error!!\n");
        return;
    }
}

void handle_R_type(char *str)
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

    int opcode = 0, funct3 = 0, funct7 = 0;

    if (strcmp(op, "ADD") == 0)
    {
        opcode = ADD_OPCODE;
        funct3 = ADD_FUNCT3;
        funct7 = ADD_FUNCT7;
    }
    else if (strcmp(op, "SUB") == 0)
    {
        opcode = SUB_OPCODE;
        funct3 = SUB_FUNCT3;
        funct7 = SUB_FUNCT7;
    }
    else if (strcmp(op, "AND") == 0)
    {
        opcode = AND_OPCODE;
        funct3 = AND_FUNCT3;
        funct7 = AND_FUNCT7;
    }
    else if (strcmp(op, "OR") == 0)
    {
        opcode = OR_OPCODE;
        funct3 = OR_FUNCT3;
        funct7 = OR_FUNCT7;
    }
    else if (strcmp(op, "XOR") == 0)
    {
        opcode = XOR_OPCODE;
        funct3 = XOR_FUNCT3;
        funct7 = XOR_FUNCT7;
    }
    else if (strcmp(op, "SLL") == 0)
    {
        opcode = SLL_OPCODE;
        funct3 = SLL_FUNCT3;
        funct7 = SLL_FUNCT7;
    }
    else if (strcmp(op, "SRL") == 0)
    {
        opcode = SRL_OPCODE;
        funct3 = SRL_FUNCT3;
        funct7 = SRL_FUNCT7;
    }
    else if (strcmp(op, "SRA") == 0)
    {
        opcode = SRA_OPCODE;
        funct3 = SRA_FUNCT3;
        funct7 = SRA_FUNCT7;
    }

    int machine_code = (funct7 << 25) | (rs2_num << 20) | (rs1_num << 15) | (funct3 << 12) | (rd_num << 7) | opcode;
    print_binary(machine_code);
}

void handle_I1_type(char *str) // 일반적인 I타입
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

    int opcode = 0, funct3 = 0, funct7 = 0;

    if (strcmp(op, "ADDI") == 0)
    {
        opcode = ADDI_OPCODE;
        funct3 = ADDI_FUNC3;
    }
    else if (strcmp(op, "ANDI") == 0)
    {
        opcode = ADDI_OPCODE;
        funct3 = ANDI_FUNC3;
    }
    else if (strcmp(op, "ORI") == 0)
    {
        opcode = ORI_OPCODE;
        funct3 = ORI_FUNC3;
    }
    else if (strcmp(op, "XORI") == 0)
    {
        opcode = XORI_OPCODE;
        funct3 = XORI_FUNC3;
    }
    else if (strcmp(op, "SLLI") == 0)
    {
        opcode = SLLI_OPCODE;
        funct3 = SLLI_FUNC3;
        funct7 = SLLI_FUNC7;
    }
    else if (strcmp(op, "SRLI") == 0)
    {
        opcode = SRLI_OPCODE;
        funct3 = SRLI_FUNC3;
        funct7 = SRLI_FUNC7;
    }
    else if (strcmp(op, "SRAI") == 0)
    {
        opcode = SRAI_OPCODE;
        funct3 = SRAI_FUNC3;
        funct7 = SRAI_FUNC7;
    }

    int machine_code;
    if (strcmp(op, "SLLI") == 0 || strcmp(op, "SRLI") == 0 || strcmp(op, "SRAI") == 0)
        machine_code = (funct7 << 25) | (immValue << 20) | (rs1_num << 15) | (funct3 << 12) | (rd_num << 7) | opcode;
    else
        machine_code = (immValue << 20) | (rs1_num << 15) | (funct3 << 12) | (rd_num << 7) | opcode;
    print_binary(machine_code);
}

void handle_I2_type(char *str) // LW, JALR
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

    int opcode = 0, funct3 = 0;

    if (strcmp(op, "LW") == 0)
    {
        opcode = LW_OPCODE;
        funct3 = LW_FUNC3;
    }
    else if (strcmp(op, "JALR") == 0)
    {
        opcode = JALR_OPCODE;
        funct3 = JALR_FUNC3;
    }

    int machine_code = (immValue << 20) | (rs1_num << 15) | (funct3 << 12) | (rd_num << 7) | opcode;
    print_binary(machine_code);
}

void handle_S_type(char *str)
{
    char op[100], rs2[100], tmp[100], rs1[100], imm[100]; // tmp: 괄호 분리해서 rs1과 imm값 추출하기 위한 임시배열
    sscanf(str, "%s %s %s", op, rs2, tmp);

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
    lowercase(rs2);
    lowercase(rs1);

    int rs2_num = get_register(rs2);
    int rs1_num = get_register(rs1);
    int immValue = atoi(imm);

    if (rs2_num == 999 || rs1_num == 999)
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

    int imm_high = (immValue >> 5) & 0b1111111; // 상위 7비트
    int imm_low = immValue & 0b11111;           // 하위 5비트

    int opcode = 0, funct3 = 0;

    if (strcmp(op, "SW") == 0)
    {
        opcode = SW_OPCODE;
        funct3 = SW_FUNC3;
    }

    int machine_code = (imm_high << 25) | (rs2_num << 20) | (rs1_num << 15) | (funct3 << 12) | (imm_low << 7) | opcode;
    print_binary(machine_code);
}

void handle_SB_type(char *str) // 라벨 주소를 가져와야 하므로 일단 int형으로 주소값이 들어온다고 가정
{
    // 실제 SB타입 파싱할 떄는 imm[100]대신 lb[100] 사용, imm값은 라벨 주소 - juso벡터에 저장돼있는 현재 명령어의 주소, **라벨 없을 시 예외처리 하기
    char op[100], rs1[100], rs2[100], imm[100];
    sscanf(str, "%s %s %s %s", op, rs1, rs2, imm);

    if (!is_num(imm))
    {
        printf("Syntax Error!!\n");
        return;
    }

    // 이거 활성화 시키기
    // int exist = 0, imm;
    // for (int i = 0; i < label->size; i++)
    // {
    //     if (strcmp(label->data[i].instruction, lb) == 0)
    //     {
    //         exist = 1;
    //         imm = label->data[i].address - pc; // imm값은 타겟 라벨 주소에서 현재 주소를 뺀 값임
    //     }
    // }

    uppercase(op);
    lowercase(rs2);
    lowercase(rs1);

    int rs2_num = get_register(rs2);
    int rs1_num = get_register(rs1);
    int immValue = atoi(imm);

    if (rs2_num == 999 || rs1_num == 999)
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

    int imm_12 = (immValue >> 12) & 0b1;       // imm[12]
    int imm_10_5 = (immValue >> 5) & 0b111111; // imm[10:5]
    int imm_4_1 = (immValue >> 1) & 0b1111;    // imm[4:1]
    int imm_11 = (immValue >> 11) & 0b1;       // imm[11]

    int opcode = 0, funct3 = 0;

    if (strcmp(op, "BEQ") == 0)
    {
        opcode = BEQ_OPCODE;
        funct3 = BEQ_FUNC3;
    }
    else if (strcmp(op, "BNE") == 0)
    {
        opcode = BNE_OPCODE;
        funct3 = BNE_FUNC3;
    }
    else if (strcmp(op, "BGE") == 0)
    {
        opcode = BGE_OPCODE;
        funct3 = BGE_FUNC3;
    }
    else if (strcmp(op, "BLT") == 0)
    {
        opcode = BLT_OPCODE;
        funct3 = BLT_FUNC3;
    }

    int machine_code = (imm_12 << 31) | (imm_10_5 << 25) | (rs2_num << 20) | (rs1_num << 15) | (funct3 << 12) |
                       (imm_4_1 << 8) | (imm_11 << 7) | opcode;
    print_binary(machine_code);
}

void handle_UJ_type(char *str)
{
    // 실제 UJ타입 파싱할 떄는 imm[100]대신 lb[100] 사용, imm값은 라벨 주소 - juso벡터에 저장돼있는 현재 명령어의 주소
    char op[100], rd[100], imm[100];
    sscanf(str, "%s %s %s", op, rd, imm);

    if (!is_num(imm))
    {
        printf("Syntax Error!!\n");
        return;
    }

    uppercase(op);
    lowercase(rd);

    int rd_num = get_register(rd);
    int immValue = atoi(imm);

    if (rd_num == 999)
    {
        printf("Syntax Error!!\n");
        return;
    }
    else
    {
        if (immValue < -pow(2, 19) || immValue > pow(2, 19) - 1)
        {
            printf("Syntax Error!!\n");
            return;
        }
    }

    int imm_20 = (immValue >> 20) & 0b1;           // imm[20]
    int imm_10_1 = (immValue >> 1) & 0b1111111111; // imm[10:1]
    int imm_11 = (immValue >> 11) & 0b1;           // imm[11]
    int imm_19_12 = (immValue >> 12) & 0b11111111; // imm[19:12]

    int opcode = 0;

    if (strcmp(op, "JAL") == 0)
    {
        opcode = JAL_OPCODE;
    }

    int machine_code = (imm_20 << 31) | (imm_19_12 << 12) | (imm_11 << 20) | (imm_10_1 << 21) | (rd_num << 7) | opcode;
    print_binary(machine_code);
}

void handle_exit(char *str)
{
    int machine_code = 0xFFFFFFFF;
    print_binary(machine_code);
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

void print_binary(int num) // 32비트 기계어 출력 함수
{
    char parsed[33]; // 32비트 + 널 문자
    for (int i = 31; i >= 0; i--)
    {
        int n = (num >> i) & 1;   // 각 비트를 추출
        parsed[31 - i] = '0' + n; // '0' 또는 '1'을 저장
    }
    parsed[32] = '\0'; // 문자열 종료

    push_back(parse, parsed); // parsed 문자열을 vec에 저장
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

int main()
{
    // 벡터 포인터 공간 할당(Vector 구조체 접근하는 용도)
    inst = (Vector *)malloc(sizeof(Vector));
    parse = (Vector *)malloc(sizeof(Vector));
    while (1)
    {
        init_vector(inst); // 벡터 초기화('vector<string> data' 역할 하고있는 char** data의 공간 할당)
        init_vector(parse);
        char name[1024];
        printf("Enter Input File Name: ");
        scanf("%s", name);
        if (strcmp(name, "terminate") == 0) // 파일 이름 대신 terminate가 입력되면 종료
            break;
        file_read(name);

        for (size_t i = 0; i < inst->size; i++) // 문자열 파싱 후 배열에 저장
        {
            char *ch = inst->data[i];
            type_check(ch);
        }

        for (size_t i = 0; i < parse->size; i++)
        {
            printf("%s\n", parse->data[i]);
        }

        free(inst); // 메모리 해제
        free(parse);
    }
    return 0;
}
