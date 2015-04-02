all: common engine tools

common:
	cd Common; make

engine:
	cd Engine; make

tools:
	cd Tools; make

clean:
	cd Common; make clean
	cd Engine; make clean
	cd Tools; make clean

.PHONY: common engine tools
