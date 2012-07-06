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
	cat $(NAME).tex chap/*.tex | ~/mkbib > $(NAME).bib

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

CODESAMPLES=$(notdir $(wildcard code/*))

gentex: $(addprefix gen/, $(addsuffix .pyg.tex, $(CODESAMPLES)))

snapshot:
	make distclean
	git checkout pdf
	git merge master
	make distclean
	make
	git commit -av -m snapshot
	git checkout master

# Debian package: latex-make
include /usr/include/LaTeX.mk
