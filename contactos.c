#include <stdio.h>
#include <string.h>

 
int main()
{
    struct
    {
        char contacto[81];
       unsigned short int puerto;
        int ip;/*esta en int para probarlo mas facil, pero en realidad es uint32_t*/
       
    } agenda [1000];
 
    FILE* archivob; /* El archivo con los datos */
    int ultimocontacto = -1; /* Ultimo contacto. Inicialmente -1 porque no hay ninguno */
    char nombrecontacto[200]; /* Para leer del teclado linea por linea */
    int opcion; /* La opcion escogida del menu */
    int i; /* Para recorrer los datos con "for" */
    char contactoc [81];
    unsigned short int puertoc;
    int ipc;/*esta en int para probarlo mas facil, pero en realidad es uint32_t*/
   
 
   
    do
    {
        /* Se despliega el menu */
        puts("\n Mensajeria Instantanea\n");
        puts("Elija una opcion\n");
        puts("1.- Nuevo Contacto");
        puts("2.- Ver agenda de contactos");
        puts("3.- Obtener los datos de un contacto");
        puts("0.- Finalizar Operacion");
 
        scanf("%d", &opcion);
        getchar(); /* para captar la tecla "enter"*/
 
        switch (opcion)
        {
 
            case 1: /* Añadir un nuevo dato y meterlo al arreglo llamado agenda de tipo struct */
                puts ("Añadiendo nuevo contacto\n");
                printf ("Escriba el nombre del contacto nuevo: ");
                scanf ("%s",agenda[ultimocontacto+1].contacto);
 
                printf ("Escriba el puerto del nuevo contacto");
                scanf ("%hu",&agenda[ultimocontacto+1].puerto);
 
                printf ("Escriba la direccion ip del nuevo contacto");
                scanf ("%d",&agenda[ultimocontacto+1].ip);
 
                ultimocontacto ++;
                break;
 
 
            case 2:/* Ver todos los nombres de la lista de contactos mediante un ciclo que recorre el arreglo de la variable agendda de tipo struct */
                puts ("Lista de contactos\n");
                for (i=0; i<=ultimocontacto; i++)
                    puts (agenda[i].contacto);
                break;
 
 
            case 3: /* Recibe el nombre del contacto por parte del usuario y */
                printf ("Escriba el nombre del contacto");
                scanf ("%s",nombrecontacto);
 
                for (i=0; i<=ultimocontacto; i++)
                    if (strcmp (nombrecontacto, agenda[i].contacto) == 0)
                    {
                        strcpy(contactoc,agenda[i].contacto);
                        puertoc=agenda[i].puerto;
                        ipc= agenda[i].ip;

                        printf("%s",contactoc);
                        printf("%hu",puertoc);
                        printf("%d",ipc);
                    }


                break;
 
 
        }
 
    } while (opcion != 0); //Este ciclo no finaliza hasta que el usuario escriba el digito 0 en pantalla. Una vez hecho guarda los contactos en el archivo binario donde esta el arreglo de tipo struct.
 
 
 
    // Finalmente, guardo los cambios
    archivob = fopen("agenda.dat", "ab");
    puts("Guardando contacto\n");
 
    for (i=0; i<=ultimocontacto; i++)
    {
        fprintf (archivob, "%s\n", agenda[i].contacto);
        fprintf (archivob, "%u\n", agenda[i].puerto);
        fprintf (archivob, "%u\n", agenda[i].ip);
       
    }
    fclose(archivob);
 
    printf("Terminado\n");
 
    return 0;
}
