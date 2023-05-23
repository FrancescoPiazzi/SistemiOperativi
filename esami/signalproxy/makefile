main:
	@-[ -f ${FILE} ] || (touch ${FILE}; echo "start" > ${FILE})
	@gcc main.c -o signalProxy.out

clean:
	@-[ -f ${FILE} ] && rm ${FILE}
	@-[ -f signalProxy.out ] && rm signalProxy.out
