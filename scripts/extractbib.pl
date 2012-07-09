#!/usr/bin/env perl
while (<>) {
  while (/\\cite\{([^}]+)\}/g) {
    map {print "$ENV{HOME}\/bib\/$_.bib\n";} split /,/, $1
  }
}
