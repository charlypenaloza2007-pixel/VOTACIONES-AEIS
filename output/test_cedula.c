#define main harness_main
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
bool validarCedulaEcuatoriana(const char *cedula, char *mensajeError, size_t tamMensaje);
int harness_main(void) {
    char msg[120];
    bool ok1 = validarCedulaEcuatoriana("1712345678", msg, sizeof(msg));
    bool ok2 = validarCedulaEcuatoriana("1712345670", msg, sizeof(msg));
    printf("ok1=%d ok2=%d msg=%s\n", ok1, ok2, msg);
    return 0;
}
