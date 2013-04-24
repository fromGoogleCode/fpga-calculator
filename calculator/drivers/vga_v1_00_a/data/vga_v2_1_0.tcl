##############################################################################
## Filename:          G:\Sandboxes\Xilinx\calculator/drivers/vga_v1_00_a/data/vga_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Fri Apr 12 09:57:58 2013 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "vga" "NUM_INSTANCES" "DEVICE_ID" "C_MEM0_BASEADDR" "C_MEM0_HIGHADDR" "C_MEM1_BASEADDR" "C_MEM1_HIGHADDR" 
}
