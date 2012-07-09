#!/usr/bin/env perl
while (<>) {
  if (/\\cite\{([^}]+)\}/) {
    map {print "$ENV{HOME}\/bib\/$_.bib\n";} split /,/, $1
  }
}

