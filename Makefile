SRCS		= main.cpp mathsUtils.cpp parsingPolynomials.cpp PolynomialEquation.cpp test.cpp

DIR_SRC		= srcs/

OBJS		= $(addprefix .obj/, ${SRCS:.cpp=.o})

CXX		= c++

RM		= rm -f

NAME		= Solver

FLAGS		= -Wall -Werror -Wextra

DEPS		= $(OBJS:.o=.d)

all:		${NAME}

-include	$(DEPS)

.obj/%.o:	$(addprefix ${DIR_SRC}, %.cpp)
		@mkdir .obj -p
		${CXX} ${FLAGS} -c $< -o $@ -I./headers -MD -MP

${NAME}:	${OBJS}
		${CXX} ${FLAGS} ${OBJS} -o ${NAME}

clean:
		${RM} -r .obj

fclean:		clean
		${RM} ${NAME}

re:		fclean all

.PHONY:		clean fclean all re
