SRCS=	code_review_test_node.cpp test_class.cpp
FOLDER=	_bin/
OBJS=	$(addprefix $(FOLDER),$(notdir $(SRCS:.cpp=.o)))
NAME=	code_review
CFLAGS=	-Wall -Werror -Wextra -std=c++20

all:	$(NAME)

$(FOLDER):
	mkdir $(FOLDER)

$(FOLDER)/$.o:	%.cpp | $(FOLDER)
	c++ $(CFLAGS) -MMD -MP -c $< -o $@

$(NAME):	$(OBJS)
	c++ $(CFLAGS) -MMD -MP $^ -o $@

fclean:	clean
	rm $(NAME)

clean:
	rm -rf $(FOLDER)

re:		fclean all

.PHONY:	all clean fclean re
-include $(OBJS:o-.d)