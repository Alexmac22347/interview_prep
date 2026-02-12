output_folder = bin
CXXFLAGS = -g -Wall -Wextra -std=c++20

run : main.o arrays_and_hashing.o stack.o
	$(CXX) $(CXXFLAGS) -o bin/out $(output_folder)/main.o $(output_folder)/arrays_and_hashing.o $(output_folder)/stack.o

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(output_folder)/main.o

arrays_and_hashing.o : arrays_and_hashing/arrays_and_hashing.cpp
	$(CXX) $(CXXFLAGS) -c ./arrays_and_hashing/arrays_and_hashing.cpp -o $(output_folder)/arrays_and_hashing.o

stack.o : stack/stack.cpp
	$(CXX) $(CXXFLAGS) -c ./stack/stack.cpp -o $(output_folder)/stack.o

clean :
	rm bin/*
