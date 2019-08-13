#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>

#define N 19
#define M 40
#define SPEED 20000000



	int t,score = 0,score2 = 0;

	int vreme = 0;
	int ko;
	int x1,y1;

typedef struct pacman{
        int x,y;
        int kretanje[2];
}Pac;

Pac pac;
Pac pac2;
char slika[N][M];


int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getch();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
void crtanje()
{
	int i,j;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	int c;
	              printf("\n\n\x1B[33m");
                        printf("PLAY1 = %d        ",score);
						printf("\x1B[31m");
					  printf("PlAY2 = %d\n",score2);


			    printf("\n\n\x1B[32m");


        FILE *file;
        file = fopen("nivo1.txt", "r");
	for(i = 0; i < N; i++) //ivice
	{

        	for(j = 0; j < M; j++)
                {
		/*	if(i  == 0  || (j % 4 == 0 && i % 4 != 0) || i == N-1 || (j == M-1 && i != 8))
                        	slika[i][j] = '#';

			else
				slika[i][j] = ' ';*/

			if (file) {
    				if((c = getc(file)) != EOF)
				{
					if(c == '\n')
					c = getc(file);
					if(c == '1')
					c = ' ';
        				slika[i][j] = c;
				}
			}
			if(j == pac2.x && i == pac2.y)
			{
				printf("\x1B[33m");
				slika[i][j] = 'C';
			}
			if(j == pac.x && i == pac.y)
			{
				printf("\x1B[31m");
				slika[i][j] = 'C';
			}
			if(j == x1 && i == y1 && t == 0)
			{
				printf("\x1B[0m");

				slika[i][j] ='T';
			}
			printf("%c",slika[i][j]);
				printf("\x1B[32m");

		}
		printf("\n");
	}
	fclose(file);

	return;
}


int main()
{

	pac.x = M - 2;  // pocetne koordinate
	pac.y = N - 2;
	pac.kretanje[0] = 0;
	pac.kretanje[1] = 0;
	        pac2.x = 1;  // pocetne koordinate
        pac2.y = 1;
        pac2.kretanje[0] = 0;
        pac2.kretanje[1] = 0;
	ko = 3;
	x1 = M/2 ;
	y1 = N/2;
	t = 0;
	vreme = 0;
	while(1)
	{
		crtanje(slika);

		if ( kbhit() )
        	{
            		char ch = getch();
            		if(ch == 'a'){
                		pac.kretanje[0] = -1;
				pac.kretanje[1] = 0;
            		}
            		if(ch == 'd') {
                		pac.kretanje[0] = 1;
                                pac.kretanje[1] = 0;
            		}
            		if(ch == 's') {
                		pac.kretanje[0] = 0;
                                pac.kretanje[1] = 1;
            		}
			if(ch == 'w'){
				pac.kretanje[0] = 0;
                                pac.kretanje[1] = -1;
				
								}

            		if(ch == 'j'){
                		pac2.kretanje[0] = -1;
				pac2.kretanje[1] = 0;
            		}
            		if(ch == 'l') {
                		pac2.kretanje[0] = 1;
                                pac2.kretanje[1] = 0;
            		}
            		if(ch == 'k') {
                		pac2.kretanje[0] = 0;
                                pac2.kretanje[1] = 1;
            		}
			if(ch == 'i'){
				pac2.kretanje[0] = 0;
                                pac2.kretanje[1] = -1;

						}

       }
		int k=0;
		if(slika[pac.y + pac.kretanje[1]][pac.x + pac.kretanje[0]] == '#'){
			pac.kretanje[0] = 0;
			pac.kretanje[1] = 0;
		}
		if(slika[pac2.y + pac2.kretanje[1]][pac2.x + pac2.kretanje[0]] == '#'){
			pac2.kretanje[0] = 0;
			pac2.kretanje[1] = 0;
		}
		/*if(pac.y == 8 && pac.x == M-1)
		{
			pac.x = 0;
			pac.kretanje[0] = 1;
			k++;
		}
                if(pac.y == 8 && pac.x == 0 && k == 0)
                {
                        pac.y = 8;
                        pac.x = M - 1;
                        pac.kretanje[0] = -1;
                }
*/
		pac.x+=pac.kretanje[0];
                pac.y+=pac.kretanje[1];
				pac2.x+=pac2.kretanje[0];
                pac2.y+=pac2.kretanje[1];

				int j = 0;

                if(pac.y == 8 && pac.x == M-1)
                {
                        pac.x = 0;
                        pac.kretanje[0] = 1;
                        k++;
                }
                if(pac2.y == 8 && pac2.x == M-1)
                {
                        pac2.x = 0;
                        pac2.kretanje[0] = 1;
                        j++;
                }
                if(pac.y == 8 && pac.x == 0 && k == 0)
                {
                        pac.y = 8;
                        pac.x = M - 1;
                        pac.kretanje[0] = -1;
                }
                if(pac2.y == 8 && pac2.x == 0 && j == 0)
                {
                        pac2.y = 8;
                        pac2.x = M - 1;
                        pac2.kretanje[0] = -1;
                }
		if(pac.x == x1 && pac.y == y1)
		{
			ko = 0;
			t = 1;
		}
		if(pac2.x == x1 && pac2.y == y1)
		{
			ko = 1;
			t = 1;
		}

		if(t == 1)
			{
				vreme++;
			}
			if(vreme%100 == 0)
			{
				t = 0;
			}


		if(pac.x == pac2.x && pac.y == pac2.y)
		{
			if(ko == 1)
			{
				score++;
			}
			else if(ko == 0)
			{
				score2++;
			}
		}
                unsigned a = SPEED;
                while(a)a--;

	}


}
