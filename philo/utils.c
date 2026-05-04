#include "philosopher.h"

long long get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}