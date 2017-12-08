Nminos: Entity.o Nminos.o
	g++ -w -o Nminos Entity.o Nminos.o

Nminos.o: Entity.h Entity.cpp Nminos.cpp
	g++ -w -c Entity.cpp Nminos.cpp

entity.o: Entity.h Entity.cpp
	g++ -w -c Entity.cpp
