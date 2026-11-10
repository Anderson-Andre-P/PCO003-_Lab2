# PCO003 – Lab 2: Criando seu primeiro kernel

```
parte2/   itens 1 e 2: kernel round-robin (fila circular) e 4 processos
parte3/   item 3: kernel com campo priority e escalonamento por prioridade
```

Antes de compilar, edite `MEU_NOME` e `MINHA_MATRICULA` no `main.c` de cada parte.

## Compilar e executar

```sh
cd parte2   # ou parte3
cc -Wall -o lab main.c kernel.c
./lab | head -n 20   # o kernelLoop() nunca termina; use Ctrl+C ou head
```

## Saída da parte 2 (round-robin)

```
Nome: ...
Matricula: ...
UNIFEI
PCO003 - execucao 1
UNIFEI
PCO003 - execucao 2
...
```

Os processos 1 e 2 retornam `SUCCESS`, rodam uma vez e saem da fila. Os processos 3 e 4
retornam `REPEAT`, voltam para o fim da fila e se alternam para sempre.

## Parte 3: prioridades 4 (nome), 3 (matrícula), 2 (UNIFEI), 1 (PCO003)

Saída:

```
Nome: ...
Matricula: ...
UNIFEI
UNIFEI
UNIFEI
...            (PCO003 nunca aparece)
```

### O que aconteceu

1. A fila começa com `[Nome(4), Matr(3), UNIFEI(2), PCO003(1)]`. O kernel escolhe Nome (4),
   executa, e como ele retorna `SUCCESS` ele sai da fila.
2. Depois Matrícula (3) é o de maior prioridade: executa e sai.
3. Restam `[UNIFEI(2), PCO003(1)]`. UNIFEI tem a maior prioridade, executa e retorna `REPEAT`,
   então volta para o fim da fila: `[PCO003(1), UNIFEI(2)]`.
4. Na rodada seguinte o kernel procura de novo o de maior prioridade. Ainda é UNIFEI, que é
   trocado com o primeiro da fila e executado outra vez. Isso se repete indefinidamente.

O processo PCO003 **nunca é executado**. Isso é **starvation** (inanição): um escalonador
por prioridade fixa (aqui cooperativo), sem envelhecimento (*aging*), deixa um processo de alta
prioridade que sempre pede reexecução monopolizar a CPU. Colocar o processo no fim da fila
não ajuda, porque a escolha é feita pela prioridade e não pela posição na fila. Para corrigir,
dá para aumentar a prioridade de quem espera (*aging*), reduzir a prioridade de quem acabou de
rodar, ou usar round-robin entre processos de mesma prioridade.
