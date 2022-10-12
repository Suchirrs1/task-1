cl: task.c
	gcc -o task task.c

run: cl
	./task

clean:
	rm -f task
