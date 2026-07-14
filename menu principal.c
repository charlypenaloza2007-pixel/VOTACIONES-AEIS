#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

// Estructuras para el manejo de elecciones y resultados
typedef struct {
    char nombre[50];
    int votos;
} Resultado;

typedef struct {
    char partido[50];
    char presidente[50];
    char cedula[15];
    char vicepresidente[50];
    char campana[50];
} Partido;

// Variables globales para el control del periodo y candidatos activos
char periodo[10] = " ";
Partido candidatosGlobales[5];

// Construye la ruta absoluta para los archivos en el escritorio de carlo
void rutaArchivo(char ruta[], char nombre[], int numero)
{
    sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\%s%d.txt", nombre, numero);
}

// Busca el siguiente índice disponible para no sobreescribir elecciones anteriores
int obtenerNuevoArchivo()
{
    FILE *archivo;
    char ruta[150];
    int numero = 0;

    while(1)
    {
        sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\candidatos%d.txt", numero);
        archivo = fopen(ruta, "r");
        if(archivo == NULL)
            return numero; // Retorna el número si el archivo no existe
        fclose(archivo);
        numero++;
    }
}

// Cuenta la cantidad de procesos electorales registrados históricamente
int contarElecciones()
{
    FILE *archivo;
    char nombreArchivo[250];
    int contador = 0;
    int numero = 0;
    while (1)
    {
        sprintf(nombreArchivo, "C:\\Users\\carlo\\Desktop\\votaciones\\candidatos%d.txt", numero);
        archivo = fopen(nombreArchivo, "r");
        if (archivo == NULL)
        {
            break; // Detiene la búsqueda cuando ya no encuentra correlativos
        }
        fclose(archivo);
        contador++;
        numero++;
    }
    return contador;
}

// Verifica si un código de periodo ya ha sido registrado previamente
int comprobarPeriodo(char periodoInput[])
{
    FILE *archivo;
    char periodoGuardado[10];
    int numeroArchivo;
    archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\periodos.txt", "r");

    if(archivo == NULL)
    {
        return 0;
    }
    while(fscanf(archivo, "%s %d", periodoGuardado, &numeroArchivo) == 2)
    {
        if(strcmp(periodoGuardado, periodoInput) == 0)
        {
            fclose(archivo);
            return 1; // El periodo ya existe
        }
    }
    fclose(archivo);
    return 0; // Periodo libre para registro
}

