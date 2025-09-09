all: debug/modular.exe debug/complex.exe

debug/definteger.o: src/definteger.cpp
	g++ -c -o debug/definteger.o src/definteger.cpp


debug/complex.o: src/test_complex.cpp src/FFT_C64.hpp src/FFT.hpp src/FT.hpp src/Field.hpp src/definteger.hpp
	g++ -c -o debug/complex.o src/test_complex.cpp 


debug/modular.o: src/test_mod.cpp src/FFT_Mod.hpp src/FFT.hpp src/Field.hpp src/FieldMod.hpp src/ModArithm.hpp src/definteger.hpp
	g++ -c -o debug/modular.o src/test_mod.cpp


debug/complex.exe: debug/complex.o  debug/definteger.o
	g++  debug/complex.o debug/definteger.o -o debug/complex.exe


debug/modular.exe: debug/modular.o debug/definteger.o
	g++  debug/modular.o debug/definteger.o -o debug/modular.exe 

