all: montador simulacao run
	
simulacao: #compila todos os módulos + testbench
	iverilog -o testbench/simulacao_TP modulos-verilog/*.v testbench/testbench.v

run: #roda a simulação
	vvp testbench/simulacao_TP

montador:
	gcc montador-tp1-adaptado/main.c montador-tp1-adaptado/Montador/montador.c -o montador-tp1-adaptado/binario-programa
	montador-tp1-adaptado/binario-programa arquivos-entrada/assembly.asm -o arquivos-entrada/assembly.bin