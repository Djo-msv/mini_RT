NAME	:= miniRT_bonus
MAKEFLAGS += --no-print-directory

#==============================COMPIL===========================#

CC = clang
CFLAGS = -Wall -Wextra -Werror

MAX_RES_W ?= 1920
MAX_RES_H ?= 1080
NB_THREAD ?= 32
SIZE_CHUNK ?= 4096

CFLAGS += -DMAX_RES_W=$(MAX_RES_W)
CFLAGS += -DMAX_RES_H=$(MAX_RES_H)
CFLAGS += -DNB_THREAD=$(NB_THREAD)
CFLAGS += -DSIZE_CHUNK=$(SIZE_CHUNK)

ifeq ($(DEBUG), 1)
	CFLAGS += -g -pthread
endif

ifeq ($(MEGA_PERF), 1)
	CFLAGS += -O3 -mavx2 -mfma -march=native -mtune=native -funroll-loops -fvectorize -ffp-contract=fast  -freciprocal-math -ffast-math -fstrict-aliasing  -fomit-frame-pointer -flto=full -mprefer-vector-width=256
endif

#================================COUNT============================#

NB_COMP	:=	1

ifndef RECURSION
TO_COMP :=	$(shell make RECURSION=1 -n | grep Compiling | wc -l)
else
TO_COMP	:=	1
endif

PERCENT	:= 0

NB_COMP_BONUS := 1
ifndef RECURSION
TO_COMP_BONUS := $(shell make bonus RECURSION=1 -n | grep Compiling | wc -l)
else
TO_COMP_BONUS := 1
endif

