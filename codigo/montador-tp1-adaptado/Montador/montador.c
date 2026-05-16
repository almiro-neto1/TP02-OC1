#include "montador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tipoInstrucao verificarInstrucao(char instrucao[]){
    char instrucaoReduzida[5];
    sscanf(instrucao, "%s", instrucaoReduzida);
    if(strcmp(instrucaoReduzida, "add") == 0){
        return tipoR;
    }
    else if(strcmp(instrucaoReduzida, "xor") == 0){
        return tipoR;
    }
    else if(strcmp(instrucaoReduzida, "sll") == 0){
        return tipoR;
    }
    else if(strcmp(instrucaoReduzida, "addi") == 0){
        return tipoI;
    }
    else if(strcmp(instrucaoReduzida, "lw") == 0){
        return tipoI;
    }
    else if(strcmp(instrucaoReduzida, "sw") == 0){
        return tipoS;
    }
    else if(strcmp(instrucaoReduzida, "bne") == 0){
        return tipoSB;
    }
    else {
        return tipoNulo;
    }
}

int encontrarRotulos(Rotulo rotulos[], FILE *arquivoEntrada){
    char instrucaoAssembly[35];
    int linhaDoRotulo = 1;
    int enderecoApontado = 0;
    int numRotulos = 0;
    while(fgets(instrucaoAssembly, 35, arquivoEntrada) != NULL){
        char primeiraPalavra[20];
        sscanf(instrucaoAssembly, "%s", primeiraPalavra);
        int flagEhRotulo = 0;
        int lenPrimeiraPalavra = strlen(primeiraPalavra);
        if(primeiraPalavra[lenPrimeiraPalavra - 1] == ':'){
            strncpy(rotulos[numRotulos].stringRotulo, primeiraPalavra, lenPrimeiraPalavra - 1);
            rotulos[numRotulos].stringRotulo[lenPrimeiraPalavra - 1] = '\0';
            rotulos[numRotulos].enderecoApontado = enderecoApontado;
            rotulos[numRotulos].linhaDoRotulo = linhaDoRotulo;
            flagEhRotulo = 1;
            numRotulos++;
        }
        if(numRotulos >= 50){
            break;
        }
        linhaDoRotulo++;
        if(flagEhRotulo == 0){
            enderecoApontado += 4;
        }
    }

    rewind(arquivoEntrada);
    return numRotulos;
}

void registradorParaBinario(char registrador[], char binario[]){
    registrador[0] = ' ';
    unsigned int registradorInteiro;
    int c = 0;
    sscanf(registrador, "%d", &registradorInteiro);
    for(int i = 4; i >= 0; i--){
        int bitInteiro = (registradorInteiro >> i) & 1;
        char bitChar = bitInteiro + '0';
        binario[c] = bitChar;
        c++;
    }
    binario[c] = '\0';
}

void imediatoParaBinario(char imediato[], char binario[]){
    int imediatoInteiro;
    int c = 0;
    sscanf(imediato, "%d", &imediatoInteiro);
    for(int i = 11; i >= 0; i--){
        int bitInteiro = (imediatoInteiro >> i) & 1;
        char bitChar = bitInteiro + '0';
        binario[c] = bitChar;
        c++;
    }
    binario[c] = '\0';
}

void binarioFunct7(char instrucao[], char funct7[]){
    if(strcmp(instrucao, "add") == 0){
        strncpy(funct7, "0000000", 8);
    }
    else if(strcmp(instrucao, "xor") == 0){
        strncpy(funct7, "0000000", 8);
    }
    else if(strcmp(instrucao, "sll") == 0){
        strncpy(funct7, "0000000", 8);
    }
    else {
        strncpy(funct7, "\0", 2);
    }
}

void binarioFunct3(char instrucao[], char funct3[]){
    if(strcmp(instrucao, "add") == 0 || strcmp(instrucao, "addi") == 0){
        strncpy(funct3, "000", 4);
    }
    else if(strcmp(instrucao, "xor") == 0){
        strncpy(funct3, "100", 4);
    }
    else if(strcmp(instrucao, "sll") == 0){
        strncpy(funct3, "001", 4);
    }
    else if(strcmp(instrucao, "lw") == 0 || strcmp(instrucao, "sw") == 0){
        strncpy(funct3, "010", 4);   
    }
    else if(strcmp(instrucao, "bne") == 0){
        strncpy(funct3, "001", 4);
    }else{
        strncpy(funct3, "\0", 2);
    }
}

