#!/usr/bin/perl
# $Id: egyptian-division.perl,v 1.2 2015-01-20 17:50:47-08 - - $

$0 =~ s|.*/||;
print STDERR "Usage: $0 numerator denominator\n" and exit
unless @ARGV == 2 and ($numer, $denom) = @ARGV
       and $numer =~ m/^\d+$/ and $denom =~ m/^\d+$/;

print "$0: verification: $numer / $denom = ", int $numer / $denom,
      " remainder ", $numer % $denom, "\n\n";

$top = 1;
$right = $denom;

while ($right <= $numer) {
   push @stack, [$top, $right];
   $top += $top;
   $right += $right;
}

($remdr, $quot) = ($numer, 0);
$fmt = "%12s %12s   %12s %12s\n";
while (@stack) {
   printf $fmt, "", "", $remdr, $quot;
   ($top, $right) = @{pop @stack};
   if ($right <= $remdr) {
      $remdr -= $right;
      $quot += $top;
      printf $fmt, $top, $right, "- " . $right, "+ " . $top;
   }else {
      printf $fmt, $top, $right, "- 0", "+ 0";
   }
   printf $fmt, "", "", "= " . $remdr, "= " . $quot;
   printf "\n";
}

printf $fmt, "", "", "remainder", "quotient";

__DATA__
//TEST// egyptian-division.perl 76543 123 >egyptian-division.out
//TEST// mkpspdf egyptian-division.ps \
//TEST//         egyptian-division.perl egyptian-division.out
