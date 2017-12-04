Results_hw5.pdf : Results_hw5.tex

	pdflatex Results_hw5.tex

Results_hw5.tex : Grafica.pdf Plots.py

	python Plots.py

Grafica.pdf: Plots.py
	python Plots.py

Plots.py : CurvaRotacion.x 
	./CurvaRotacion.x
	
CurvaRotacion.x: CurvaRotacion.c
	cc CurvaRotacion.c -o CurvaRotacion.x -lm
	


