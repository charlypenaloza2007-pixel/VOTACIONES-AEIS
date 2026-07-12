#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

typedef struct {
    char nombre[50];
    int votos;
} Resultado;

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
    printf("Ingrese los datos de su candidato #%d: ", i + 1);
    fgets(candidatos[i], 50, stdin);
    candidatos[i][strcspn(candidatos[i], "\n")] = '\0';
    fprintf(archivo, "Candidato %d: %s\n", i + 1, candidatos[i]);
    }
    fclose(archivo);
    return k;
   }
  }
}

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

int panelEstudiantes(int j, int cantidad)
{
    int votacion;
    char ruta[150];
    char cedula[50];
    int edad;
    FILE *archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\candidatos.txt", "r");

    if (archivo == NULL)
    {
        printf("No se encontro el archivo de candidatos.\n");
        return 1;
    }

    char Linea[100];
    int total = 0;
    comp:
    printf("\v\t\t//// Módulo de votación ///\n");
     printf("Ingrese su Edad: ");
    scanf("%d",&edad);
    
    do {
        printf("Ingrese su número de cédula: ");
        scanf("%49s", cedula);
        printf("\n-----------------------------\n");
        while(getchar() != '\n');
        
        if (validarCedulaEcuatoriana(cedula) == 0) {
            continue; 
        }

        if (yaVoto(cedula)) {
            printf("\nAviso: Usted ya registró su voto con esta cédula.\n");
            return 2; 
        }
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

    cantidad = total;

    printf("Si desea votar en blanco, ingrese 0.\n");
    printf("Si desea votar en nulo, ingrese  -1.\n");
    printf("Ingrese el numero del candidato que desea votar:\n");
    

    scanf("%d", &votacion);
    if(votacion <-2 || votacion > cantidad || edad < 18 )
    {
        printf("Voto inválido.\n");
        goto comp;
    }else{
    while(getchar() != '\n');


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
  for (int i = 0; i < 5; i++) {
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
  return 0;
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
    
   *total=(float)res[0].votos/(*a+*blanco+*nulo);
    
for(int i = 0; i < x; i++)
{
    acta[i] = res[i];
}
}

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
        printf("Error al crear acta\n");
        return;
    }
  fprintf(archivo,"\v\t\t==============ACTA DE RESULTADOS================\n");
  printf("\v\t\t==============ACTA DE RESULTADOS================\n");
  for(int i=0;i<cantidad;i++) {
     fprintf(archivo,"\nCandidato %d: %s, votos: %d",i+1,acta[i].nombre,acta[i].votos);
     printf("Candidato %d: %s, votos: %d\n",i+1,acta[i].nombre,acta[i].votos);
  }
  printf("Votos en blanco: %d\n",blanco);
  printf("Votos nulos: %d\n",nulo);
  printf("---------------------------------\n");
  printf("El ganador es: %s con %d votos\n",acta[0].nombre,acta[0].votos);
  printf("El total de votos es: %d\n",a+blanco+nulo);
  printf("El margen de votos total es %.2f %%\n",total*100);
  
  fprintf(archivo,"Votos en blanco: %d\n",blanco);
  fprintf(archivo,"Votos nulos: %d\n",nulo);
  
  fprintf(archivo,"El ganador es: %s con %d votos\n",acta[0].nombre,acta[0].votos);
  fprintf(archivo,"El total de votos es: %d\n",a+blanco+nulo);
  fprintf(archivo,"El margen de votos total es %.2f %%\n",total*100);
  fclose(archivo);
}

int controlArchivos(){
  FILE *archivo=fopen("C:\\Users\\carlo\\Desktop\\votaciones\\candidatos.txt","r");
  if(archivo!=NULL){
    fclose(archivo);
    return 1;
  }else
  return 0;
}

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

void administrarUsuarios() {
    int opcion_admin;
    
    do {
        printf("\t\t1.- Ver lista de usuarios que ya votaron\n");
        printf("\t\t2.- Buscar y banear usuario\n");
        printf("\t\t3.- Regresar al panel principal\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion_admin);
        while(getchar() != '\n');

        if (opcion_admin == 1) {
            FILE *archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\cedulas.txt", "r");
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
            FILE *archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\cedulas.txt", "r");
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

                archivo = fopen("C:\\Users\\carlo\\Desktop\\votaciones\\cedulas.txt", "w");
                if (archivo) {
                    for (int i = 0; i < n; i++) {
                        fprintf(archivo, "%s\n", arregloCedulas[i]);
                    }
                    fclose(archivo);
                }
                printf("Éxito: El usuario con cédula %s fue eliminado de la lista negra y puede votar.\n", cedulaEliminar);
            } else {
                printf("Error: La cédula %s no se encontró en los registros de votación.\n", cedulaEliminar);
            }
        }
        else if (opcion_admin != 3) {
            printf("\nOpción no válida. Intente de nuevo.\n");
        }

    } while (opcion_admin != 3);
}
int contarVotosExistentes() {
    char ruta[200];
    int i = 0;
    FILE *archivo;
    
    // Bucle infinito que busca archivos hasta que encuentra uno que no existe
    while (1) {
        snprintf(ruta, sizeof(ruta), "C:\\Users\\carlo\\Desktop\\votaciones\\datos%d.txt", i);
        archivo = fopen(ruta, "r");
        
        if (archivo == NULL) {
            // Si el archivo no existe, significa que este es el número de voto que sigue
            return i; 
        }
        fclose(archivo);
        i++;
    }
}

int panelAdministrador(char admin[],char pasar[]){
  char nombre[]="Administrador1";
  char contr[]="123456";
  int op,comp=0;
  int cont = 0, cont1 = 0, cont2 = 0, cont3 = 0, cont4 = 0, a=0;
  float total=0;
  Resultado acta[5];
    int blanco = 0, nulo = 0,dif=contarCandidatos();
  if(strcmp(admin,nombre)==0 && strcmp(pasar,contr)==0){
  printf("\nAcceso concedido, presione enter para continuar");
  printf("\n\v\t\t1.-Elección nueva");
  printf("\n\t\t2.-Generar reportes/actas");
  printf("\n\t\t3.-Auditoría de archivos");
  printf("\n\t\t4.-Administrador de usuarios");
  printf("\n\t\t5.-Resultado");
  printf("\n\t\t6.-Salir al menú principal");
  printf("\n\nIngrese su opción:");
  scanf("%d",&op);
  switch(op)
  {
    case 1:
    comp=controlArchivos();
    if(comp==1)
    {
       printf("Ya existe una elección activa, no se puede crear una nueva\n");
       return 0;
    }else
    {
      return controlarPanel();
    }
      case 2:
      generarActa(dif);
      return 0;
    case 3:
      printf("Hola\n");
      return 0;
    case 4:
      administrarUsuarios();
      return 0;
    case 5:
      {
        contarResultados(&cont,&cont1,&cont2,&cont3,&cont4,&blanco,&nulo);
        resultadosFinales(dif,&cont,&cont1,&cont2,&cont3,&cont4,&blanco,&nulo,&a,&total,acta);
      }
      return 0;
    case 6:
      return 0;
    default:
      return 0;
  }
  }  else if(strcmp(admin,nombre)!=0 && strcmp(pasar,contr)!=0){
    printf("\nNombre y contraseña incorrectos\n");
    return 0;
  }else if(strcmp(admin,nombre)!=0)
  {
  printf("\nNombre incorrecto\n");
  return 0;
  }
   else if(strcmp(pasar,contr)!=0){
  printf("\nContraseña incorrecta\n");
  return 0;
 } 
}

  int main(void){
  SetConsoleOutputCP(65001);
   char pasar[20];
   char admin[20];
   char c;
   int i = 0, ver, dif = 0;
   int j = contarVotosExistentes(); 
   int opcion = 0;

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

//fin