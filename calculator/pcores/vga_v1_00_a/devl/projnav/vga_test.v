`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   10:11:15 04/26/2013
// Design Name:   user_logic
// Module Name:   G:/Sandboxes/Xilinx/calculator/pcores/vga_v1_00_a/devl/projnav/vga_test.v
// Project Name:  vga
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: user_logic
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module vga_test;

	// Inputs
	reg Bus2IP_Clk;
	reg Bus2IP_Reset;
	reg [0:31] Bus2IP_Addr;
	reg [0:1] Bus2IP_CS;
	reg Bus2IP_RNW;
	reg [0:31] Bus2IP_Data;
	reg [0:3] Bus2IP_BE;

	// Outputs
	wire h_sync;
	wire v_sync;
	wire [0:5] video;
	wire [0:31] IP2Bus_Data;
	wire IP2Bus_RdAck;
	wire IP2Bus_WrAck;
	wire IP2Bus_Error;

	// Instantiate the Unit Under Test (UUT)
	user_logic uut (
		.h_sync(h_sync), 
		.v_sync(v_sync), 
		.video(video), 
		.Bus2IP_Clk(Bus2IP_Clk), 
		.Bus2IP_Reset(Bus2IP_Reset), 
		.Bus2IP_Addr(Bus2IP_Addr), 
		.Bus2IP_CS(Bus2IP_CS), 
		.Bus2IP_RNW(Bus2IP_RNW), 
		.Bus2IP_Data(Bus2IP_Data), 
		.Bus2IP_BE(Bus2IP_BE), 
		.IP2Bus_Data(IP2Bus_Data), 
		.IP2Bus_RdAck(IP2Bus_RdAck), 
		.IP2Bus_WrAck(IP2Bus_WrAck), 
		.IP2Bus_Error(IP2Bus_Error)
	);

	initial begin
		// Initialize Inputs
		Bus2IP_Clk = 0;
		Bus2IP_Reset = 0;
		Bus2IP_Addr = 0;
		Bus2IP_CS = 0;
		Bus2IP_RNW = 0;
		Bus2IP_Data = 0;
		Bus2IP_BE = 0;
		// Wait 100 ns for global reset to finish
		#100;
		
		Bus2IP_Reset = ~ Bus2IP_Reset;
 #20		
		Bus2IP_Reset = ~ Bus2IP_Reset;
		// Add stimulus here

 
	end
		always
			#5 Bus2IP_Clk = ~Bus2IP_Clk;
      
      
endmodule

