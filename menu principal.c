#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

typedef struct {
    char nombre[50];
    int votos;
} Resultado;

// Esta función permite al administrador crear una nueva votación en el sistema.
// Pide la cantidad de candidatos que van a participar en el proceso
// y guarda todos sus nombres directamente en un archivo de texto.
int controlarPanel(){
  int cantidad=0,aut,k=0;
  char candidatos[100][50];
  int codigoPrimario=2026;
  FILE *archivo;
    printf("\t\t/ / / / / Nueva elección / / / / /\n");
    while(cantidad<=0||cantidad>5) {
     printf("Ingrese cuántos candidatos quiere ingresar:");
    scanf("%d",&cantidad);
    if(cantidad>5){
        printf("No puede ingresar más de 5 candidatos.\n");
        
    }else{      
    printf("\nIngrese el código de autenticación primario:");
    scanf("%d",&aut);
    if(aut!=codigoPrimario)
    {
      printf("Error: Código de autentificación no válido");
      return 0;
    }
    getchar();
    if (cantidad <= 0) {
        printf("Debe ingresar al menos un candidato para crear una elección.\n");
        return 0;
    }
    k=cantidad;
    archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\candidatos.txt", "w");
    if (archivo == NULL) {
    printf("No se pudo crear el archivo de candidatos.\n");
    return 0;
    }
    for (int i = 0; i < cantidad; i++) {
    printf("Ingrese el nombre de su candidato #%d: ", i + 1);
    // CORRECCIÓN: Se eliminó el printf("Datos ingresados") que salía antes de tiempo
    fgets(candidatos[i], 50, stdin);
    candidatos[i][strcspn(candidatos[i], "\n")] = '\0';
    fprintf(archivo, "Para este candidato vota %d: %s\n", i + 1, candidatos[i]);
    }
    fclose(archivo);
    return k;
   }
  }
  return 0;
}

// Esta función busca en el archivo de texto para saber si la cédula ya votó.
// Abre el documento donde se registran los ciudadanos que ya participaron
// y devuelve un valor afirmativo si encuentra una coincidencia exacta.
int yaVoto(const char *cedula) {
    FILE *archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\cedulas.txt", "r");
    if (archivo == NULL) return 0; 

    char cedulaGuardada[50];
    while (fscanf(archivo, "%49s", cedulaGuardada) == 1) {
        if (strcmp(cedulaGuardada, cedula) == 0) {
            fclose(archivo);
            return 1; 
        }
    }
    fclose(archivo);
    return 0;
}

// Busca la cédula en el padrón estructurado y extrae el nombre y la edad asignados.
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
    
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        if (sscanf(linea, "%49[^;];%99[^;];%d", cedulaPadron, nombrePadron, &edadPadron) == 3) {
            if (strcmp(cedulaPadron, cedula) == 0) {
                strcpy(nombreOut, nombrePadron);
                *edadOut = edadPadron;
                fclose(archivo);
                return 1;
            }
        }
    }
    fclose(archivo);
    return 0;
}

int contarCandidatos();

// Esta función despliega la interfaz en pantalla para que el alumno vote.
int panelEstudiantes(int j, int cantidad)
{
    int votacion;
    char ruta[150];
    char cedula[50];
    char nombreEstudiante[100] = "";
    int edad = 18; 
    
    if (contarCandidatos() <= 0)
    {
        return 1;
    }

    FILE *archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\candidatos.txt", "r");
    if (archivo == NULL)
    {
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

        // El padrón se encarga de filtrar directamente de forma segura.
        if (verificarPadron(cedula, nombreEstudiante, &edad) == 0) {
            printf("ACCESO DENEGADO: Usted no consta en el padrón electoral.\n");
            fclose(archivo);
            return 1;
        }

        if (yaVoto(cedula)) {
            printf("\nAviso: Usted ya registró su voto con esta cédula.\n");
            fclose(archivo);
            return 2; 
        }
        
        printf("BIENVENIDO/A: %s\n", nombreEstudiante);
        printf("EDAD REGISTRADA: %d años\n", edad);
        printf("-----------------------------\n");
        break; 
        
    } while (1);

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

    amount:
    cantidad = total;

    printf("Si desea votar en blanco, ingrese 0.\n");
    printf("Si desea votar en nulo, ingrese  -1.\n");
    printf("Ingrese el numero del candidato que desea votar:\n");
    
    scanf("%d", &votacion);
    while(getchar() != '\n'); // Limpia el búfer inmediatamente aquí para evitar bucles infinitos con letras o errores

    if(votacion < -1 || votacion > cantidad) // Filtrado correcto para evitar que el número -2 pase como voto fantasma
    {
        printf("Voto inválido.\n");
        goto comp;
    }else{

    sprintf(ruta, "C:\\Users\\carlo\\Desktop\\votaciones\\datos%d.txt", j);

    FILE *fp = fopen(ruta, "w");

    if(fp == NULL)
    {
        printf("Error al crear el archivo.\n");
        return 1;
    }
    fprintf(fp, "Edad: %d\nCédula: %s\nVoto: %d\n", edad, cedula, votacion);
    printf("\nSu voto ha sido registrado.\n");
    fclose(fp);

    FILE *fc = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\cedulas.txt", "a");
    if(fc != NULL){
        fprintf(fc, "%s\n", cedula);
        fclose(fc);
    }

    return 0;
 }
}

