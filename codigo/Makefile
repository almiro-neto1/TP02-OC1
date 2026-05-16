all: simulacao run
	
simulacao: #compila todos os módulos + testbench
	iverilog -o testbench/simulacao_TP modulos/*.v testbench/testbench.v

run: #roda a simulação
	vvp testbench/simulacao_TP