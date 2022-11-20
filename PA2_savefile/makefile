all:
	gcc -o closest_pair closest_pair.c kernel.c -lm -O2

test:
	
	echo '10000' | ./closest_pair daq 3d
	echo '10000' | ./closest_pair n 3d
	echo '10000' | ./closest_pair daq 3d
	echo '10000' | ./closest_pair n 3d
	echo '10000' | ./closest_pair daq 3d
	echo '10000' | ./closest_pair n 3d

