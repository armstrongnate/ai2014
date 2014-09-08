include ../Makefile.top

PROJECT_LIST  :=  utils ScavengerWorld WumpusWorld PLTest FOLTest Rectangle Candy \
	CCheckers TicTacToe Mancala Numbers Maze

all install clean spotless:
	for d in $(PROJECT_LIST); do \
		(cd $$d; $(MAKE) -j $@) \
	done

include ../Makefile.dep
