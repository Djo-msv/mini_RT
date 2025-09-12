MAKEFLAGS += --no-print-directory

NOC   = \033[0m
RED   = \033[1;31m
GREEN = \033[1;32m
YELLOW= \033[1;33m
BLUE  = \033[1;34m

MANDA_DIR := manda
BONUS_DIR := bonus
MLX_DIR   := MacroLibX
LIBRT_DIR := lib_RT

NAME_MANDA := $(MANDA_DIR)/miniRT
NAME_BONUS := $(BONUS_DIR)/miniRT_bonus

all: $(MLX_DIR) $(LIBRT_DIR)
	@echo "$(BLUE)[INFO]$(NOC) Compilation mandatory"
	@$(MAKE) -C $(MANDA_DIR)

bonus: $(MLX_DIR) $(LIBRT_DIR)
	@echo "$(BLUE)[INFO]$(NOC) Compilation bonus"
	@$(MAKE) -C $(BONUS_DIR)

$(MLX_DIR):
	@echo "$(YELLOW)[CLONE]$(NOC) MacroLibX"
	@git clone https://github.com/seekrs/MacroLibX.git $(MLX_DIR)
	@$(MAKE) -C $(MLX_DIR)

$(LIBRT_DIR):
	@echo "$(YELLOW)[CLONE]$(NOC) lib_RT"
	@git clone git@github.com:Djo-msv/lib_RT.git $(LIBRT_DIR)
	@$(MAKE) -C $(LIBRT_DIR)

clean:
	@echo "$(RED)[CLEAN]$(NOC) Objects"
	@$(MAKE) -C $(MANDA_DIR) clean
	@$(MAKE) -C $(BONUS_DIR) clean

fclean: clean
	@echo "$(RED)[REMOVE]$(NOC) Binaries"
	@rm -f $(NAME_MANDA) $(NAME_BONUS)
	@echo "$(RED)[REMOVE]$(NOC) Libraries"
	@rm -rf $(MLX_DIR) $(LIBRT_DIR)

re: fclean all

rebonus: fclean bonus

.PHONY: all bonus clean fclean re rebonus
