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

gen/%.pyg.tex: code/% gen
	pygmentize -f latex -o $@ $<

gen/pygments-style.tex: gen
	pygmentize -f latex -S autumn > $@

gen:
	mkdir $@

clean:: gen-clean

gen-clean:
	rm -rf gen/

$(NAME).tex: gen/pygments-style.tex gen/struct-array.c.pyg.tex

# Debian package: latex-make
include /usr/include/LaTeX.mk
