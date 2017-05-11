CXX = g++-6
CXXFLAGS = $(shell pkg-config --cflags gtkmm-3.0) 
LDFLAGS = $(shell pkg-config --libs gtkmm-3.0) -ldl

TSOURCES = database.cpp customer.cpp test.cpp interface.cpp product.cpp orders.cpp util.cpp sqlite3.c
TOBJECTS = database.o customer.o test.o interface.o product.o orders.o util.o sqlite3.o

SOURCES = database.cpp customer.cpp system.cpp interface.cpp product.cpp orders.cpp util.cpp sqlite3.c 
OBJECTS = database.o customer.o system.o interface.o product.o orders.o util.o sqlite3.o

TEXE = test

EXE = main

database.o: database.cpp
	$(CXX) -c $<

test.o: test.cpp
	$(CXX) -c $<

customer.o: customer.cpp
	$(CXX) -c $<

system.o: system.cpp
	$(CXX) -c $<

interface.o: interface.cpp
	$(CXX) -c $<

product.o: product.cpp
	$(CXX) -c $<

orders.o: orders.cpp
	$(CXX) -c $<
	
util.o: util.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $<

sqlite3.o: sqlite3.c
	gcc -c $<

$(EXE): $(OBJECTS)
	$(CXX) -std=c++11 $(CXXFLAGS) $(LDFLAGS) $^ -o $@

$(TEXE): $(TOBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

clean:
	$(RM) $(OBJECTS) $(EXE)
