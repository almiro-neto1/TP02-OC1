module somadorBranch (
    input wire [31:0] pc, imediato,
    output wire [31:0] enderecoBranch
);
    assign enderecoBranch = pc + imediato;

endmodule