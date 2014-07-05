.PHONY: all watch full check
WHAT=pres

CODESAMPLES=$(notdir $(wildcard code/*))
GEN=$(addprefix gen/, $(addsuffix .pyg.tex, $(CODESAMPLES))) gen

all: $(GEN) gen/pygments-style.tex
	pdflatex -halt-on-error $(WHAT)

gen:
	mkdir $@

gen/%.pyg.tex: code/% gen
	pygmentize -f latex -o $@ $<

gen/pygments-style.tex:
	pygmentize -f latex -S vs > $@

full:
	$(MAKE) all
	bibtex $(WHAT)
	$(MAKE) all
	$(MAKE) all

watch:
	$(MAKE) ; while true ; do inotifywait -qe close_write *.tex; $(MAKE) ; done

regen-bib:
	cat $(WHAT).tex |\
	  perl scripts/extractbib.pl |\
	  sort -u |\
	  xargs cat |\
	  grep -v doi |\
	  grep -v -F acm.org |\
	  grep -v issn |\
	  grep -v isbn |\
	  grep -v address |\
	  cat >\
	  $(WHAT).bib

clean:
	rm -f *.aux *.nav *.log *.out *.snm *.vrb

check:
	! ack 'begin{frame}$$'
