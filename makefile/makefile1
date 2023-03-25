# variabili
A:=hello $(LATER)
B=hello $(LATER)
LATER=world

# $@ nome del target
# $^ lista prerequisiti
# $< nome prerequisito 1 (shiftabile immagino)
target:
	echo $(A)
	echo $(B)
	echo $@
	echo $^
	echo $<


# funzioni speciali
# eval crea nuove regole dinamicamente
# $(eval LATER+= pollo)
# shell ottiene l'output di un comando shell
# X=$(shell pwd)