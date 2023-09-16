#include "source.h"
#include <unistd.h>

void draw(int snake[][2], int fruit_x, int fruit_y, int score){
	int draw_space = 0;
	for (int i=0; i<=40; i++){
		for (int j=0; j<=50; j++){
			/* if (i == player_y && j == player_x){ */
			/* 	printf("0 "); */
			/* 	continue; */
			/* } */
			for (int k=0; k<=score; k++){
				if (snake[k][0] == j && snake[k][1] == i){
					printf("0 ");
					continue;
				}
				
				if (i == fruit_y && j == fruit_x){
					printf("@ ");
					draw_space = 0;
					continue;
				}
				printf("  ");
			}
		}
		printf("|\n");
	}

	for (int i=0; i<=50; i++){
		printf("__");
	}
	printf("|\n");
	printf("Score - %d\n", score);
	for (int i=0; i<=score; i++){
		printf("{%d, %d} - ", snake[i][0], snake[i][1]);
		printf("{%d, %d}\n", fruit_x, fruit_y);
	}
}

int main(){
	int snake[100][2] = {{0,0}};
	int speed_x = 1;
	int speed_y = 0;
	char key_pressed;
	int fruit_x = rand() % 50;
	int fruit_y = rand() % 40;
	int score = 0;

	while (1){
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
		if (!(snake[0][1] >= 0 && snake[0][1] < 40) | !(snake[0][0] >= 0 && snake[0][0] < 50)){
			printf("Game over lmaoooo\n");
			break;
		}
		
		for (int i=score; i>=0; i--){
			snake[i+1][0] = snake[i][0]; 
			snake[i+1][1] = snake[i][1];
		}

		snake[0][0] += speed_x;
		snake[0][1] += speed_y;

		if (snake[0][0] == fruit_x && snake[0][0] == fruit_y){
			score += 1;
			fruit_x = rand()%50;
			fruit_y = rand()%40;
		}

		printf("\e[1;H\e[2J"); // clear the screen
		draw(snake, fruit_x, fruit_y, score);

		usleep(300*1000);
	}
}
