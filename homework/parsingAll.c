// 문자열 파싱 테스트
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
    char cleaned[1000]; // 공백, 쉼표, 탭 제거된 깔끔한 형태로 저장할 배열
    clean_input(str, cleaned);
    char op[100]; // operation(명령어 저장)
    sscanf(cleaned, "%s", op);
    uppercase(op); // 대문자 변환
    // 명령어에 따라 분류하고 나머지 인수를 처리하는 함수 호출
    if (strcmp(op, "ADD") == 0 || strcmp(op, "SUB") == 0 || strcmp(op, "AND") == 0 || strcmp(op, "OR") == 0 ||
        strcmp(op, "XOR") == 0 || strcmp(op, "SLL") == 0 || strcmp(op, "SRL") == 0 || strcmp(op, "SRA") == 0)
        handle_R_type(cleaned);
    else if (strcmp(op, "ADDI") == 0 || strcmp(op, "ANDI") == 0 || strcmp(op, "ORI") == 0 || strcmp(op, "XORI") == 0 ||
             strcmp(op, "SLLI") == 0 || strcmp(op, "SRLI") == 0 || strcmp(op, "SRAI") == 0)
        handle_I1_type(cleaned);
    else if (strcmp(op, "LW") == 0 || strcmp(op, "JALR") == 0)
        handle_I2_type(cleaned);
    else if (strcmp(op, "SW") == 0)
        handle_S_type(cleaned);
    else if (strcmp(op, "BEQ") == 0 || strcmp(op, "BNE") == 0 || strcmp(op, "BGE") == 0 || strcmp(op, "BLT") == 0)
        handle_SB_type(cleaned);
    else if (strcmp(op, "JAL") == 0)
        handle_UJ_type(cleaned);
    else if (strcmp(op, "EXIT") == 0)
        handle_exit(cleaned);
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
    char op[100], rs1[100], rs2[100], imm[100];
    sscanf(str, "%s %s %s %s", op, rs1, rs2, imm);

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
    else
    {
        printf("Syntax Error!!");
        return;
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
    for (int i = 31; i >= 0; i--)
    {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
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
    char ch[1000];
    while (fgets(ch, sizeof(ch), stdin) != NULL) // EOF가 아닐 때까지 루프(cs academy에서 테스트하는 용도)
    {
        ch[strcspn(ch, "\n")] = '\0'; // 입력 문자열에서 개행 문자 제거
        type_check(ch);               // 명령어 처리
    }
    return 0;
}
