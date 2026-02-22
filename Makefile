output_folder = bin
CXXFLAGS = -g -Wall -O0 -Wextra -std=c++20

run : main.o arrays_and_hashing.o stack.o minstack.o two_pointers.o
	$(CXX) $(CXXFLAGS) -o bin/out $(output_folder)/main.o $(output_folder)/arrays_and_hashing.o $(output_folder)/stack.o $(output_folder)/minstack.o $(output_folder)/two_pointers.o

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(output_folder)/main.o

arrays_and_hashing.o : arrays_and_hashing/arrays_and_hashing.cpp
	$(CXX) $(CXXFLAGS) -c ./arrays_and_hashing/arrays_and_hashing.cpp -o $(output_folder)/arrays_and_hashing.o

stack.o : stack/stack.cpp
	$(CXX) $(CXXFLAGS) -c ./stack/stack.cpp -o $(output_folder)/stack.o

minstack.o : stack/minstack.cpp
	$(CXX) $(CXXFLAGS) -c ./stack/minstack.cpp -o $(output_folder)/minstack.o

two_pointers.o : two_pointers/two_pointers.cpp
	$(CXX) $(CXXFLAGS) -c ./two_pointers/two_pointers.cpp -o $(output_folder)/two_pointers.o

clean :
	rm bin/*
