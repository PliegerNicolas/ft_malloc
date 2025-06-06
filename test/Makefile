#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2025-04-27 21:29:03 by nplieger          #+#    #+#             *#
#*   Updated: 2025-04-27 21:29:03 by nplieger         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

#* *************************************************************************** *#
#* *                                    ID                                   * *#
#* *************************************************************************** *#

NAME				:=	tester

# Compilation flags and utils.
CC					:=	gcc
CFLAGS				:=	-Wall -Wextra

# Libraries
LIBFT_MALLOC_PATH	:=	$(CURDIR)/..
LIBFT_MINI_PATH		:=	$(LIBFT_MALLOC_PATH)/libft_mini

# Linkage
LD_FLAGS			= -L $(LIBFT_MINI_PATH) -lft_mini
RPATH_FLAGS			=

# Artefact
HOSTTYPE			?=	$(shell uname -m)_$(shell uname -s)
ARTEFACT_NAME		:=	$(NAME)

#* *************************************************************************** *#
#* *                             RULE FILTERS                                * *#
#* *************************************************************************** *#

ifneq (std, $(filter std, $(MAKECMDGOALS)))
	CFLAGS				+=	-D STD_MALLOC=0
	LD_FLAGS			+=	-L$(LIBFT_MALLOC_PATH) -lft_malloc
	RPATH_FLAGS			+=	-Wl,-rpath,$(LIBFT_MALLOC_PATH)
else
	CFLAGS				+=	-D STD_MALLOC=1
endif

ifeq (debug, $(filter debug, $(MAKECMDGOALS)))
	CFLAGS				+=	-g3
endif

ifeq (optimize, $(filter optimize, $(MAKECMDGOALS)))
	CFLAGS				+=	-O2
endif

#* *************************************************************************** *#
#* *                                  FILES                                  * *#
#* *************************************************************************** *#

#* Config *#

# Directories
SOURCES_DIR_PATH	:=	sources
HEADERS_DIR_PATH	:=	includes $(LIBFT_MALLOC_PATH)/includes $(LIBFT_MINI_PATH)/includes
OBJECTS_DIR_PATH	:=	objects

# File extensions
SOURCES_FILE_EXTENSION			:=	.c
HEADERS_FILE_EXTENSION			:=	.h

# Files
SOURCES_FILE_NAMES				:=	main \
									test_macros \
									test_malloc \
									test_realloc \
									test_free \
									test_sandbox \
									utils/please \
									utils/put \
									utils/thread/thread \
									utils/thread/routines

SOURCES_FILE_NAMES_WITH_EXT := $(foreach file, $(SOURCES_FILE_NAMES), $(basename $(file))$(SOURCES_FILE_EXTENSION))
DIRECTORIES := $(sort $(dir $(SOURCES_FILE_NAMES_WITH_EXT)))
SORTED_COMPLETE_SOURCES_FILE_NAMES := $(foreach directory, $(DIRECTORIES), \
    	$(sort $(foreach file, $(SOURCES_FILE_NAMES_WITH_EXT), \
        	$(if $(filter $(directory), $(dir $(file))), $(file), ))))

#* Data *#

SOURCES			:= $(addprefix $(SOURCES_DIR_PATH)/, $(SORTED_COMPLETE_SOURCES_FILE_NAMES))
OBJECTS			:= $(addprefix $(OBJECTS_DIR_PATH)/, $(SORTED_COMPLETE_SOURCES_FILE_NAMES:%$(SOURCES_FILE_EXTENSION)=%.o))
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
ORANGE		:=		\033[0;38;5;209m
GRAY		:=		\033[0;37m
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

define clean_message
		echo "🗑️🧹 $(ORANGE)Cleaning up object files...$(RESET)"
endef

define fclean_message
		echo "🗑️🧹 $(ORANGE)Cleaning up artefacts...$(RESET)"
endef




define build_object_message
	echo "Creating $(nodir $<)"
endef

define build_object_message
		echo "    $(YELLOW)•$(RESET) $(CYAN)$(notdir $<)$(RESET)"
endef

LAST_DIR	:=
define build_object_dir_and_message
	if [ "$(dir $@)" != "$(LAST_DIR)" ]; then \
		mkdir -p $(dir $@); \
		echo "$(CYAN)Building object files in directory $(BOLD)./$(patsubst %/,%,$(dir $@))$(RESET)"; \
	fi
	$(eval LAST_DIR := $(dir $@))
endef

#* *************************************************************************** *#
#* *                                  RULES                                  * *#
#* *************************************************************************** *#

all: build_ft_malloc $(ARTEFACT_NAME)

build_ft_malloc:
	@$(MAKE) -C $(LIBFT_MALLOC_PATH) $(filter-out std,$(MAKECMDGOALS))

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
	@$(call clean_message)
	@rm -rf $(OBJECTS_DIR_PATH)

# Rule to delete all objects (.o), dependencies (.d) and artifact (.a, .so, .dll, ...).
fclean: clean
	@$(call fclean_message)
	@rm -f $(ARTEFACT_NAME)
	@rm -f $(SYM_LINK_NAME)

# Rule to clean all and build it everything from scratch again.
re: fclean
	@$(MAKE) all

# Rule to build project with malloc from c's standard library.
std: all
debug: all
optimize: all

.PHONY: clean fclean re std debug optimize
