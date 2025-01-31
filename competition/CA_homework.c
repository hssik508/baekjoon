#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// 공백 제거 함수
char *trim(char *s) {
    // 앞쪽 공백 제거
    while (isspace((unsigned char)*s)) s++;

    // 문자열이 모두 공백인 경우
    if (*s == 0)
        return s;

    // 뒤쪽 공백 제거
    char *end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end)) end--;

    // 문자열 끝에 널 문자 추가
    *(end + 1) = '\0';

    return s;
}

// 파일명에서 확장자 제거 함수
void removeExtension(char *filename) {
    char *dot = strrchr(filename, '.');
    if (dot != NULL) {
        *dot = '\0';
    }
}

// 문자열을 대문자로 변환하는 함수
void toUpperStr(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

// 레지스터 문자열을 번호로 변환하는 함수
int getRegister(char *reg) {
    toUpperStr(reg);
    if (reg[0] == 'X') {
        int regNum = atoi(&reg[1]);
        if (regNum < 0 || regNum > 31) {
            return -1; // 오류 처리용
        }
        return regNum;
    }
    return -1; // 오류 처리용
}

// 32비트 기계어 코드를 생성하는 함수들
unsigned int encodeRType(int opcode, int funct3, int funct7, int rd, int rs1, int rs2) {
    unsigned int code = 0;
    code |= (funct7 & 0x7F) << 25;
    code |= (rs2 & 0x1F) << 20;
    code |= (rs1 & 0x1F) << 15;
    code |= (funct3 & 0x7) << 12;
    code |= (rd & 0x1F) << 7;
    code |= opcode & 0x7F;
    return code;
}

unsigned int encodeIType(int opcode, int funct3, int rd, int rs1, int imm) {
    unsigned int code = 0;
    code |= (imm & 0xFFF) << 20;
    code |= (rs1 & 0x1F) << 15;
    code |= (funct3 & 0x7) << 12;
    code |= (rd & 0x1F) << 7;
    code |= opcode & 0x7F;
    return code;
}

unsigned int encodeSType(int opcode, int funct3, int rs1, int rs2, int imm) {
    unsigned int code = 0;
    unsigned int imm11_5 = (imm >> 5) & 0x7F;
    unsigned int imm4_0 = imm & 0x1F;
    code |= (imm11_5) << 25;
    code |= (rs2 & 0x1F) << 20;
    code |= (rs1 & 0x1F) << 15;
    code |= (funct3 & 0x7) << 12;
    code |= (imm4_0) << 7;
    code |= opcode & 0x7F;
    return code;
}

unsigned int encodeBType(int opcode, int funct3, int rs1, int rs2, int imm) {
    unsigned int code = 0;
    unsigned int imm12 = (imm >> 12) & 0x1;
    unsigned int imm10_5 = (imm >> 5) & 0x3F;
    unsigned int imm4_1 = (imm >> 1) & 0xF;
    unsigned int imm11 = (imm >> 11) & 0x1;

    code |= (imm12) << 31;
    code |= (imm10_5) << 25;
    code |= (rs2 & 0x1F) << 20;
    code |= (rs1 & 0x1F) << 15;
    code |= (funct3 & 0x7) << 12;
    code |= (imm4_1) << 8;
    code |= (imm11) << 7;
    code |= opcode & 0x7F;
    return code;
}

unsigned int encodeJType(int opcode, int rd, int imm) {
    unsigned int code = 0;
    unsigned int imm20 = (imm >> 20) & 0x1;
    unsigned int imm10_1 = (imm >> 1) & 0x3FF;
    unsigned int imm11 = (imm >> 11) & 0x1;
    unsigned int imm19_12 = (imm >> 12) & 0xFF;

    code |= (imm20) << 31;
    code |= (imm19_12) << 12;
    code |= (imm11) << 20;
    code |= (imm10_1) << 21;
    code |= (rd & 0x1F) << 7;
    code |= opcode & 0x7F;
    return code;
}

// 기계어 코드를 32비트 이진수 문자열로 출력하는 함수
void printBinary(FILE *file, unsigned int code) {
    for (int i = 31; i >= 0; i--) {
        fprintf(file, "%d", (code >> i) & 1);
    }
    fprintf(file, "\n");
}

// 명령어 구조체 정의
typedef struct {
    char instruction[10];
    char operands[50];
} Instruction;

// 명령어 매핑
typedef struct {
    char name[10];
    int opcode;
    int funct3;
    int funct7;
    char type;
} InstructionMap;

InstructionMap instructionMap[] = {
    {"ADD", 0x33, 0x0, 0x00, 'R'},
    {"SUB", 0x33, 0x0, 0x20, 'R'},
    {"AND", 0x33, 0x7, 0x00, 'R'},
    {"OR",  0x33, 0x6, 0x00, 'R'},
    {"XOR", 0x33, 0x4, 0x00, 'R'},
    {"SLL", 0x33, 0x1, 0x00, 'R'},
    {"SRL", 0x33, 0x5, 0x00, 'R'},
    {"SRA", 0x33, 0x5, 0x20, 'R'},

    {"ADDI",0x13, 0x0, 0x00, 'I'},
    {"ANDI",0x13, 0x7, 0x00, 'I'},
    {"ORI", 0x13, 0x6, 0x00, 'I'},
    {"XORI",0x13, 0x4, 0x00, 'I'},
    {"SLLI",0x13, 0x1, 0x00, 'I'},
    {"SRLI",0x13, 0x5, 0x00, 'I'},
    {"SRAI",0x13, 0x5, 0x20, 'I'},
    {"LW",  0x03, 0x2, 0x00, 'I'},
    {"JALR",0x67, 0x0, 0x00, 'I'},

    {"SW",  0x23, 0x2, 0x00, 'S'},

    {"BEQ", 0x63, 0x0, 0x00, 'B'},
    {"BNE", 0x63, 0x1, 0x00, 'B'},
    {"BLT", 0x63, 0x4, 0x00, 'B'},
    {"BGE", 0x63, 0x5, 0x00, 'B'},

    {"JAL", 0x6F, 0x0, 0x00, 'J'},

    {"EXIT",0xFFFFFFFF, 0x0, 0x00, 'E'},

    {"",0,0,0,'\0'} // 끝 표시
};

// 라벨 맵 구조체 정의
typedef struct {
    char label[20];
    int address;
} LabelMap;

// 프로그램의 최대 줄 수를 알 수 없으므로 동적 배열을 관리하기 위한 구조체 정의
typedef struct {
    Instruction *instructions;
    int *instrAddress;
    int count;
    int capacity;
} InstructionList;

// 명령어 리스트 관리용 함수들
void initInstructionList(InstructionList *list) {
    list->capacity = 100;
    list->count = 0;
    list->instructions = (Instruction *)malloc(sizeof(Instruction) * list->capacity);
    list->instrAddress = (int *)malloc(sizeof(int) * list->capacity);
}

void appendInstruction(InstructionList *list, Instruction instr, int address) {
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        list->instructions = (Instruction *)realloc(list->instructions, sizeof(Instruction) * list->capacity);
        list->instrAddress = (int *)realloc(list->instrAddress, sizeof(int) * list->capacity);
    }
    list->instructions[list->count] = instr;
    list->instrAddress[list->count] = address;
    list->count++;
}

