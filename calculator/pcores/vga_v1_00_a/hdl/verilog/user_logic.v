module user_logic
(
  // -- ADD USER PORTS BELOW THIS LINE ---------------
 h_sync,
 v_sync,
 video,
  // -- ADD USER PORTS ABOVE THIS LINE ---------------

  // -- DO NOT EDIT BELOW THIS LINE ------------------
  // -- Bus protocol ports, do not add to or delete 
  Bus2IP_Clk,                     // Bus to IP clock
  Bus2IP_Reset,                   // Bus to IP reset
  Bus2IP_Addr,                    // Bus to IP address bus
  Bus2IP_CS,                      // Bus to IP chip select for user logic memory selection
  Bus2IP_RNW,                     // Bus to IP read/not write
  Bus2IP_Data,                    // Bus to IP data bus
  Bus2IP_BE,                      // Bus to IP byte enables
  IP2Bus_Data,                    // IP to Bus data bus
  IP2Bus_RdAck,                   // IP to Bus read transfer acknowledgement
  IP2Bus_WrAck,                   // IP to Bus write transfer acknowledgement
  IP2Bus_Error                    // IP to Bus error response
  // -- DO NOT EDIT ABOVE THIS LINE ------------------
); // user_logic

// -- ADD USER PARAMETERS BELOW THIS LINE ------------
// --USER parameters added here 
// -- ADD USER PARAMETERS ABOVE THIS LINE ------------

// -- DO NOT EDIT BELOW THIS LINE --------------------
// -- Bus protocol parameters, do not add to or delete
parameter C_SLV_AWIDTH                   = 32;
parameter C_SLV_DWIDTH                   = 32;
parameter C_NUM_MEM                      = 2;
// -- DO NOT EDIT ABOVE THIS LINE --------------------

// -- ADD USER PORTS BELOW THIS LINE -----------------
output reg			h_sync;
output reg			v_sync;
output reg	[0:6] video; 
// -- ADD USER PORTS ABOVE THIS LINE -----------------

// -- DO NOT EDIT BELOW THIS LINE --------------------
// -- Bus protocol ports, do not add to or delete
input                                     Bus2IP_Clk;
input                                     Bus2IP_Reset;
input      [0 : C_SLV_AWIDTH-1]           Bus2IP_Addr;
input      [0 : C_NUM_MEM-1]              Bus2IP_CS;
input                                     Bus2IP_RNW;
input      [0 : C_SLV_DWIDTH-1]           Bus2IP_Data;
input      [0 : C_SLV_DWIDTH/8-1]         Bus2IP_BE;
output     [0 : C_SLV_DWIDTH-1]           IP2Bus_Data;
output                                    IP2Bus_RdAck;
output                                    IP2Bus_WrAck;
output                                    IP2Bus_Error;
// -- DO NOT EDIT ABOVE THIS LINE --------------------

//----------------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------------

  // --USER nets declarations added here, as needed for user logic

  // --USER logic implementation added here
	parameter RAM_WIDTH = 32;
   parameter RAM_ADDR_BITS = 32;


  // ------------------------------------------------------------
  // Example code to drive IP to Bus signals
  // ------------------------------------------------------------

// Block RAM for character table

   (* RAM_STYLE="{ BLOCK }" *)
   reg [RAM_WIDTH-1:0] char_mem [(2**RAM_ADDR_BITS)-1:0];
   reg [RAM_WIDTH-1:0] vga_output_data;   
   reg [RAM_ADDR_BITS-1:0] vga_read_address;   

	//<reg_or_wire> [RAM_ADDR_BITS-1:0] <read_address>, <write_address>;
   //<reg_or_wire> [RAM_WIDTH-1:0] <input_data>;

   //  The following code is only necessary if you wish to initialize the RAM 
   //  contents via an external file (use $readmemb for binary data)
   //initial
      //$readmemh("<data_file_name>", <rom_name>, <begin_address>, <end_address>);

  always @(posedge Bus2IP_Clk) begin
      if (Bus2IP_CS[0])
         char_mem[Bus2IP_Addr] <= Bus2IP_Data;
      vga_output_data <= char_mem[vga_read_address];
   end
// Block RAM for character codes in each position

   (* RAM_STYLE="{ BLOCK }" *)
   reg [RAM_WIDTH-1:0] pos_mem [(2**RAM_ADDR_BITS)-1:0];
   reg [RAM_WIDTH-1:0] pos_output_data;   
   reg [RAM_ADDR_BITS-1:0] pos_read_address;   

	//<reg_or_wire> [RAM_ADDR_BITS-1:0] <read_address>, <write_address>;
   //<reg_or_wire> [RAM_WIDTH-1:0] <input_data>;

   //  The following code is only necessary if you wish to initialize the RAM 
   //  contents via an external file (use $readmemb for binary data)
   //initial
      //$readmemh("<data_file_name>", <rom_name>, <begin_address>, <end_address>);

  always @(posedge Bus2IP_Clk) begin
      if (Bus2IP_CS[1])
         pos_mem[Bus2IP_Addr] <= Bus2IP_Data;
      pos_output_data <= char_mem[pos_read_address];
   end

reg [9:0] x ;
reg [9:0] y;
//reg char_col [1:0];
//reg char_row [1:0];

// Increment x position
always @(posedge Bus2IP_Clk)	
	begin
		if(!Bus2IP_Reset)
		begin
			x <= x + 1;
		end
end
// Increment y position
always @(posedge Bus2IP_Clk)
begin
	if(!Bus2IP_Reset)
		begin
			if(x == 799)
			begin
				if(y == 520)
					begin
						y <= 0;
					end
				else
					begin
						y <= y + 1;
					end
			end
		end
	else
	/* Reset */
	begin
		y <= 0;
	end
end
// video
always @(posedge Bus2IP_Clk)
begin
	if(!Bus2IP_Reset)
	begin
		video <= 6'b101010;
	end
end
// hsync
reg hsync_phase1;
always @(posedge Bus2IP_Clk)
begin
	if(!Bus2IP_Reset)
	begin
		/* Hsync must be reset at 655 but it shall be delayed with one clock cycle 
		 due to delay of block RAM */
		if(x == 654)
		begin
			hsync_phase1 <= 0;
		end
		else if(x == 750)
		begin
			hsync_phase1 <= 1;
		end
		 h_sync <= hsync_phase1;
	end
	else
	begin
		hsync_phase1 <= 0;
		h_sync <= 0;
	end	 
end

// vsync
reg vsync_phase1;
always @(posedge Bus2IP_Clk)
begin
	if(!Bus2IP_Reset)
	begin
		/* Hsync must be reset at 655 but it shall be delayed with one clock cycle 
		 due to delay of block RAM */
		if(y == 479)
		begin
			vsync_phase1 <= 0;
		end
		else if(x == 481)
		begin
			vsync_phase1 <= 1;
		end
		 v_sync <= vsync_phase1;
	end
	else
	begin
		vsync_phase1 <= 0;
		v_sync <= 0;
	end
end

 assign IP2Bus_Data    = 0;
 assign IP2Bus_WrAck   = Bus2IP_CS[0] | Bus2IP_CS[1];
 assign IP2Bus_RdAck   = Bus2IP_CS[0] | Bus2IP_CS[1];
 assign IP2Bus_Error   = 0;


endmodule
