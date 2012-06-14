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

$(NAME).tex: gentex

gentex: gen/pygments-style.tex

CODESAMPLES=\
	    showread.hs \
	    listrev.ml \
	    non-typable.py \
	    radeon-buggy.c \
	    radeon-git.diff \
	    struct-array.c \
	    euclide.c \
	    euclide-npk.c

gentex: $(addprefix gen/, $(addsuffix .pyg.tex, $(CODESAMPLES)))

# Debian package: latex-make
include /usr/include/LaTeX.mk
