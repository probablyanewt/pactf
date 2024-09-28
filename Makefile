install: uninstall
	cp ./pactf.h /usr/include/pactf.h

link: uninstall
	ln -sr pactf.h /usr/include/pactf.h

uninstall:
	rm -f /usr/include/pactf.h
