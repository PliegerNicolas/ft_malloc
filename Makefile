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

NAME				:=	libft_malloc

# Compilation flags and utils.
CC					:=	gcc
CFLAGS				:=	-Wall -Wextra -Werror -Wno-unused -fPIC

# Libraries
LIBFT_MINI_PATH		:=	$(CURDIR)/libft_mini
LIBFT_MINI_LD_FLAGS	:=	-L$(LIBFT_MINI_PATH) -lft_mini

# Linkage
# Shared is used to specify we want to create a shared library (.so).
LD_FLAGS			:= -shared -lpthread
LIB_FILE_EXTENSION	:= .so

# Artefact
HOSTTYPE			?=	$(shell uname -m)_$(shell uname -s)
ARTEFACT_NAME		:=	$(NAME)_${HOSTTYPE}$(LIB_FILE_EXTENSION)
SYM_LINK_NAME		:=	$(NAME)$(LIB_FILE_EXTENSION)

#* *************************************************************************** *#
#* *                             RULE FILTERS                                * *#
#* *************************************************************************** *#

ifeq (debug, $(filter debug, $(MAKECMDGOALS)))
	CFLAGS				+=	-g3 -D MALLOC_DEBUG=1
endif

ifeq (optimize, $(filter optimize, $(MAKECMDGOALS)))
	CFLAGS				+=	-O3
endif

#* *************************************************************************** *#
#* *                                  FILES                                  * *#
#* *************************************************************************** *#

#* Config *#

# Directories
SOURCES_DIR_PATH	:=	sources
HEADERS_DIR_PATH	:=	includes $(LIBFT_MINI_PATH)/includes
OBJECTS_DIR_PATH	:=	objects

# File extensions
SOURCES_FILE_EXTENSION			:=	.c
HEADERS_FILE_EXTENSION			:=	.h

# Files
INTERNAL_SOURCE_FILE_NAMES	:=	\
								gmarena \
								alloc_mchunk \
								realloc_mchunk \
								free_mchunk_or_mregion \
								print_marena \
								\
								marena/init_marena \
								marena/init_marena_once \
								\
								mregion/init_mregion \
								mregion/init_mregions \
								mregion/free_mregion \
								mregion/get_mregion_by_mchunk \
								mregion/utils/mmap_mregion \
								mregion/utils/append_mregion \
								mregion/utils/prepend_mregion \
								mregion/utils/is_on_mregion_boundary \
								mregion/utils/does_mregion_contain_mchunk \
								\
								mchunk/use_mchunk \
								mchunk/free_mchunk \
								mchunk/select_best_fit_mbin_mchunk \
								mchunk/insert_free_mchunk_in_mbin \
								mchunk/migrate_mchunk_to_new_mregion \
								mchunk/partition_mchunk \
								mchunk/grow_mchunk \
								mchunk/shrink_mchunk \
								mchunk/coalesce/try_coalesce_with_next_free_mchunk \
								mchunk/coalesce/try_coalesce_with_neighboring_free_mchunks \
								mchunk/coalesce/try_coalesce_until_allocation_size_reached \
								mchunk/utils/mchunk_has_aberrant_values \
								\
								limits/get_max_allocation_size \
								limits/get_max_mregion_size \
								\
								mappings/map_allocation_size_to_marena_mregion_head \
								mappings/map_mregion_bound_type_to_max_allocation_size \
								mappings/map_allocation_size_to_mregion_size \
								mappings/map_mregion_bound_type_to_name \
								\
								errors/printerr

PUBLIC_SOURCES_FILE_NAMES	:=	\
								malloc \
								realloc \
								free \
								show_alloc_mem

SOURCES_FILE_NAMES			:=	$(PUBLIC_SOURCES_FILE_NAMES) $(addprefix internal/, $(INTERNAL_SOURCE_FILE_NAMES))

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

define symlink_build_message
	$(if $1,, $(error Missing argument for symlink_build_message))
	echo "➿ $(YELLOW)Building symbolic link: $(BOLD)$(CYAN)$(1)$(WHITE) -> $(CYAN)$(@)$(RESET)$(YELLOW)...$(RESET)"
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

all: build_libft_mini $(ARTEFACT_NAME)

build_libft_mini:
	@make -C $(LIBFT_MINI_PATH) $(MAKECMDGOALS)

# Rule to build the final executable/shared object/...
$(ARTEFACT_NAME): $(OBJECTS)
	@$(call linkage_message)
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ $(OBJECTS) $(LD_FLAGS) $(LIBFT_MINI_LD_FLAGS)
	@$(call symlink_build_message,$(SYM_LINK_NAME))
	@ln -sf $(ARTEFACT_NAME) $(SYM_LINK_NAME)
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
	@make -C $(LIBFT_MINI_PATH) clean

# Rule to delete all objects (.o), dependencies (.d) and artifact (.a, .so, .dll, ...).
fclean: clean
	@$(call fclean_message)
	@rm -f $(ARTEFACT_NAME)
	@rm -f $(SYM_LINK_NAME)
	@make -C $(LIBFT_MINI_PATH) fclean

# Rule to clean all and build it everything from scratch again.
re: fclean all

debug: all
optimize: all

.PHONY: clean fclean re debug optimize
