#include "philosopher.h"

static int check_args_digit(char **argv);

int parse_args(t_data *data, char **argv)
{
    if (check_args_digit(argv + 1))
        return (EXIT_FAILURE);
    data->num_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        data->max_meals = ft_atoi(argv[5]);
    else
        data->max_meals = -1;
    data->is_dead = 0;
    return (EXIT_SUCCESS);
}

static int check_args_digit(char **argv)
{
    int i;
    int j;

    i = 0;
    while (argv[i] != NULL)
    {
        j = 0;
        while (argv[i][j] != '\0')
        {
            if (!ft_isdigit(argv[i][j]))
                return (EXIT_FAILURE);
            j++;
        }
        i++;
    }
    return (EXIT_SUCCESS);
}
