all:
	g++ -o pmc -DPEPMC_LINUX_SETAFFINITY -L. -lhoard *.cpp -O3 -lboost_thread -lpthread -g -std=c++0x

debug:
	g++ -o pmc *.cpp -g -lboost_thread -lpthread -std=c++0x

nohoard:
	g++ -o pmc -DPEPMC_LINUX_SETAFFINITY *.cpp -O3 -lboost_thread -lpthread -g -std=c++0x
