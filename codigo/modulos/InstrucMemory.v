//Entrada: endereço (32 bits)
//Saída: instrução (32 bits)
//Inicial: arquivo de instruções

module InstrucMemory (
    input wire [31:0] endereco,
    output reg [31:0] instrucao
);

    // memória de bytes
    reg [7:0] mem [0:127];

    initial begin
        $readmemb("../arquivos-entrada/assembly.bin", mem);
    end

    always @(*) begin

        // little-endian
        instrucao = {
            mem[endereco + 3],
            mem[endereco + 2],
            mem[endereco + 1],
            mem[endereco]
        };

    end

endmodule