#include <termios.h> //termios
#include <unistd.h> //read
#include <time.h>
#include <stdio.h> 
#include <stdlib.h> //rand
#include <math.h>

struct result {
	int a, b, inp;
	long t;
};

int main(){

	struct termios ctrl;
	tcgetattr(STDIN_FILENO, &ctrl); //stores info  from the file descriptor (whichever that is) into ctrl
	ctrl.c_lflag &= ~ICANON; // turning off canonical mode makes input unbuffered
	tcsetattr(STDIN_FILENO, TCSANOW, &ctrl);
	//set the options in ctrl to stdin and apply NOW
	setvbuf(stdout, NULL, _IONBF, 0);

	srand(time(NULL));

	struct result results[5];

	long global_start = time(NULL);
	for (int t = 0; t < 5; t++){
		long start = time(NULL);

		int a = rand() % 20;
		int b = rand() % 20;
		int sum = a + b;
		int digits = ceil(log10(sum +1));

		ctrl.c_cc[VMIN] = (digits < 2) ? 2: digits;

		tcsetattr(STDIN_FILENO, TCSANOW, &ctrl);
		printf("\n%d + %d = ", a,b);

		char inp[5] = {0};
		read(STDIN_FILENO, &inp, digits);

		printf("%s\n",
			   (atoi(inp) == sum) ? " [ok]" : " [ko]");

		results[t].a = a; results[t].b = b; results[t].inp = atoi(inp); results[t].t = time(NULL) - start;

	}
	long total_time = time(NULL) - global_start;
	int wins = 0;
	printf("Time: %ld\n", total_time);

	for (int i =0;i<5;i++){
		char won = ((results[i].a + results[i].b) == results[i].inp);
		if (won) wins++;

		printf("[%d]: %s | ", i+1, won ? "OK" : "KO");
	}

	printf("\nResults: %d/%d\n", wins, 5);
}

