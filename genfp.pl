use strict;
use warnings;

main();

sub main
{
	my @vectors;
	my $i = 0;
	#print get_tani(50,90,50);
	my $num_of_ones = 32;
	generate_vector(\@vectors,$num_of_ones);
	print_vectors(\@vectors);
	print_report();

}

sub generate_vector()
{
	my $vectors = $_[0];
	my $ones = $_[1];
	my $tmp_str = "";
	my $i = 0;
	while($i != (1024 - $ones))
	{
		$tmp_str = ("0" x $i).("1"x 32).("0" x (1024 - $ones - $i - 1));
		@{$vectors}[$i] = $tmp_str;
		$i = $i + 1; 
	}
}
sub print_vectors()
{
	my $vectors = $_[0];
	open (FILE,">test_vectors.txt");
	foreach my $vector (@{$vectors})
	{
		print FILE "$vector \n";
	}
	
}
sub print_report()
{
	print get_tani(32,32,31)
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

