all: debug/modular.exe debug/complex.exe debug/gfft.exe

debug/complex.o: src/test_complex.cpp src/FFT_C64.hpp src/FFT.hpp src/FT.hpp src/Field.hpp src/FieldComplex.hpp src/definteger.hpp
	g++ -o debug/complex.o -c src/test_complex.cpp 

debug/modular.o: src/test_mod.cpp src/FFT_Mod.hpp src/FieldMod.hpp src/ModArithm.hpp src/definteger.hpp src/FFT.hpp src/FT.hpp  src/Field.hpp 
	g++ -c -o debug/modular.o src/test_mod.cpp


debug/complex.exe: debug/complex.o
	g++ -o debug/complex.exe debug/complex.o # && rm -v debug/complex.o

debug/modular.exe: debug/modular.o
	g++ -o debug/modular.exe debug/modular.o # && rm -v debug/modular.o

debug/gfft.exe: src/GF2nArithm.hpp src/GF2nFT.hpp src/GF2nFT.cpp src/definteger.hpp src/Field.hpp src/FFT.hpp src/FT.hpp  
	g++ -o debug/gfft.exe src/GF2nFT.cpp


run-mod:
	debug/modular.exe;

run-comp:
	debug/complex.exe;

test-g2: 
	g++ -o debug/galois2n_test.exe src/Galois2n_test.cpp
	debug/galois2n_test.exe

run-gf2n:
	debug/gfft.exe


