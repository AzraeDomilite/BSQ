#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

char *mapgen(int x, int y, int p, char o, char e)
{
	int 	i;
	int 	len;
	char	*map;

	len = x * y;
	i = 0;
	map = (char *)malloc(sizeof(char) * (len + 1));
	srand(time(NULL));
	while (i < len)
	{
		if (rand() % 100 > p)
			map[i] = e;
		else
			map[i] = o;
		i++;
	}
	map[i] = '\0';
	return (map);
}

void mapwrite(char *name, char *map, int x, int y, char o, char e, char f)
{
	FILE *file = fopen(name, "w");
	if (file == NULL)
	{
		perror("Error");
		return;
	}

	fprintf(file, "%d%c%c%c\n", y, e, o, f);

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			fprintf(file, "%c", map[i * x + j]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}

int main(int ac, char **av)
{
	int		x = atoi(av[1]);
	int		y = atoi(av[2]);
	int		p = atoi(av[3]);
	char	e = av[4][0];
	char	o = av[5][0];
	char	f = av[6][0];
	char	command[1060000];

	char	*map;

	if (ac != 8)
	{
		printf("Arg error\n");
		return (0);
	}
	map = mapgen(x, y, p, o, e);
	mapwrite(av[7], map, x, y, o, e, f);

	// sprintf(command, "python test.py %d %d %c %c %c %s > solutionpy.map",y, x, e, o, f, map);
	// system(command);
	// sprintf(command, "./../bsq test.map > solutionc.map");
	// system(command);
	// sprintf(command, "./../bsq test.map > solutionc.map");
	// system(command);
	

	free(map);
	return (0);
}