#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PEAO1 0
#define PEAO2 1
#define PEAO3 2
#define PEAO4 3
#define DIM 100

int main(int argc, char *argv[]) {

  list tabuleiro;
  node *novo_no, *k, *l;
  int numeroLido, vetorValores[DIM], pos;
  int numCasas = 0, count, valorDados = 0, modo = 0, rows = 0, cols = 0,
      vezJogador = 0;
  int jogA = 0, jogB = 0, jogC = 0, jogD = 0, jogW = 0, jogX = 0, jogY = 0,
      jogZ = 0;
  char valor, ficheiro[DIM];

  FILE *fp;

  srand(1);
  if (argc >= 5) {
    modo = atoi(argv[1]);
    rows = atoi(argv[2]);
    cols = atoi(argv[3]);
    strcpy(ficheiro, argv[4]);
  } else if (argc >= 4) {
    modo = atoi(argv[1]);
    rows = atoi(argv[2]);
    cols = atoi(argv[3]);
  } else if (argc >= 3) {
    modo = atoi(argv[1]);
    rows = atoi(argv[2]);
  } else if (argc >= 2) {
    modo = atoi(argv[1]);
  }

  if ((ficheiro[0])) {
    fp = fopen(ficheiro, "r");
    if (fp == NULL) {
      printf("fich %s Ficheiro nao encontrado ERRO: Parametros invalidos",
             ficheiro);
      exit(0);
    }
    pos = 0;
    while (fscanf(fp, "%d", &numeroLido) != EOF) {

      vetorValores[pos] = numeroLido + 1;
      pos++;
      if (pos >= DIM)
        break;
    }

    fclose(fp);
  }

  
  if (modo == 0 || modo == 1) {

    if (rows >= 3 || rows % 2 == 1) {

      if (cols > 4) {

      } else {
        cols = 7;
      }
    } else {
      rows = 3;
      cols = 7;
    }
  } else {
    modo = 0;
    rows = 3;
    cols = 7;
  }

  numCasas = 2 * (cols + rows - 2);

  tabuleiro.head = NULL;
  tabuleiro.tail = NULL;
  tabuleiro.length = numCasas;

  for (int i = 1; i <= numCasas; i++) {
    novo_no = (node *)malloc(sizeof(node));

    if (i == 1) {

      novo_no->item.casaSegura = TRUE;

      novo_no->item.jogador_peao[JOGADOR1][PEAO1] = TRUE;
      novo_no->item.jogador_peao[JOGADOR1][PEAO2] = TRUE;
      novo_no->item.jogador_peao[JOGADOR1][PEAO3] = TRUE;
      novo_no->item.jogador_peao[JOGADOR1][PEAO4] = TRUE;

      novo_no->item.jogador_peao[JOGADOR2][PEAO1] = FALSE;
      novo_no->item.jogador_peao[JOGADOR2][PEAO2] = FALSE;
      novo_no->item.jogador_peao[JOGADOR2][PEAO3] = FALSE;
      novo_no->item.jogador_peao[JOGADOR2][PEAO4] = FALSE;

    } else if (i == (cols + rows - 1)) {

      novo_no->item.casaSegura = TRUE;

      novo_no->item.jogador_peao[JOGADOR1][PEAO1] = FALSE;
      novo_no->item.jogador_peao[JOGADOR1][PEAO2] = FALSE;
      novo_no->item.jogador_peao[JOGADOR1][PEAO3] = FALSE;
      novo_no->item.jogador_peao[JOGADOR1][PEAO4] = FALSE;

      novo_no->item.jogador_peao[JOGADOR2][PEAO1] = TRUE;
      novo_no->item.jogador_peao[JOGADOR2][PEAO2] = TRUE;
      novo_no->item.jogador_peao[JOGADOR2][PEAO3] = TRUE;
      novo_no->item.jogador_peao[JOGADOR2][PEAO4] = TRUE;

    } else {

      int l;

      for (l = 0; l < DIM; l++) {
        if (vetorValores[l] == i) {
          novo_no->item.casaSegura = TRUE;
          break;
        }
      }

      if (l == DIM - 1) {
        novo_no->item.casaSegura = FALSE;
      }

      novo_no->item.jogador_peao[JOGADOR1][PEAO1] = FALSE;
      novo_no->item.jogador_peao[JOGADOR1][PEAO2] = FALSE;
      novo_no->item.jogador_peao[JOGADOR1][PEAO3] = FALSE;
      novo_no->item.jogador_peao[JOGADOR1][PEAO4] = FALSE;

      novo_no->item.jogador_peao[JOGADOR2][PEAO1] = FALSE;
      novo_no->item.jogador_peao[JOGADOR2][PEAO2] = FALSE;
      novo_no->item.jogador_peao[JOGADOR2][PEAO3] = FALSE;
      novo_no->item.jogador_peao[JOGADOR2][PEAO4] = FALSE;
    }
    if (tabuleiro.head == NULL) {

      tabuleiro.head = novo_no;

    } else {
      node *i;
      for (i = tabuleiro.head; i->next != NULL; i = i->next)
        ;
      i->next = novo_no;
      tabuleiro.tail = novo_no;
    }
  }

  tabuleiro.head->next->next->next->next->next->next->next->item.casaSegura =
      FALSE;

  if(ficheiro[0]){
    printf("fich %s", ficheiro);
  }
  boardPrint(rows, cols, tabuleiro, modo);

  puts("+------------------------------------+");
  puts("|         Nao Te Constipes           |");
  puts("+------------------------------------+");
  puts("| <id do peao> (abcd, xyzw)          |");
  puts("| s - sair                           |");
  puts("| h - imprimir menu                  |");
  puts("+------------------------------------+");
  puts("------ Jogador 1 ------");
  valorDados = rolldice(2);

  do {

    if (vezJogador % 2 == 0 &&
        (valor == 'a' || valor == 'b' || valor == 'c' || valor == 'd' ||
         valor == 'x' || valor == 'y' || valor == 'z' || valor == 'w')) {
      puts("------ Jogador 1 ------");

    } else if (vezJogador % 2 == 1 &&
               (valor == 'a' || valor == 'b' || valor == 'c' || valor == 'd' ||
                valor == 'x' || valor == 'y' || valor == 'z' || valor == 'w')) {
      puts("------ Jogador 2 ------");
    }

    printf("Jogador lancou dados com valor %i\n > ", valorDados);

    if (scanf("%s", &valor)) {
    };

    if ((valor == 'a' || valor == 'b' || valor == 'c' || valor == 'd') &&
        vezJogador % 2 != 0) {
      valor = 'w';
    } else if ((valor == 'z' || valor == 'x' || valor == 'y' || valor == 'w') &&
               vezJogador % 2 != 1) {
      valor = 'a';
    }

    switch (valor) {

    case 's':
      puts("Fim do jogo");
      return 0;

    case 'h':
      puts("+------------------------------------+");
      puts("|         Nao Te Constipes           |");
      puts("+------------------------------------+");
      puts("| <id do peao> (abcd, xyzw)          |");
      puts("| s - sair                           |");
      puts("| h - imprimir menu                  |");
      puts("+------------------------------------+");

      if (vezJogador % 2 == 0) {
        puts("------ Jogador 1 ------");
      } else if (vezJogador % 2 == 1) {
        puts("------ Jogador 2 ------");
      }

      break;

    case 'a':
      if (jogA ==
          0) { // meter na 1º jogada se ele passar o adv ele volta ao inicio
        tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO1] = FALSE;
        count = 0;

        k = tabuleiro.head;

        while (valorDados > count) {
          k = k->next;
          count++;
        }

        k->item.jogador_peao[JOGADOR1][PEAO1] = TRUE;

        boardPrint(rows, cols, tabuleiro, modo);

        jogA++;

      } else {

        for (k = tabuleiro.head;
             k->next->item.jogador_peao[JOGADOR1][PEAO1] != TRUE; k = k->next)
          ;

        k->next->item.jogador_peao[JOGADOR1][PEAO1] = FALSE;
        count = 0;

        while (valorDados >= count) {
          if (k->next == NULL) {
            k = tabuleiro.head;
            k->item.jogador_peao[JOGADOR1][PEAO1] = WIN;

            break;
          }

          if (k->next->item.casaSegura == FALSE) {

            if (k->next->item.jogador_peao[JOGADOR2][PEAO1] == TRUE) {
              k->next->item.jogador_peao[JOGADOR2][PEAO1] = FALSE;
              tabuleiro.head->next->next->next->next->next->next->next->next
                  ->item.jogador_peao[JOGADOR2][PEAO1] = TRUE;
              jogW = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR2][PEAO2] == TRUE) {
              k->next->item.jogador_peao[JOGADOR2][PEAO2] = FALSE;
              tabuleiro.head->next->next->next->next->next->next->next->next
                  ->item.jogador_peao[JOGADOR2][PEAO2] = TRUE;
              jogX = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR2][PEAO3] == TRUE) {
              k->next->item.jogador_peao[JOGADOR2][PEAO3] = FALSE;
              tabuleiro.head->next->next->next->next->next->next->next->next
                  ->item.jogador_peao[JOGADOR2][PEAO3] = TRUE;
              jogY = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR2][PEAO4] == TRUE) {
              k->next->item.jogador_peao[JOGADOR2][PEAO4] = FALSE;
              tabuleiro.head->next->next->next->next->next->next->next->next
                  ->item.jogador_peao[JOGADOR2][PEAO4] = TRUE;
              jogZ = 0;
            }
          }

          if (k->next != NULL) {
            k = k->next;
            count++;
          }
        }

        if (k != tabuleiro.head) {
          k->item.jogador_peao[JOGADOR1][PEAO1] = TRUE;
        }

        boardPrint(rows, cols, tabuleiro, modo);

        jogA++;
      }

      valorDados = rolldice(2);
      vezJogador++;

      break;

    case 'b':
      if (jogB == 0) {
        tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO2] = FALSE;
        count = 0;

        k = tabuleiro.head;

        while (valorDados > count) {
          k = k->next;
          count++;
        }

        k->item.jogador_peao[JOGADOR1][PEAO2] = TRUE;

        boardPrint(rows, cols, tabuleiro, modo);

        jogB++;
      } else {

        for (k = tabuleiro.head;
             k->next->item.jogador_peao[JOGADOR1][PEAO2] != TRUE; k = k->next)
          ;

        k->next->item.jogador_peao[JOGADOR1][PEAO2] = FALSE;
        count = 0;

        while (valorDados >= count) {
          if (k->next == NULL) {
            k = tabuleiro.head;
            k->item.jogador_peao[JOGADOR1][PEAO2] = WIN;

            break;
          }

          if (k->next->item.casaSegura == FALSE) {

            if (k->next->item.jogador_peao[JOGADOR2][PEAO1] == TRUE) {
              k->next->item.jogador_peao[JOGADOR2][PEAO1] = FALSE;
              tabuleiro.head->next->next->next->next->next->next->next->next
                  ->item.jogador_peao[JOGADOR2][PEAO1] = TRUE;
              jogW = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR2][PEAO2] == TRUE) {
              k->next->item.jogador_peao[JOGADOR2][PEAO2] = FALSE;
              tabuleiro.head->next->next->next->next->next->next->next->next
                  ->item.jogador_peao[JOGADOR2][PEAO2] = TRUE;
              jogX = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR2][PEAO3] == TRUE) {
              k->next->item.jogador_peao[JOGADOR2][PEAO3] = FALSE;
              tabuleiro.head->next->next->next->next->next->next->next->next
                  ->item.jogador_peao[JOGADOR2][PEAO3] = TRUE;
              jogY = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR2][PEAO4] == TRUE) {
              k->next->item.jogador_peao[JOGADOR2][PEAO4] = FALSE;
              tabuleiro.head->next->next->next->next->next->next->next->next
                  ->item.jogador_peao[JOGADOR2][PEAO4] = TRUE;
              jogZ = 0;
            }
          }

          if (k->next != NULL) {
            k = k->next;
            count++;
          }
        }

        if (k != tabuleiro.head) {
          k->item.jogador_peao[JOGADOR1][PEAO2] = TRUE;
        }

        boardPrint(rows, cols, tabuleiro, modo);

        jogB++;
      }

      valorDados = rolldice(2);
      vezJogador++;

      break;

    case 'c':

      if (jogC == 0) {
        tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO3] = FALSE;
        count = 0;

        k = tabuleiro.head;

        while (valorDados > count) {
          k = k->next;
          count++;
        }

        k->item.jogador_peao[JOGADOR1][PEAO3] = TRUE;

        boardPrint(rows, cols, tabuleiro, modo);

        jogC++;
      } else {

        for (k = tabuleiro.head;
             k->next->item.jogador_peao[JOGADOR1][PEAO3] != TRUE; k = k->next)
          ;

        k->next->item.jogador_peao[JOGADOR1][PEAO3] = FALSE;
        count = 0;

        while (valorDados >= count) {
          if (k->next == NULL) {
            k = tabuleiro.head;
            k->item.jogador_peao[JOGADOR1][PEAO3] = WIN;

            break;
          }

          if (k->next->item.casaSegura == FALSE) {

            if (k->next->item.jogador_peao[JOGADOR2][PEAO1] == TRUE) {
              k->next->item.jogador_peao[JOGADOR2][PEAO1] = FALSE;
              tabuleiro.head->next->next->next->next->next->next->next->next
                  ->item.jogador_peao[JOGADOR2][PEAO1] = TRUE;
              jogW = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR2][PEAO2] == TRUE) {
              k->next->item.jogador_peao[JOGADOR2][PEAO2] = FALSE;
              tabuleiro.head->next->next->next->next->next->next->next->next
                  ->item.jogador_peao[JOGADOR2][PEAO2] = TRUE;
              jogX = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR2][PEAO3] == TRUE) {
              k->next->item.jogador_peao[JOGADOR2][PEAO3] = FALSE;
              tabuleiro.head->next->next->next->next->next->next->next->next
                  ->item.jogador_peao[JOGADOR2][PEAO3] = TRUE;
              jogY = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR2][PEAO4] == TRUE) {
              k->next->item.jogador_peao[JOGADOR2][PEAO4] = FALSE;
              tabuleiro.head->next->next->next->next->next->next->next->next
                  ->item.jogador_peao[JOGADOR2][PEAO4] = TRUE;
              jogZ = 0;
            }
          }

          if (k->next != NULL) {
            k = k->next;
            count++;
          }
        }

        if (k != tabuleiro.head) {
          k->item.jogador_peao[JOGADOR1][PEAO3] = TRUE;
        }

        boardPrint(rows, cols, tabuleiro, modo);

        jogC++;
      }

      valorDados = rolldice(2);
      vezJogador++;

      break;

    case 'd':

      if (jogD == 0) {
        tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO4] = FALSE;
        count = 0;

        k = tabuleiro.head;

        while (valorDados > count) {
          k = k->next;
          count++;
        }

        k->item.jogador_peao[JOGADOR1][PEAO4] = TRUE;

        boardPrint(rows, cols, tabuleiro, modo);

        jogD++;
      } else {

        for (k = tabuleiro.head;
             k->next->item.jogador_peao[JOGADOR1][PEAO4] != TRUE; k = k->next)
          ;

        k->next->item.jogador_peao[JOGADOR1][PEAO4] = FALSE;
        count = 0;

        while (valorDados >= count) {
          if (k->next == NULL) {
            k = tabuleiro.head;
            k->item.jogador_peao[JOGADOR1][PEAO4] = WIN;

            break;
          }

          if (k->next->item.casaSegura == FALSE) {

            if (k->next->item.jogador_peao[JOGADOR2][PEAO1] == TRUE) {
              k->next->item.jogador_peao[JOGADOR2][PEAO1] = FALSE;
              tabuleiro.head->next->next->next->next->next->next->next->next
                  ->item.jogador_peao[JOGADOR2][PEAO1] = TRUE;
              jogW = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR2][PEAO2] == TRUE) {
              k->next->item.jogador_peao[JOGADOR2][PEAO2] = FALSE;
              tabuleiro.head->next->next->next->next->next->next->next->next
                  ->item.jogador_peao[JOGADOR2][PEAO2] = TRUE;
              jogX = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR2][PEAO3] == TRUE) {
              k->next->item.jogador_peao[JOGADOR2][PEAO3] = FALSE;
              tabuleiro.head->next->next->next->next->next->next->next->next
                  ->item.jogador_peao[JOGADOR2][PEAO3] = TRUE;
              jogY = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR2][PEAO4] == TRUE) {
              k->next->item.jogador_peao[JOGADOR2][PEAO4] = FALSE;
              tabuleiro.head->next->next->next->next->next->next->next->next
                  ->item.jogador_peao[JOGADOR2][PEAO4] = TRUE;
              jogZ = 0;
            }
          }

          if (k->next != NULL) {
            k = k->next;
            count++;
          }
        }

        if (k != tabuleiro.head) {
          k->item.jogador_peao[JOGADOR1][PEAO4] = TRUE;
        }

        boardPrint(rows, cols, tabuleiro, modo);

        jogD++;
      }

      valorDados = rolldice(2);
      vezJogador++;

      break;

    case 'w':
      if (jogW == 0) {
        for (k = tabuleiro.head;
             k->next->item.jogador_peao[JOGADOR2][PEAO1] != TRUE; k = k->next)
          ;
        k->next->item.jogador_peao[JOGADOR2][PEAO1] = FALSE;
        count = 0;

        while (valorDados > count) {
          k = k->next;
          count++;
        }

        k->next->item.jogador_peao[JOGADOR2][PEAO1] = TRUE;

        boardPrint(rows, cols, tabuleiro, modo);

        jogW++;
      } else {

        for (k = tabuleiro.head;
             k->next->item.jogador_peao[JOGADOR2][PEAO1] != TRUE; k = k->next)
          ;

        k->next->item.jogador_peao[JOGADOR2][PEAO1] = FALSE;
        count = 0;

        while (valorDados >= count) {

          if (k->next == NULL) {
            k = tabuleiro.head;
          }

          l = tabuleiro.head->next->next->next->next->next->next->next->next;
          if (k == l) {
            l->item.jogador_peao[JOGADOR2][PEAO1] = WIN;
            break;
          }

          if (k->next->item.casaSegura == FALSE) {

            if (k->next->item.jogador_peao[JOGADOR1][PEAO1] == TRUE) {
              k->next->item.jogador_peao[JOGADOR1][PEAO1] = FALSE;
              tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO1] = TRUE;
              jogA = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR1][PEAO2] == TRUE) {
              k->next->item.jogador_peao[JOGADOR1][PEAO2] = FALSE;
              tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO2] = TRUE;
              jogB = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR1][PEAO3] == TRUE) {
              k->next->item.jogador_peao[JOGADOR1][PEAO3] = FALSE;
              tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO3] = TRUE;
              jogC = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR1][PEAO4] == TRUE) {
              k->next->item.jogador_peao[JOGADOR1][PEAO4] = FALSE;
              tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO4] = TRUE;
              jogD = 0;
            }
          }

          if (k->next != NULL) {
            k = k->next;
            count++;
          }
        }

        if (k !=
            tabuleiro.head->next->next->next->next->next->next->next->next) {
          k->item.jogador_peao[JOGADOR2][PEAO1] = TRUE;
        }

        boardPrint(rows, cols, tabuleiro, modo);

        jogW++;
      }

      valorDados = rolldice(2);
      vezJogador++;

      break;

    case 'x':
      if (jogX == 0) {
        for (k = tabuleiro.head;
             k->next->item.jogador_peao[JOGADOR2][PEAO2] != TRUE; k = k->next)
          ;
        k->next->item.jogador_peao[JOGADOR2][PEAO2] = FALSE;
        count = 0;

        while (valorDados > count) {
          k = k->next;
          count++;
        }

        k->next->item.jogador_peao[JOGADOR2][PEAO2] = TRUE;

        boardPrint(rows, cols, tabuleiro, modo);

        jogX++;
      } else {

        for (k = tabuleiro.head;
             k->next->item.jogador_peao[JOGADOR2][PEAO2] != TRUE; k = k->next)
          ;

        k->next->item.jogador_peao[JOGADOR2][PEAO2] = FALSE;
        count = 0;

        while (valorDados >= count) {

          if (k->next == NULL) {
            k = tabuleiro.head;
          }

          l = tabuleiro.head->next->next->next->next->next->next->next->next;
          if (k == l) {
            l->item.jogador_peao[JOGADOR2][PEAO2] = WIN;
            break;
          }

          if (k->next->item.casaSegura == FALSE) {

            if (k->next->item.jogador_peao[JOGADOR1][PEAO1] == TRUE) {
              k->next->item.jogador_peao[JOGADOR1][PEAO1] = FALSE;
              tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO1] = TRUE;
              jogA = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR1][PEAO2] == TRUE) {
              k->next->item.jogador_peao[JOGADOR1][PEAO2] = FALSE;
              tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO2] = TRUE;
              jogB = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR1][PEAO3] == TRUE) {
              k->next->item.jogador_peao[JOGADOR1][PEAO3] = FALSE;
              tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO3] = TRUE;
              jogC = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR1][PEAO4] == TRUE) {
              k->next->item.jogador_peao[JOGADOR1][PEAO4] = FALSE;
              tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO4] = TRUE;
              jogD = 0;
            }
          }

          if (k->next != NULL) {
            k = k->next;
            count++;
          }
        }

        if (k !=
            tabuleiro.head->next->next->next->next->next->next->next->next) {
          k->item.jogador_peao[JOGADOR2][PEAO2] = TRUE;
        }

        boardPrint(rows, cols, tabuleiro, modo);

        jogX++;
      }

      valorDados = rolldice(2);
      vezJogador++;

      break;

    case 'y':
      if (jogY == 0) {
        for (k = tabuleiro.head;
             k->next->item.jogador_peao[JOGADOR2][PEAO3] != TRUE; k = k->next)
          ;
        k->next->item.jogador_peao[JOGADOR2][PEAO3] = FALSE;
        count = 0;

        while (valorDados > count) {
          k = k->next;
          count++;
        }

        k->next->item.jogador_peao[JOGADOR2][PEAO3] = TRUE;

        boardPrint(rows, cols, tabuleiro, modo);

        jogY++;
      } else {

        for (k = tabuleiro.head;
             k->next->item.jogador_peao[JOGADOR2][PEAO3] != TRUE; k = k->next)
          ;

        k->next->item.jogador_peao[JOGADOR2][PEAO3] = FALSE;
        count = 0;

        while (valorDados >= count) {

          if (k->next == NULL) {
            k = tabuleiro.head;
          }

          l = tabuleiro.head->next->next->next->next->next->next->next->next;
          if (k == l) {
            l->item.jogador_peao[JOGADOR2][PEAO3] = WIN;
            break;
          }

          if (k->next->item.casaSegura == FALSE) {

            if (k->next->item.jogador_peao[JOGADOR1][PEAO1] == TRUE) {
              k->next->item.jogador_peao[JOGADOR1][PEAO1] = FALSE;
              tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO1] = TRUE;
              jogA = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR1][PEAO2] == TRUE) {
              k->next->item.jogador_peao[JOGADOR1][PEAO2] = FALSE;
              tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO2] = TRUE;
              jogB = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR1][PEAO3] == TRUE) {
              k->next->item.jogador_peao[JOGADOR1][PEAO3] = FALSE;
              tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO3] = TRUE;
              jogC = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR1][PEAO4] == TRUE) {
              k->next->item.jogador_peao[JOGADOR1][PEAO4] = FALSE;
              tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO4] = TRUE;
              jogD = 0;
            }
          }

          if (k->next != NULL) {
            k = k->next;
            count++;
          }
        }

        if (k !=
            tabuleiro.head->next->next->next->next->next->next->next->next) {
          k->item.jogador_peao[JOGADOR2][PEAO3] = TRUE;
        }

        boardPrint(rows, cols, tabuleiro, modo);

        jogY++;
      }

      valorDados = rolldice(2);
      vezJogador++;

      break;

    case 'z':
      if (jogZ == 0) {
        for (k = tabuleiro.head;
             k->next->item.jogador_peao[JOGADOR2][PEAO4] != TRUE; k = k->next)
          ;
        k->next->item.jogador_peao[JOGADOR2][PEAO4] = FALSE;
        count = 0;

        while (valorDados > count) {
          k = k->next;
          count++;
        }

        k->next->item.jogador_peao[JOGADOR2][PEAO4] = TRUE;

        boardPrint(rows, cols, tabuleiro, modo);

        jogZ++;

      } else {

        for (k = tabuleiro.head;
             k->next->item.jogador_peao[JOGADOR2][PEAO4] != TRUE; k = k->next)
          ;

        k->next->item.jogador_peao[JOGADOR2][PEAO4] = FALSE;
        count = 0;

        while (valorDados >= count) {

          if (k->next == NULL) {
            k = tabuleiro.head;
          }

          l = tabuleiro.head->next->next->next->next->next->next->next->next;
          if (k == l) {
            l->item.jogador_peao[JOGADOR2][PEAO4] = WIN;
            break;
          }

          if (k->next->item.casaSegura == FALSE) {

            if (k->next->item.jogador_peao[JOGADOR1][PEAO1] == TRUE) {
              k->next->item.jogador_peao[JOGADOR1][PEAO1] = FALSE;
              tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO1] = TRUE;
              jogA = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR1][PEAO2] == TRUE) {
              k->next->item.jogador_peao[JOGADOR1][PEAO2] = FALSE;
              tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO2] = TRUE;
              jogB = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR1][PEAO3] == TRUE) {
              k->next->item.jogador_peao[JOGADOR1][PEAO3] = FALSE;
              tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO3] = TRUE;
              jogC = 0;
            }
            if (k->next->item.jogador_peao[JOGADOR1][PEAO4] == TRUE) {
              k->next->item.jogador_peao[JOGADOR1][PEAO4] = FALSE;
              tabuleiro.head->item.jogador_peao[JOGADOR1][PEAO4] = TRUE;
              jogD = 0;
            }
          }

          if (k->next != NULL) {
            k = k->next;
            count++;
          }
        }

        if (k !=
            tabuleiro.head->next->next->next->next->next->next->next->next) {
          k->item.jogador_peao[JOGADOR2][PEAO4] = TRUE;
        }

        boardPrint(rows, cols, tabuleiro, modo);

        jogZ++;
      }

      valorDados = rolldice(2);
      vezJogador++;

      break;

    default:
      puts("Comando Invalido");

      if (vezJogador % 2 == 0) {
        puts("------ Jogador 1 ------");
      } else if (vezJogador % 2 == 1) {
        puts("------ Jogador 2 ------");
      }

      break;
    }

  } while (valor != 's');

  exit(0);
}