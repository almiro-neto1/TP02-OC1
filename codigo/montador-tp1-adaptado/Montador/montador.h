#ifndef MONTADOR_H
#define MONTADOR_H
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    tipoR,
    tipoI,
    tipoS,
    tipoSB,
    tipoNulo
} tipoInstrucao;

typedef struct{
    char stringRotulo[20];
    int linhaDoRotulo;
    int enderecoApontado;
} Rotulo;

tipoInstrucao verificarInstrucao(char instrucao[]);
int encontrarRotulos(Rotulo rotulos[], FILE *arquivoEntrada);
void registradorParaBinario(char registrador[], char binario[]);
void imediatoParaBinario(char imediato[], char binario[]);
void binarioFunct7(char instrucao[], char funct7[]);
void binarioFunct3(char instrucao[], char funct3[]);
void binarioOpcode(char instrucao[], char opcode[]);
void processarTipoR(char instrucaoAssembly[], char instrucaoBinario[]);
void processarTipoI(char instrucaoAssembly[], char instrucaoBinario[]);
void processarTipoS(char instrucaoAssembly[], char instrucaoBinario[]);
void processarTipoSB(char instrucaoAssembly[], char instrucaoBinario[], Rotulo rotulos[], int numRotulos, int enderecoInstrucaoAtual);

#endif