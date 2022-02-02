LD=g++
CXX=g++
CXXFLAGS=-std=c++17 -Wall -pedantic

all: compile doc

compile: calculator

run: compile
	./app

doc: Doxyfile src/Calculator/CCalculator.h src/Calculator/CApplication.h src/Expression/CExpression.h src/MathObject/CMathObject.h \
 src/MathObject/CNumber.h src/Operator/COperator.h src/Operator/CAdd.h src/Operator/CBracket.h src/Operator/CDivide.h \
 src/Operator/CMod.h src/Operator/CMultiply.h src/Operator/CSubtract.h src/Test/CTest.h src/Variable/CVariable.h
	mkdir doc
	doxygen Doxyfile

calculator: main.o CNumber.o CVariable.o CMathObject.o COperator.o CAdd.o CBracket.o CDivide.o CMod.o CMultiply.o \
 CSubtract.o CExpression.o CCalculator.o CApplication.o CTest.o
	$(LD) -o app $^

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: src/Calculator/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: src/Expression/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: src/MathObject/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: src/Operator/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: src/Test/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: src/Variable/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf *.o doc app

deps:
	> Makefile.d
	$(CXX) -MM src/*cpp >> Makefile.d
	$(CXX) -MM src/Calculator/*cpp >> Makefile.d
	$(CXX) -MM src/Expression/*cpp >> Makefile.d
	$(CXX) -MM src/MathObject/*cpp >> Makefile.d
	$(CXX) -MM src/Operator/*cpp >> Makefile.d
	$(CXX) -MM src/Test/*cpp >> Makefile.d
	$(CXX) -MM src/Variable/*cpp >> Makefile.d

-include Makefile.d


