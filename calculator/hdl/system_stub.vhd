-------------------------------------------------------------------------------
-- system_stub.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

entity system_stub is
  port (
    fpga_0_LEDs_Displays_GPIO_IO_O_pin : out std_logic_vector(0 to 24);
    fpga_0_Switches_Buttons_GPIO_IO_I_pin : in std_logic_vector(0 to 11);
    fpga_0_clk_1_sys_clk_pin : in std_logic;
    fpga_0_rst_1_sys_rst_pin : in std_logic;
    xps_ps2_0_PS2_1_DATA : inout std_logic;
    xps_ps2_0_PS2_1_CLK : inout std_logic;
    vga_0_v_sync_pin : out std_logic;
    vga_0_video_pin : out std_logic_vector(0 to 6)
  );
end system_stub;

architecture STRUCTURE of system_stub is

  component system is
    port (
      fpga_0_LEDs_Displays_GPIO_IO_O_pin : out std_logic_vector(0 to 24);
      fpga_0_Switches_Buttons_GPIO_IO_I_pin : in std_logic_vector(0 to 11);
      fpga_0_clk_1_sys_clk_pin : in std_logic;
      fpga_0_rst_1_sys_rst_pin : in std_logic;
      xps_ps2_0_PS2_1_DATA : inout std_logic;
      xps_ps2_0_PS2_1_CLK : inout std_logic;
      vga_0_v_sync_pin : out std_logic;
      vga_0_video_pin : out std_logic_vector(0 to 6)
    );
  end component;

  attribute BOX_TYPE : STRING;
  attribute BOX_TYPE of system : component is "user_black_box";

begin

  system_i : system
    port map (
      fpga_0_LEDs_Displays_GPIO_IO_O_pin => fpga_0_LEDs_Displays_GPIO_IO_O_pin,
      fpga_0_Switches_Buttons_GPIO_IO_I_pin => fpga_0_Switches_Buttons_GPIO_IO_I_pin,
      fpga_0_clk_1_sys_clk_pin => fpga_0_clk_1_sys_clk_pin,
      fpga_0_rst_1_sys_rst_pin => fpga_0_rst_1_sys_rst_pin,
      xps_ps2_0_PS2_1_DATA => xps_ps2_0_PS2_1_DATA,
      xps_ps2_0_PS2_1_CLK => xps_ps2_0_PS2_1_CLK,
      vga_0_v_sync_pin => vga_0_v_sync_pin,
      vga_0_video_pin => vga_0_video_pin
    );

end architecture STRUCTURE;

