default: sdof-step sdof-sine sdof-nonlin sdof-nleq 2dof-nl ndof-step

ndof-step: ndof-step.cpp enoch.o beam.o util/structure.o
	g++ ndof-step.cpp -ondof-step -Wno-deprecated beam.o enoch.o -lm -largtable2 util/structure.o -g

2dof-nl: 2dof-nl.cpp enoch.o beam.o nlhinge.o util/structure.o 
	g++ 2dof-nl.cpp -o2dof-nl -Wno-deprecated beam.o enoch.o nlhinge.o -lm -largtable2 util/structure.o -g

sdof-step: sdof-step.cpp enoch.o beam.o util/structure.o NLHinge.o
	g++ sdof-step.cpp -osdof-step -Wno-deprecated beam.o enoch.o  -lm -largtable2 util/structure.o -g

sdof-sine: sdof-sine.cpp enoch.o beam.o util/structure.o
	g++ sdof-sine.cpp -osdof-sine -Wno-deprecated beam.o enoch.o  -lm -largtable2 util/structure.o -g

sdof-nonlin: sdof-nonlin.cpp  enoch.o nlhinge.o util/structure.o
	g++ sdof-nonlin.cpp -osdof-nonlin -Wno-deprecated nlhinge.o enoch.o  -lm -largtable2 util/structure.o -g

sdof-nleq: sdof-nleq.cpp enoch.o nlhinge.o util/structure.o
	g++ sdof-nleq.cpp -osdof-nleq -Wno-deprecated nlhinge.o enoch.o  -lm -largtable2 util/structure.o -g

enoch.o: enoch.cpp enoch.hpp beam.o util/structure.o util/solve.cpp
	g++ -c enoch.cpp -oenoch.o -Wno-deprecated -g

nlhinge.o: NLHingeNonLin.cpp NLHingeNonLin.hpp util/structure.o
	 g++ -c NLHingeNonLin.cpp -onlhinge.o -Wno-deprecated -g

beam.o: beam.cpp beam.hpp util/structure.o
	 g++ -c beam.cpp -obeam.o -Wno-deprecated -g

util/structure.o: util/structure.cpp util/structure.hpp
	g++ -c util/structure.cpp -outil/structure.o -Wno-deprecated -g

clean:
	rm util/structure.o beam.o enoch.o sdof-sine sdof-step
