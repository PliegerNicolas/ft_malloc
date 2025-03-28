#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2025-03-27 09:38:49 by nicolas           #+#    #+#             *#
#*   Updated: 2025-03-27 09:38:49 by nicolas          ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

#* *************************************************************************** *#
#* *                                    ID                                   * *#
#* *************************************************************************** *#

NAME				:=	tester

# Compilation flags and utils.
CC					:=	gcc
CFLAGS				:=	-Wall -Wextra -Werror -Wno-unused

# Libraries
LIBFT_MALLOC_PATH	:=	$(CURDIR)/..
RPATH_FLAGS			=	

# Linkage
LD_FLAGS			=

# Artefact
HOSTTYPE			?=	$(shell uname -m)_$(shell uname -s)
ARTEFACT_NAME		:=	$(NAME)

#* *************************************************************************** *#
#* *                             RULE FILTERS                                * *#
#* *************************************************************************** *#

ifneq (std, $(filter std, $(MAKECMDGOALS)))
	LD_FLAGS			+=	-L$(LIBFT_MALLOC_PATH) -lft_malloc
	RPATH_FLAGS			+=	-Wl,-rpath,$(LIBFT_MALLOC_PATH)
endif

#* *************************************************************************** *#
#* *                                  FILES                                  * *#
#* *************************************************************************** *#

#* Config *#

# Directories
SOURCES_DIR_PATH	:=	sources
HEADERS_DIR_PATH	:=	includes $(LIBFT_MALLOC_PATH)/includes
OBJECTS_DIR_PATH	:=	objects

# File extensions
SOURCES_FILE_EXTENSION			:=	.c
HEADERS_FILE_EXTENSION			:=	.h

# Files
SOURCES_FILE_NAMES					:=	main

SOURCES_FILE_NAMES_WITH_EXT			:=	$(foreach file, $(SOURCES_FILE_NAMES), \
											$(if $(filter $(SOURCES_FILE_EXTENSION), $(suffix $(file))), \
												$(file), \
												$(file)$(SOURCES_FILE_EXTENSION)))
SORTED_SOURCES_FILE_NAMES_WITH_EXT	:=	$(sort $(SOURCES_FILE_NAMES_WITH_EXT))

#* Data *#

SOURCES			:= $(addprefix $(SOURCES_DIR_PATH)/, $(SORTED_SOURCES_FILE_NAMES_WITH_EXT))
OBJECTS			:= $(addprefix $(OBJECTS_DIR_PATH)/, $(SORTED_SOURCES_FILE_NAMES_WITH_EXT:%$(SOURCES_FILE_EXTENSION)=%.o))
DEPENDENCIES	:= $(OBJECTS:%.o=%.d)
HEADERS			:= $(addprefix -I , $(HEADERS_DIR_PATH))

#* *************************************************************************** *#
#* *                              CONSTANTS                                  * *#
#* *************************************************************************** *#

# Text formatting
BOLD			:=		\033[1m
ITALIC			:=		\033[3m
UNDERLINE		:=		\033[4m
STRIKETHROUGH	:=		\033[9m

# Color codes
RED			:=		\033[0;31m
GREEN		:=		\033[0;32m
YELLOW		:=		\033[0;33m
BLUE		:=		\033[0;34m
PURPLE		:=		\033[0;35m
CYAN		:=		\033[0;36m
WHITE		:=		\033[0;37m
RESET		:=		\033[0m

#* *************************************************************************** *#
#* *                               MESSAGES                                  * *#
#* *************************************************************************** *#

define make_successful
	echo "🌟 $(GREEN)$(BOLD)Make successful$(RESET) 🌟"
endef

define linkage_message
	echo "🔗 $(YELLOW)Linking $(BOLD)$(CYAN)$@$(RESET)$(YELLOW)...$(RESET)"
endef

define build_object_message
	echo "Creating $(nodir $<)"
endef

define build_object_message
		echo "    $(YELLOW)•$(RESET) $(CYAN)$(notdir $<)$(RESET)"
endef

define build_object_dir_and_message
	if [ ! -d $(dir $@) ]; then \
		mkdir -p $(dir $@); \
		echo "$(CYAN)Building object files in directory $(BOLD)./$(patsubst %/,%,$(dir $@))$(RESET)"; \
	fi
endef

#* *************************************************************************** *#
#* *                                  RULES                                  * *#
#* *************************************************************************** *#

all: build_ft_malloc $(ARTEFACT_NAME)

build_ft_malloc:
	@make -C $(LIBFT_MALLOC_PATH)

# Rule to build the final executable/shared object/...
$(ARTEFACT_NAME): $(OBJECTS)
	@$(call linkage_message)
	@$(CC) $(CFLAGS) $(RPATH_FLAGS) $(HEADERS) -o $@ $(OBJECTS) $(LD_FLAGS)
	@$(call make_successful)

# Rule to build object and dependency files (.o & .d) from source files (.c)
-include $(DEPENDENCIES) # Include the header files if they exist, to take them into account. Fail silently if needed.
$(OBJECTS_DIR_PATH)/%.o: $(SOURCES_DIR_PATH)/%$(SOURCES_FILE_EXTENSION)
	@$(call build_object_dir_and_message)
	@$(call build_object_message)
	@$(CC) $(CFLAGS) -MMD -MP -MF $(@:%.o=%.d) $(HEADERS) -c $< -o $@

# Rule to delete all objects (.o) and dependencies (.d).
clean:
	@rm -rf $(OBJECTS_DIR_PATH)

# Rule to delete all objects (.o), dependencies (.d) and artifact (.a, .so, .dll, ...).
fclean: clean
	@rm -f $(ARTEFACT_NAME)
	@rm -f $(SYM_LINK_NAME)

# Rule to clean all and build it everything from scratch again.
re: fclean all

# Rule to build project with malloc from c's standard library.
std: $(ARTEFACT_NAME)

.PHONY: clean fclean re std