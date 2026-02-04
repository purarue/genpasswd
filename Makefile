.PHONY = all

ifdef BUILD_DIR
OUTPUT_DIR := $(BUILD_DIR)
else
OUTPUT_DIR := ./build
endif

EXE := $(OUTPUT_DIR)/genpasswd
all: $(EXE)

$(EXE):
	cmake -S . -B $(OUTPUT_DIR)
	make -C $(OUTPUT_DIR)

install: $(EXE)
	cmake --install $(OUTPUT_DIR)

clean:
	rm -rf $(OUTPUT_DIR)
