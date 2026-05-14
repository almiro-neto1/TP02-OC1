//Entrada: pcEntrada (32 bits) 
//Saída: pcSaida (32 bits)
//Inicial: 0
module pc (
    input wire clk,
    input wire reset, 
    input wire[31:0] pcEntrada,
    output reg[31:0] pcSaida
);
    always @(posedge clk or posedge reset) begin
        if (reset) 
            pcSaida <= 32'b0;
        else    
            pcSaida <= pcEntrada;
    end

endmodule           


