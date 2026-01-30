output_folder = bin
CXXFLAGS = -g -Wall -Wextra -std=c++20

run : main.o arrays_and_hashing.o
	$(CXX) $(CXXFLAGS) -o bin/out $(output_folder)/main.o $(output_folder)/arrays_and_hashing.o

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(output_folder)/main.o

arrays_and_hashing.o : arrays_and_hashing/solution.cpp
	$(CXX) $(CXXFLAGS) -c ./arrays_and_hashing/solution.cpp -o $(output_folder)/arrays_and_hashing.o

clean :
	rm bin/*
