all: SignalProxy ${FILE}


SignalProxy: main.c
	@gcc main.c -o SignalProxy


${FILE}:
	@touch ${FILE}
	@echo "start" > ${FILE}