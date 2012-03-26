NAME = typ
DEPS = $(wildcard *.tex)
all: pdf
pdf: $(NAME).pdf
dvi: $(NAME).dvi
$(NAME).pdf $(NAME).dvi: $(DEPS)
show: showpdf
showpdf: $(NAME).pdf
	xdg-open $<
showdvi: $(NAME).dvi
	xdvi $<

regen-bib:
	~/mkbib < $(NAME).tex > $(NAME).bib

# Debian package: latex-make
include /usr/include/LaTeX.mk
