all: engine tools

engine:
	cd Engine; make

tools:
	cd Tools; make

clean:
	cd Engine; make clean
	cd Tools; make clean

.PHONY: engine tools
