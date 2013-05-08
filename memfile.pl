use strict;
use warnings;

my $bit_width = $ARGV[1];
my $mem_size = 2 ** $bit_width;
my $mode = 0;
if(defined($ARGV[2]))
{
	$mode = $ARGV[2];
}

print "$bit_width $mem_size";
open OUT, ">mem_video_hex.txt";
if($mode == 0)
{
	open FILE, "<$ARGV[0]";

	while(<FILE>)
	{
		if($_ =~ /^0x(\w{2}),0x(\w{2}),0x(\w{2}),0x(\w{2}),0x(\w{2}),0x(\w{2}),0x(\w{2}),0x(\w{2}).*/)
		{
			print OUT "$1\n$2\n$3\n$4\n$5\n$6\n$7\n$8\n";
			$mem_size = $mem_size - 8;
		}
	}
}
else
{
	my $i = 64;
	while($i > 0)
	{
		my $out;
		$out = sprintf ("%02x", $i);
		print OUT "$out\n";
		$mem_size = $mem_size - 1;
		$i = $i - 1;
	}
}
while($mem_size > 0)
{
	print OUT "00\n00\n00\n00\n00\n00\n00\n00\n";
	$mem_size = $mem_size - 8;
}
