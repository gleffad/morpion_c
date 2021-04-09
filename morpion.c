#include <stdio.h>
#include <stdlib.h>

//test l'existance d'une combinaison gagnante.
int		ft_check_win(char **grid, char p, int size, int align)
{
	int		i;
	int		j;
	int 	tmp1;
	int		tmp2;
	int		cpt;

	i = -1;
	j = -1;
	while (++i < size)
	{
		while (++j < size)
		{
			tmp1 = i;
			tmp2 = j;
			cpt = 0;
			//droite
			while (tmp1 < size && tmp1 >= 0 && tmp2 < size
					&& tmp2 >= 0 && grid[tmp1][tmp2] == p)
			{
				tmp2++;
				cpt++;
				if (cpt == align)
				{
					printf("\nPlayer (%c) win the game !\n", p);
					return (1);
				}
			}
			tmp1 = i;
			tmp2 = j;
			cpt = 0;
			//bas
			while (tmp1 < size && tmp1 >= 0 && tmp2 < size
					&& tmp2 >= 0 && grid[tmp1][tmp2] == p)
			{
				tmp1++;
				cpt++;
				if (cpt == align)
				{
					printf("\nPlayer (%c) win the game !\n", p);
					return (1);
				}
			}
			tmp1 = i;
			tmp2 = j;
			cpt = 0;
			//diagonale bas_gauche
			while (tmp1 < size && tmp1 >= 0 && tmp2 < size
					&& tmp2 >= 0 && grid[tmp1][tmp2] == p)
			{
				tmp1++;
				tmp2--;
				cpt++;
				if (cpt == align)
				{
					printf("\nPlayer (%c) win the game !\n", p);
					return (1);
				}
			}
			tmp1 = i;
			tmp2 = j;
			cpt = 0;
			//diagonale bas_droit
			while (tmp1 < size && tmp1 >= 0 && tmp2 < size
					&& tmp2 >= 0 && grid[tmp1][tmp2] == p)
			{
				tmp1++;
				tmp2++;
				cpt++;
				if (cpt == align)
				{
					printf("\nPlayer (%c) win the game !\n", p);
					return (1);
				}
			}
		}
		j = -1;
	}
	return (0);
}

//affichage de la grille
void	ft_print_grid(char **grid, int size)
{
	int	i;
	int j;

	i = -1;
	j = -1;
	while (++i < size)
	{
		while (++j < size)
		{
			printf(" %c", grid[i][j]);
		}
		printf("\n");
		j = -1;
	}
}

//initialisation de la grille avec des caracteres '.'.
void	ft_init(char **grid, int size)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < size)
	{
		while (++j < size)
			grid[i][j] = '.';
		j = -1;
	}
}

//saisi du choix choix du joueur.
void	ft_get_choice(int *a, int *b, char player, int size)
{
	char	c;
	while (!(*a < size && *a >= 0 && *b < size && *b >= 0))
	{
		printf("Joueur %c, a vous de jouer ! (format : [X,X])\n", player);
		scanf("%i,%i", a, b);
		while((c = getchar()) != '\n' && c != EOF);
	}
}

//insertion du choix du joueur
void	ft_insert_choice(char player, char **grid, int size)
{
	int 	i;
	int		j;

	i = -1;
	j = -1;
	while (1)
	{
		ft_get_choice(&i, &j, player, size);
		if (grid[i][j] != '.')
		{
			printf("\nErreur : case deja pleine ! Jouez une autre case ;)\n");
			i = -1;
			j = -1;
		}
		else
		{
			grid[i][j] = player;
			break;
		}
	}
}

//verification de grille pleine.
int		ft_check_full(char **grid, int size)
{
	int	i;
	int j;

	i = -1;
	j = -1;
	while(++i < size)
	{
		while(++j < size)
			if(grid[i][j] == '.')
				return (0);
		j = -1;
	}
	return (1);
}

int		main(int argc, char** argv)
{
	int		cpt;
	int		i;
	char	player;
	int		size;
	char	**grille;
	int		align;

	cpt = 0;
	i = -1;
	if (argc > 3 || argc <= 2 || atoi(argv[1]) < 3 || atoi(argv[1]) > 33
				|| atoi(argv[2]) <= 1 || atoi(argv[2]) > 5
						|| atoi(argv[1]) < atoi(argv[2]))
	{
		printf("\nMerci de saisir deux arguments correctes [[3 > taille > 33] [1 < alignement < 5]] : alignement <= taille\n\n");
		return (1);
	}
	//recuperation de la dimension
	size = atoi(argv[1]);
	//recuperation de l'alignement gagnant
	align = atoi(argv[2]);
	//allocation memoire de taille size*size
	if (!(grille = (char **)malloc(size*sizeof(char *))))
	{
		printf("\nErreur allocation memoire.\n");
		return (1); 
	}
	while (++i < size)
		if (!(grille[i] = (char *)malloc(size*sizeof(char))))
		{
			printf("\nErreur allocation memoire.\n");
			return (1); 
		}
	//initiation de la grille et affichage
	ft_init(grille, size);
	ft_print_grid(grille, size);
	//tour a tour
	while (!ft_check_win(grille, 'X', size, align) 
			&& !ft_check_win(grille, 'O', size, align)
			&& !ft_check_full(grille, size))
	{
		cpt++;
		if (cpt % 2 != 0)
			player = 'X';
		else
			player = 'O';
		ft_insert_choice(player, grille, size);
		ft_print_grid(grille, size);
	}
	if (ft_check_full(grille, size))
		printf("\nGrille pleine.\n");
	return (0);
}
