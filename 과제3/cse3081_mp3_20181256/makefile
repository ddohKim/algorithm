cc = gcc
target = mp3_20181256
objects = main.o
$(target) : $(objects)
	$(cc) -o $(target) $(objects) -lm
.PHONY:clean
clean:
	rm $(target) $(objects)
