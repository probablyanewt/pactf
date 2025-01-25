EXAMPLEDIRS:= $(wildcard ./examples/*)

install: uninstall
	cp ./pactf.h /usr/include/pactf.h

link: uninstall
	ln -sr pactf.h /usr/include/pactf.h

uninstall:
	rm -f /usr/include/pactf.h

test: $(EXAMPLEDIRS)
$(EXAMPLEDIRS):
	$(MAKE) run_tests --no-print-directory -C $@

.PHONY: test $(EXAMPLEDIRS)
.SILENT: test $(EXAMPLEDIRS)
