// Librerias

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <signal.h>


void servidor(int puertolocal){ // Servidor Proceso Padre.

char buffer1[256]; // buffer de memoria que contiene el string de lectura.

printf("Este es el puerto servidor que mandaron desde el main: %d\n",puertolocal); // Para checkear


// 1. Inicializar el Socket.

int idSocketServidor;
struct sockaddr_in DireccionSocketServidor;// Estructura tipo sockaddr_in para el servidor. //
struct sockaddr_in DireccionSocketCliente; // Estructura tipo sockaddr_in para el cliente. //
int idConexionCS; // Crea ID para la conexion Cliente-Servidor
int idread; // id del read


//PARAMETROS
//AF_INET: deja que se conecte entre computadoras distintas.
//SOCK_STREAM: indica que el socket es orientado a conexion.
//3er parametro se pone 0.


idSocketServidor = socket (AF_INET, SOCK_STREAM, 0);

if (idSocketServidor < 0)

{
    fprintf(stderr,"Error creando socket servidor! \n\a");
    exit(1);
} // Manejo de errores. El idSocket da un numero negativo si tuvo algun problema.


bzero((char *) &DireccionSocketServidor, sizeof(DireccionSocketServidor));//borra los datos de DireccionSocketServidor.



//2. Bind. Enlaza el socket con un puerto.
//Ya el socket esta inicializado y ahora lo vamos a atender.
//Su parametro es una estructura sockaddr_in que contiene lo siguiente:



DireccionSocketServidor.sin_family = AF_INET;
//AF_INET: deja que se conecte entre computadoras distintas.

DireccionSocketServidor.sin_addr.s_addr =INADDR_ANY;
//INADDR_ANY: Enlaza cualquier IP.

DireccionSocketServidor.sin_port = htons(puertolocal); // htons(int) convierte de entero a tipo network.
//Aqui se pone el puerto (servidor)




if(bind(idSocketServidor,(struct sockaddr *)&DireccionSocketServidor,sizeof (DireccionSocketServidor)) == -1) //Enlaza el socket con la direccion
{
fprintf(stderr,"No se pudo unir el socket servidor\n\a");
exit(1); // Manejo de errores devuelve -1 si tuvo algun error en el bind.
}


//3. Listen. Le decimos al servidor que empieze a escuchar solicitudes de clientes.
//PARAMETROS
//-ID del socket
//-Numero maximo de solicitudes que pueda tener en espera en este caso 8.




if(listen(idSocketServidor,8) == -1)
{
fprintf(stderr,"No se escuchar solicitudes servidor\n\a");
exit(1); // Manejo de errores el listen devuelve -1 si da algun error.
}


//4. Accept. El servidor acepta el cliente, el primero en la cola. Se crea un ID de la conexion de ambos. Todas las variables que inicializamos a continuacion son parametros del Accept.



socklen_t largodircliente = sizeof(DireccionSocketCliente); // Largo de estructura del cliente.

idConexionCS = accept (idSocketServidor,(struct sockaddr *) &DireccionSocketCliente, &largodircliente); // Hace un cast de sockaddr_in a sockadrr.

if (idConexionCS < 0)
{
fprintf(stderr,"No se pueden aceptar solicitudes servidor\n\a");
exit(1); // Manejo de errores el idConexionCS devuelve un negativo si da error y lo mandamos al std error.
}

//5. Read.



while(1){ // ciclo infinito



bzero(buffer1,256); // limpia el buffer

idread = read(idConexionCS,buffer1,255); // lee del buffer

if (idread < 0){

fprintf(stderr,"No se pudo leer servidor\n\a");
exit(1); // Manejo de errores el n devuelve un negativo si da error

}

printf("\033[2K\r\033[01;34m""Mensaje :\033[00;34m %s",buffer1); // \033[00;37m azul

}



} // Final funcion. Servidor




// Cliente Proceso Hijo.




