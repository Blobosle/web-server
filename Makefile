all:
	g++ -std=c++20 -o server main.cpp ./networking/socket.cpp
	g++ -std=c++20 -o client client.cpp ./networking/socket.cpp
