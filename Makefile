all:
	cd src; make;
	cd src/test; make;

clean:
	cd src; make clean;
	cd src/test; make clean;

install:
	cd src/test; make install;