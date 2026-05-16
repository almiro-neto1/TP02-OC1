module somadorPCmais4 (
    input wire [31:0] pc,
    output wire [31:0] pcMais4
);
    assign pcMais4 = pc + 4;

endmodule