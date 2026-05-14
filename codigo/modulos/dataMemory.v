module dataMemory (
    input wire [31:0] endereco, valorParaEscrita, 
    input wire memRead, memWrite, clk,
    output reg [31:0] valorSaida
);

    reg [7:0] mem [0:127];
    initial begin
        $readmemb("../arquivos-entrada/data-memory.bin", mem);
    end

    always @(*) begin
        if(memRead == 1 && memWrite == 0) begin
            valorSaida = {mem[endereco + 3], mem[endereco + 2], mem[endereco + 1], mem[endereco]};
        end
        else begin
            valorSaida = 32'b0;
        end
    end

    always @(negedge clk) begin
        if(memRead == 0 && memWrite == 1) begin
            mem[endereco] <= valorParaEscrita[7:0];
            mem[endereco + 1] <= valorParaEscrita[15:8];
            mem[endereco + 2] <= valorParaEscrita[23:16];
            mem[endereco + 3] <= valorParaEscrita[31:24];
        end
    end
endmodule 