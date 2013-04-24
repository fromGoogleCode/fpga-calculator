use strict;
use warnings;

open FILE, "<$ARGV[0]";
open OUT, ">mem_data_hex.txt";
while(<FILE>)
{
	if($_ =~ /^0x(\w{2}),0x(\w{2}),0x(\w{2}),0x(\w{2}),0x(\w{2}),0x(\w{2}),0x(\w{2}),0x(\w{2}).*/)
	{
		print OUT "$1$2\r\n$3$4\r\n$5$6\r\n$7$8\r\n";
	}
}