# Corrected Makefile for MiniLibX on macOS

# --- Variables ---
NAME=libmlx.a
CC=cc
CFLAGS=-O3
AR=ar
ARFLAGS=rcs
SWIFTC=swiftc
SWIFTCFLAGS=-I. -parse-as-library

# --- Sources ---
MODULE_SRC= mlx_image.swift mlx_window.swift mlx_init.swift
MODULE_OBJ=$(MODULE_SRC:.swift=.swiftmodule)

SWIFT_SRC= interface.swift $(MODULE_SRC)
SWIFT_OBJ=$(SWIFT_SRC:.swift=.o)

C_SRC= mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ=$(C_SRC:.c=.o)

OBJS=$(SWIFT_OBJ) $(C_OBJ)

# --- Rules ---
all: $(NAME)

# Rule to create the static library (.a file)
$(NAME): $(MODULE_OBJ) $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

# Rule to compile Swift sources to object files (.o)
%.o: %.swift
	$(SWIFTC) $(SWIFTCFLAGS) -c $< -o $@

# Rule to create Swift modules (.swiftmodule)
%.swiftmodule: %.swift
	$(SWIFTC) $(SWIFTCFLAGS) -emit-module $< -o $@

# Rule to compile C sources to object files (.o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Cleanup ---
clean:
	rm -f $(OBJS) $(MODULE_OBJ) *.swiftdoc *~

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

