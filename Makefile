all: debug/modular.exe debug/complex.exe

debug/complex.o: src/test_complex.cpp src/FFT_C64.hpp src/FFT.hpp src/FT.hpp src/Field.hpp src/FieldComplex.hpp src/definteger.hpp
	g++ -o debug/complex.o -c src/test_complex.cpp 

debug/modular.o: src/test_mod.cpp src/FFT_Mod.hpp src/FFT.hpp src/FT.hpp  src/Field.hpp src/FieldMod.hpp src/ModArithm.hpp src/definteger.hpp
	g++ -c -o debug/modular.o src/test_mod.cpp


debug/complex.exe: debug/complex.o
	g++ -o debug/complex.exe debug/complex.o # && rm -v debug/complex.o

debug/modular.exe: debug/modular.o
	g++ -o debug/modular.exe debug/modular.o # && rm -v debug/modular.o

