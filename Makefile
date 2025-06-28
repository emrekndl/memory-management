CC        ?= gcc
CFLAGS     = -std=c99 -Wall -I./munit
BIN_DIR    = bin
CHAPTERS   = 1-basics 2-structs 3-pointers 4-enums 5-unions \
             6-stack-heap 7-adv-pointers 8-stack-ds \
             9-objects 10-refcounting-gc 11-mark-sweep-gc

.PHONY: all build run clean

# Default: build all chapters
all: build

# "make build" builds all chapters;
# "make build <chapter>" builds only that chapter
build:
	@goals=$(filter-out build,$(MAKECMDGOALS)); \
	if [ -z "$$goals" ]; then \
	  chapters="$(CHAPTERS)"; \
	else \
	  chapters="$$goals"; \
	fi; \
	for c in $$chapters; do \
	  echo "Building: $$c"; \
	  mkdir -p $(BIN_DIR); \
	  $(CC) $(CFLAGS) -o $(BIN_DIR)/$$c $$c/main.c $$c/exercise*.c munit/munit.c; \
	done

# "make run <chapter>" compiles (if needed) and runs that chapter
run:
	@goal=$(filter-out run,$(MAKECMDGOALS)); \
	if [ -z "$$goal" ]; then \
	  echo "Usage: make run <chapter>"; \
	  exit 1; \
	fi; \
	echo "Running: $$goal"; \
	$(BIN_DIR)/$$goal

clean:
	@echo "Cleaning binaries..."
	rm -rf $(BIN_DIR)

# for warnings 
%:
	@:
