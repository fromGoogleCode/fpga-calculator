use strict;
use warnings;

main();

sub main
{
	my @vectors;
	#print get_tani(50,90,50);
	generate_rnd_1024();
}


sub generate_rnd_1024()
{
	my $numofones = $1;
	my $i = 0;
	my $num_of_ones = 0 ;
	my $output_str = "";
	while($i < 32)
	{
		my $tmp_num = 0;
		$tmp_num = int(rand(255));
		$num_of_ones = $num_of_ones + bit_count($tmp_num);
		$output_str .= sprintf("%b",$tmp_num);
		$i = $i + 1;
	}
	print "\n".$output_str."\n";
	print "\n".$num_of_ones."\n";
	#while($numofones)
	#{
	#	bit_count(int(rand(255)));
	#}
}

sub bit_count()
{
	my $num = $_[0];
	my $count = 0;
	while($num != 0)
	{
		if(($num % 2) == 1)
		{
			$count++;
		}
		$num = $num >> 1;
	}
	return $count;
}

sub get_tani()
{
	my($a,$b,$c)= @_;
	return $c/($a + $b - $c);
}

