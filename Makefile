# Root Makefile to build all days or specific day

.PHONY: all clean day%

all:
	@for dir in */; do \
		if [ -f "$$dir/Makefile" ]; then \
			echo "Building $$dir..."; \
			$(MAKE) -C "$$dir" || exit 1; \
		fi \
	done

day%:
	$(MAKE) -C $@

clean:
	@for dir in */; do \
		if [ -f "$$dir/Makefile" ]; then \
			$(MAKE) -C "$$dir" clean; \
		fi \
	done