// Módulo para la creación y configuración de un nuevo proceso electoral
int controlarPanel(){
  int cantidad = 0, k = 0;
  char aut[20];
  Partido candidatos[5];
  char nombrar_Archivo[250];
  FILE *archivo;
  FILE *prueba;
  FILE *periodoArchivo;
  int cant;
  cant = contarElecciones();

  while(1)
  {
    printf("\nIngrese el Periodo de elecciones: ");
    fgets(aut, 20, stdin);
    aut[strcspn(aut, "\n")] = '\0';
    
    // Validación de longitud del código del periodo
    if(strlen(aut) != 6)
    {
        printf("Error: Código de autentificación no válido\n");
        return 0;
    }
    if(comprobarPeriodo(aut))
    {
        printf("Error: El periodo %s ya existe. No se puede registrar nuevamente.\n", aut);
        return 0;
    }
    sprintf(nombrar_Archivo, "C:\\Users\\carlo\\Desktop\\votaciones\\candidatos%d.txt", cant);
    prueba = fopen(nombrar_Archivo, "r");
    if(prueba == NULL)
    {
      printf("\t\t/ / / / / Nueva elección / / / / /\n");
      while(cantidad <= 0 || cantidad > 5)
      {
        printf("Ingrese cuántos candidatos quiere ingresar:");
        scanf("%d", &cantidad);
        getchar();
        if(cantidad > 5)
        {
            printf("No puede ingresar más de 5 candidatos.\n");
        }
        else
        {
            if(cantidad <= 0)
            {
                printf("Debe ingresar al menos un candidato para crear una elección.\n");
                return 0;
            }
            k = cantidad;
            archivo = fopen(nombrar_Archivo, "w");
            if(archivo == NULL)
            {
                printf("No se pudo crear el archivo de candidatos.\n");
                return 0;
            }
            
            // Captura de datos de partidos y candidatos
            for(int i = 0; i < cantidad; i++)
            {
                printf("Ingrese el nombre del partido #%d: ", i + 1);
                fgets(candidatos[i].partido, 50, stdin);
                candidatos[i].partido[strcspn(candidatos[i].partido, "\n")] = '\0';

                printf("Ingrese el nombre del presidente: ");
                fgets(candidatos[i].presidente, 50, stdin);
                candidatos[i].presidente[strcspn(candidatos[i].presidente, "\n")] = '\0';

                printf("Ingrese el nombre del vicepresidente: ");
                fgets(candidatos[i].vicepresidente, 50, stdin);
                candidatos[i].vicepresidente[strcspn(candidatos[i].vicepresidente, "\n")] = '\0';
            }
            
            // Estructuración visual en el archivo de texto de candidatos
            fprintf(archivo, "==========================================================\n");
            fprintf(archivo, "               ELECCIONES ESTUDIANTILES\n");
            fprintf(archivo, "                 PERIODO: %s\n", aut);
            fprintf(archivo, "==========================================================\n\n");

            for(int i = 0; i < cantidad; i++)
            {
                fprintf(archivo, "Partido Político : %s\n", candidatos[i].partido);
                fprintf(archivo, "Número de Lista  : %d\n\n", i + 1);
                fprintf(archivo, "----------------------------------------------------------\n");
                fprintf(archivo, "CANDIDATO A PRESIDENTE\n");
                fprintf(archivo, "----------------------------------------------------------\n");
                fprintf(archivo, "Nombre: %s\n", candidatos[i].presidente);
                fprintf(archivo, "----------------------------------------------------------\n");
                fprintf(archivo, "CANDIDATO A VICEPRESIDENTE\n");
                fprintf(archivo, "----------------------------------------------------------\n");
                fprintf(archivo, "Nombre: %s\n\n", candidatos[i].vicepresidente);
            }
            fclose(archivo);

            // Registro del nuevo periodo en el índice general
            periodoArchivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\periodos.txt", "a");
            if(periodoArchivo == NULL)
            {
                printf("No se pudo abrir el archivo de periodos.\n");
                return 0;
            } 
            fprintf(periodoArchivo, "%s %d\n", aut, cant);
            fclose(periodoArchivo);
            strcpy(periodo, aut);
            printf("Actualmente hay un total de %d elecciones creadas\n", cant + 1);
            
            // Selección de continuidad de flujo
            int opcion;
            printf("\n\nDesea continuar con el periodo actual?");
            printf("\n1. Si");
            printf("\n2. Elegir otro periodo");
            printf("\nOpcion: ");
            scanf("%d", &opcion);
            while(getchar() != '\n');
            if(opcion == 1)
            {
                return k;
            }
            else if(opcion == 2)
            {
                char nuevoPeriodo[10];
                printf("Ingrese el periodo que desea utilizar: ");
                fgets(nuevoPeriodo, 10, stdin);
                nuevoPeriodo[strcspn(nuevoPeriodo, "\n")] = '\0';
                if(comprobarPeriodo(nuevoPeriodo))
                {
                    strcpy(periodo, nuevoPeriodo);
                    printf("Periodo cambiado correctamente a: %s\n", periodo);
                    return k;
                }
                else
                {
                    printf("El periodo ingresado no existe.\n");
                    return 0;
                }
            }
            else
            {
                printf("Opción inválida\n");
                return 0;
            }
        }
      }
    }
    else
    {
        fclose(prueba);
        cant++;
    }
  }
}

// Algoritmo matemático para validar la estructura de la cédula ecuatoriana
int validarCedulaEcuatoriana(const char *cedula) {
    if (cedula == NULL || strlen(cedula) == 0) {
        printf("Error: La cédula ingresada es nula o está vacía.\n");
        return 0;
    }
    if (strlen(cedula) != 10) {
        printf("Error: La cédula debe tener exactamente 10 dígitos.\n");
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        if (cedula[i] < '0' || cedula[i] > '9') {
            printf("Error: La cédula debe contener exclusivamente números.\n");
            return 0;
        }
    }
    int provincia = (cedula[0] - '0') * 10 + (cedula[1] - '0');
    if ((provincia < 1 || provincia > 24) && provincia != 30) {
        printf("Error: Código de provincia inválido (Debe ser entre 01-24 o 30).\n");
        return 0;
    }
    return 1;
}

// Comprueba si el estudiante ya cuenta con un registro de voto en el periodo actual
int yaVoto(const char *cedula, int numeroArchivo)
{
    FILE *archivo;
    char ruta[150];
    sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\cedulas%d.txt", numeroArchivo);
    archivo = fopen(ruta, "r");
    if(archivo == NULL)
    {
        return 0;
    }
    char cedulaGuardada[50];
    while(fscanf(archivo, "%49s", cedulaGuardada) == 1)
    {
        if(strcmp(cedulaGuardada, cedula) == 0)
        {
            fclose(archivo);
            return 1; // Ya votó
        }
    }
    fclose(archivo);
    return 0; // No ha votó
}

// Obtiene el ID correlativo correspondiente a una cadena de texto de periodo
int obtenerArchivoPeriodo(char periodoInput[])
{
    FILE *archivo;
    char periodoGuardado[20];
    int numeroArchivo;
    archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\periodos.txt", "r");
    if(archivo == NULL)
        return -1;
    while(fscanf(archivo, "%s %d", periodoGuardado, &numeroArchivo) == 2)
    {
        if(strcmp(periodoGuardado, periodoInput) == 0)
        {
            fclose(archivo);
            return numeroArchivo;
        }
    }
    fclose(archivo);
    return -1;
}

