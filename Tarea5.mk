Results_hw5.pdf : Results_hw5.tex

	pdflatex Results_hw5.tex

Results_hw5.tex : Plots.py

	python Plots.py

Plots.py : CurvaRotacion.c RadialVelocities.dat

	cc CurvaRotacion.c -o CurvaRotacion.x
	./CurvaRotacion.x




