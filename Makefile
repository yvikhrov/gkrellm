# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/14 20:54:39 by yvikhrov          #+#    #+#              #
#    Updated: 2018/10/21 16:05:50 by hshakula         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FULL_PATH=$(shell pwd)
BUILD_PATH=$(FULL_PATH)/build

all: ft_gkrellm

ft_gkrellm: build
	@cmake --build $(BUILD_PATH) --config Release --target ft_gkrellm -- -j4

build: build_folder
	@cmake -DFULL_PATH="$(FULL_PATH)" \
			-B"$(BUILD_PATH)" \
			-H"$(FULL_PATH)"

build_folder:
	@mkdir -p $(BUILD_PATH)

xcode:
	@cmake -G "Xcode" \
			-DFULL_PATH="$(FULL_PATH)" \
			-B"$(BUILD_PATH)Xcode" \
			-H"$(FULL_PATH)"

clean:
	@rm -rf $(BUILD_PATH)
	@rm -rf $(BUILD_PATH)Xcode

fclean: clean
	@rm -f ft_gkrellm

re: fclean all

.PHONY: re fclean all clean