// Cruza la información del usuario con la base de datos de padron.txt
int verificarPadron(const char *cedula, char *nombreOut, int *edadOut) {
    FILE *archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\padron.txt", "r");
    if (archivo == NULL) {
        printf("Error: No se encontró el archivo padron.txt.\n");
        return 0;
    }
    char linea[150];
    char cedulaPadron[50];
    char nombrePadron[100];
    int edadPadron;
    
    // Parseo de estructura separada por punto y coma (;)
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        if (sscanf(linea, "%49[^;];%99[^;];%d", cedulaPadron, nombrePadron, &edadPadron) == 3) {
            if (strcmp(cedulaPadron, cedula) == 0) {
                strcpy(nombreOut, nombrePadron);
                *edadOut = edadPadron;
                fclose(archivo);
                return 1; // Encontrado en el padrón
            }
        }
    }
    fclose(archivo);
    return 0; // No consta en el padrón
}

int contarCandidatos(int numeroArchivo);

// Interfaz para el sufragio del estudiante
int panelEstudiantes(int j, int cantidad)
{
    int votacion;
    char ruta[150];
    char cedula[50];
    char nombreEstudiante[100] = "";
    int edad = 18; 
    char archivoCandidatos[150];

    int numeroArchivo = obtenerArchivoPeriodo(periodo);
    if(numeroArchivo == -1)
    {
        printf("El periodo seleccionado no existe.\n");
        return 1;
    }

    if (contarCandidatos(numeroArchivo) <= 0)
    {
        return 1;
    }

    sprintf(archivoCandidatos, "C:\\Users\\carlo\\Desktop\\votaciones\\candidatos%d.txt", numeroArchivo);
    FILE *archivo = fopen(archivoCandidatos, "r");
    if (archivo == NULL)
    {
        printf("No se encontro el archivo de candidatos.\n");
        return 1;
    }

    char Linea[100];
    int total = 0;
comp:
    printf("\v\t\t//// Módulo de votación ///\n");
    
    do {
        printf("Ingrese su número de cédula: ");
        scanf("%49s", cedula);
        printf("\n-----------------------------\n");
        while(getchar() != '\n');

        if(validarCedulaEcuatoriana(cedula) == 0)
        {
            continue;
        }

        if (verificarPadron(cedula, nombreEstudiante, &edad) == 0) {
            printf("ACCESO DENEGADO: Usted no consta en el padrón electoral.\n");
            fclose(archivo);
            return 1;
        }

        if (yaVoto(cedula, numeroArchivo)) {
            printf("\nAviso: Usted ya registró su voto en esta elección.\n");
            fclose(archivo);
            return 2; 
        }
        
        printf("BIENVENIDO/A: %s\n", nombreEstudiante);
        printf("EDAD REGISTRADA: %d años\n", edad);
        printf("-----------------------------\n");
        break; 
        
    } while (1);

    // Muestra las listas de opciones electorales disponibles en pantalla
    while (fgets(Linea, sizeof(Linea), archivo) != NULL)
    {
        total++;
        printf("%s", Linea);
    }
    fclose(archivo);

    if (total <= 0)
    {
        printf("No hay candidatos registrados.\n");
        return 1;
    }

    cantidad = total;

    printf("Si desea votar en blanco, ingrese 0.\n");
    printf("Si desea votar en nulo, ingrese  -1.\n");
    printf("Ingrese el numero del candidato que desea votar:\n");
    
    scanf("%d", &votacion);
    while(getchar() != '\n'); 

    if(votacion < -1 || votacion > cantidad) 
    {
        printf("Voto inválido. Seleccione un candidato válido, 0 para voto blanco o -1 para voto nulo.\n");
        goto comp;
    } else {
        // Almacenamiento transaccional individual del voto
        sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\datos%d_%d.txt", numeroArchivo, j);
        FILE *fp = fopen(ruta, "w");
        if(fp == NULL)
        {
            printf("Error al crear el archivo.\n");
            return 1;
        }
        fprintf(fp, "Edad: %d\nCédula: %s\nVoto: %d\n", edad, cedula, votacion);
        printf("\nSu voto ha sido registrado.\n");
        fclose(fp);

        // Agrega al votante a la lista negra interna del periodo
        char rutaCedula[150];
        sprintf(rutaCedula, "C:\\Users\\carlo\\Desktop\\votaciones\\cedulas%d.txt", numeroArchivo);
        FILE *fc = fopen(rutaCedula, "a");
        if(fc != NULL){
            fprintf(fc, "%s\n", cedula);
            fclose(fc);
        }
        return 0;
    }
}

