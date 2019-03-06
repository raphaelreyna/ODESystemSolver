all: solver clean

solver: nm.o main.o
	gcc nm.o main.o -o solver

nm.o:
	gcc -c src/NumericalMethods.c -o nm.o

main.o:
	gcc -c src/main.c -o main.o

HowItWorks.pdf: hiw.tex
	pdflatex -interaction=nonstopmode hiw.tex -o HowItWorks.pdf

hiw.tex:
	pandoc -s HowItWorks.org -o hiw.tex

clean:
	rm *.o
