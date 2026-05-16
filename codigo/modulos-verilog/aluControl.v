module ALUControl (
    input wire bit30, 
    input wire [1:0] ALUOp, 
    input wire [2:0] funct3,
    output reg [1:0] operacao
);
    always @(*) begin
        if(ALUOp == 2'b00 || ALUOp == 2'b11) begin // load/store ou addi 
            operacao = 2'b00; //soma
        end
        else if(ALUOp == 2'b01) begin // branch
            operacao = 2'b01; //subtração
        end
        else if(ALUOp == 2'b10) begin // tipo R
            case(funct3)
                3'b000: begin
                    if(bit30 == 1) begin
                        operacao = 2'b01; //subtração
                    end
                    else begin
                        operacao = 2'b00; //soma
                    end
                end
                3'b001: operacao = 2'b11; //sll
                3'b100: operacao = 2'b10; //xor
                default: operacao = 2'b00;
            endcase
        end
        else begin
            operacao = 2'b00;
        end
    end

endmodule