// Escanea y cuantifica de manera independiente las transacciones de archivos de votos individuales
void contarResultados(int numeroArchivo, int *cont, int *cont1, int *cont2, int *cont3, int *cont4, int *blanco, int *nulo){
  char ruta[250];
  char votos[150];
  FILE *archivo;
  int voto = 0;
  *cont = 0;
  *cont1 = 0;
  *cont2 = 0;
  *cont3 = 0;
  *cont4 = 0;
  *blanco = 0;
  *nulo = 0;
  
  for (int i = 0; i < 1000; i++) {
    sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\datos%d_%d.txt", numeroArchivo, i);
    archivo = fopen(ruta, "r");
    if (archivo == NULL) {
      continue;
    }
    while (fgets(votos, sizeof(votos), archivo) != NULL){
      if (sscanf(votos, "Voto: %d", &voto) == 1) {
        if (voto == 0) {
          (*blanco)++;
        }
        else if (voto == -1) {
          (*nulo)++;
        }
        else if (voto == 1) {
          (*cont)++;
        }
        else if (voto == 2) {
          (*cont1)++;
        }
        else if (voto == 3) {
          (*cont2)++;
        }
        else if (voto == 4) {
          (*cont3)++;
        }
        else if (voto == 5) {
          (*cont4)++;
        }
      }
    }
    fclose(archivo);
  }
}

// Aplica el ordenamiento por método de inserción directa para desplegar ganadores
void resultadosFinales(int numeroArchivo, int cantidad, int *cont, int *cont1, int *cont2, int *cont3, int *cont4, int *blanco, int *nulo, int *a, float *total, Resultado acta[]){
  Resultado res[5];
  FILE *archivo;
  char linea[100];
  char ruta[150];
  int x = 0;
  *a = 0;
  if (cantidad > 5) {
    clearerr(archivo);
    cantidad = 5;
  }
  sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\candidatos%d.txt", numeroArchivo);
  archivo = fopen(ruta, "r");
  if (archivo == NULL) {
    printf("No existe el archivo de candidatos.\n");
    return;
  }
  while (x < cantidad && fgets(linea, sizeof(linea), archivo) != NULL) {
    char *p = strchr(linea, ':');
    if (p != NULL) {
      p++;
      while (*p == ' ') {
         p++;
       }
      p[strcspn(p, "\r\n")] = '\0';
      strcpy(res[x].nombre, p);
    } else {
      strcpy(res[x].nombre, linea);
    }
    switch (x) {
       case 0: res[x].votos = *cont; break;
       case 1: res[x].votos = *cont1; break;
       case 2: res[x].votos = *cont2; break;
       case 3: res[x].votos = *cont3; break;
       case 4: res[x].votos = *cont4; break;
    }
    x++;
  }
  fclose(archivo);

  // Ordenamiento por inserción directa (Menor a Mayor / Mayor a Menor)
  for (int i = 1; i < x; i++) {
    Resultado actual = res[i];
    int j = i - 1;
    while (j >= 0 && res[j].votos < actual.votos) {
      res[j + 1] = res[j];
      j--;
    }
    res[j + 1] = actual;
  }

  for (int i = 0; i < x; i++) {
    printf("Candidato %d: %s -> %d votos\n", i + 1, res[i].nombre, res[i].votos);
    *a = *a + res[i].votos;  
    acta[i] = res[i];
  }
    
  if((*a + *blanco + *nulo) > 0) {
      *total = (float)res[0].votos / (*a + *blanco + *nulo);
  } else {
      *total = 0.0;
  }

  printf("Votos en blanco: %d\n", *blanco);
  printf("Votos nulos: %d\n", *nulo);
  printf("El ganador es %s con %d votos\n", res[0].nombre, res[0].votos);
  printf("El margen de votos es de %.2f %%\n", *total * 100);
}

// Cuenta la cantidad de líneas dentro del archivo para calcular candidatos reales
int contarCandidatos(int numeroArchivo){
  FILE *archivo;
  char linea[100];
  char ruta[150];
  int contador = 0;
  sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\candidatos%d.txt", numeroArchivo);
  archivo = fopen(ruta, "r");
  if (archivo == NULL){
    return 0;
  }
  while (fgets(linea, 100, archivo) != NULL){
    contador++;
  }
  fclose(archivo);
  return contador;
}

