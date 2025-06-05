BINARY=cub3d

CC= gcc
C_FLAGS= -Wall -Wextra -Werror
C_FLAGS += -g3 -fsanitize=address

RM= rm -rf

SRC_FILES = main.c \
			parser.c \
			mlx.c \
			hooks.c \
			player.c \
			render.c 
SRC_DIR = ./Src/
SRC := $(addprefix $(SRC_DIR),$(SRC_FILES))

# OBJECTS
OBJ_DIR = ./Obj/
OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

#INCLUDES
INC_DIR		= ./Inc/
INC_FILES	= cub3d.h \
			  structs.h \

INC			:= $(addprefix $(INC_DIR), $(INC_FILES))

#LIBRARIES
##LIBFT
LIBFT_DIR=./libft/
LIBFT:= $(LIBFT_DIR)libft.a
LIBFT_LD = -L $(LIBFT_DIR)  -lft 

##MLX
MLX_DIR = ./minilibx-linux/
MLX := $(MLX_DIR)libmlx.a
MLX_LD :=   -L $(MLX_DIR)  -lbsd -lmlx -lXext -lX11

##MATH_H
MATH_LD = -lm

LD_FLAGS := $(LIBFT_LD) $(MLX_LD) $(MATH_LD)

# Rules
all: $(BINARY)

$(BINARY): $(OBJ) $(LIBFT) $(MLX)
	@printf "\n$(CY)Generating $(BINARY) executable...$(RC)\n"
	$(CC) $(C_FLAGS) -o $(BINARY) $(OBJ) $(LD_FLAGS)
	@printf "$(GR)Done!$(RC)\n\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@printf "\n$(CY)Compiling $<...$(RC)\n"
	$(CC) $(C_FLAGS) -c -I$(INC_DIR) $< -o $@
	@printf "$(GR)Object $@ ready!$(RC)\n"

$(MLX):
	@printf "\n$(CY)Generating MiniLibX...$(RC)\n"
	@make -sC $(MLX_DIR)
	@printf "$(GR)MiniLibX created!$(RC)\n\n"

$(LIBFT):
	@printf "\n$(GR)Generating Libft...$(RC)\n"
	@make -sC $(LIBFT_DIR)
	@printf "$(GR)Libft created!$(RC)\n\n"

bonus: all

re: fclean all

rebonus: fclean bonus

clean:
	@printf "\n$(YE)Cleaning all object files from libft...$(RC)\n"
	@make clean -sC $(LIBFT_DIR)
	@printf "$(GR)Libft objects removed!$(RC)\n\n"
	@$(RM) $(OBJ_DIR)

fclean: clean
	@printf "\n$(YE)Cleaning all additional objects and libraries...$(RC)\n"
	@make fclean -sC $(LIBFT_DIR)
	@$(RM) $(BINARY)
	@printf "$(GR)All libraries removed!$(RC)\n\n"


.PHONY: clean fclean re rebonus all bonus

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m
