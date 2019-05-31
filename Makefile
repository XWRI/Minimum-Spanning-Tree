all: test_index_min_pq prim_mst

prim_mst: prim_mst.cc index_min_pq.h
	g++ -g -Wall -Werror -std=c++11 -o prim_mst prim_mst.cc

test_index_min_pq: test_index_min_pq.cc index_min_pq.h
	g++ -g -Wall -Werror -std=c++11 -o test_index_min_pq test_index_min_pq.cc -pthread -lgtest

clean:
	rm -f test_index_min_pq prim_mst