// Generación formal y formateada del acta final de escrutinio
void generarActa(){
  FILE *archivo;
  char ruta[150];
  int numeroArchivo = obtenerArchivoPeriodo(periodo);
  if(numeroArchivo == -1)
  {
      printf("No existe un periodo seleccionado.\n");
      return;
  }
  int cantidad = contarCandidatos(numeroArchivo);
  int cont = 0, cont1 = 0, cont2 = 0, cont3 = 0, cont4 = 0, blanco = 0, nulo = 0;
  int a = 0;
  float total = 0;
  Resultado acta[5];
  
  contarResultados(numeroArchivo, &cont, &cont1, &cont2, &cont3, &cont4, &blanco, &nulo);
  resultadosFinales(numeroArchivo, cantidad, &cont, &cont1, &cont2, &cont3, &cont4, &blanco, &nulo, &a, &total, acta);
  
  sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\acta%d.txt", numeroArchivo);
  archivo = fopen(ruta, "w");
  if(archivo == NULL){
        printf("No se pudo generar el acta.\n");
        return;
  }
  
  fprintf(archivo, "\v\t\t==============ACTA DE RESULTADOS================\n");
  printf("\v\t\t==============ACTA DE RESULTADOS================\n");
  
  fprintf(archivo, "+------------------------------------------------+\n");
  fprintf(archivo, "|           CUADRO OFICIAL DE RESULTADOS         |\n");
  fprintf(archivo, "+------------------------------------------------+\n");
  
  printf("+------------------------------------------------+\n");
  printf("|           CUADRO OFICIAL DE RESULTADOS         |\n");
  printf("+------------------------------------------------+\n");
  
  for(int i = 0; i < cantidad; i++) {
      fprintf(archivo, "| LISTA #%-39d |\n", i + 1);
      fprintf(archivo, "| DATOS: %-39s |\n", acta[i].nombre);
      fprintf(archivo, "| Votos Totales: %-31d |\n", acta[i].votos);
      fprintf(archivo, "+------------------------------------------------+\n");
      
      printf("| LISTA #%-39d |\n", i + 1);
      printf("| DATOS: %-39s |\n", acta[i].nombre);
      printf("| Votos Totales: %-31d |\n", acta[i].votos);
      printf("+------------------------------------------------+\n");
  }
  
  printf("Votos en blanco: %d\n", blanco);
  printf("Votos nulos: %d\n", nulo);
  printf("---------------------------------\n");
  printf("El ganador es: %s con %d votos\n", acta[0].nombre, acta[0].votos);
  printf("El total de votos es: %d\n", a + blanco + nulo);
  printf("El margen de votos total es %.2f %%\n", total * 100);
  
  fprintf(archivo, "Votos en blanco: %d\n", blanco);
  fprintf(archivo, "Votos nulos: %d\n", nulo);
  fprintf(archivo, "---------------------------------\n");
  fprintf(archivo, "El ganador es: %s con %d votos\n", acta[0].nombre, acta[0].votos);
  fprintf(archivo, "El total de votos es: %d\n", a + blanco + nulo);
  fprintf(archivo, "El margen de votos total es %.2f %%\n", total * 100);
  
  fclose(archivo);
  printf("\nActa generada correctamente: acta%d.txt\n", numeroArchivo);
}

// Verifica la consistencia lógica de los archivos del periodo electoral activo
int controlArchivos()
{
    FILE *archivo;
    char periodoGuardado[20];
    int numeroArchivo;
    char ruta[150];

    archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\periodos.txt", "r");
    if(archivo == NULL)
    {
        printf("No existen elecciones registradas.\n");
        return 0;
    }
    while(fscanf(archivo, "%s %d", periodoGuardado, &numeroArchivo) == 2)
    {
        sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\candidatos%d.txt", numeroArchivo);
        FILE *candidatos = fopen(ruta, "r");
        if(candidatos == NULL)
        {
            printf("Error: falta archivo de candidatos del periodo %s\n", periodoGuardado);
            fclose(archivo);
            return 0;
        }
        fclose(candidatos);
    }
    fclose(archivo);
    return 1;
}

// Búsqueda binaria iterativa y recursiva para encontrar cédulas rápidamente
int busquedaBinariaRecursiva(char arr[][50], int inicio, int fin, const char *objetivo) {
    if (inicio > fin) {
        return -1; 
    }
    int medio = inicio + (fin - inicio) / 2;
    int comparacion = strcmp(arr[medio], objetivo);
    
    if (comparacion == 0) {
        return medio; 
    }
    if (comparacion > 0) {
        return busquedaBinariaRecursiva(arr, inicio, medio - 1, objetivo);
    }
    return busquedaBinariaRecursiva(arr, medio + 1, fin, objetivo);
}

