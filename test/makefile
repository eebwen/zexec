
zexec: test_zexec.o ../zexec.o ../zlog/zlog.o
	g++ -g -o $@ $^ 

execvp: test_execvp.cpp
	g++ -o $@ $^ -g
	

hello: hello.c
	g++ -o $@ $^ -g
	
co:
	cp /mnt/zexec/* .. -fa
	touch *.cpp *.h *.c
	
