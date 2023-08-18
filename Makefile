LIBS = -L ./lib64 
subsystem:
	$(MAKE) -C src
	$(MAKE) install -C src
	$(MAKE) -C examples