void cliente (char *ipcliente, int puertocliente) {
// 1. Inicializar el Socket.

struct sockaddr_in DireccionSocketServidor;// estructura que contiene puerto e ip.

struct hostent *ip; // estructura que recibirá información sobre el nodo remoto //

int idSocket;// Identificador para el socket que se va a crear.

int idwrite; // Identificador para el write y poder manejar errores.

char buffer1[256];// Mensaje a enviar

int hayconexion; // variable para salirse del while infinito cuando hay alguna conexion.


printf("Este es el puerto cliente que mandaron desde el main: %d\n",puertocliente); // Checkeo
printf("Este es el ip cliente que mandaron desde el main: %s\n",ipcliente); // Checkeo


idSocket = socket (AF_INET, SOCK_STREAM, 0);

//PARAMETROS
//AF_INET: deja que se conecte entre computadoras distintas.
//SOCK_STREAM: indica que el socket es orientado a conexion.
//3er parametro se pone 0.


if (idSocket == -1){
    fprintf(stderr,"Error creando socket cliente! \n\a");
    exit(1); // Manejo de errores el idSocketCliente devuelve -1 si no se pudo inicializar.
}


ip = gethostbyname(ipcliente); // Agarra la direccion ip en el formato deseado.

if (ip == NULL) {
fprintf(stderr,"Error con la direccion ip. \a\n");
exit(1); // Manejo de errores con la direccion ip.
}

//2. Connect


bzero((char *) &DireccionSocketServidor, sizeof(DireccionSocketServidor)); // limpia la estructura.

DireccionSocketServidor.sin_family = AF_INET;

bcopy((char *)ip->h_addr,(char*)&DireccionSocketServidor.sin_addr.s_addr,ip->h_length); // Direccion IP del cliente

  
DireccionSocketServidor.sin_port = htons(puertocliente);// Puerto del cliente


while(1){ //while infinito para espera de conexion con el cliente.

if (hayconexion >= 0){ // Si hay una conexion: salgase del while infinito.

puts("HAY CONEXION \n");

break;
}

else{

if((hayconexion=connect(idSocket,(struct sockaddr *) &DireccionSocketServidor,sizeof(DireccionSocketServidor))==-1))
{
fprintf(stderr,"No se pudo conectar cliente\n\a");
exit(1);
} // Manejo de errores con el connect.
}// fin del else.
} // Fin del while.


//3. Write

while(1){ // while infinito para escribir muchas veces.

puts("Escriba su mensaje: \n");

bzero(buffer1,256); // Limpia el buffer

fgets(buffer1,255,stdin); // Agarra datos del stdin

idwrite = write(idSocket,buffer1,strlen(buffer1)); // escribe

  
if (idwrite < 0){
    fprintf(stderr,"No se pudo escribir, cliente \n\a");
    exit(1); // Manejo de errores.
}

printf("\033[A\033[2K\033[01;31m""Mensaje Enviado: \033[31m %s ",buffer1); // \033[31m color rojo


}

} // Final cliente




// Funcion de entrada MAIN:


int main()
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
    unsigned short int puertocliente;/*Variable que va a contener el numero del puerto del usuario a buscar*/
    char ipcliente[16];/*Variable que posee la direccion ip del usuario a buscar*/
	unsigned short int puertolocal;/*Variable que va a contener el dato del puerto local */
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
    printf(" %d Contactos Existentes en la Agenda", ultimocontacto+1);
    
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
                        puertocliente=agenda[i].puerto;
                        strcpy(ipcliente,agenda[i].ip);
                        printf("Tenemos los siguientes datos en memoria para comunicarse con:\n");	
                        printf("Nombre: %s \n",contactoc);
                        printf("Puerto: %hu \n",puertocliente);
                        printf("Direccion IP: %s \n",ipcliente);
                    printf("Si desea empezar a comunicarse con esta persona digite 0 \n ");


                     }
                break;

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
 


// Division de procesos FORK

int IDproceso;	

IDproceso = fork(); // Le asignamos el fork que devuelve un entero a una variable para identificar los procesos.



if ( IDproceso < 0 )
{
fprintf(stderr,"No se pudo dividir el proceso\n\a");
exit(1);
}

if ( IDproceso == 0 ) // Proceso Hijo -> Cliente (escribe)
{



printf("soy el proceso hijo\n");

cliente(ipcliente, puertocliente); // le mandamos el ip y el puerto que tomamos del contacto de la agenda.


}

else // Proceso Padre -> Servidor (lee)

{

printf("soy el proceso padre\n");

servidor(puertolocal);

}

return 0;

} 
