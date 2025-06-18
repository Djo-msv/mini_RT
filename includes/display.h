#ifndef DISPLAY_H
# define DISPLAY_H

void	handle_low_resolution(t_data *data, int x, int y, int resolution);
void	display_screen(t_data *data);
void	sampling(t_fcolor *o_pixel, t_fcolor n_pixel, double coef_new_p, double coef_old_p);

#endif
