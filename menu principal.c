#include <stdio.h>
#include <conio.h>
#include <string.h>
void controlarPanel(){
   
    printf("Nueva eleccion \n");
    printf("")

}
int panelAdministrador(char admin[],char pasar[]){
  char nombre[]="Administrador1";
  char contr[]="123456";
  int op;
  if(strcmp(admin,nombre)==0 && strcmp(pasar,contr)==0){
  printf("\nAcceso consedido, presione enter para continuar");
  printf("\n1.-Eleccion nueva");
  printf("\n2.-Continuar con eleccion previa");
  printf("\n3.-Borrar voto ilegal");
  printf("\n4.-Eliminar Nombre de usuario");
  printf("\n5.-Generar reportes/actas");
  printf("\n6.-Audirtoria de archivos");
  printf("\n7.-Administrador de usuarios");
  printf("\n8.-Resultado");
  printf("\n9.-Salir al menu principal");
  switch(op)
  {
    case 1:
    controlarPanel();
    break;
    case 2:
    break;
    case 3:
    break;
    case 4:
    break;
    case 5:
    break;
    case 6:
    break;
    default:
    break;
  }
  return 0;
  }  else if(strcmp(admin,nombre)!=0 && strcmp(pasar,contr)!=0){
    printf("\nNombre y contrasenia incorrectos\n");
    return 0;
  }else if(strcmp(admin,nombre)!=0)
  {
  printf("\nNombre incorrecto\n");
  return 0;
  }
   else if(strcmp(pasar,contr)!=0){
  printf("\nContrasenia incorrecta\n");
  return 0;
 } 
}
int main(void)
{
   char pasar[20];
   char admin[20];
   char c;
   int i = 0,ver; 
   int opcion; 
   repeticion:
   printf("------------------Programa de elecciones---------------\n");
   printf("Ingrese su solicitud:\n");
   printf("1.- Modulo de estudiantes:\n");
   printf("2.- Modulo de administrador:\n");
   printf("3.- salir\n");
   printf("Escoja su opcion: ");
   scanf("%d",&opcion);
   while(getchar() != '\n');
   switch (opcion)
   {
   case 1:
   printf("Ingrese su edad: ");
   printf("Ingrese su numero de cedula: ");
    break;
   case 2:
   printf("Ingrese su nombre de usuario: ");
   fgets(admin,20,stdin);
   admin[strcspn(admin,"\n")] = '\0';
  printf("Ingrese su contrasenia: ");
  i=0;
  while((c = getch()) != 13)  
    {
        pasar[i] = c;
        i++;

        printf("*");
    }

    pasar[i] = '\0';
    ver=panelAdministrador(admin,pasar);
    if(ver==0)
    goto repeticion;
    break;
   case 3:
   printf("Programa finalizado");
   return 1;
    break;
   default:
   printf("Opcion no valida\n");
   goto repeticion;
   break;
   } 
   return 0; 
}