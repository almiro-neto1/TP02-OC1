//Entrada: endereço (32 bits)
//Saída: instrução (32 bits)
//Inicial: arquivo de instruções

module InstrucMemory (
    input wire [31:0] endereco,
    output reg [31:0] instrucao,
);

    reg [31:0] mem [0:63];      //64 instruções

    initial begin
        $readmemb("instrucoes.mem", mem);
    end

    always @(*) begin
        instrucao = mem[endereco[7:2]];   //endereço é dividido por 4
    end

end module        
