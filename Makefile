EXAMPLEDIRS:= $(wildcard ./examples/*)

install: uninstall
	cp ./pactf.h /usr/include/pactf.h

link: uninstall
	ln -sr pactf.h /usr/include/pactf.h

uninstall:
	rm -f /usr/include/pactf.h

run_all_examples:
	./scripts/run_all_examples.sh

test: $(EXAMPLEDIRS)
$(EXAMPLEDIRS):
	$(MAKE) run_tests --no-print-directory -C $@

.PHONY: test $(EXAMPLEDIRS)
.SILENT: test $(EXAMPLEDIRS)
