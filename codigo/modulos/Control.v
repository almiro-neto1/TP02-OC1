// Entrada: opcode = instrucao[6:0] (7 bits)
// Saídas: branch, memRead, memtoReg (1 bit cada)
//ALUOp (2 bits)
//memWrite, ALUSrc, regWrite (1 bit cada)

module Control (
    input wire [6:0] opcode,
    output reg branch,
    output reg memRead,
    output reg memtoReg,
    output reg [1:0] ALUOp,
    output reg memWrite,
    output reg ALUSrc,
    output reg regWrite
);

    always @(*) begin
        //Valores padrão
        branch = 0;
        memRead = 0;
        memtoReg = 0;
        ALUOp = 2'b00;
        memWrite = 0;
        ALUSrc = 0;
        regWrite = 0;

        case(opcode)
            7'b0110011: begin  //Tipo R: add, xor, sll
                regWrite = 1;
                ALUOp = 2'b10;
            end

            7'b0000011: begin   //lw
                memRead = 1;
                memtoReg = 1;
                ALUSrc = 1;
                regWrite = 1;
                ALUOp = 2'b00;
            end    

            7'b0010011: begin  //addi
                ALUSrc   = 1;
                regWrite = 1;
                ALUOp    = 2'b11; //ALUControl trata como soma pelo imediato
            end

            7'b0100011: begin //sw
                ALUSrc   = 1;
                memWrite = 1;
                ALUOp    = 2'b00; //soma para calcular endereço
            end

            7'b1100011: begin //bne
                branch = 1;
                ALUOp  = 2'b01; //subtração para comparar
            end
        endcase
    end
 
endmodule





