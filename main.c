// source.h contains kbhit and getch functions to get keyboard presses
#include "source.h"
#include <unistd.h>
#include <time.h>

int width = 100;
int height = 40;

// handles printing all the spaces and character for snake and fruit
void draw(int snake[][2], int fruit_x, int fruit_y, int score){
	int draw_space = 0;

	for (int i=0; i<=height; i++){
		draw_space = 1;
		for (int j=0; j<=width; j++){
			draw_space = 1;
			for (int k=0; k<=score; k++){
				// printing 0 if i and j are same as coordinates of snake
				if (snake[k][0] == j && snake[k][1] == i){
					printf("0");
					draw_space = 0;
					break;
				}

				// setting draw_space 1 if no 0's are printed
				else{ 
					draw_space = 1;
				}
				
			}

			// checking if prints @ if the coordinates matches fruits location
			if (i == fruit_y && j == fruit_x){
				printf("@");
				draw_space = 0;
				continue;
			}
			// draw_space is to prevent program from printing extra space, without it the boundaries come out weird
			if (draw_space){
				printf(" ");
			}
		}
		printf("|\n");
	}

	for (int i=0; i<=width; i++){
		printf("_");
	}
	printf("|\n");

	// printing score and x, y coordinates of snake (for debug only)
	printf("Score - %d\n", score);
	for (int i=0; i<=score; i++){
		printf("{%d, %d} - ", snake[i][0], snake[i][1]);
		printf("{%d, %d}\n", fruit_x, fruit_y);
	}
}


int main(){
	srand(time(0));
	int snake[100][2] = {{0,0}, {1,0}}; // starting coordinates of snake is (0,0)
	int speed_x = 1;
	int speed_y = 0;
	char key_pressed;
	int fruit_x = rand() % 50;
	int fruit_y = rand() % 40;
	int score = 1;
	int running = 1;

	while (running){
		if (kbhit()) {
			key_pressed = getch(); // get key defined, declared in source.h

			switch (key_pressed){
				case 'w':
					speed_y = -1;
					speed_x = 0;
					break;

				case 'a':
					speed_x = -1;
					speed_y = 0;
					break;

				case 's':
					speed_y = 1;
					speed_x = 0;
					break;

				case 'd':
					speed_x = 1;
					speed_y = 0;
					break;
				
				case 'c':
					score += 1;
					break;

				default:
					break;
			}
			
		}

		// checking for collision	
		// this only checks if the head has collided with any walls
		if (!(snake[0][1] >= 0 && snake[0][1] < height) | !(snake[0][0] >= 0 && snake[0][0] < width)){
			printf("\nGame over lmaoooo\n");
			running = 0;
		}

		for (int k=1; k<=score; k++){
			if (snake[k][0] == snake[0][0] && snake[k][1] == snake[0][1]){
				printf("\ngame over lmaoooo, loser\n");
				running = 0;
			}
		}
		
		// this just cycles value of array in forward direction
		for (int i=score; i>=0; i--){
			snake[i+1][0] = snake[i][0]; 
			snake[i+1][1] = snake[i][1];
		}

		// checking for collision with fruit
		if (snake[0][0] == fruit_x && snake[0][1] == fruit_y){
			score += 1;
			fruit_x = rand()%50;
			fruit_y = rand()%40;
		}

		// incrementing speed to x and y of snake
		snake[0][0] += speed_x;
		snake[0][1] += speed_y;


		// break out of loop before printing this frame
		if (!running){ break; }

		printf("\e[1;H\e[2J"); // clear the screen
		draw(snake, fruit_x, fruit_y, score);
		usleep(100*1000); // using constant sleep because the draw functions takes around 0.0002 second to complete which is negligible as compared to 0.001
	}
}
