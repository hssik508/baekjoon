#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

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


#define SW_OPCODE 0x23

#define SW_FUNC3 0x2


#define BEQ_OPCODE 0x63
#define BNE_OPCODE 0x63
#define BGE_OPCODE 0x63
#define BLT_OPCODE 0x63

#define BEQ_FUNC3 0x0
#define BNE_FUNC3 0x1
#define BGE_FUNC3 0x5
#define BLT_FUNC3 0x4


#define JAL_OPCODE 0x6F


#define EXIT 0xFFFFFFFF

typedef struct
{
    char **data;     
    size_t size;     
    size_t capacity; 
} Vector;

Vector *inst;  
Vector *parse; 


typedef struct
{
    char instruction[1024];
    int address;
} Juso;

typedef struct
{
    Juso *data;      
    size_t size;     
    size_t capacity; 
} JusoVector;

JusoVector *juso;  
JusoVector *label;
JusoVector *trace; 

size_t I, J; 

int reg[32] = {0};
int pc = 1000;

int is_error = 0; 


void init_vector(Vector *vec);
void push_back(Vector *vec, const char *str);
void free_vector(Vector *vec);
void init_juso_vector(JusoVector *vec);
void push_back_juso(JusoVector *vec, const char *inst, int address);
void free_juso_vector(JusoVector *vec);
void init_register();

int is_num(char *str);
int separation(char *str);
int tokenize(char *str, char *delimiter);
void error_message();

void file_read(char *name);
void file_write(char *name, char **parsingArray, int parsingArraySize, Juso *array, int jusoArraySize);
int get_register(char *reg);

void clean_input(char *input, char *cleaned);
void uppercase(char *str);
void lowercase(char *str);

void type_check(char *str);
void handle_R_type(char *str);
void handle_I1_type(char *str);
void handle_I2_type(char *str);
void handle_S_type(char *str);
void handle_SB_type(char *str);
void handle_UJ_type(char *str);
void handle_exit(char *str);
void print_binary(int num);

void operation_R_type(char *str);
void operation_I1_type(char *str);
void operation_I2_type(char *str);
void operation_S_type(char *str);
void operation_SB_type(char *str);
void operation_UJ_type(char *str);
void operation_exit(char *str);
void trace_pc();


void init_vector(Vector *vec)
{
    vec->data = (char **)malloc(30 * sizeof(char *)); 
    vec->size = 0;
    vec->capacity = 30; 
}

void push_back(Vector *vec, const char *str)
{
    if (vec->size == vec->capacity) 
    {
        vec->capacity *= 2;
        vec->data = (char **)realloc(vec->data, vec->capacity * sizeof(char *));
    }
    vec->data[vec->size] = strdup(str); 
    vec->size++;
}

void free_vector(Vector *vec)
{
    for (size_t i = 0; i < vec->size; i++)
    {
        free(vec->data[i]);
    }
    free(vec->data);
}

void init_juso_vector(JusoVector *vec)
{
    vec->data = (Juso *)malloc(30 * sizeof(Juso));
    vec->size = 0;
    vec->capacity = 30;
}

void push_back_juso(JusoVector *vec, const char *inst, int address)
{
    if (vec->size == vec->capacity)
    { 
        vec->capacity *= 2;
        vec->data = (Juso *)realloc(vec->data, vec->capacity * sizeof(Juso));
    }
    strncpy(vec->data[vec->size].instruction, inst, sizeof(vec->data[vec->size].instruction) - 1);
    vec->data[vec->size].instruction[sizeof(vec->data[vec->size].instruction) - 1] = '\0';
    vec->data[vec->size].address = address;
    vec->size++;
}

void free_juso_vector(JusoVector *vec)
{
    free(vec->data);
}

void init_register() 
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

int is_num(char *str)
{
    int i = 0, error = 0;
    if (str[i] == '-') 
    {
        i++;
    }
    while (str[i] != '\0') 
    {
        if (str[i] < '0' || str[i] > '9')
        {
            error = 1;
            break;
        }
        i++;
    }
    if (error == 1 || i == 0) 
        return 0;
    else
        return 1;
}

int separation(char *str)
{
    int i = 0, error = 1;
    while (str[i] != '\0')
    {
        if (str[i] == ')')
        {
            if (str[i + 1] == '\0')
            {
                error = 0;
                break;
            }
        }
        else if (str[i] == '(')
            str[i] = ' ';
        i++;
    }
    str[i] = '\0';
    return error;
}

