FLAGS =	-pedantic-errors	-std=c++11

newgame.o: newgame.cpp newgame.h
					g++	$(FLAGS)	-c	$<

loadgame.o: loadgame.cpp loadgame.h newgame.h
						g++ $(FLAGS)	-c	$<

minesweep.o: minesweep.cpp newgame.h loadgame.h
						g++	$(FLAGS)	-c	$<

minesweep: minesweep.o newgame.o loadgame.o
					g++ $(FLAGS)	$^	-o	$@

clean:
			rm	-f	calc	calc.o	lcm.o	gcd.o	calc.tgz

tar:
			tar	-czvf	calc.tgz	*.cpp	*.h

.PHONY:	clean	tar

