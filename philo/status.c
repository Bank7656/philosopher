#include "philosopher.h"

void    get_death_flag(t_data *data)
{
    pthread_mutex_lock(&data->dead_lock);
    data->is_dead = 1;
    pthread_mutex_unlock(&data->dead_lock);
}

int check_death_flag(t_data *data)
{
    int status;

    pthread_mutex_lock(&data->dead_lock);
    status = data->is_dead;
    pthread_mutex_unlock(&data->dead_lock);
    return (status);
}

