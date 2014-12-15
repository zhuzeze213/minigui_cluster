people:god.o job.o map.o people.o 
	cc -o people god.o job.o map.o people.o
god.o:god.c arg.h
	cc -c -g god.c
job.o:job.c job.h 
	cc -c -g job.c
map.o:map.c map.h
	cc -c -g map.c
people.o:people.c job.h weather.h
	cc -c -g people.c
clean:
	rm *.o people