// Esta función lee los archivos de los votos guardados uno por uno.
// Va revisando las elecciones individuales para sumar los puntos de cada
// participante, calculando también las elecciones en blanco y las nulas.
void contarResultados(int *cont, int *cont1, int *cont2, int *cont3,int *cont4, int *blanco, int *nulo){
  char ruta[250];
  char votos[150];
  FILE *archivo;
  int voto=0;
 *cont = 0;
  *cont1 = 0;
  *cont2 = 0;
  *cont3 = 0;
  *cont4 = 0;
  *blanco = 0;
  *nulo = 0;
  
  // Se amplió el límite de lectura de 50 a 1000 archivos para evitar pérdidas en el escrutinio
  for (int i = 0; i < 1000; i++) {
    snprintf(ruta, sizeof(ruta), "C:\\Users\\carlo\\Desktop\\votaciones\\datos%d.txt", i);
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

// Esta función une los nombres con sus respectivos totales acumulados.
// Ordena los datos de mayor a menor para organizar las posiciones
// finales y muestra en pantalla un mensaje indicando quién ganó.
void resultadosFinales(int cantidad, int *cont, int *cont1, int *cont2, int *cont3, int *cont4, int *blanco, int *nulo, int *a,float *total, Resultado acta[]){
  Resultado res[5];
  FILE *archivo;
  char linea[100];
  int x = 0;
  *a=0;
  if (cantidad > 5) {
    cantidad = 5;
  }
  archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\candidatos.txt", "r");
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
       case 0:
       res[x].votos = *cont;
       break;
       case 1:
        res[x].votos = *cont1;
       break;
            case 2:
                res[x].votos = *cont2;
                break;
            case 3:
                res[x].votos = *cont3;
                break;
            case 4:
                res[x].votos = *cont4;
                break;
        }
        x++;
    }
    fclose(archivo);
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
      *a=*a+res[i].votos;  
    }
    
    int total_votos_validos = (*a + *blanco + *nulo);
    if(total_votos_validos > 0) {
        *total = (float)res[0].votos / total_votos_validos;
    } else {
        *total = 0.0;
    }

for(int i = 0; i < x; i++){
    acta[i] = res[i];
 }
}

// Esta función cuenta cuántas líneas tiene el archivo de los candidatos.
// Abre el documento de texto donde están inscritos los participantes
// y calcula el número total de registros disponibles en la lista.
int contarCandidatos(){
  FILE *archivo;
  char linea[100];
  int contador = 0;
  archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\candidatos.txt", "r");
  if (archivo == NULL){
    return 0;
  }
  while (fgets(linea, 100, archivo) != NULL){
    contador++;
  }
  fclose(archivo);
  return contador;
}

// MODIFICACIÓN: Se unificó todo en un solo reporte integrado (acta.txt)
void generarActa(){
  FILE *archivo;
  int cantidad = contarCandidatos();
  int cont=0,cont1=0,cont2=0,cont3=0,cont4=0,blanco=0,nulo=0;
  int a=0;
  float total=0;
  Resultado acta[5];
  contarResultados(&cont,&cont1,&cont2,&cont3,&cont4,&blanco,&nulo);
  resultadosFinales(cantidad,&cont,&cont1,&cont2,&cont3,&cont4,&blanco,&nulo,&a,&total,acta);
  
  archivo=fopen("C:\\Users\\carlo\\Desktop\\votaciones\\acta.txt","w");
  if(archivo == NULL){
        printf("Error al crear el acta única.\n");
        return;
  }
  
  fprintf(archivo,"\v\t\t==============ACTA DE RESULTADOS================\n");
  printf("\v\t\t==============ACTA DE RESULTADOS================\n");
  
  // Imprime el cuadro estructurado tanto en el archivo como en la pantalla
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
  
  // Métricas adicionales integradas al final del mismo documento
  printf("Votos en blanco: %d\n",blanco);
  printf("Votos nulos: %d\n",nulo);
  printf("---------------------------------\n");
  printf("El ganador es: %s con %d votos\n",acta[0].nombre,acta[0].votos);
  printf("El total de votos es: %d\n",a+blanco+nulo);
  printf("El margen de votos total es %.2f %%\n",total*100);
  
  fprintf(archivo,"Votos en blanco: %d\n",blanco);
  fprintf(archivo,"Votos nulos: %d\n",nulo);
  fprintf(archivo,"---------------------------------\n");
  fprintf(archivo,"El ganador es: %s con %d votos\n",acta[0].nombre,acta[0].votos);
  fprintf(archivo,"El total de votos es: %d\n",a+blanco+nulo);
  fprintf(archivo,"El margen de votos total es %.2f %%\n",total*100);
  
  fclose(archivo);
  printf("\n>> Acta integrada generada exitosamente en un único archivo: acta.txt\n");
}

