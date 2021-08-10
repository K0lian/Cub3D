#ifndef CUBE3D_H
# define CUBE3D_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>
# include <limits.h>
# include "colors.h"
# define UP	13
# define DOWN	1
# define LEFT	0
# define RIGHT	2
# define LEFT2	123
# define RIGHT2	124

# define MAXLEN	1000
# define TEXWIGTH	64
# define TEXHEIGHT	64

typedef struct s_vars {
	void				*mlx;
	void				*win;
}	t_vars;

typedef struct s_tex {
	int					height;
	int					width;
	void				*mlx;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}	t_tex;

typedef struct s_wall {
	t_tex				tex1;
	t_tex				tex2;
	t_tex				tex3;
	t_tex				tex4;
	t_tex				sprit;
}	t_wall;

typedef struct s_prite
{
	double				x;
	double				y;
	double				distance;
}	t_sprite;

typedef struct s_img
{
	void				*ptr;
	void				*addr;
	unsigned			*data;
	unsigned long long	size_x;
	unsigned long long	size_y;
	double				distance;
	int					line_length;
}	t_img;

typedef struct s_bmp
{
	int					fd;
	int					size;
	int					h2;
	int					clr;
	int					offset;
	unsigned char		*head;
}	t_bmp;

typedef struct s_object
{
	t_img				*sprite;
	double				posX;
	double				posY;
	unsigned int		sizeX;
	unsigned int		sizeY;
	double				distance;
}	t_object;

typedef struct s_data {
	void				*mlx;
	void				*win;
	t_img				img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	unsigned int		color_ceil;
	unsigned int		color_floor;
	t_object			*objects;
	struct s_map
	{
		unsigned int	size_x;
		unsigned int	size_y;
		char			*karta[MAXLEN];
	}	map;
	struct s_column
	{
		double			distance;
		unsigned int	height;
		double			texture_pos;
		char			dir;
	}	**colum;
	int					side;
	double				posX;
	double				posY;
	double				dirX;
	double				dirY;
	double				planeX;
	double				planeY;
	double				moveSpeed;
	double				rotSpeed;
	double				angle;
	double				col_step;
	double				col_scale;
	double				col_center;
	double				fov;
	double				ZBuffer[10000];
	int					screen;
	int					numsprites;
	int					x;
	int					y;
	int					color;
	int					drawStart;
	int					drawEnd;
	int					drawStartY;
	int					drawEndY;
	int					drawStartX;
	int					drawEndX;
	double				cameraX;
	double				rayDirX;
	double				rayDirY;
	int					mapX;
	int					mapY;
	double				sideDistX;
	double				sideDistY;
	double				deltaDistX;
	double				deltaDistY;
	int					stepX;
	int					stepY;
	int					texX;
	int					lineHeight;
	double				wallX;
	double				step;
	double				texPos;
	double				spriteX;
	double				spriteY;
	double				invDet;
	double				transformX;
	double				transformY;
	int					spriteScreenX;
	int					spriteHeight;
	int					spriteWidth;
	t_bmp				bmp;
	t_img				texture[5];
	t_sprite			sprite[2048];
	t_vars				*vars;
	t_wall				*wall;
	int					n_pvrt;
}	t_data;

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		verLine(int x, int drawStart, int drawEnd, t_data *data);
void		f_left(double oldDirX, double oldPlaneX, t_data *data);
void		f_rite(double oldDirX, double oldPlaneX, t_data *data);
void		move_r_l(int keycode, t_data *data);
void		move_horizontal(int keycode, t_data *data);
void		move_u_d_l_r(int keycode, t_data *data);
void		sort_tex(t_data *data, int sprnum);
void		rasschet_raydir(t_data *data);
void		rasschet_hit(t_data *data);
void		rasschet_start(int x, t_data *data);
void		rasschet_draw(double k, t_data *data);
void		prorisovka_sten(int x, double k, t_data *data);
void		draw_walls(int x, t_data *data);
void		rasschet_spr(int i, t_data *data);
void		ft_risyem(int texX, int color, int sprX, t_data *data);
void		draw_sprites(int color, t_data *data);
void		podgotovka(t_data *data, int ac, char **av);
void		hgfd(int screenshot, t_data *data);
int			q_exit(t_data *data);
int			move(int keycode, t_data *data);
int			jizn(t_data *data);
int			main(int ac, char **av);

size_t		ft_strlen(const char *s);
int			ft_chek_simb(const char *s, int c);
int			ft_isdigit(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_say(int return_value, char *message, t_data *data);
int			ft_parser(int as, char **av, t_data *data);
int			ytre(unsigned int ln_len, char *len, t_data *data);
int			smol_chek(int status, char **len, t_data *data, int i);
int			rewd(int as, char **av, int id, t_data *data);
void		chek_up_krt(int i, t_data *data);
void		sttr(t_sprite tmp, t_data *data, int sprnum);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strchr(const char *s, int c);
void		term_put(char *s, int fd);
void		free_say(t_data *data);
void		game_init(t_data *data);
void		player_turn(char **map, t_data *data, int x, int y);
void		chek_map(char **map, int x, int y, t_data *data);
void		proc_set_map(t_data *data);
void		setle_map(t_data *data);
char		*my_atoi(const char *src_str, unsigned long long *dsi,
				unsigned long max, t_data *data);
void		res_set(const char *res_str, t_img *img, t_data *data);
void		colors_set(unsigned int *trg, const char *scolor, t_data *data);
void		text_form_set(char *str, t_img *texture, t_data *data);
void		text_set(char *str, t_data *data);
void		validate_set(t_data *data);
void		ft_parse_map(int id, char *len, t_data *data);
void		ft_screne_parse(int id, char **len, t_data *data);
void		nbevcf(t_object *obj, t_data *data);
void		yntf(t_data *data);
char		*ft_strdup(const char *s1);

const char	*colors_set1(unsigned int *trg, const char *scolor,
				unsigned long long *Rd, t_data *data);
char		*ft_strnstr(const char *str, const char *ne, size_t len);
void		huyach_skrin(t_data *data, char *av);

int			ft_strchrr(char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strcpy(char *dst, char *src);
char		*proverka(char **ostatok, char **line);
int			ret(int p, char *tre);
int			get_next_line(int fd, char **line, t_data *data);

#endif