// Interfaz administrativa para desbloquear o visualizar usuarios infractores/votantes
void administrarUsuarios() {
    int opcion_admin;
    int numeroArchivo = obtenerArchivoPeriodo(periodo);
    if(numeroArchivo == -1)
    {
        printf("No existe un periodo seleccionado.\n");
        return;
    }
    char ruta[150];
    sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\cedulas%d.txt", numeroArchivo);
    do {
        printf("\t\t1.- Ver lista de usuarios que ya votaron\n");
        printf("\t\t2.- Buscar y banear usuario\n");
        printf("\t\t3.- Regresar al panel principal\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion_admin);
        while(getchar() != '\n');
        if (opcion_admin == 1) {
            FILE *archivo = fopen(ruta, "r");
            if (!archivo) {
                printf("\nAviso: Aún no hay registros de usuarios que hayan votado.\n");
            } else {
                char cedulaGuardada[50];
                int count = 0;
                printf("\n--- Lista de Cédulas Registradas ---\n");
                while (fscanf(archivo, "%49s", cedulaGuardada) == 1) {
                    count++;
                    printf("%d. %s\n", count, cedulaGuardada);
                }
                if (count == 0) {
                    printf("La lista está vacía.\n");
                }
                fclose(archivo);
            }
        } 
        else if (opcion_admin == 2) {
            FILE *archivo = fopen(ruta, "r");
            if (!archivo) {
                printf("\n Error: No hay registros de usuarios.\n");
                continue;
            }
            char arregloCedulas[200][50];
            int n = 0;
            while (fscanf(archivo, "%49s", arregloCedulas[n]) == 1) {
                n++;
            }
            fclose(archivo);
            if (n == 0) {
                printf("\n -> La lista de votantes está vacía.\n");
                continue;
            }
            
            // Método de ordenamiento Burbuja previo a realizar la búsqueda binaria
            char temporal[50];
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if (strcmp(arregloCedulas[j], arregloCedulas[j+1]) > 0) {
                        strcpy(temporal, arregloCedulas[j]);
                        strcpy(arregloCedulas[j], arregloCedulas[j+1]);
                        strcpy(arregloCedulas[j+1], temporal);
                    }
                }
            }
            char cedulaEliminar[50];
            printf("\nIngrese la cédula del usuario que desea desbanear: ");
            scanf("%49s", cedulaEliminar);
            while(getchar() != '\n');
            int indice = busquedaBinariaRecursiva(arregloCedulas, 0, n - 1, cedulaEliminar);
            if (indice != -1) {
                for (int i = indice; i < n - 1; i++) {
                    strcpy(arregloCedulas[i], arregloCedulas[i+1]);
                }
                n--;
                archivo = fopen(ruta, "w");
                if (archivo) {
                  for (int i = 0; i < n; i++) {
                        fprintf(archivo, "%s\n", arregloCedulas[i]);
                    }
                    fclose(archivo);
                }
                printf("Éxito: El usuario con cédula %s fue eliminado de la lista negra y puede votar.\n", cedulaEliminar);
            } 
            else {
                printf("Error: La cédula %s no se encontró en los registros de votación.\n", cedulaEliminar);
            }
        }
        else if (opcion_admin != 3) {
            printf("\nOpción no válida. Intente de nuevo.\n");
        }
    } while (opcion_admin != 3);
}

// Cuenta la cantidad transaccional física de archivos *.txt de votos para calcular j
int contarVotosExistentes(int numeroArchivo) {
    char ruta[200];
    int i = 0;
    FILE *archivo;
    while (1) {
        snprintf(ruta, sizeof(ruta), "C:\\Users\\carlo\\Desktop\\votaciones\\datos%d_%d.txt", numeroArchivo, i);
        archivo = fopen(ruta, "r");
        if (archivo == NULL) {
            return i; 
        }
        fclose(archivo);
        i++;
    }
}

// Suma el valor ASCII de los caracteres para la firma criptográfica base de integridad
void integridadArchivos(int *suma)
{
    FILE *archivo;
    int linea;
    char ruta[150];
    int numeroArchivo = obtenerArchivoPeriodo(periodo);
    *suma = 0;
    if(numeroArchivo == -1)
    {
        printf("No existe un periodo seleccionado.\n");
        return;
    }
    sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\candidatos%d.txt", numeroArchivo);
    archivo = fopen(ruta, "r");
    if(archivo == NULL)
    {
        printf("No se encontro el archivo.\n");
        return;
    }
    while((linea = fgetc(archivo)) != EOF) {
        *suma += linea;
    }
    fclose(archivo);
}

