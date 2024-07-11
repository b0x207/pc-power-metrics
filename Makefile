SRC := src/main.c
OBJ := $(SRC:.c=.o)
BUILD_DIR ?= build
BUILD_OBJ := $(addprefix $(BUILD_DIR)/,$(OBJ))

CFLAGS := -Wall -Werror

$(BUILD_DIR)/pc-power-metrics: $(BUILD_OBJ)
	cc -o $@ $(CFLAGS) $<

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	cc -c -o $@ $(CFLAGS) $<

@PHONY: run
run: $(BUILD_DIR)/pc-power-metrics
	@exec $(BUILD_DIR)/pc-power-metrics
