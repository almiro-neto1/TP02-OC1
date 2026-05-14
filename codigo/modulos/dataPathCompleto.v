module dataPathCompleto (
    input clk, reset
);
    wire [31:0] pcSaida;
    wire [31:0] pcMais4;
    wire [31:0] instrucaoCompleta;
    wire branch, memRead, memToReg, memWrite, ALUSrc, regWrite;
    wire [1:0] ALUOp;
    wire [31:0] dadoLeitura1, dadoLeitura2;
    wire [31:0] imediato;
    wire [31:0] pcBranch;
    wire [1:0] operacaoALU;
    wire [31:0] entrada2ALU;
    wire [31:0] resultadoALU;
    wire flagZeroALU;
    wire controleMuxPC;
    wire [31:0] resultadoMuxPC;
    wire [31:0] valorLeituraMemoria;
    wire [31:0] valorEscritaRegs;

    pc PC(
        .clk(clk),
        .reset(reset),
        .pcEntrada(resultadoMuxPC),
        .pcSaida(pcSaida)
    );

    somadorPCmais4 somadorPCmais4(
        .pc(pcSaida),
        .pcMais4(pcMais4)
    );

    InstrucMemory instructionMemory(
        .endereco(pcSaida),
        .instrucao(instrucaoCompleta)
    );

    Control control(
        .opcode(instrucaoCompleta[6:0]),
        .branch(branch),
        .memRead(memRead),
        .memtoReg(memToReg),
        .memWrite(memWrite),
        .ALUSrc(ALUSrc),
        .regWrite(regWrite),
        .ALUOp(ALUOp)
    );

    Registers registers(
        .clk(clk),
        .regWrite(regWrite),
        .regLeitura1(instrucaoCompleta[19:15]),
        .regLeitura2(instrucaoCompleta[24:20]),
        .regEscrita(instrucaoCompleta[11:7]),
        .dadoEscrita(valorEscritaRegs),
        .dadoLeitura1(dadoLeitura1),
        .dadoLeitura2(dadoLeitura2)
    );

    ImmGen immGen(
        .instrucao(instrucaoCompleta),
        .imediato(imediato)
    );

    somadorBranch somadorBranch(
        .pc(pcSaida),
        .imediato(imediato),
        .enderecoBranch(pcBranch)
    );

    ALUControl ALUControl(
        .bit30(instrucaoCompleta[30]),
        .ALUOp(ALUOp),
        .funct3(instrucaoCompleta[14:12]),
        .operacao(operacaoALU)
    );

    multiplexador multiplexadorALU(
        .controle(ALUSrc),
        .input1(dadoLeitura2),
        .input2(imediato),
        .saida(entrada2ALU)
    );

    ALU alu(
        .valor1(dadoLeitura1),
        .valor2(entrada2ALU),
        .ALUControl(operacaoALU),
        .resultado(resultadoALU),
        .zero(flagZeroALU)
    );

    assign controleMuxPC = branch & (~flagZeroALU);
    
    multiplexador multiplexadorPC(
        .controle(controleMuxPC),
        .input1(pcMais4),
        .input2(pcBranch),
        .saida(resultadoMuxPC)
    );

    dataMemory dataMemory(
        .endereco(resultadoALU),
        .valorParaEscrita(dadoLeitura2),
        .memRead(memRead),
        .memWrite(memWrite),
        .clk(clk),
        .valorSaida(valorLeituraMemoria)
    );

    multiplexador muxDataMemory(
        .controle(memToReg),
        .input1(resultadoALU),
        .input2(valorLeituraMemoria),
        .saida(valorEscritaRegs)
    );

endmodule