
# Projeto 1 - Sistemas em Tempo Real

---

## Descrição Geral

    O projeto consiste em um programa na linguguagem C, executado em multithread.
    Utilizando a Lógica de semaforos para controlara execução do programa

SO:
    Red Hat Enterprise Linux 8 (Red Hat 8.5.0-22)

gcc version:
    8.5.0 20210514

Bibliotecas:
    stdio.h
    stdlib.h
    pthread.h
    semaphore.h
    unistd.h
    time.h

### Barbeiros

Função destinada para implementar lógica de "consumidor", ele tem como base de funcionamento
"dormir" caso não haja nenhuma pessoa para ser atendida, acordar ao chegar algum cliente 
e atende-lo com base em um tempo aleatório.

### Clientes

Os Clientes serão gerados em tempos aleatórios e ao chegarem ao salão ficaram esperando na cadeira
de espera até que um dos barbeiros acorde para atendê-lo. Ao cliente chegar e não ter nenhuma cadeira vaga
ele irá sairá do salão sem nada ser usado. Ele implementa a lógica de um "produtor".

### Main (Barbearia)

A barbearia terá 5 cadeiras de espera, 3 barbeiros e 3 cadeiras para atendimento ao cliente.
A função main tem o papel de criar todas essas estuturas, alem de criar os semaforos visíveis.

## Desenvolvedores

    Tulio Tavares   (tulio.tavares@ee.ufcg.edu.br)
    Tamara Ruth     (tamara.santos@ee.ufcg.edu.br)
    Matheus Lucas   (matheuslucas.farias@ee.ufcg.edu.br)


by Túlio Tavares
