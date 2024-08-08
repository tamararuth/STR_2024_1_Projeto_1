CC = gcc
CFLAGS = -Wall -pthread

all: projeto run

projeto: projeto.c
	$(CC) $(CFLAGS) -o projeto projeto.c

run: 
	./projeto

clean:
	rm -f projeto

help:
	@echo " ----------------------- Sistemas em Tempo Real P1 -------------------------- "
	@echo " all - Cria um arquivo Executavel com base no código 'projeto.c' e o Executa "
	@echo " projeto - Cria um arquivo Executavel com base no código 'projeto.c' "
	@echo " clean - Exclui o arquivo executavel gerado "
	@echo " ---------------------------------------------------------------------------- "