void binarioOpcode(char instrucao[], char opcode[]){
    //Tipo R (0110011)
    if(strcmp(instrucao, "add") == 0 || strcmp(instrucao, "xor") == 0 || strcmp(instrucao, "sll") == 0){
        strncpy(opcode, "0110011", 8);
    }
    //Tipo I (Aritmético)
    else if(strcmp(instrucao, "addi") == 0){
        strncpy(opcode, "0010011", 8);
    }
    //Tipo I (Load)
    else if(strcmp(instrucao, "lw") == 0){
        strncpy(opcode, "0000011", 8);
    }
    //Tipo S (0100011)
    else if(strcmp(instrucao, "sw") == 0){
        strncpy(opcode, "0100011", 8);
    }
    //Tipo B (1100011)
    else if(strcmp(instrucao, "bne") == 0){
        strncpy(opcode, "1100011", 8);
    }else{
        strncpy(opcode, "\0", 2);
    }
}

void processarTipoR(char instrucaoAssembly[], char instrucaoBinario[]){
    for (int i = 0; i < strlen(instrucaoAssembly); i++){     //Limpa a string
        if (instrucaoAssembly[i] == ',' || instrucaoAssembly[i] == '(' || instrucaoAssembly[i] == ')'){
            instrucaoAssembly[i] = ' ';
        }
    }

    char operacao[5], rdStr[4], rs1Str[4], rs2Str[4];  //extrai: ex -> add x1, x2, x3
    sscanf(instrucaoAssembly, "%s %s %s %s", operacao, rdStr, rs1Str, rs2Str);

    char funct7[8], funct3[4], opcode[8], rd[6], rs1[6], rs2[6]; //Recebe os binários

    binarioFunct7(operacao, funct7);
    binarioFunct3(operacao, funct3);
    binarioOpcode(operacao, opcode);

    registradorParaBinario(rdStr, rd);
    registradorParaBinario(rs1Str, rs1);
    registradorParaBinario(rs2Str, rs2);

    instrucaoBinario[0] = '\0'; //Inicializa a string de saída

    strncat(instrucaoBinario, funct7, 8);
    strncat(instrucaoBinario, rs2, 6);
    strncat(instrucaoBinario, rs1, 6);
    strncat(instrucaoBinario, funct3, 4);
    strncat(instrucaoBinario, rd, 6);
    strncat(instrucaoBinario, opcode, 8);
}

void processarTipoI(char instrucaoAssembly[], char instrucaoBinario[]){
    for (int i = 0; i < strlen(instrucaoAssembly); i++){     //Limpa a string
        if (instrucaoAssembly[i] == ',' || instrucaoAssembly[i] == '(' || instrucaoAssembly[i] == ')'){
            instrucaoAssembly[i] = ' ';
        }
    }

    char operacao[5], rdStr[4], rs1Str[4], imediatoStr[10];  //extrai: ex -> addi x1, x2, 10

    sscanf(instrucaoAssembly, "%s", operacao);

    if (strcmp(operacao, "lw") == 0){                      //If e else para verificar qual é a instrução
        sscanf(instrucaoAssembly, "%s %s %s %s", operacao, rdStr, imediatoStr, rs1Str);
    }else{
        sscanf(instrucaoAssembly, "%s %s %s %s", operacao, rdStr, rs1Str, imediatoStr);      //addi
    }
    
    char funct3[4], opcode[8], rd[6], rs1[6], imediato[13];    //Recebe os binários

    binarioFunct3(operacao, funct3);
    binarioOpcode(operacao, opcode);
    registradorParaBinario(rdStr, rd);
    registradorParaBinario(rs1Str, rs1);

    imediatoParaBinario(imediatoStr, imediato);      //chama a função que converte o imediato para binário

    instrucaoBinario[0] = '\0';   //Montagem

    strncat(instrucaoBinario, imediato, 13);
    strncat(instrucaoBinario, rs1, 6);
    strncat(instrucaoBinario, funct3, 4);
    strncat(instrucaoBinario, rd, 6);
    strncat(instrucaoBinario, opcode, 8);
}

