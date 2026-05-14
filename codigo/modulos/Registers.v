
// Entradas: regLeitura1 = instrucao[19:15] (5 bits)
//           regLeitura2 = instrucao[24:20] (5 bits)
//           regEscrita = instrucao[11:7]  (5 bits)
//           dadoEscrita = valor a gravar   (32 bits)
//           regWrite = habilita escrita (1 bit)
// Saídas: dadoLeitura1 (32 bits)
//         dadoLeitura2 (32 bits)

module Registers (
    input  wire clk,
    input  wire regWrite,
    input  wire [4:0]  regLeitura1,
    input  wire [4:0]  regLeitura2,
    input  wire [4:0]  regEscrita,
    input  wire [31:0] dadoEscrita,
    output reg  [31:0] dadoLeitura1,
    output reg  [31:0] dadoLeitura2
);

reg [31:0] regs [0:31];
 
    integer i;
    initial begin
        for (i = 0; i < 32; i = i + 1)
            regs[i] = 32'b0;
    end
 
    always @(*) begin
        dadoLeitura1 = (regLeitura1 == 5'b0) ? 32'b0 : regs[regLeitura1];
        dadoLeitura2 = (regLeitura2 == 5'b0) ? 32'b0 : regs[regLeitura2];
    end
 
    always @(posedge clk) begin
        if (regWrite && regEscrita != 5'b0)
            regs[regEscrita] <= dadoEscrita;
    end
 
endmodule