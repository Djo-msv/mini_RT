#include "miniRT.h"

int	size_of_float(float size)
{
	int	i = 0;

	while (size / 10 >= 10)
	{
		size = size / 10;
		i++;
	}
	return (i);
}

void	print_nb_fps(float fps)
{
	if (fps >= 9999.99)
		printf("│???????│\n");
	else if (fps < 10.0f)
		printf("│  %s%.2f%s │\n", P_RED, fps, P_GREEN);
	else if (fps < 30.0f)
		printf("│ %s%.2f%s │\n", P_YELLOW, fps, P_GREEN);
	else
	{
		int	i = 0;
		int size = size_of_float(fps) + 3;
		ft_putstr("│");
		while (i++ != 3 - ((size + 1) >> 1))
			ft_putchar(' ');
		printf("%.2f", fps);
		fflush(stdout);
		i += size;
		while (i++ != 6)
			ft_putchar(' ');
		ft_putstr("│\n");
	}
}

void	print_info(t_print_info *info)
{
	if (!info->first_display)
		printf("\033[11A");
	else
		info->first_display = false;
	printf("%s%s┌──FPS──┐\n", P_GREEN, P_BOLD);
	print_nb_fps(info->fps);
	printf("└───────┘%s\n\n", P_NOC);
	printf("display : %d × %d\n", info->x, info->y);
	printf("resolution : %d\n", info->resolution);
	if (info->aa)
		printf("AA : %strue%s\n\n", P_GREEN, P_NOC);
	else
		printf("AA : %sfalse%s\n\n", P_RED, P_NOC);


	printf("%s%s╔══════CAMERA══════╗\n", P_TEAL, P_BOLD);
//	print_cam_info
	printf("╚══════════════════╝%s\n\n", P_NOC);
//	if obj select, print obj info
}