// Módulo de control que valida si los archivos han sufrido alteraciones externas maliciosas
void verificarIntegridad()
{
    FILE *archivo;
    FILE *integridad;
    char nombre[50];
    char rutaIntegridad[150];
    char rutaAuditoria[150];
    int integr1;
    int integr2;
    time_t tiempo;
    struct tm *fechaHora;
    char fecha[50];
    char aud[50];

    int numeroArchivo = obtenerArchivoPeriodo(periodo);
    if(numeroArchivo == -1)
    {
        printf("No existe un periodo seleccionado.\n");
        return;
    }

    sprintf(nombre, "candidatos%d.txt", numeroArchivo);
    sprintf(rutaIntegridad, "C:\\Users\\carlo\\Desktop\\votaciones\\integridad%d.txt", numeroArchivo);
    sprintf(rutaAuditoria, "C:\\Users\\carlo\\Desktop\\votaciones\\auditoria%d.txt", numeroArchivo);

    integridad = fopen(rutaIntegridad, "r");
    if(integridad == NULL)
    {
        integridadArchivos(&integr1);
        tiempo = time(NULL);
        fechaHora = localtime(&tiempo);
        strftime(aud, sizeof(aud), "%d/%m/%Y %H:%M:%S", fechaHora);
        integridad = fopen(rutaIntegridad, "w");

        if(integridad == NULL)
        {
            printf("No se pudo crear archivo de integridad.\n");
            return;
        }
        fprintf(integridad, "%d\n%s", integr1, aud);
        fclose(integridad);
        printf("Archivo de integridad creado.\n");
        return;
    }

    fscanf(integridad, "%d", &integr1);
    fgetc(integridad); 
    fgets(aud, sizeof(aud), integridad);
    fclose(integridad);

    integridadArchivos(&integr2);
    archivo = fopen(rutaAuditoria, "w");
    if(archivo == NULL){
        printf("No se pudo crear auditoria.\n");
        return;
    }
    fprintf(archivo, "--- AUDITORIA DE CANDIDATOS ---\n");
    fprintf(archivo, "Archivo revisado: %s\n", nombre);
    fprintf(archivo, "Fecha de integridad inicial: %s\n", aud);
    fprintf(archivo, "Integridad inicial: %d\n", integr1);
    fprintf(archivo, "Integridad actual: %d\n", integr2);
    
    printf("--- AUDITORIA DE CANDIDATOS ---\n");
    printf("Archivo revisado: %s\n", nombre);
    printf("Fecha de integridad inicial: %s", aud);
    printf("Integridad inicial: %d\n", integr1);
    printf("Integridad actual: %d\n", integr2);
    
    if(integr1 == integr2){
        fprintf(archivo, "Estado: Archivo de candidatos integro.\n");
        printf("Estado: Archivo de candidatos integro.\n");
    }
    else {
        fprintf(archivo, "Estado: ALERTA. Archivo modificado.\n");
        printf("Estado: ALERTA. Archivo modificado.\n");
    }
    tiempo = time(NULL);
    fechaHora = localtime(&tiempo);
    strftime(fecha, sizeof(fecha), "%d/%m/%Y %H:%M:%S", fechaHora);
    fprintf(archivo, "Fecha y hora de auditoria: %s\n", fecha);
    printf("Fecha y hora de auditoria: %s\n", fecha);
    fprintf(archivo, "-----------------------------\n");
    fclose(archivo);
}

// Menú y enrutamiento interno de privilegios para Administrador y Supervisor
int panelAdministrador(char admin[], char pasar[]){
  char nombre[] = "Administrador1";
  char contr[] = "123456";
  char supNombre[] = "Supervisor1";
  char supContr[] = "654321";
  char elec;
  int op, comp = 0;
  int cont = 0, cont1 = 0, cont2 = 0, cont3 = 0, cont4 = 0, a = 0, var = 0;
  float total = 0;
  Resultado acta[5];
  int blanco = 0;
  int nulo = 0;
  int numeroArchivo = obtenerArchivoPeriodo(periodo);
  int dif = 0;

  if(numeroArchivo != -1)
  {
      dif = contarCandidatos(numeroArchivo);
  }

  if(strcmp(admin, nombre) == 0 && strcmp(pasar, contr) == 0){
      printf("\nAcceso concedido, presione enter para continuar...\n");
      do {
          printf("\n\t\t\tPANEL DE ADMINISTRADOR");
          printf("\n\v\t\t1.-Elección nueva");
          printf("\n\t\t2.-Generar reportes/actas");
          printf("\n\t\t3.-Auditoría de archivos");
          printf("\n\t\t4.-Administrador de usuarios");
          printf("\n\t\t5.-Resultado");
          printf("\n\t\t6.-Salir al menú principal");
          printf("\n\nIngrese su opción:");
          scanf("%d", &op);
          getchar();
          switch(op)
          {
            case 1:
              comp = controlArchivos();
              if(comp == 1)
              {
                 printf("Ya existe una elección activa, no se puede crear una nueva\n");
                 printf("Quiere crear una nueva eleccion si (s), no(n)?\n");
                 printf("Ingrese su eleccion s o n: ");
                 scanf(" %c", &elec);
                 if(elec == 's' || elec == 'S')
                 {
                   while(getchar() != '\n');
                   controlarPanel();
                 }
              } else {
                controlarPanel();
              }
              break;
            case 2:
              generarActa();
              break;
            case 3:
              printf("¿Desea realizar auditoria del archivo de los candidatos(1)o los votos(2)?");
              printf("\nIngrese 1 o 2: ");
              scanf("%d", &var);
              getchar();
              if(var == 1) {
                verificarIntegridad();
              }
              break;
            case 4:
              administrarUsuarios();
              break;
            case 5:
              numeroArchivo = obtenerArchivoPeriodo(periodo);
              if(numeroArchivo != -1) {
                  dif = contarCandidatos(numeroArchivo);
              }
              contarResultados(numeroArchivo, &cont, &cont1, &cont2, &cont3, &cont4, &blanco, &nulo);
              resultadosFinales(numeroArchivo, dif, &cont, &cont1, &cont2, &cont3, &cont4, &blanco, &nulo, &a, &total, acta);
              break;
            case 6:
              break;
            default:
              printf("Opción no válida\n");
              break;
          }
      } while(op != 6);
      return 0;
      
  } else if(strcmp(admin, supNombre) == 0 && strcmp(pasar, supContr) == 0){
      printf("\nAcceso concedido...\n");
      do {
          printf("\n\t\t\tPANEL DE SUPERVISOR");
          printf("\n\v\t\t1.-Generar reportes/actas");
          printf("\n\t\t2.-Auditoría de archivos");
          printf("\n\t\t3.-Salir al menú principal");
          printf("\n\nIngrese su opción:");
          scanf("%d", &op);
          switch(op)
          {
            case 1:
              generarActa();
              break;
            case 2:
              verificarIntegridad();
              break;
            case 3:
              break;
            default:
              printf("Opción no válida\n");
              break;
          }
      } while(op != 3);
      return 0;
      
  } else if(strcmp(admin, nombre) != 0 && strcmp(admin, supNombre) != 0 && strcmp(pasar, contr) != 0){
    printf("\nNombre y contraseña incorrectos\n");
    return 0;
  } else if(strcmp(admin, nombre) != 0 && strcmp(admin, supNombre) != 0) {
    printf("\nNombre incorrecto\n");
    return 0;
  } else {
    printf("\nContraseña incorrecta\n");
    return 0;
  } 
}

