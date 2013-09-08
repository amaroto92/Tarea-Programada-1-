#include <stdio.h>
#include <string.h>


void main()
{
 /* Se define la estructura y se crea un arreglo de tipo struct llamado agenda donde van a ir todos los contactos */
    struct
    {
        char contacto[81];
        unsigned short int puerto;
        char ip[16];
       
    } agenda [1000]; // La agenda tendra la capacidad de guardar 1000 contactos
 
    FILE* archivob; /* El archivo de tipo file que va a contener a los contactos */
    FILE* archivob2;/* El archivo de tipo file que va a contener el puerto de escucha local */
    int opcion;/* La opcion escogida del menu */
    opcion=5; // se inicializa en cualquier valor para que no tome el valor default de 0 
    char buffer[200]; /*Lee del teclado*/
    int ultimocontacto = -1; /* Ultimo contacto. Inicialmente -1 porque no hay ninguno */
    int i; /* Para recorrer los datos con "for" */
    char contactoc [81]; /*Variable que va a contener el dato del nombre del contacto */
    unsigned short int puertolocal;/*Variable que va a contener el dato del puerto local */
    unsigned short int puertoc;/*Variable que va a contener el numero del puerto del usuario a buscar*/
    char ipc[16];/*Variable que posee la direccion ip del usuario a buscar*/

/*Empieza el proceso de lectura del archivo que contiene los contactos */

archivob = fopen("agenda.dat", "rt");
     if (archivob != NULL)
     {
        while (! feof(archivob)) // mientras no llegue al final del archivo:
        {
            /* Lee los datos y lo guarda en el caso de que existan*/
            fgets(buffer, 81, archivob);
            if (feof(archivob)) break; /*En caso de no conseguir leer nada realiza un break */
            if (strlen(buffer) > 0) /*If que compara que la linea que lee tenga tamaño mayor a 0 */
            buffer[strlen(buffer) -1] = '\0';/*Establece que el len de la linea -1 va a ser el fin del string */
            strcpy(agenda[ultimocontacto+1].contacto, buffer);/*Copia la linea que pertenece a contacto en el array agenda */

 
            /*Aca se establece el mismo proceso del contacto, nada mas que el modo de copia cambia por ser un short int */
           fgets(buffer, 20, archivob);
           if (feof(archivob)) break;
           sscanf(buffer, "%hd", &agenda[ultimocontacto+1].puerto);
           
            /*Lo mismo con la direccion ip*/
            fgets(buffer, 80, archivob);
            if (feof(archivob)) break;
            if (strlen(buffer) > 0)
            buffer[strlen(buffer) -1] ='\0';
            strcpy(agenda[ultimocontacto+1].ip, buffer);

            /* Si logra leerlo todo, existe un contacto mas */
            ultimocontacto ++;
        }
        fclose(archivob); // cierra el archivo
    }
    printf(" %d Contactos Existentes en la Agenda\n", ultimocontacto+1);
    
   
    
    while (opcion != 0){ // Mientras que el usuario no digite 0 para salir, Haga:
        /* Interaccion con el usuario (Menú)*/
        puts("\n Mensajeria Instantanea\n");
        puts("Elija una opcion\n");
        puts("1.- Nuevo Contacto");
        puts("2.- Ver agenda de contactos");
        puts("3.- Escoger los datos de un contacto para comunicarse");
        puts("4.- Agregar o actualizar puerto de escucha local");
        puts("0.- Continuar al envio y recepcion de mensajes");
        scanf("%d", &opcion);
        getchar(); /*capta la tecla enter*/

        /*Comienza el ciclo que involucra el menú*/
        switch (opcion)
        {
            /* Añadir un nuevo contacto con sus respectivos datos y lo guarda en el arreglo agenda*/
            case 1:
                puts ("Añadiendo nuevo contacto\n");
                printf ("Escriba el nombre del contacto nuevo:\n ");
                scanf ("%s",agenda[ultimocontacto+1].contacto);
 
                printf ("Escriba el puerto del nuevo contacto:\n ");
                scanf ("%hu",&agenda[ultimocontacto+1].puerto);
 
                printf ("Escriba la direccion ip del nuevo contacto:\n ");
                scanf ("%s",agenda[ultimocontacto+1].ip);
 
                ultimocontacto ++;
		puts ("Contacto guardado exitosamente!\n");
                break;
 
 /* Ver todos los nombres de la lista de contactos mediante un ciclo que recorre el arreglo agenda de tipo struct hasta que i sea mayor al indice del ultimocontacto */
            case 2:
puts ("Lista de contactos\n");

                for (i=0; i<=ultimocontacto; i++)
                    puts (agenda[i].contacto);
                
break;
/* Recibe el nombre del contacto que desea buscar, recorre el arreglo, compara y guarda e imprime la informacion de ese contacto mediante una variable */
            case 3:
                    printf ("Escriba el nombre del contacto:\n ");
                    scanf ("%s",buffer);
                    for (i=0; i<=ultimocontacto; i++)
                    if (strcmp (buffer, agenda[i].contacto) == 0) // strcmp, compara strings, si son iguales retorna 0.
                    {
                        strcpy(contactoc,agenda[i].contacto);
                        puertoc=agenda[i].puerto;
                        strcpy(ipc,agenda[i].ip);
                        printf("Tenemos los siguientes datos en memoria para comunicarse con:\n");	
                        printf("Nombre: %s \n",contactoc);
                        printf("Puerto: %hu \n",puertoc);
                        printf("Direccion IP: %s \n",ipc);
                    printf("Si desea empezar a comunicarse con esta persona digite 0 \n ");


                     }
                break;
    /* Recibe el nombre del contacto que desea buscar, recorre el arreglo, compara y guarda e imprime la informacion de ese contacto mediante una variable */
            case 4:
                     
            
                     /* Proceso de lectura del archivo del puerto local */
    
                    archivob2 = fopen("puertolocal.dat", "rt"); 
                    if (archivob2 != NULL)
                    {
                        while (! feof(archivob2)) 
                        {
                        /*Guarda lo leido del archivo del puerto local en la variable para su posterior uso*/
                        fgets(buffer, 20, archivob2);
                        if (feof(archivob2)) break;
                        sscanf(buffer, "%hd", &puertolocal);
                        }
                        fclose(archivob2); // cierra el archivo
                    }
                    printf("Puerto de escucha local actual: %d \n ", puertolocal);
                     
                     printf ("Escriba el puerto de escucha local que desea guardar:\n ");
                     scanf ("%hu",&puertolocal);
                     archivob2 = fopen("puertolocal.dat", "w+");
                     fprintf (archivob2, "%u\n", puertolocal);
                     fclose(archivob2); // cierra el archivo binario
                     printf ("El puerto local se ha guardado correctamente\n ");
                break;
        }
 
    } //Este ciclo no finaliza hasta que el usuario escriba el digito 0 en pantalla. Una vez hecho guarda los contactos en el archivo binario donde esta el arreglo de tipo struct.
 
// Se guardan los contactos ingresados en el arreglo de tipo struct
archivob = fopen("agenda.dat", "wt"); // abre el archivo binario
    for (i=0; i<=ultimocontacto; i++)
    {
        fprintf (archivob, "%s\n", agenda[i].contacto); 
        fprintf (archivob, "%u\n", agenda[i].puerto);
        fprintf (archivob, "%s\n", agenda[i].ip);
       
    }
    fclose(archivob); // cierra el archivo binario
 
}
