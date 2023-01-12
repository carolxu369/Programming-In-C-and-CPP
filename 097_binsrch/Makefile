CPPFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
test_bsearch: test_bsearch.o search.o
	g++ -o test_bsearch test_bsearch.o search.o
test_bsearch.o: test_bsearch.cpp
	g++ $(CPPFLAGS) -c test_bsearch.cpp
search.o: search.cpp function.h
	g++ $(CPPFLAGS) -c search.cpp
.PHONY: clean
clean:
	rm -f *.o *~ test_bsearch
