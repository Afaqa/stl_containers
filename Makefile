GTEST_DIR = gtest

.PHONY: all clean fclean re clone_gtest

all: clone_gtest
	mv Makefile Makefile_tmp
	cmake CMakeLists.txt
	mv Makefile Makefile_cmake
	make -f Makefile_cmake
	mv Makefile_tmp Makefile

clone_gtest:
	if [ -d "$(GTEST_DIR)" ];\
	then\
		git -C $(GTEST_DIR) pull;\
	else\
		git clone https://github.com/google/googletest.git $(GTEST_DIR);\
	fi

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