void processarTipoS(char instrucaoAssembly[], char instrucaoBinario[]){
    for (int i = 0; i < strlen(instrucaoAssembly); i++){     //Limpa a string
        if (instrucaoAssembly[i] == ',' || instrucaoAssembly[i] == '(' || instrucaoAssembly[i] == ')'){
            instrucaoAssembly[i] = ' ';
        }
    }

    char operacao[5], rs2Str[4], rs1Str[4], imediatoStr[10];   //extrai: ex -> sw x1, 10(x2)
    sscanf(instrucaoAssembly, "%s %s %s %s", operacao, rs2Str, imediatoStr, rs1Str);

    char funct3[4], opcode[8], rs1[6], rs2[6], imediato[13];  //Recebe os binários

    binarioFunct3(operacao, funct3);
    binarioOpcode(operacao, opcode);
    registradorParaBinario(rs1Str, rs1);
    registradorParaBinario(rs2Str, rs2);

    imediatoParaBinario(imediatoStr, imediato);        //novamente chamando a função que converte o imediato para binário

    char imm11a5[8], imm4a0[6];      //bits 11:5 e bist 4:0, de acordo com a estrutura de uma instrução do tipo S

    strncpy(imm11a5, imediato, 7);
    imm11a5[7] = '\0';

    strncpy(imm4a0, &imediato[7], 5);
    imm4a0[5] = '\0';

    instrucaoBinario[0] = '\0';

    strncat(instrucaoBinario, imm11a5, 7);
    strncat(instrucaoBinario, rs2, 5);
    strncat(instrucaoBinario, rs1, 5);
    strncat(instrucaoBinario, funct3, 3);
    strncat(instrucaoBinario, imm4a0, 5);
    strncat(instrucaoBinario, opcode, 7);

}   

void processarTipoSB(char instrucaoAssembly[], char instrucaoBinario[], Rotulo rotulos[], int numRotulos, int enderecoInstrucaoAtual){
    for(int i = 0; i < strlen(instrucaoAssembly); i++){ //limpa a string para que se possa usar o sscanf.
        if(instrucaoAssembly[i] == ',' || instrucaoAssembly[i] == '(' || instrucaoAssembly[i] == ')'){
            instrucaoAssembly[i] = ' ';
        }
    }
    char operacao[5], registrador1[4], registrador2[4], rotulo[20];
    sscanf(instrucaoAssembly, "%s %s %s %s", operacao, registrador1, registrador2, rotulo); //lê a string e salva os valores de acordo com a estrutura da instrução.

    char funct3[4], opcode[8], imediato[13], rs1[6], rs2[6]; //recebe todos os valores binários que irão compor a instrução.
    binarioFunct3(operacao, funct3);
    binarioOpcode(operacao, opcode);
    registradorParaBinario(registrador1, rs1);
    registradorParaBinario(registrador2, rs2);
    int flagEncontreiRotulo = 0;
    for(int i = 0; i < numRotulos; i++){
        if(strcmp(rotulo, rotulos[i].stringRotulo) == 0){
            char Aux[20];
            sprintf(Aux, "%d", (rotulos[i].enderecoApontado - enderecoInstrucaoAtual) / 2);
            imediatoParaBinario(Aux, imediato);
            flagEncontreiRotulo = 1;
            break;
        }
    }
    if(flagEncontreiRotulo == 0){
        strncpy(imediato, "010101010101", 13);
    }

    char slice10a5Endereco[7], slice4a1Endereco[5]; //realiza a separação do binário do imediato (endereço), de acordo com a estrutura de uma instrução do tipo B.
    int c = 0;
    for(int i = 2; i <= 7; i++){
        slice10a5Endereco[c] = imediato[i];
        c++;
    }
    slice10a5Endereco[6] = '\0'; //importante incluir o caractere de fim de string ao fazer mudanças manuais em uma string.
    c = 0;
    for(int i = 8; i <= 11; i++){
        slice4a1Endereco[c] = imediato[i];
        c++;
    }
    slice4a1Endereco[4] = '\0';

    instrucaoBinario[0] = imediato[0]; //concatena, na ordem correta, todos os binários que formam uma instrução tipo B de 32 bits.
    instrucaoBinario[1] = '\0';
    strncat(instrucaoBinario, slice10a5Endereco, 7);
    strncat(instrucaoBinario, rs2, 6);
    strncat(instrucaoBinario, rs1, 6);
    strncat(instrucaoBinario, funct3, 4);
    strncat(instrucaoBinario, slice4a1Endereco, 5);
    instrucaoBinario[24] = imediato[1];
    instrucaoBinario[25] = '\0';
    strncat(instrucaoBinario, opcode, 8);
}