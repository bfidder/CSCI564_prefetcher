CC = g++
CCFLAGS = -g

cacheSim: CPU.o cache.o main.o memQueue.o prefetcher.o
	${CC} ${CCFLAGS} CPU.o cache.o main.o memQueue.o prefetcher.o -o cacheSim

CPU.o: CPU.C CPU.h mem-sim.h
	${CC} ${CCFLAGS} -c CPU.C

cache.o: cache.C cache.h
	${CC} ${CCFLAGS} -c cache.C

main.o: main.C mem-sim.h CPU.h cache.h memQueue.h prefetcher.h
	${CC} ${CCFLAGS} -c main.C

memQueue.o: memQueue.C memQueue.h mem-sim.h cache.h
	${CC} ${CCFLAGS} -c memQueue.C

prefetcher.o: prefetcher.C prefetcher.h mem-sim.h
	${CC} ${CCFLAGS} -c prefetcher.C

test: CPU.o cache.o main.o memQueue.o prefetcher.o
	${CC} ${CCFLAGS} CPU.o cache.o main.o memQueue.o prefetcher.o -o cacheSim
	rm -f requests1.txt requests2.txt requests3.txt requests4.txt requests5.txt all.traces.out
	./cacheSim grep.trace > requests1.txt
	./cacheSim g++.trace > requests2.txt
	./cacheSim ls.trace > requests3.txt
	./cacheSim plamap.trace > requests4.txt
	./cacheSim testgen.trace > requests5.txt
	paste grep.trace.out g++.trace.out ls.trace.out plamap.trace.out testgen.trace.out > all.traces.out

clean:
	rm -f *.o cacheSim
