#include <stdio.h>
#include <string.h>

// FALTA QUE GUARDE LOS DATOS DESPUES DE CERRADO EL PROGRAMA!
// FALTA PASAR EL CHAR A IP
 
int main()
{
    struct
    {
        char contacto[81];
        unsigned short int puerto;
        char ip[16]; /*esta en char para probarlo mas facil, pero en realidad es uint32_t*/
       
    } agenda [1000];
 
    FILE* archivob; /* El archivo con los datos */
    int ultimocontacto = -1; /* Ultimo contacto. Inicialmente -1 porque no hay ninguno */
    char nombrecontacto[200]; /* Para leer del teclado linea por linea */
    int opcion; /* La opcion escogida del menu */
    int i; /* Para recorrer los datos con "for" */
    char contactoc [81];
    unsigned short int puertoc;
    char ipc[16];/*esta en int para probarlo mas facil, pero en realidad es uint32_t*/


	archivob = fopen("agenda.dat", "rt");
    	if (archivob != NULL)
    	{
        puts("Leyendo datos...");
        while (! feof(archivob)) 
        {
            /* Intento leer cada dato, y lo guardo si lo he conseguido */
            
	    fgets(nombrecontacto, 81, archivob);       
            if (feof(archivob)) break;  /* Si no he podido, interrumpo */
            if (strlen(nombrecontacto) > 0)      
            nombrecontacto[strlen(nombrecontacto) -1]  = '\0';
            strcpy(agenda[ultimocontacto+1].contacto, nombrecontacto);

            fgets(nombrecontacto, 80, archivob);       
            if (feof(archivob)) break;
            if (strlen(nombrecontacto) > 0)
            nombrecontacto[strlen(nombrecontacto)  -1]  ='\0';
            strcpy(agenda[ultimocontacto+1].ip, nombrecontacto);
 
            
 	   fgets(nombrecontacto, 20, archivob);
           
           if (feof(archivob)) break;
           sscanf(nombrecontacto, "%hd", &agenda[ultimocontacto+1].puerto);
	 
	   
            /* Si pude leer todo, hay una ficha mas */
            ultimocontacto ++;
        }
        fclose(archivob);
    }
 
    printf("Leidos %d datos", ultimocontacto+1);
 




















   
 
   
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
 
                printf ("Escriba el puerto del nuevo contacto: ");
                scanf ("%hu",&agenda[ultimocontacto+1].puerto);
 
                printf ("Escriba la direccion ip del nuevo contacto: ");
                scanf ("%s",agenda[ultimocontacto+1].ip);
 
                ultimocontacto ++;
                break;
 
 
            case 2:/* Ver todos los nombres de la lista de contactos mediante un ciclo que recorre el arreglo de la variable agenda de tipo struct */
               
	        puts ("Lista de contactos\n");
		
                for (i=0; i<=ultimocontacto; i++)
                    puts (agenda[i].contacto);
                
		break;
 
 
            case 3: /* Recibe el nombre del contacto por parte del usuario y */
                printf ("Escriba el nombre del contacto: ");
                scanf ("%s",nombrecontacto);
 
                for (i=0; i<=ultimocontacto; i++)
                    if (strcmp (nombrecontacto, agenda[i].contacto) == 0)
                    {
                        strcpy(contactoc,agenda[i].contacto);
                        puertoc=agenda[i].puerto;
			strcpy(ipc,agenda[i].ip);
                        

			printf("Nombre: %s \n",contactoc);
			printf("Puerto: %hu \n",puertoc);
			printf("Direccion IP: %s",ipc);
                     }


                break;
 
 
        }
 
    } while (opcion != 0); //Este ciclo no finaliza hasta que el usuario escriba el digito 0 en pantalla. Una vez hecho guarda los contactos en el archivo binario donde esta el arreglo de tipo struct.
 
 
 
    // Finalmente, guardo los cambios
    
	archivob = fopen("agenda.dat", "wt");
    
 
    for (i=0; i<=ultimocontacto; i++)
    {
        fprintf (archivob, "%s\n", agenda[i].contacto);
        fprintf (archivob, "%u\n", agenda[i].puerto);
        fprintf (archivob, "%s\n", agenda[i].ip);
       
    }
    fclose(archivob);
 
    printf("Terminado\n");
 
    return 0;
}