// Esta función sirve para verificar si el archivo de candidatos ya existe.
// Intenta abrir el documento para comprobar si hay un proceso abierto
// y le indica al menú si es seguro o no crear una nueva elección.
int controlArchivos(){
  FILE *archivo=fopen("C:\\Users\\carlo\\Desktop\\votaciones\\candidatos.txt","r");
  if(archivo!=NULL){
    fclose(archivo);
    return 1;
  }else
  return 0;
}

// Esta función cuenta los archivos individuales de votos almacenados en el disco.
// Escanea la carpeta del proyecto para identificar cuántas personas votaron
// y determina el número consecutivo que le corresponde al próximo archivo.
int contarVotosExistentes() {
    char ruta[200];
    int i = 0;
    FILE *archivo;
    
    while (1) {
        snprintf(ruta, sizeof(ruta), "C:\\Users\\carlo\\Desktop\\votaciones\\datos%d.txt", i);
        archivo = fopen(ruta, "r");
        
        if (archivo == NULL) {
            return i; 
        }
        fclose(archivo);
        i++;
    }
}

// Esta función genera un código numérico sumando el valor de cada letra.
void integridadArchivos(int *suma)
{
    FILE *archivo;
    int linea;
    *suma = 0;
    archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\candidatos.txt", "r");
    if(archivo == NULL){
        return;
    }
    while((linea = fgetc(archivo)) != EOF) {
        *suma += linea;
    }
    fclose(archivo);
}

// Esta función comprueba que el documento de candidatos no haya sido alterado.
// Contrasta el código de verificación guardado antes con el estado actual
// para alertar de inmediato en caso de que alguien hiciera cambios externos.
void verificarIntegridad()
{
    FILE *archivo;
    FILE *integridad;
    char nombre[50] = "candidatos.txt";
    int integr1 = 0;
    int integr2 = 0;
    time_t tiempo;
    struct tm *fechaHora;
    char fecha[50];
    char aud[50] = "Sin fecha inicial";

    integridad = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\integridad.txt","r");
    if(integridad == NULL) {
        integridadArchivos(&integr1);
        tiempo = time(NULL);
        fechaHora = localtime(&tiempo);
        strftime(aud, sizeof(aud), "%d/%m/%Y %H:%M:%S", fechaHora);
        integridad = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\integridad.txt","w");

        if(integridad == NULL)
        {
            printf("No se pudo crear integridad.txt\n");
            return;
        }
        fprintf(integridad,"%d\n%s", integr1, aud);
        fclose(integridad);
    } else {
        fscanf(integridad,"%d",&integr1);
        fgetc(integridad); 
        fgets(aud,sizeof(aud),integridad);
        fclose(integridad);
    }

    integridadArchivos(&integr2);
    archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\auditoria.txt","w");
    if(archivo == NULL){
        printf("No se pudo crear auditoria.txt\n");
        return;
    }
    fprintf(archivo,"--- AUDITORIA DE CANDIDATOS ---\n");
    fprintf(archivo,"Archivo revisado: %s\n",nombre);
    fprintf(archivo,"Fecha de integridad inicial: %s\n",aud);
    fprintf(archivo,"Integridad inicial: %d\n",integr1);
    fprintf(archivo,"Integridad actual: %d\n",integr2);
    
    printf("--- AUDITORIA DE CANDIDATOS ---\n");
    printf("Archivo revisado: %s\n",nombre);
    printf("Fecha de integridad inicial: %s\n",aud);
    printf("Integridad inicial: %d\n",integr1);
    printf("Integridad actual: %d\n",integr2);
    
    if(integr1 == integr2){
        fprintf(archivo,"Estado: Archivo de candidatos integro.\n");
        printf("Estado: Archivo de candidatos integro.\n");
    }
    else {
        fprintf(archivo,"Estado: ALERTA. Archivo modificado.\n");
        printf("Estado: ALERTA. Archivo modificado.\n");
    }
    tiempo = time(NULL);
    fechaHora = localtime(&tiempo);
    strftime(fecha,sizeof(fecha),"%d/%m/%Y %H:%M:%S",fechaHora);
    fprintf(archivo,"Fecha y hora de auditoria: %s\n",fecha);
    printf("Fecha y hora de auditoria: %s\n",fecha);
    fprintf(archivo,"-----------------------------\n");
    fclose(archivo);
}