#==============================COLORS==============================#
NOC			= \e[0m
BOLD		= \e[1m
DIM			= \e[2m
UNDERLINE	= \e[4m
BLACK		= \e[1;30m
RED			= \e[1m\e[38;5;196m
GREEN		= \e[1m\e[38;5;76m
YELLOW		= \e[1m\e[38;5;220m
BLUE		= \e[1m\e[38;5;33m
PURPLE		= \e[1;35m
CYAN		= \e[1;36m
WHITE		= \e[1;37m
SPECIAL		= \e[1m\e[38;5;223m

BLACK_BG 	= \033[0;40m
RED_BG 		= \033[0;41m
GREEN_BG 	= \033[0;42m
YELLOW_BG 	= \033[0;43m
BLUE_BG 	= \033[0;44m
MAGENTA_BG 	= \033[0;45m
CYAN_BG 	= \033[0;46m
WHITE_BG 	= \033[0;47m
RESET_BG	= \033[0m

#================================DIRS============================#

SRC_DIR			:=  srcs_bonus
#SRC_DIR_BONUS	:=	srcs_bonus
HEADER_DIR		:=	includes_bonus
BUILD_DIR		:=	.build_bonus
MLX_DIR			:=	MacroLibX
LIBRT_DIR		:=	lib_RT

#==============================SOURCES===========================#

SRCS_FILES:=	main_bonus.c \
		display_bonus/display_screen_bonus.c \
		display_bonus/make_average_pixel_bonus.c \
		display_bonus/resolution_bonus.c \
		math_bonus/color_bonus.c \
		math_bonus/ray_bonus.c \
		math_bonus/vector_bonus.c \
		math_bonus/matrix_bonus.c	\
		math_bonus/move_matrix_bonus.c \
		math_bonus/change_vector_bonus.c \
		mlx_bonus/move_obj_bonus.c	\
		mlx_bonus/mlx_events_bonus.c \
		mlx_bonus/mlx_loop_bonus.c \
		mlx_bonus/mlx_mouse_bonus.c \
		mlx_bonus/mlx_setting_bonus.c \
		mlx_bonus/mlx_setup_bonus.c \
		mlx_bonus/rotate_obj_bonus.c \
		mlx_bonus/del_obj_bonus.c \
		mlx_bonus/resize_obj_bonus.c \
		mlx_bonus/translation_obj_bonus.c \
		mlx_bonus/mlx_key_bonus.c \
		print_bonus/print_bonus.c \
		parsing_bonus/parse_cam_light_bonus.c \
		parsing_bonus/parse_sphere_bonus.c \
		parsing_bonus/parse_plane_bonus.c \
		parsing_bonus/parse_triangle_bonus.c \
		parsing_bonus/parse_ellipsoid_bonus.c \
		parsing_bonus/parsing_bonus.c \
		parsing_bonus/scene_bonus.c \
		parsing_bonus/verif_utils_bonus.c \
		parsing_bonus/verif_float_bonus.c \
		parsing_bonus/parse_cylinder_bonus.c \
		parsing_bonus/parse_a_light_bonus.c \
		render_bonus/antialiasing_bonus.c \
		render_bonus/shape_bonus/cylinder_bonus.c \
		render_bonus/shape_bonus/plane_bonus.c \
		render_bonus/shape_bonus/sphere_bonus.c \
		render_bonus/shape_bonus/triangle_bonus.c \
		render_bonus/shape_bonus/ellipsoid_bonus.c \
		render_bonus/nearest_obj_bonus.c \
		render_bonus/pathtracing_bonus.c \
		render_bonus/raytracing_bonus.c \
		render_bonus/render_bonus.c \
		render_bonus/hit_obj_bonus.c \
		render_bonus/nearest_elli_cyl_bonus.c \
		render_bonus/bump_map_texture_bonus.c \
		thread_bonus/setup_thread_bonus.c \
		thread_bonus/run_thread_bonus.c \
		utils_bonus/alloc_bonus.c \
		utils_bonus/input_bonus.c \
		utils_bonus/add_texture_bonus.c	\
		view_bonus/camera_bonus.c \
		view_bonus/move_camera_bonus.c \
		view_bonus/angle_camera_bonus.c


#SRCS_FILES_BONUS:=

SRCS:=			$(addprefix $(SRC_DIR)/, $(SRCS_FILES))
#SRCS_BONUS:=	$(addprefix $(SRC_DIR_BONUS)/, $(SRCS_FILES_BONUS))

#=============================OBJECTS===========================#

OBJS:=			${SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o}
#OBJS_BONUS:=	${SRCS_BONUS:$(SRC_DIR_BONUS)/%.c=$(BUILD_DIR)/bonus/%.o}

#===============================DEPS=============================#

DEPS:=			${SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.d}
#DEPS_BONUS:=	${SRCS_BONUS:$(SRC_DIR_BONUS)/%.c=$(BUILD_DIR)/bonus/%.d}

#=============================INCLUDES===========================#

LIBS :=  -L$(LIBRT_DIR) -l_rt -L$(MLX_DIR) -lmlx -lSDL2
LDFLAGS := -Wl,-rpath=$(MLX_DIR)
INC := -I$(HEADER_DIR) -I$(LIBRT_DIR) -I$(MLX_DIR)

#================================DIR=============================#

DIRS			:=	$(sort $(shell dirname $(OBJS))) #no duplicates
#DIRS_BONUS		:=	$(sort $(shell dirname $(OBJS_BONUS))) #no duplicates

#===============================RULES============================#

all: $(MLX_DIR) $(LIBRT_DIR) $(NAME)

bonus: $(BONUS_NAME)

$(DIRS):
	@mkdir -p $@

$(DIRS_BONUS):
	@mkdir -p $@

$(NAME): $(OBJS)
	@echo "\n$(GREEN)Create binaries$(NOC)"
	@$(CC) $(CFLAGS) $(OBJS) $(INC) -o $@ $(LIBS) $(LDFLAGS) -lm
	@echo "$(RED)"
	@printf "%s\n" \
	"██████╗ ████████╗        ██╗  ██╗████████╗██████╗ ███████╗███╗   ███╗" \
	"██╔══██╗╚══██╔══╝        ╚██╗██╔╝╚══██╔══╝██╔══██╗██╔════╝████╗ ████║" \
	"██████╔╝   ██║            ╚███╔╝    ██║   ██████╔╝█████╗  ██╔████╔██║" \
	"██╔══██╗   ██║            ██╔██╗    ██║   ██╔══██╗██╔══╝  ██║╚██╔╝██║" \
	"██║  ██║   ██║   ███████╗██╔╝ ██╗   ██║   ██║  ██║███████╗██║ ╚═╝ ██║" \
	"╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝"
	@echo "$(NOC)"

$(BONUS_NAME): $(OBJS_BONUS)
	@echo "\n$(GREEN)Create bonus binaries$(NOC)"
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(INC) -o $@ -lreadline

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(DIRS)
	@mkdir -p $(BUILD_DIR)
	@if [ $(NB_COMP) -eq 1 ]; then echo "\n$(BOLD)Compilation of source files :$(NOC)";fi
	$(eval PERCENT=$(shell expr $(NB_COMP)00 "/" $(TO_COMP)))
	@if [ $(PERCENT) -le 30 ]; then echo -n "$(RED)"; elif [ $(PERCENT) -le 66 ]; then echo -n "$(YELLOW)"; elif [ $(PERCENT) -gt 66 ]; then echo -n "$(GREEN)"; fi
	@echo -n "\r"; for i in $$(seq 1 $$(/usr/bin/tput cols)); do echo -n " "; done
	@echo -n "\r"; for i in $$(seq 1 25); do if [ $$(expr $$i "*" 4) -le $(PERCENT) ]; then echo -n "█"; else echo -n " "; fi; done; echo -n "";
	@printf " $(NB_COMP)/$(TO_COMP) - Compiling $<"
	@echo -n "$(NOC)"
	@$(CC) $(CFLAGS) $(INC) $< -c -o $@
	$(eval NB_COMP=$(shell expr $(NB_COMP) + 1))


$(BUILD_DIR)/bonus/%.o: $(SRC_DIR_BONUS)/%.c | $(DIRS_BONUS)
	@mkdir -p $(BUILD_DIR)/bonus/
	@if [ $(NB_COMP_BONUS) -eq 1 ]; then echo "$(BOLD)Compilation of source files :$(NOC)";fi
	$(eval PERCENT=$(shell expr $(NB_COMP_BONUS)00 "/" $(TO_COMP_BONUS)))
	@if [ $(PERCENT) -le 30 ]; then echo -n "$(RED)"; elif [ $(PERCENT) -le 66 ]; then echo -n "$(YELLOW)"; elif [ $(PERCENT) -gt 66 ]; then echo -n "$(GREEN)"; fi
	@echo -n "\r"; for i in $$(seq 1 $$(/usr/bin/tput cols)); do echo -n " "; done
	@echo -n "\r"; for i in $$(seq 1 25); do if [ $$(expr $$i "*" 4) -le $(PERCENT) ]; then echo -n "█"; else echo -n " "; fi; done; echo -n "";
	@printf " $(NB_COMP_BONUS)/$(TO_COMP_BONUS) - Compiling $<"
	@echo -n "$(NOC)"
	@$(CC) $(CFLAGS) $(INC) $< -c -o $@
	$(eval NB_COMP_BONUS=$(shell expr $(NB_COMP_BONUS) + 1))

$(MLX_DIR):
	@git clone https://github.com/seekrs/MacroLibX.git $@
	@$(MAKE) -C $@

$(LIBRT_DIR):
	@git clone git@github.com:Djo-msv/lib_RT.git $@
	@$(MAKE) -C $@

clean:
	@echo "$(RED)Remove objects$(NOC)"
	@rm -rf $(BUILD_DIR)

fclean: clean
	@echo "$(RED)Remove binary$(NOC)"
	@rm -f $(NAME)
	@rm -f $(BONUS_NAME)

re: fclean
	@make

rebonus: fclean
	@make bonus

.PHONY: all clean fclean re rebonus

-include $(DEPS)
