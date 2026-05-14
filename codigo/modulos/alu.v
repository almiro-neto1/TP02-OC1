module ALU (
    input wire [31:0] valor1, valor2,
    input wire [1:0] ALUControl,
    output reg [31:0] resultado,
    output wire zero
);
    always @(*) begin
        case(ALUControl)
            2'b00: begin //soma 
                resultado = valor1 + valor2;
            end
            2'b01: begin //subtração
                resultado = valor1 - valor2;
            end
            2'b10: begin //xor
                resultado = valor1 ^ valor2;
            end
            2'b11: begin //deslocamento para esquerda
                resultado = valor1 << valor2;
            end
            default: resultado = valor1 + valor2;
        endcase
    end

    assign zero = (resultado == 0) ? 1'b1 : 1'b0;

endmodule