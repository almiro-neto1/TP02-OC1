`timescale 1ns / 1ps

module testbench;

    reg clk;
    reg reset;

    dataPathCompleto dut (
        .clk  (clk),
        .reset(reset)
    );

    // Clock: inicializa antes de oscilar
    initial clk = 0;
    always #15 clk = ~clk;

    integer i;

    initial begin
        // Reset por 2 ciclos
        reset = 1;
        repeat(2) @(posedge clk);

        // Libera e executa 30 ciclos
        reset = 0;
        repeat(30) @(posedge clk);

        $display("========================================");
        $display("        ESTADO DOS REGISTRADORES        ");
        $display("========================================");
        for (i = 0; i < 32; i = i + 1) begin
            $display("Register [%2d] : %b", i, dut.registers.regs[i]);
        end

        $display("\n========================================");
        $display("           ESTADO DA MEMORIA            ");
        $display("========================================");
        for (i = 0; i < 128; i = i + 1) begin
            $display("Memoria [%3d] : %b", i, dut.dataMemory.mem[i]);
        end
        $display("========================================");

        $finish;
    end

endmodule