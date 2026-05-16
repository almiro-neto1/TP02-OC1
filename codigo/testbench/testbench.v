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
        repeat(150) @(posedge clk);

        $display("========================================");
        $display("        ESTADO DOS REGISTRADORES        ");
        $display("========================================\n");
        for (i = 0; i < 32; i = i + 1) begin
            $display("Register [%2d] : %d - %b", i, dut.registers.regs[i], dut.registers.regs[i]);
        end

        $display("\n========================================");
        $display("           ESTADO DA MEMORIA            ");
        $display("========================================\n");
        for (i = 0; i < 128; i = i + 4) begin
            $display("Memoria [%3d] : %d - %b", i, {dut.dataMemory.mem[i + 3], dut.dataMemory.mem[i + 2], dut.dataMemory.mem[i + 1], dut.dataMemory.mem[i]}, {dut.dataMemory.mem[i + 3], dut.dataMemory.mem[i + 2], dut.dataMemory.mem[i + 1], dut.dataMemory.mem[i]});
        end
        $display("========================================");

        $finish;
    end

endmodule