void freeInstructionList(InstructionList *list) {
    free(list->instructions);
    free(list->instrAddress);
}

// 라벨 맵을 동적 배열로 관리
typedef struct {
    LabelMap *labels;
    int count;
    int capacity;
} LabelList;

void initLabelList(LabelList *list) {
    list->capacity = 100;
    list->count = 0;
    list->labels = (LabelMap *)malloc(sizeof(LabelMap) * list->capacity);
}

void appendLabel(LabelList *list, LabelMap label) {
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        list->labels = (LabelMap *)realloc(list->labels, sizeof(LabelMap) * list->capacity);
    }
    list->labels[list->count] = label;
    list->count++;
}

void freeLabelList(LabelList *list) {
    free(list->labels);
}

// 동적 메모리로 한 줄을 읽는 함수
char *readLineDynamic(FILE *file) {
    size_t bufferSize = 1024; // 초기 버퍼 크기
    size_t position = 0;
    char *buffer = (char *)malloc(bufferSize);
    if (!buffer) {
        return NULL;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        // 버퍼 크기를 초과하면 메모리 확장
        if (position >= bufferSize - 1) {
            bufferSize *= 2;
            char *newBuffer = (char *)realloc(buffer, bufferSize);
            if (!newBuffer) {
                free(buffer);
                return NULL;
            }
            buffer = newBuffer;
        }
        // 줄 끝이면 종료
        if (ch == '\n') {
            break;
        }
        buffer[position++] = (char)ch;
    }

    // EOF 시 빈 줄 처리
    if (position == 0 && ch == EOF) {
        free(buffer);
        return NULL;
    }

    buffer[position] = '\0'; // 문자열 종료
    return buffer;
}

