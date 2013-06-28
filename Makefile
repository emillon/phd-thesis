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
	cat *.tex chap/*.tex | perl scripts/extractbib.pl | sort -u | xargs cat > $(NAME).bib

gen/%.pycon.pyg.tex: code/%.pycon gen
	pygmentize -f latex -l pycon -o $@ $<

gen/%.pyg.tex: code/% gen
	pygmentize -f latex -o $@ $<

gen/%.pdf: fig/%.svg gen
	inkscape -A $@ $<

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

gentex: gen/travaux.pdf

snapshot:
	make distclean
	git checkout pdf
	git merge --no-edit master
	make distclean
	make
	git add gen/*
	git commit -av -m snapshot
	git checkout master
	make

upload:
	scp typ.pdf tibre:public_html/these.pdf

# Debian package: latex-make
include /usr/include/LaTeX.mk
