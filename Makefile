# -*- MakeFile -*-

SRC		=	TestClass.cpp DerivedTestClass.cpp main.cpp PointerFactory.cpp 
OBJ		=	$(addprefix _obj/,$(notdir $(SRC:.cpp=.o)))
NAME	=	technical_challenge
CFLAGS	=	-Wall -Werror -Wextra -std=c++17

all:		$(NAME)

_obj:
	mkdir _obj

_obj/%.o:	%.cpp | _obj
	c++ $(CFLAGS) -MMD -MP -c $< -o $@

$(NAME):	$(OBJ)
	c++ $(CFLAGS) -MMD -MP $^ -o $@

fclean:		clean
	rm -rf $(NAME)

clean:
	rm -rf testfile.txt
	rm -rf _obj

re:			fclean all

.PHONY: all clean fclean re
-include $(OBJ:.o=.d)