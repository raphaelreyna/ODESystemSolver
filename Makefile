all: solver

solver: nm.o vma.o main.o
	gcc -g nm.o vma.o main.o -lm -o solver

nm.o:
	gcc -g -c src/NumericalMethods.c -o nm.o

vma.o:
	gcc -g -c src/VectorMatrixAlgebra.c -o vma.o

main.o:
	gcc -g -c src/main.c -o main.o

HowItWorks.pdf: hiw.tex
	pdflatex -interaction=nonstopmode hiw.tex -o HowItWorks.pdf

hiw.tex:
	pandoc -s HowItWorks.org -o hiw.tex

clean:
	rm *.o

run: solver
	./solver

debug: solver
	lldb solver
