#--------------------------------------#
#- CONFIG -----------------------------#
#--------------------------------------#

# main source codes
APP				:= philo
APP_DIR			:= app
APP_CODES		:= \
	$(APP_DIR)/app.c \
	$(APP_DIR)/app_run.c \
	$(APP_DIR)/main.c \
	$(APP_DIR)/worker.c \
	$(APP_DIR)/worker_main.c \
	$(APP_DIR)/worker_update.c
APP_OBJS		:= $(APP_CODES:.c=.o)

BIN_DIR			:= bin
INC_DIR			:= include

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror
CFLAGS			+= -I $(INC_DIR)
CFLAGS			+= $(DBG)	# make DBG="-g"

SRC_DIR			:= src
SRC_CODES		:= \
	$(SRC_DIR)/app/cond.c \
	$(SRC_DIR)/app/counter.c \
	$(SRC_DIR)/app/event.c \
	$(SRC_DIR)/app/philo.c \
	$(SRC_DIR)/app/philo_set.c \
	$(SRC_DIR)/app/seat.c \
	$(SRC_DIR)/app/store.c \
	$(SRC_DIR)/app/table.c \
	$(SRC_DIR)/def/ctx.c \
	$(SRC_DIR)/def/mem.c \
	$(SRC_DIR)/def/mutex.c \
	$(SRC_DIR)/def/thread.c \
	$(SRC_DIR)/def/util.c \
	$(SRC_DIR)/lib/clock.c \
	$(SRC_DIR)/lib/clock_control.c \
	$(SRC_DIR)/lib/time.c \
	$(SRC_DIR)/lib/time2.c
SRC_OBJS		:= $(SRC_CODES:.c=.o)

#--------------------------------------#
#- CMD --------------------------------#
#--------------------------------------#

.PHONY: all
all: app

.PHONY: clean
clean:
	find . -name "*.o" -delete

.PHONY: fclean
fclean: clean
	rm -f $(APP)
	rm -f $(BIN_DIR)/*

.PHONY: re
re: fclean all

#--------------------------------------#
#- APP --------------------------------#
#--------------------------------------#

.PHONY: app
app: $(APP)

$(APP): $(SRC_OBJS) $(APP_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

#--------------------------------------#
#- SRC --------------------------------#
#--------------------------------------#

.PHONY: src
src: $(SRC_OBJS)

#--------------------------------------#
#- COMMONS ----------------------------#
#--------------------------------------#

$(BIN_DIR):
	mkdir $(BIN_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
