#ifndef CORES_H
#define CORES_H

/* =========================================================
   cores.h  –  macros de cor em código ANSI + inicialização Win32
   ---------------------------------------------------------
   No Windows, ANSI só funciona após habilitar o modo virtual
   no console (VT_PROCESSING). Chame cores_inicializar() em
   main() antes de qualquer printf colorido.
   ========================================================= */

#ifdef _WIN32
  #include <windows.h>
#endif

/* --- códigos ANSI --- */
#define COR_RESET    "\033[0m"
#define COR_AMARELO  "\033[33m"
#define COR_AZUL     "\033[34m"
#define COR_VIOLETA  "\033[35m"
#define COR_LARANJA  "\033[38;5;208m"   /* 256-color: laranja */
#define COR_VERDE    "\033[32m"
#define COR_VERMELHO "\033[31m"
#define COR_CIANO    "\033[36m"
#define COR_BRANCO   "\033[97m"
#define COR_NEGRITO  "\033[1m"

/* Habilita sequências ANSI no terminal Windows.
   Em sistemas POSIX não faz nada (já funciona por padrão). */
static inline void cores_inicializar(void) {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

#endif /* CORES_H */
