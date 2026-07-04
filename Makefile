NAME =  Arczn

S_PARG =  arg.c  pars.c  check.c
D_PARG =  pArg/
PARG = $(addprefix $(D_PARG), $(S_PARG))

S_GEN =  random.c  ivy.c  petri.c
D_GEN =  gen/
GEN = $(addprefix $(D_GEN), $(S_GEN))

S_PRINT =  print.c  color.c  frame.c  nColor.c
D_PRINT =  print/
PRINT = $(addprefix $(D_PRINT), $(S_PRINT))

S_UTILS =  random.c  color.c  hashtable.c  vector.c
D_UTILS =  utils/
UTILS = $(addprefix $(D_UTILS), $(S_UTILS))

SRC =  $(PARG)  $(GEN)  $(PRINT)  $(UTILS)  main.c
D_SRC = src/

D_BUILD = .build/
OBJ =  $(addprefix $(D_BUILD), $(SRC:.c=.o))

CC =  cc
FLAGS = -Wall -Wextra -Werror -MMD -g -O3
INC_FLAGS =  $(addprefix -I, $(INC))
INC = inc/

RM =  rm -rf

MAKE += --no-print-directory

all:	$(NAME)

$(NAME):	$(OBJ)
	echo $(SRC)
	$(CC) -o$@ $^ $(LIB_FLAGS)

$(OBJ): $(D_BUILD)%.o:	$(D_SRC)%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(INC_FLAGS) -c $< -o $@

D_SPNG =  

SYML_SPNG_SO =  ./libspng.so

$(SYML_SPNG_SO):
	ln -s $@ 

clean:
	@$(RM) $(D_BUILD)

fclean: clean
	@$(RM) $(NAME)

re: fclean
	@$(MAKE) all

DEPS = $(addprefix $(D_BUILD), $(SRC:.c=.d))
-include $(DEPS)

.PHONY: re fclean clean all $(CC) $(FLAGS) $(RM)