int main() {
    char filename[1000];
    FILE *inputFile;

    while (1) {
        printf(">> Enter Input File Name: ");
        scanf("%s", filename);

        if (strcmp(filename, "terminate") == 0) {
            break;
        }

        inputFile = fopen(filename, "r");
        if (inputFile == NULL) {
            printf("Input file does not exist!!\n");
            continue;
        }

        // 파일명에서 확장자 제거
        removeExtension(filename);

        // 파일이 성공적으로 열렸으므로 다음 단계로 진행

        // 입력 라인 동적 배열로 저장
        char **lines = NULL;
        int lineCount = 0;
        int lineCapacity = 100;

        lines = (char **)malloc(sizeof(char *) * lineCapacity);

        char *line;
        while ((line = readLineDynamic(inputFile)) != NULL) {
            // 좌측 공백 제거
            char *trimmedLine = trim(line);
            // 공백 라인 무시
            if (strlen(trimmedLine) == 0) {
                free(line);
                continue;
            }
            if (lineCount >= lineCapacity) {
                lineCapacity *= 2;
                lines = (char **)realloc(lines, sizeof(char *) * lineCapacity);
            }
            lines[lineCount] = (char *)malloc(strlen(trimmedLine) + 1);
            strcpy(lines[lineCount], trimmedLine);
            lineCount++;
            free(line);
        }

        fclose(inputFile);

        // 라벨 주소 저장을 위한 리스트
        LabelList labelList;
        initLabelList(&labelList);

        // 명령어 리스트
        InstructionList instrList;
        initInstructionList(&instrList);

        // 라벨 수집 및 명령어 분리
        int address = 1000; // 시작 주소

        for (int i = 0; i < lineCount; i++) {
            char *linePtr = lines[i];
            char *labelToken = NULL;
            char *instrPart = NULL;

            // 라벨과 명령어 분리
            char *colonPos = strchr(linePtr, ':');
            if (colonPos != NULL) {
                // 라벨이 존재함
                *colonPos = '\0';
                labelToken = trim(linePtr);
                instrPart = colonPos + 1;

                toUpperStr(labelToken);
                LabelMap newLabel;
                strcpy(newLabel.label, labelToken);
                newLabel.address = address;
                appendLabel(&labelList, newLabel);

                // 명령어 부분이 있는지 확인
                instrPart = trim(instrPart);
                if (strlen(instrPart) == 0) {
                    // 라벨만 있는 라인
                    continue;
                } else {
                    strcpy(linePtr, instrPart);
                }
        
            }   else {
                strcpy(linePtr, trim(linePtr));
            }

            // 명령어와 피연산자 분리
            Instruction instr = {"", ""};
            char *token = strtok(linePtr, " \t");
            if (token == NULL) {
                continue;
            }
            strcpy(instr.instruction, token);
            toUpperStr(instr.instruction);

            char *operands = strtok(NULL, "");
            if (operands != NULL) {
                strcpy(instr.operands, operands);
            } else {
                instr.operands[0] = '\0';
            }

            appendInstruction(&instrList, instr, address);
            address += 4;
        }

        // 기계어 코드 생성
        unsigned int *machineCodes = NULL;
        int machineCodeCount = 0;
        int machineCodeCapacity = 100;
        machineCodes = (unsigned int *)malloc(sizeof(unsigned int) * machineCodeCapacity);

        int syntaxError = 0;

        for (int idx = 0; idx < instrList.count; idx++) {
            Instruction instr = instrList.instructions[idx];
            unsigned int code = 0;
            int rd, rs1, rs2, imm;
            char *opTokens[5];
            int opCount = 0;
            char *token;

            if (strlen(instr.operands) > 0) {
                char operandCopy[50];
                strcpy(operandCopy, instr.operands);
                token = strtok(operandCopy, ",");
                while (token != NULL && opCount < 5) {
                    opTokens[opCount++] = trim(token);
                    token = strtok(NULL, ",");
                }
            }

            // 명령어 매핑 찾기
            InstructionMap *map = NULL;
            for (int j = 0; instructionMap[j].type != '\0'; j++) {
                if (strcmp(instr.instruction, instructionMap[j].name) == 0) {
                    map = &instructionMap[j];
                    break;
                }
            }

            if (map == NULL) {
                syntaxError = 1;
                break;
            }

            switch (map->type) {
                case 'R':
                    if (opCount != 3) {
                        syntaxError = 1;
                        break;
                    }
                    rd = getRegister(opTokens[0]);
                    rs1 = getRegister(opTokens[1]);
                    rs2 = getRegister(opTokens[2]);
                    if (rd == -1 || rs1 == -1 || rs2 == -1) {
                        syntaxError = 1;
                        break;
                    }
                    code = encodeRType(map->opcode, map->funct3, map->funct7, rd, rs1, rs2);
                    break;
                case 'I':
                    if (strcmp(map->name, "LW") == 0 || strcmp(map->name, "JALR") == 0) {
                        // LW x1, offset(x2)
                        if (opCount != 2) {
                            syntaxError = 1;
                            break;
                        }
                        rd = getRegister(opTokens[0]);
                        char offsetPart[20], rs1Part[5];
                        sscanf(opTokens[1], "%[^()](%[^)])", offsetPart, rs1Part);
                        rs1 = getRegister(rs1Part);
                        imm = atoi(offsetPart);
                        if (rd == -1 || rs1 == -1) {
                            syntaxError = 1;
                            break;
                        }
                        code = encodeIType(map->opcode, map->funct3, rd, rs1, imm);
                    } else if (strcmp(map->name, "SLLI") == 0 || strcmp(map->name, "SRLI") == 0 || strcmp(map->name, "SRAI") == 0) {
                        if (opCount != 3) {
                            syntaxError = 1;
                            break;
                        }
                        rd = getRegister(opTokens[0]);
                        rs1 = getRegister(opTokens[1]);
                        imm = atoi(opTokens[2]);
                        if (rd == -1 || rs1 == -1) {
                            syntaxError = 1;
                            break;
                        }
                        code = encodeIType(map->opcode, map->funct3, rd, rs1, imm | (map->funct7 << 5));
                    } else {
                        if (opCount != 3) {
                            syntaxError = 1;
                            break;
                        }
                        rd = getRegister(opTokens[0]);
                        rs1 = getRegister(opTokens[1]);
                        imm = atoi(opTokens[2]);
                        if (rd == -1 || rs1 == -1) {
                            syntaxError = 1;
                            break;
                        }
                        code = encodeIType(map->opcode, map->funct3, rd, rs1, imm);
                    }
                    break;
                case 'S':
                    if (opCount != 2) {
                        syntaxError = 1;
                        break;
                    }
                    rs2 = getRegister(opTokens[0]);
                    char offsetPart[20], rs1Part[5];
                    sscanf(opTokens[1], "%[^()](%[^)])", offsetPart, rs1Part);
                    rs1 = getRegister(rs1Part);
                    imm = atoi(offsetPart);
                    if (rs1 == -1 || rs2 == -1) {
                        syntaxError = 1;
                        break;
                    }
                    code = encodeSType(map->opcode, map->funct3, rs1, rs2, imm);
                    break;
                case 'B':
                    if (opCount != 3) {
                        syntaxError = 1;
                        break;
                    }
                    rs1 = getRegister(opTokens[0]);
                    rs2 = getRegister(opTokens[1]);
                    // 라벨 주소 찾기
                    imm = 0;
                    int found = 0;
                    opTokens[2] = trim(opTokens[2]);
                    toUpperStr(opTokens[2]);
                    for (int k = 0; k < labelList.count; k++) {
                        if (strcmp(labelList.labels[k].label, opTokens[2]) == 0) {
                            imm = labelList.labels[k].address - instrList.instrAddress[idx];
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        syntaxError = 1;
                        break;
                    }
                    if (rs1 == -1 || rs2 == -1) {
                        syntaxError = 1;
                        break;
                    }
                    code = encodeBType(map->opcode, map->funct3, rs1, rs2, imm);
                    break;
                case 'J':
                    if (opCount != 2) {
                        syntaxError = 1;
                        break;
                    }
                    rd = getRegister(opTokens[0]);
                    // 라벨 주소 찾기
                    imm = 0;
                    int foundJ = 0;
                    opTokens[1] = trim(opTokens[1]);
                    toUpperStr(opTokens[1]);
                    for (int k = 0; k < labelList.count; k++) {
                        if (strcmp(labelList.labels[k].label, opTokens[1]) == 0) {
                            imm = labelList.labels[k].address - instrList.instrAddress[idx];
                            foundJ = 1;
                            break;
                        }
                    }
                    if (!foundJ) {
                        syntaxError = 1;
                        break;
                    }
                    if (rd == -1) {
                        syntaxError = 1;
                        break;
                    }
                    code = encodeJType(map->opcode, rd, imm);
                    break;
                case 'E':
                    code = map->opcode;
                    break;
                default:
                    syntaxError = 1;
                    break;
            }

            if (syntaxError) {
                break;
            }

            if (machineCodeCount >= machineCodeCapacity) {
                machineCodeCapacity *= 2;
                machineCodes = (unsigned int *)realloc(machineCodes, sizeof(unsigned int) * machineCodeCapacity);
            }

            machineCodes[machineCodeCount++] = code;
        }

        if (syntaxError) {
            printf("Syntax Error!!\n");
            // 동적 메모리 해제
            for (int i = 0; i < lineCount; i++) {
                free(lines[i]);
            }
            free(lines);
            freeLabelList(&labelList);
            freeInstructionList(&instrList);
            free(machineCodes);
            continue;
        }

        // .o 파일 저장
        char oFilename[100];
        strcpy(oFilename, filename);
        strcat(oFilename, ".o");

        FILE *oFile = fopen(oFilename, "w");
        if (oFile == NULL) {
            // 동적 메모리 해제
            for (int i = 0; i < lineCount; i++) {
                free(lines[i]);
            }
            free(lines);
            freeLabelList(&labelList);
            freeInstructionList(&instrList);
            free(machineCodes);
            continue;
        }

        for (int i = 0; i < machineCodeCount; i++) {
            printBinary(oFile, machineCodes[i]);
        }

        fclose(oFile);

        // 레지스터 초기화
        int registers[32] = 
        {0, 1, 2, 3, 4, 5, 6, 0, 
         0, 0, 0, 0, 0, 0, 0, 0, 
         0, 0, 0, 0, 0, 0, 0, 0, 
         0, 0, 0, 0, 0, 0, 0, 0};

        // PC 초기화
        int pc = 1000;

        // .trace 파일 저장
        char traceFilename[100];
        strcpy(traceFilename, filename);
        strcat(traceFilename, ".trace");

        FILE *traceFile = fopen(traceFilename, "w");
        if (traceFile == NULL) {
            // 동적 메모리 해제
            for (int i = 0; i < lineCount; i++) {
                free(lines[i]);
            }
            free(lines);
            freeLabelList(&labelList);
            freeInstructionList(&instrList);
            free(machineCodes);
            continue;
        }

        // 명령어 실행 루프
        int idx = 0;
        while (idx < machineCodeCount) {
            fprintf(traceFile, "%d\n", pc);

            unsigned int code = machineCodes[idx];

            // EXIT 명령어 처리
            if (code == 0xFFFFFFFF) {
                break;
            }

            // 명령어 디코딩
            unsigned int opcode = code & 0x7F;
            unsigned int rd = (code >> 7) & 0x1F;
            unsigned int funct3 = (code >> 12) & 0x7;
            unsigned int rs1 = (code >> 15) & 0x1F;
            unsigned int rs2 = (code >> 20) & 0x1F;
            unsigned int funct7 = (code >> 25) & 0x7F;
            int imm;

            if (opcode == 0x33) { // R-type
                switch (funct3) {
                    case 0x0: // ADD or SUB
                        if (funct7 == 0x00) { // ADD
                            registers[rd] = registers[rs1] + registers[rs2];
                        } else if (funct7 == 0x20) { // SUB
                            registers[rd] = registers[rs1] - registers[rs2];
                        }
                        break;
                    case 0x7: // AND
                        registers[rd] = registers[rs1] & registers[rs2];
                        break;
                    case 0x6: // OR
                        registers[rd] = registers[rs1] | registers[rs2];
                        break;
                    case 0x4: // XOR
                        registers[rd] = registers[rs1] ^ registers[rs2];
                        break;
                    case 0x1: // SLL
                        registers[rd] = registers[rs1] << (registers[rs2] & 0x1F);
                        break;
                    case 0x5: // SRL or SRA
                        if (funct7 == 0x00) { // SRL
                            registers[rd] = (unsigned int)registers[rs1] >> (registers[rs2] & 0x1F);
                        } else if (funct7 == 0x20) { // SRA
                            registers[rd] = registers[rs1] >> (registers[rs2] & 0x1F);
                        }
                        break;
                }
            } else if (opcode == 0x13) { // I-type
                imm = (int)code >> 20; // sign-extended immediate
                switch (funct3) {
                    case 0x0: // ADDI
                        registers[rd] = registers[rs1] + imm;
                        break;
                    case 0x7: // ANDI
                        registers[rd] = registers[rs1] & imm;
                        break;
                    case 0x6: // ORI
                        registers[rd] = registers[rs1] | imm;
                        break;
                    case 0x4: // XORI
                        registers[rd] = registers[rs1] ^ imm;
                        break;
                    case 0x1: // SLLI
                        registers[rd] = registers[rs1] << (imm & 0x1F);
                        break;
                    case 0x5: // SRLI or SRAI
                        if (funct7 == 0x00) { // SRLI
                            registers[rd] = (unsigned int)registers[rs1] >> (imm & 0x1F);
                        } else if (funct7 == 0x20) { // SRAI
                            registers[rd] = registers[rs1] >> (imm & 0x1F);
                        }
                        break;
                }
            } else if (opcode == 0x63) { // Branch
                imm = ((code >> 31) & 0x1) << 12 |
                    ((code >> 25) & 0x3F) << 5 |
                    ((code >> 8) & 0xF) << 1 |
                    ((code >> 7) & 0x1) << 11;
                if (imm & 0x1000) { // 음수 처리
                    imm |= 0xFFFFE000;
                }
                int takeBranch = 0;
                switch (funct3) {
                    case 0x0: // BEQ
                        if (registers[rs1] == registers[rs2]) takeBranch = 1;
                        break;
                    case 0x1: // BNE
                        if (registers[rs1] != registers[rs2]) takeBranch = 1;
                        break;
                    case 0x4: // BLT
                        if (registers[rs1] < registers[rs2]) takeBranch = 1;
                        break;
                    case 0x5: // BGE
                        if (registers[rs1] >= registers[rs2]) takeBranch = 1;
                        break;
                }
                if (takeBranch) {
                    pc += imm;
                    idx = (pc - 1000) / 4;
                    continue;
                }
            } else if (opcode == 0x6F) { // JAL
                imm = ((code >> 31) & 0x1) << 20 |
                    ((code >> 12) & 0xFF) << 12 |
                    ((code >> 20) & 0x1) << 11 |
                    ((code >> 21) & 0x3FF) << 1;
                if (imm & 0x100000) { // 음수 처리
                    imm |= 0xFFF00000;
                }
                registers[rd] = pc + 4;
                pc += imm;
                idx = (pc - 1000) / 4;
                continue;
            } else if (opcode == 0x03) { // LW
                imm = (int)code >> 20; // sign-extended immediate
                rs1 = (code >> 15) & 0x1F;
                rd = (code >> 7) & 0x1F;

                // 메모리 접근을 생략하고 레지스터 rd에 0을 저장
                registers[rd] = 0;
            } else if (opcode == 0x23) { // SW (메모리 미구현으로 넘어감)
                // 메모리 접근을 하지 않기에 아무것도 하지 않음.
            } else if (opcode == 0x67) { // JALR
                imm = (int)code >> 20; // sign-extended immediate
                int temp = pc + 4;
                pc = (registers[rs1] + imm) & ~1;
                registers[rd] = temp;
                idx = (pc - 1000) / 4;
                continue;
            }

            // 다음 명령어로 이동
            pc += 4;
            idx++;
        }

        fclose(traceFile);

        // 동적 메모리 해제
        for (int i = 0; i < lineCount; i++) {
            free(lines[i]);
        }
        free(lines);
        freeLabelList(&labelList);
        freeInstructionList(&instrList);
        free(machineCodes);
    }

    return 0;
}
