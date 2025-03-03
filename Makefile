#Define the C compiler to use
CC=gcc

#Define any compile -time flag
CFLAGS=-Wall -g #-Wall: Enable all warning messages, -g: Add debugging information

#Define the target executable name
TARGETS=RR SJF

#'all' is the default target. It's customary to have it as the first target.
#This target will be executed when you just type 'make' in the terminal
all: $(TARGETS)
#Need to seperate two files so that we can check the error of each files
# Rule to compile SJF Scheduling Program
SJF: SJF.c
	@echo "Compiling SJF.c"
	$(CC) $(CFLAGS) -o $@ $<
	@echo "Compilation successful!"

# Rule to compile RR (Round Robin) Scheduling Program
RR: RR.c
	@echo "Compiling RR.c"
	$(CC) $(CFLAGS) -o $@ $<
	@echo "Compilation successful! "

# Clean up generated files
clean:
	@echo "Cleaning up"
	rm -f $(TARGETS)
	@echo "Cleanup complete!"
