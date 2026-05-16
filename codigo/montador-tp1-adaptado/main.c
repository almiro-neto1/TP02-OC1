#include "Montador/montador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    //abre e verifica os arquivos de entrada e saída.
    if(argc == 1){
        printf("Arquivo de entrada nao foi passado!\n");
        exit(1);
    }
    FILE *arquivoEntrada = fopen(argv[1], "r");
    if(arquivoEntrada == NULL){
        printf("Erro ao abrir o arquivo de entrada!\n");
        exit(1);
    }
    FILE *arquivoSaida;
    if(argc != 4){
        arquivoSaida = stdout; //caso o usuário não passe um arquivo de saída, coloca o terminal como saída de dados.
    }
    else {
        arquivoSaida = fopen(argv[3], "w");
        if(arquivoSaida == NULL){
            printf("Erro ao abrir o arquivo de saida!\n");
            exit(1);
        }
    }

    int contadorImpressoes = 0;
    Rotulo rotulos[50];
    int numRotulos = encontrarRotulos(rotulos, arquivoEntrada);

    int linhaInstrucaoAtual = 1;
    int enderecoInstrucaoAtual = 0;
    char instrucaoAssembly[35];
    while(fgets(instrucaoAssembly, 35, arquivoEntrada) != NULL){
        int flagEhRotulo = 0;
        for(int i = 0; i < numRotulos; i++){
            if(rotulos[i].linhaDoRotulo == linhaInstrucaoAtual){
                flagEhRotulo = 1;
                break;
            }
        }
        if(flagEhRotulo == 0){
            tipoInstrucao tipoInstrucaoAssembly = verificarInstrucao(instrucaoAssembly);
            char instrucaoBinario[35] = "\0";
            if(tipoInstrucaoAssembly == tipoR){
                processarTipoR(instrucaoAssembly, instrucaoBinario);
                enderecoInstrucaoAtual += 4;
            }
            else if(tipoInstrucaoAssembly == tipoI){
                processarTipoI(instrucaoAssembly, instrucaoBinario);
                enderecoInstrucaoAtual += 4;
            }
            else if(tipoInstrucaoAssembly == tipoS){
                processarTipoS(instrucaoAssembly, instrucaoBinario);
                enderecoInstrucaoAtual += 4;
            }
            else if(tipoInstrucaoAssembly == tipoSB){
                processarTipoSB(instrucaoAssembly, instrucaoBinario, rotulos, numRotulos, enderecoInstrucaoAtual);
                enderecoInstrucaoAtual += 4;
            }
            else if(tipoInstrucaoAssembly == tipoNulo){
                printf("Nao foi possivel concluir a montagem. O arquivo de entrada possui uma instrucao nao suportada por esse montador!\n");
                exit(1);
            }
            for(int i = 31; i >= 0; i -= 8){
                fprintf(arquivoSaida, "%c%c%c%c%c%c%c%c\n", instrucaoBinario[i - 7], instrucaoBinario[i - 6], instrucaoBinario[i - 5], instrucaoBinario[i - 4], instrucaoBinario[i - 3], instrucaoBinario[i - 2], instrucaoBinario[i - 1], instrucaoBinario[i]);
                contadorImpressoes++;
            }
        }
    linhaInstrucaoAtual++;
    }

    for(int i = contadorImpressoes; i < 128; i++){
        fprintf(arquivoSaida, "00000000\n");
    }

    fclose(arquivoEntrada);
    if(arquivoSaida != stdout){
        fclose(arquivoSaida);
    }

    return 0;
}

