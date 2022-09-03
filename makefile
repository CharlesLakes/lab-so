compile1: main1.c
	gcc main1.c -o main1.o
compile2: main2.c 
	gcc main2.c -o main2.o
run1: compile1
	./main1.o
run2: compile2
	./main2.o
dev1: compile1 run1
dev2: compile2 run2
RunAndCompile: dev1 dev2
deleteFolder:
	rm -r 2019 2020 2021