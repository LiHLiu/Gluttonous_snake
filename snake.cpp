/*
文件：贪吃蛇
内容：由墙、蛇身、蛇头、食物等元素组成，通过操控蛇的方向吃到食物，撞到墙或吃到身体失败
方案：主函数通过循环清屏和读取按键操作实现画面输出
*/
#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>

#define longth 20
#define extent 15
#define difficult 0.1

/*
0 1 2 3 4 5 6 7 8 9 ...
1
2
3
4
5
...
*/
int esc_flag = 1;
int map[longth][extent] = { 0 };		//0空  1墙  2身体  3头  4食物
int direction = 2;						//1上  2右  3下  4左
int snake[longth*extent][3];			//0:类型  1:x坐标  2:y坐标
int snake_long = 3;						//蛇长
int food_x , food_y;
int score = 0;

void esc()
{
	esc_flag = 0;
}
int is_wall(int x, int y)
{
	if (y == 0 || y == extent-1)
		return 1;
	else
	{
		if (x == 0 || x == longth-1)
			return 1;
		else
			return 0;
	}
}
void build_wall()
{
	for (int i = 0; i <= extent - 1; i++)
	{
		for (int j = 0; j <= longth - 1; j++)
		{
			if (is_wall(j, i))
			{
				map[j][i] = 1;
			}
		}
	}
}
int get_press(int a) {

	if (GetKeyState(a) < 0)
		return 1;
	else
		return 0;
}
void fill()
{
	for (int i = 1; i <= extent - 2; i++)
	{
		for (int j = 1; j <= longth - 2; j++)
		{
			for (int k = 0; k <= snake_long - 1; k++)
			{
				if (snake[k][0] == 2 &&
					snake[k][1] == j &&
					snake[k][2] == i)
				{
					map[j][i] = 2;
					break;
				}
				else if (snake[k][0] == 3 &&
					snake[k][1] == j &&
					snake[k][2] == i)
				{
					map[j][i] = 3;
					break;
				}
				else
				{
					map[j][i] = 0;
				}
			}
			if (food_x == j && food_y == i)		//食物判断
			{
				map[j][i] = 4;
			}
		}
	}
}
int is_snake(int x,int y)
{
	for (int i = 0; i <= snake_long - 1; i++)
	{
		if ((snake[i][0] == 2 ||
			snake[i][0] == 3) && 
			snake[i][1] == x && 
			snake[i][2] == y)
		{
			return 1;
		}
	}
	return 0;
}
void summon_food()
{
	food_x = rand() % (longth - 2) + 1;
	food_y = rand() % (extent - 2) + 1;
	while (is_snake(food_x, food_y))
	{
		food_x = rand() % (longth - 2) + 1;
		food_y = rand() % (extent - 2) + 1;
	}
}
void summon_snake()
{
	snake[0][0] = 3;
	snake[0][1] = longth / 2;
	snake[0][2] = extent / 2;
	snake[1][0] = 2;
	snake[1][1] = longth / 2-1;
	snake[1][2] = extent / 2;
	snake[2][0] = 2;
	snake[2][1] = longth / 2-2;
	snake[2][2] = extent / 2;
	fill();
}
void has_eat()
{
	if (snake[0][1] == food_x &&
		snake[0][2] - 1 == food_y &&
		direction == 1)
	{
		snake[snake_long][0] = 2;
		snake[snake_long][1] = snake[snake_long - 1][1];
		snake[snake_long][2] = snake[snake_long - 1][2];
		snake_long++;
		summon_food();
		score++;
	}
	else if (snake[0][1] + 1 == food_x &&
			snake[0][2] == food_y &&
			direction == 2)
	{
		snake[snake_long][0] = 2;
		snake[snake_long][1] = snake[snake_long - 1][1];
		snake[snake_long][2] = snake[snake_long - 1][2];
		snake_long++;
		summon_food();
		score++;
	}
	else if (snake[0][1] == food_x &&
			snake[0][2] + 1 == food_y &&
			direction == 3)
	{
		snake[snake_long][0] = 2;
		snake[snake_long][1] = snake[snake_long - 1][1];
		snake[snake_long][2] = snake[snake_long - 1][2];
		snake_long++;
		summon_food();
		score++;
	}
	else if (snake[0][1] - 1 == food_x &&
			snake[0][2] == food_y &&
			direction == 4)
	{
		snake[snake_long][0] = 2;
		snake[snake_long][1] = snake[snake_long - 1][1];
		snake[snake_long][2] = snake[snake_long - 1][2];
		snake_long++;
		summon_food();
		score++;
	}
}
void defill()
{
	for (int i = 1; i <= extent - 2; i++)
	{
		for (int j = 1; j <= longth - 2; j++)
		{
			map[j][i] = 0;
		}
	}	
}
void output()
{
	system("cls");
	for(int i = 0;i <= extent - 1;i++)
	{
		for (int j = 0; j <= longth - 1; j++)
		{
			if (is_wall(j,i))
			{
				printf("墙");
			}
			else
			{
				if (map[j][i] == 0)
				{
					printf("  ");
				}
				else if (map[j][i] == 2)
				{
					printf("体");
				}
				else if (map[j][i] == 3 )//|| map[j][i] == 4)
				{
					printf("头");
				}
				else if (map[j][i] == 4)
				{
					printf("食");
				}
			}
			if (j == longth - 1)
			{
				printf("\n");
			}
		}
	}
}
void t_up()
{
	if ((direction == 2 ||
		direction == 4) &&
		snake[0][2] - 1 != snake[1][2])
	{
		direction = 1;
	}
}	   
void t_down()
{
	if ((direction == 2 || 
		direction == 4) &&
		snake[0][2] + 1 != snake[1][2])
	{
		direction = 3;
	}
}
void t_left()
{
	if ((direction == 1 || 
		direction == 3) &&
		snake[0][1] - 1 != snake[1][1])
	{
		direction = 4;
	}
}
void t_right()
{
	if ((direction == 1 || 
		direction == 3) &&
		snake[0][1] + 1 != snake[1][1])
	{
		direction = 2;
	}
}
void is_dead()
{
	if (map[snake[0][1]][snake[0][2]] == 1 || 
		map[snake[0][1]][snake[0][2]] == 2)
	{
		esc();
	}
}
void out_press()
{
	if (get_press('W'))
	{
		t_up();
	}
	if (get_press('A'))
	{
		t_left();
	}
	if (get_press('S'))
	{
		t_down();
	}
	if (get_press('D'))
	{
		t_right();
	}
	if (get_press(27))
	{
		esc();
	}
}
void move()
{
	has_eat();
	if (direction == 1)
	{
		for (int i = 1; i <= snake_long - 1; i++)
		{
			snake[snake_long - i][1] = snake[snake_long - i - 1][1];
			snake[snake_long - i][2] = snake[snake_long - i - 1][2];
		}
		snake[0][2] -= 1;
	}
	if (direction == 2)
	{
		for (int i = 1; i <= snake_long - 1; i++)
		{
			snake[snake_long - i][1] = snake[snake_long - i - 1][1];
			snake[snake_long - i][2] = snake[snake_long - i - 1][2];
		}
		snake[0][1] += 1;
	}
	if (direction == 3)
	{
		for (int i = 1; i <= snake_long - 1; i++)
		{
			snake[snake_long - i][1] = snake[snake_long - i - 1][1];
			snake[snake_long - i][2] = snake[snake_long - i - 1][2];
		}
		snake[0][2] += 1;
	}
	if (direction == 4)
	{
		for (int i = 1; i <= snake_long - 1; i++)
		{
			snake[snake_long - i][1] = snake[snake_long - i - 1][1];
			snake[snake_long - i][2] = snake[snake_long - i - 1][2];
		}
		snake[0][1] -= 1;
	}
	is_dead();						
	defill();
	fill();
	output();
}
int main()
{
	srand((unsigned int)(time(NULL)));
	double basic_time = difficult;
	double time_sum = 0;
	build_wall();
	summon_snake();
	summon_food();
	while (esc_flag)
	{
		clock_t start, end;
		start = clock();

		out_press();

		end = clock();
		double diff_sec = ((double)(end - start) / CLOCKS_PER_SEC);
		time_sum += diff_sec;
		if (time_sum >= basic_time)
		{
			move();
		time_sum = 0;
		}
	}
	printf("you dead!\n");
	printf("score:%d\n\n\n\n\n\n\n\n\n", score);
	system("pause");
	return 0;
}
