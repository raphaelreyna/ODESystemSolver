cursesExample: nm.o vma.o cursesExample.o
	gcc nm.o vma.o cursesExample.o -lm -lcurses -o cursesExample
	rm *.o

cursesExample.o:
	gcc -c examples/cursesExample.c -o cursesExample.o

example: nm.o vma.o example.o
	gcc nm.o vma.o example.o -lm -o example
	rm *.o

example.o:
	gcc -c examples/example.c -o example.o

nm.o:
	gcc -c src/NumericalMethods.c -o nm.o

vma.o:
	gcc -c src/VectorMatrixAlgebra.c -o vma.o

main.o:
	gcc -c src/main.c -o main.o

HowItWorks.pdf: hiw.tex
	pdflatex -interaction=nonstopmode hiw.tex -o HowItWorks.pdf

hiw.tex:
	pandoc -s HowItWorks.org -o hiw.tex

clean:
	rm *.o
