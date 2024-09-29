install: uninstall
	cp ./pactf.h /usr/include/pactf.h

link: uninstall
	ln -sr pactf.h /usr/include/pactf.h

uninstall:
	rm -f /usr/include/pactf.h

run_all_examples:
	./scripts/run_all_examples.sh
