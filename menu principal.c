#include <stdio.h>
#include <conio.h>
#include <string.h>

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
    
    for (int i = 0; i < x; i++) {
      printf("Candidato %d: %s -> %d votos\n", i + 1, res[i].nombre, res[i].votos);
      *a=*a+res[i].votos;  
    }
   *total=(float)res[0].votos/(*a+*blanco+*nulo);
    printf("Votos en blanco: %d\n", *blanco);
    printf("Votos nulos: %d\n", *nulo);
    printf("El ganador es %s con %d votos\n",res[0].nombre,res[0].votos);
    printf("El margen de votos es de %.2f %%\n",*total*100);
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
     fprintf(archivo,"Candidato %d: %s, votos: %d\n",i+1,acta[i].nombre,acta[i].votos);
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
int panelAdministrador(char admin[],char pasar[]){
  char nombre[]="Administrador1";
  char contr[]="123456";
  int op,comp=0;
  int cont = 0, cont1 = 0, cont2 = 0, cont3 = 0, cont4 = 0, a=0,var=0;
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
     printf("¿Desea realizar auditoria del archivo de los candidatos(1)o los votos(2)?");
    printf("\nIngrese 1 o 2: ");
    scanf("%d",&var);
    if(var==1){
      verificarIntegridad();
    }else if(var==2){
      //verificarVotos();
    }else{
      printf("Opcion invalida");
    }
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
