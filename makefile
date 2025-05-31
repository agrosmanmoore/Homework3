# Compilador y flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Reglas para compilar y ejecutar cada archivo
make1:
	@$(CXX) $(CXXFLAGS) ej1.cpp -o ej1
	@./ej1
	@rm ej1

make2:
	@$(CXX) $(CXXFLAGS) ej2.cpp -o ej2
	@./ej2
	@rm ej2

make3:
	@$(CXX) $(CXXFLAGS) ej3.cpp -o ej3
	@./ej3
	@rm ej3