// Esta función valida las claves secretas de acceso para el administrador.
// Evalúa los datos de entrada para otorgar permisos a las herramientas de
// control, permitiendo auditar, generar reportes o cerrar el sistema.
int panelAdministrador(char admin[],char pasar[]){
  char nombre[]="Administrador1";
  char contr[]="123456";
  char supNombre[]="Supervisor1";
  char supContr[]="654321";
  int op,comp=0;
  int retorno=0;

  if(strcmp(admin,nombre)==0 && strcmp(pasar,contr)==0){
      printf("\nAcceso concedido...\n");
      do {
          printf("\n\t\t\tPANEL DE ADMINISTRADOR");
          printf("\n\v\t\t1.-Elección nueva");
          printf("\n\t\t2.-Generar reportes/actas");
          printf("\n\t\t3.-Salir al menú principal");
          printf("\n\nIngrese su opción:");
          scanf("%d",&op);
          switch(op)
          {
            case 1:
            comp=controlArchivos();
            if(comp==1)
            {
               printf("Ya existe una elección activa, no se puede crear una nueva\n");
            }else
            {
              retorno = controlarPanel();
            }
            break;
            case 2:
              generarActa();
              break;
            case 3:
              break;
            default:
              printf("Opción no válida\n");
              break;
          }
      } while(op != 3);
      return retorno;
      
  } else if(strcmp(admin,supNombre)==0 && strcmp(pasar,supContr)==0){
      printf("\nAcceso concedido...\n");
      do {
          printf("\n\t\t\tPANEL DE SUPERVISOR");
          printf("\n\v\t\t1.-Generar reportes/actas");
          printf("\n\t\t2.-Auditoría de archivos");
          printf("\n\t\t3.-Salir al menú principal");
          printf("\n\nIngrese su opción:");
          scanf("%d",&op);
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
      
  } else if(strcmp(admin,nombre)!=0 && strcmp(admin,supNombre)!=0 && strcmp(pasar,contr)!=0){
    printf("\nNombre y contraseña incorrectos\n");
    return 0;
  } else if(strcmp(admin,nombre)!=0 && strcmp(admin,supNombre)!=0) {
    printf("\nNombre incorrecto\n");
    return 0;
  } else {
    printf("\nContraseña incorrecta\n");
    return 0;
  } 
}

// Crea el padrón estructurado con Cédula;Nombre;Edad usando un delimitador ';'
void inicializarPadronAutomatico() {
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

// Esta es la función principal que inicia la ejecución completa del programa.
// Configura la consola para caracteres especiales, escanea los votos previos
// y mantiene activo el menú general hasta que se decida cerrar la aplicación.
int main(void){
  SetConsoleOutputCP(65001);
   char pasar[20];
   char admin[20];
   char c;
   int i = 0, ver, dif = 0;
   int j = contarVotosExistentes(); 
   int opcion = 0;

   inicializarPadronAutomatico();

 while(opcion!=3){
   printf("\n\v\t------------------Programa de elecciones---------------\n");
   printf("Ingrese su solicitud\n");
   printf("\v\t\t1.- Módulo de estudiantes\n");
   printf("\t\t2.- Módulo de administrador\n");
   printf("\t\t3.- Salir\n\n");
   printf("Escoja su opcion: ");
   scanf("%d",&opcion);
   while(getchar() != '\n');
   switch (opcion){ 
   case 2:
   printf("Ingrese su nombre de usuario: ");
   fgets(admin,20,stdin);
   admin[strcspn(admin,"\n")] = '\0';
  printf("Ingrese su contraseña: ");
  i=0;
  while((c = getch()) != 13)  {
        pasar[i] = c;
        i++;
        printf("*");
    }
    pasar[i] = '\0';
    ver=panelAdministrador(admin,pasar);
    if (ver > 0) {
        dif = ver;
    } else {
        dif = 0;
    }
    break;

    case 1:
   ver = panelEstudiantes(j, dif);
   if(ver == 0){
    j++;
   }
   else if(ver==1){
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