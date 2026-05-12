module multiplexador (
    input wire controle, 
    input wire [31:0] input1, input2,
    output wire [31:0] saida
);
    assign saida = controle ? input2 : input1;
    
endmodule