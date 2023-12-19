# Compiler
CC = g++
# Compiler flags
# CFLAGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused

# Source files
SRCS = main.cpp Rides.cpp Ride.cpp Passengers.cpp Passenger.cpp Drivers.cpp Driver.cpp InputHelper.cpp EconomyDriver.cpp BasicDriver.cpp GroupDriver.cpp LuxuryDriver.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Binary/executable name
TARGET = a.out

# Main target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to compile each .cpp file into a .o file
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets to prevent conflicts with filenames
.PHONY: all clean