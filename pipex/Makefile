#--------------------------------------#
#- CONFIG -----------------------------#
#--------------------------------------#

# main source codes
NAME			:= pipex
APP				:= $(NAME)
APP_DIR			:= .
APP_CODES		:= $(APP_DIR)/main.c
APP_OBJS		:= $(APP_CODES:.c=.o)

BIN_DIR			:= bin
INC_DIR			:= .

LIBFT_DIR		:= libft
LIBFT			:= libft/libft.a

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror
CFLAGS			+= -I $(INC_DIR)
CFLAGS			+= $(DBG)	# make DBG="-g"

SRC_DIR			:= .
SRC_CODES		:= \
	$(SRC_DIR)/context.c \
	$(SRC_DIR)/error.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/util.c \
	$(SRC_DIR)/wrap.c
SRC_OBJS		:= $(SRC_CODES:.c=.o)

TEST_DIR		:= test
TEST_NAMES		:= $(shell find $(TEST_DIR) -mindepth 1 -maxdepth 1 -type d -printf '%f\n')
TEST_CODES		:= $(shell find $(TEST_DIR) -name '*.c')
TEST_INC_DIR	:= test_include		# shared headers for test
TEST_SRC_DIR	:= test_src			# shared srcs for test
TEST_SRC_CODES	:= $(shell find $(TEST_SRC_DIR) -name '*.c')
TEST_SRC_OBJS	:= $(TEST_SRC_CODES:.c=.o)
# objs including all test srcs and shared srcs
TEST_OBJS		:= $(TEST_CODES:.c=.o) $(TEST_SRC_OBJS)

#--------------------------------------#
#- CMD --------------------------------#
#--------------------------------------#

.PHONY: all
all: app

.PHONY: clean
clean:
	make -C $(LIBFT_DIR) clean
	find . -name "*.o" -delete

.PHONY: fclean
fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(APP)
	rm -f $(BIN_DIR)/*

.PHONY: re
re: fclean all

#--------------------------------------#
#- APP --------------------------------#
#--------------------------------------#

.PHONY: app
app: $(NAME)

$(NAME): $(SRC_OBJS) $(APP_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^

#--------------------------------------#
#- LIBFT ------------------------------#
#--------------------------------------#

$(LIBFT):
	make -C $(LIBFT_DIR)

#--------------------------------------#
#- SRC --------------------------------#
#--------------------------------------#

.PHONY: src
src: $(SRC_OBJS)

#--------------------------------------#
#- TEST -------------------------------#
#--------------------------------------#

.PHONY: test
test: $(BIN_DIR) $(TEST_NAMES)

.SECONDEXPANSION:
%_test: \
	$(TEST_SRC_OBJS) \
	$(SRC_OBJS) \
	$$(shell find $(TEST_DIR)/$$*_test -type f -name '*.c' | sed 's/\.c/\.o/') \
	$(LIBFT) | \
	$(BIN_DIR)	# order only prerequisite
	$(CC) $(CFLAGS) -I $(TEST_INC_DIR) -o $(BIN_DIR)/$@ $^

#--------------------------------------#
#- COMMONS ----------------------------#
#--------------------------------------#

$(BIN_DIR):
	mkdir $(BIN_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# include test headers for test objs
$(TEST_OBJS): %.o: %.c
	$(CC) $(CFLAGS) -I $(TEST_INC_DIR) -c -o $@ $<