// Crea la carpeta contenedora si no existe e inicializa el padrón electoral base
void inicializarPadronAutomatico() {
    // Asegura dinámicamente que la ruta del directorio exista para prevenir errores de puntero nulo
    CreateDirectory("C:\\Users\\carlo\\Desktop\\votaciones", NULL);
    
    FILE *archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\padron.txt", "r");
    if (archivo == NULL) {
        archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\padron.txt", "w");
        if (archivo != NULL) {
            fprintf(archivo, "1713575974;Juan Perez;19\n");
            fprintf(archivo, "0926574136;Maria Flores;21\n");
            fprintf(archivo, "1003463121;Carlos Andrade;20\n");
            fprintf(archivo, "0104104279;Ana Belen Cueva;22\n");
            fprintf(archivo, "1104323281;Luis Miguel Toapanta;18\n");
            fprintf(archivo, "1804253164;Diana Carolina Ortiz;23\n");
            fprintf(archivo, "0704025178;Kevin Alejandro Rios;20\n");
            fprintf(archivo, "1311746244;Estefania Nicole Mendoza;24\n");
            fprintf(archivo, "2400124474;Christian David Torres;19\n");
            fprintf(archivo, "3050123456;Sofia Valentina Ruiz;22\n");
            fclose(archivo);
        }
    } else {
        fclose(archivo);
    }
}

int main(void){
  // Establece codificación UTF-8 para evitar caracteres extraños en la consola de Windows
  SetConsoleOutputCP(65001);
   char pasar[20];
   char admin[20];
   char c;
   int i = 0, ver, dif = 0;
   
   // Ejecución inmediata obligatoria para la persistencia del padrón electoral
   inicializarPadronAutomatico();

   int numeroArchivo = obtenerArchivoPeriodo(periodo);
   int j = contarVotosExistentes(numeroArchivo); 
   int opcion = 0;

 while(opcion != 3){
   printf("\n\v\t------------------Programa de elecciones---------------\n");
   printf("Ingrese su solicitud\n");
   printf("\v\t\t1.- Módulo de estudiantes\n");
   printf("\t\t2.- Módulo de administrador\n");
   printf("\t\t3.- Salir\n\n");
   printf("Escoja su opcion: ");
   scanf("%d", &opcion);
   while(getchar() != '\n');
   switch (opcion){ 
   case 2:
     printf("Ingrese su nombre de usuario: ");
     fgets(admin, 20, stdin);
     admin[strcspn(admin, "\n")] = '\0';
     printf("Ingrese su contraseña: ");
     i = 0;
     
     // Enmascaramiento de caracteres por asteriscos (*) en consola
     while((c = getch()) != 13)  {
        pasar[i] = c;
        i++;
        printf("*");
     }
     pasar[i] = '\0';
     ver = panelAdministrador(admin, pasar);
     if (ver > 0) {
        dif = ver;
     } else {
        dif = 0;
     }
     break;

   case 1:
     numeroArchivo = obtenerArchivoPeriodo(periodo);
     j = contarVotosExistentes(numeroArchivo);
     ver = panelEstudiantes(j, dif);
     if(ver == 0){
       j++; // Incrementa el contador transaccional de votos concurrentes
     }
     else if(ver == 1){
       printf("No existe una elección activa, reinicie el programa en el módulo de administrador\n");
     }
     break;
   case 3:
     printf("--------------------\n");
     printf("Programa finalizado");
     return 1;
     break;
   default:
     printf("Opcion no valida\n");
     break;
   } 
  }
   return 0; 
}