int tokenize(char *str, char *delimiter)
{
    int token_count = 0; 
    char temp[10000];   
    strncpy(temp, str, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0'; 

    char *token = strtok(temp, delimiter);
    while (token != NULL)
    {
        if (token_count >= 1000)
        { 
            return 1000;
        }
        token_count++; 
        token = strtok(NULL, delimiter);
    }
    return token_count; 
}

void error_message()
{
    printf("Syntax Error!!\n");
    is_error = 1;
}

void file_read(char *name)
{
    FILE *fp;
    char *s = name;
    fp = fopen(s, "r");
    if (fp == NULL)
    {
        printf("Input file does not exist!!\n");
        is_error = 1;
        return;
    }
    char *res;
    while (1)
    {
        char ch[10000];
        res = fgets(ch, sizeof(ch), fp);
        if (res == NULL)
            break;
        size_t len = strlen(ch);
        if (len > 0 && ch[len - 1] == '\n')
        {
            ch[len - 1] = '\0';
        }

        char cleaned[10000]; 
        clean_input(res, cleaned);

        if (strlen(cleaned) == 0)
        {
            continue;
        }

        push_back(inst, cleaned);
        char op[5000];
        sscanf(cleaned, "%s", op);
        uppercase(op); 
        if (op[strlen(op) - 1] == ':')
        {
            char lb[5000];
            strncpy(lb, op, strlen(op) - 1);
            lb[strlen(op) - 1] = '\0';
            push_back_juso(label, lb, pc); 
            continue;
        }
        push_back_juso(juso, cleaned, pc);
        pc += 4;
    }
    fclose(fp);
}

void file_write(char *name, char **parsingArray, int parsingArraySize, Juso *array, int jusoArraySize)
{
    char baseFilename[10000]; 
    strcpy(baseFilename, name);
    char *dotPosition = strrchr(baseFilename, '.');
    if (dotPosition != NULL)
    {
        *dotPosition = '\0'; 
    }

    char oFilename[10000];
    snprintf(oFilename, sizeof(oFilename), "%s.o", baseFilename);
    FILE *oFile = fopen(oFilename, "w");
    if (oFile == NULL)
    {
        perror("fileopen failed (.o)");
        exit(1);
    }
    for (int i = 0; i < parsingArraySize; i++)
    {
        fprintf(oFile, "%s\n", parsingArray[i]);
    }
    fclose(oFile);

    char traceFilename[10000];
    snprintf(traceFilename, sizeof(traceFilename), "%s.trace", baseFilename);
    FILE *traceFile = fopen(traceFilename, "w");
    if (traceFile == NULL)
    {
        perror("fileopen failed (.trace)");
        exit(1);
    }
    for (int i = 0; i < jusoArraySize; i++)
    {
        fprintf(traceFile, "%d\n", array[i].address);
    }
    fclose(traceFile);
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
    else 
        return 999;
}

void clean_input(char *input, char *cleaned) 
{
    int i = 0, j = 0;
    while (input[i] != '\0')
    {
        if (!isspace(input[i]) && input[i] != ',') 
            cleaned[j++] = input[i];
        else if (j > 0 && cleaned[j - 1] != ' ') 
            cleaned[j++] = ' ';
        i++;
    }

    if (j > 0 && cleaned[j - 1] == ' ')
    {
        j--;
    }
    cleaned[j] = '\0';
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

void type_check(char *str) 
{
    char op[100]; 
    sscanf(str, "%s", op);
    uppercase(op); 

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
    else 
    {
        error_message();
        return;
    }
}

void handle_R_type(char *str)
{
    char op[100], rd[100], rs1[100], rs2[100];
    sscanf(str, "%s %s %s %s", op, rd, rs1, rs2);

    if (tokenize(str, " ") > 4)
    {
        error_message();
        return;
    }

    uppercase(op);
    lowercase(rd);
    lowercase(rs1);
    lowercase(rs2);

    int rd_num = get_register(rd);
    int rs1_num = get_register(rs1);
    int rs2_num = get_register(rs2);

    if (rd_num == 999 || rs1_num == 999 || rs2_num == 999)
    {
        error_message();
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

void handle_I1_type(char *str) 
{
    char op[100], rd[100], rs1[100], imm[100];
    sscanf(str, "%s %s %s %s", op, rd, rs1, imm);

    if (tokenize(str, " ") > 4)
    {
        error_message();
        return;
    }

    uppercase(op);
    lowercase(rd);
    lowercase(rs1);

    if (!is_num(imm)) 
    {
        error_message();
        return;
    }

    int rd_num = get_register(rd);
    int rs1_num = get_register(rs1);
    int immValue = atoi(imm);

    if (rd_num == 999 || rs1_num == 999)
    {
        error_message();
        return;
    }
    else if (strcmp(op, "SLLI") == 0 || strcmp(op, "SRLI") == 0 || strcmp(op, "SRAI") == 0)
    {
        if (immValue < 0 || immValue > 31) 
        {
            error_message();
            return;
        }
    }
    else
    {
        if (immValue < -pow(2, 11) || immValue > pow(2, 11) - 1) 
        {
            error_message();
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

void handle_I2_type(char *str) 
{
    char op[100], rd[100], tmp[100], rs1[100], imm[100]; 
    sscanf(str, "%s %s %s", op, rd, tmp);

    if (tokenize(str, " ") > 3)
    {
        error_message();
        return;
    }

    int error = separation(tmp);
    if (error == 1)
    {
        error_message();
        return;
    }

    sscanf(tmp, "%s %s", imm, rs1);

    if (!is_num(imm))
    {
        error_message();
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
        error_message();
        return;
    }
    else
    {
        if (immValue < -pow(2, 11) || immValue > pow(2, 11) - 1)
        {
            error_message();
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
    char op[100], rs2[100], tmp[100], rs1[100], imm[100]; 
    sscanf(str, "%s %s %s", op, rs2, tmp);

    if (tokenize(str, " ") > 3)
    {
        error_message();
        return;
    }

    int error = separation(tmp);
    if (error == 1)
    {
        error_message();
        return;
    }

    sscanf(tmp, "%s %s", imm, rs1);

    if (!is_num(imm))
    {
        error_message();
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
        error_message();
        return;
    }
    else
    {
        if (immValue < -pow(2, 11) || immValue > pow(2, 11) - 1)
        {
            error_message();
            return;
        }
    }

    int imm_high = (immValue >> 5) & 0b1111111; 
    int imm_low = immValue & 0b11111;          

    int opcode = 0, funct3 = 0;

    if (strcmp(op, "SW") == 0)
    {
        opcode = SW_OPCODE;
        funct3 = SW_FUNC3;
    }

    int machine_code = (imm_high << 25) | (rs2_num << 20) | (rs1_num << 15) | (funct3 << 12) | (imm_low << 7) | opcode;
    print_binary(machine_code);
}

void handle_SB_type(char *str) 
{
    char op[100], rs1[100], rs2[100], lb[100];
    sscanf(str, "%s %s %s %s", op, rs1, rs2, lb);

    if (tokenize(str, " ") > 4)
    {
        error_message();
        return;
    }

    uppercase(lb); 
    uppercase(op);
    lowercase(rs2);
    lowercase(rs1);

    int exist = 0, immValue;
    for (int i = 0; i < label->size; i++)
    {
        if (strcmp(label->data[i].instruction, lb) == 0)
        {
            exist = 1;
            immValue = label->data[i].address - juso->data[J].address; 
        }
    }

    if (exist == 0)
    {
        error_message();
        return;
    }

    int rs2_num = get_register(rs2);
    int rs1_num = get_register(rs1);

    if (rs2_num == 999 || rs1_num == 999)
    {
        error_message();
        return;
    }

    int imm_12 = (immValue >> 12) & 0b1;       
    int imm_10_5 = (immValue >> 5) & 0b111111; 
    int imm_4_1 = (immValue >> 1) & 0b1111;    
    int imm_11 = (immValue >> 11) & 0b1;       

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
    char op[100], rd[100], lb[100];
    sscanf(str, "%s %s %s", op, rd, lb);

    if (tokenize(str, " ") > 3)
    {
        error_message();
        return;
    }

    uppercase(lb); 
    uppercase(op);
    lowercase(rd);

    int exist = 0, immValue;
    for (int i = 0; i < label->size; i++)
    {
        if (strcmp(label->data[i].instruction, lb) == 0)
        {
            exist = 1;
            immValue = label->data[i].address - juso->data[J].address; 
        }
    }

    if (exist == 0)
    {
        error_message();
        return;
    }

    int rd_num = get_register(rd);

    if (rd_num == 999)
    {
        error_message();
        return;
    }

    int imm_20 = (immValue >> 20) & 0b1;           
    int imm_10_1 = (immValue >> 1) & 0b1111111111; 
    int imm_11 = (immValue >> 11) & 0b1;          
    int imm_19_12 = (immValue >> 12) & 0b11111111; 

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
    if (tokenize(str, " ") > 1)
    {
        error_message();
        return;
    }
    int machine_code = 0xFFFFFFFF;
    print_binary(machine_code);
}

void print_binary(int num) 
{
    char parsed[33]; 
    for (int i = 31; i >= 0; i--)
    {
        int n = (num >> i) & 1; 
        parsed[31 - i] = '0' + n; 
    }
    parsed[32] = '\0';

    push_back(parse, parsed); 
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

    if (rd_num == 999 || rs1_num == 999 || rs2_num == 999) 
    {
        error_message();
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

void operation_I1_type(char *str) 
{
    char op[100], rd[100], rs1[100], imm[100];
    sscanf(str, "%s %s %s %s", op, rd, rs1, imm);

    uppercase(op);
    lowercase(rd);
    lowercase(rs1);

    if (!is_num(imm))
    {
        error_message();
        return;
    }

    int rd_num = get_register(rd);
    int rs1_num = get_register(rs1);
    int immValue = atoi(imm);

    if (rd_num == 999 || rs1_num == 999)
    {
        error_message();
        return;
    }
    else if (strcmp(op, "SLLI") == 0 || strcmp(op, "SRLI") == 0 || strcmp(op, "SRAI") == 0)
    {
        if (immValue < 0 || immValue > 31) 
        {
            error_message();
            return;
        }
    }
    else
    {
        if (immValue < -pow(2, 11) || immValue > pow(2, 11) - 1)
        {
            error_message();
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

void operation_I2_type(char *str)
{
    char op[100], rd[100], tmp[100], rs1[100], imm[100];
    sscanf(str, "%s %s %s", op, rd, tmp);

    int error = separation(tmp);
    if (error == 1)
    {
        error_message();
        return;
    }

    sscanf(tmp, "%s %s", imm, rs1);

    if (!is_num(imm))
    {
        error_message();
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
        error_message();
        return;
    }
    else
    {
        if (immValue < -pow(2, 11) || immValue > pow(2, 11) - 1)
        {
            error_message();
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

        int target_address = (reg[rs1_num] + immValue) & ~1;
        if (target_address < 0)
        {
            error_message();
            return;
        }

        int found = 0;
        for (size_t i = 0; i < juso->size; i++)
        {
            if (juso->data[i].address == target_address)
            {
                pc = target_address;
                I = i;               
                found = 1;
                break;
            }
        }
        if (!found)
        {
            error_message();
            return;
        }
    }
}

void operation_S_type(char *str)
{
    pc += 4;
}

void operation_SB_type(char *str)
{
    char op[100], rs1[100], rs2[100], lb[100];
    sscanf(str, "%s %s %s %s", op, rs1, rs2, lb);

    uppercase(lb); 
    uppercase(op);
    lowercase(rs1);
    lowercase(rs2);

    int rs1_num = get_register(rs1);
    int rs2_num = get_register(rs2);

    if (rs1_num == 999 || rs2_num == 999)
    {
        error_message();
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
        error_message();
        return;
    }

    if ((strcmp(op, "BGE") == 0 && reg[rs1_num] >= reg[rs2_num]) ||
        (strcmp(op, "BEQ") == 0 && reg[rs1_num] == reg[rs2_num]) ||
        (strcmp(op, "BNE") == 0 && reg[rs1_num] != reg[rs2_num]) ||
        (strcmp(op, "BLT") == 0 && reg[rs1_num] < reg[rs2_num]))
    {
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
        pc += 4;
        I++;
    }
}

void operation_UJ_type(char *str)
{
    char op[100], rd[100], lb[100];
    sscanf(str, "%s %s %s", op, rd, lb);

    uppercase(lb); 
    uppercase(op);
    lowercase(rd);

    int rd_num = get_register(rd);

    if (rd_num == 999)
    {
        error_message();
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
        error_message();
        return;
    }

    reg[rd_num] = pc + 4;
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

void operation_exit(char *str)
{
    I = juso->size;
}

void trace_pc() 
{
    pc = 1000;
    I = 0;

    while (I < juso->size)
    {
        char *instruction = juso->data[I].instruction; 
        char op[100];                                  
        sscanf(instruction, "%s", op);
        uppercase(op);
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
        else
        {
            error_message();
            return;
        }

        if (is_error == 1)
        {
            return;
        }
    }
}

int main()
{
    inst = (Vector *)malloc(sizeof(Vector));
    parse = (Vector *)malloc(sizeof(Vector));
    juso = (JusoVector *)malloc(sizeof(JusoVector));
    label = (JusoVector *)malloc(sizeof(JusoVector));
    trace = (JusoVector *)malloc(sizeof(JusoVector));
    while (1)
    {
        init_vector(inst);
        init_vector(parse);
        init_juso_vector(juso);
        init_juso_vector(label);
        init_juso_vector(trace);
        init_register();

        char name[10000];
        printf(">> Enter Input File Name: ");
        scanf("%s", name);
        if (strcmp(name, "terminate") == 0) 
            break;
        pc = 1000;
        file_read(name);
        if (is_error == 1)
        {
            is_error = 0;
            continue;
        }

        J = 0;                                 
        for (size_t i = 0; i < juso->size; i++) 
        {
            J = i;
            char *ch = juso->data[i].instruction;
            type_check(ch);
            if (is_error == 1)
                break;
        }
        if (is_error == 1)
        {
            is_error = 0;
            continue;
        }

        trace_pc();
        if (is_error == 1)
        {
            is_error = 0;
            continue;
        }
        
        file_write(name, parse->data, parse->size, trace->data, trace->size);

        free_vector(inst); 
        free_vector(parse);
        free_juso_vector(juso);
        free_juso_vector(label);
        free_juso_vector(trace);
    }
    return 0;
}