GTEST_DIR = gtest

.PHONY: all clean fclean re clone_gtest

all: clone_gtest
	mv Makefile Makefile_tmp
	cmake CMakeLists.txt
	mv Makefile Makefile_cmake
	mv Makefile_tmp Makefile
	make -f Makefile_cmake

clone_gtest:
	git clone https://github.com/google/googletest.git $(GTEST_DIR)
	cd $(GTEST_DIR)
	git pull
	cd -

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
