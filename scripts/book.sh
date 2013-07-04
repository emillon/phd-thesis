#!/bin/bash
set -e
set -x
pdftk "$1" cat   1-40  output p1.pdf
pdftk "$1" cat  41-80  output p2.pdf
pdftk "$1" cat  81-120 output p3.pdf
pdftk "$1" cat 121-161 output p4.pdf
pdftk "$1" cat 161-end output p5.pdf
pdfbook p1.pdf
pdfbook p2.pdf
pdfbook p3.pdf
pdfbook p4.pdf
pdfbook p5.pdf
pdftk p1-book.pdf p2-book.pdf p3-book.pdf p4-book.pdf p5-book.pdf output typ-book.pdf
