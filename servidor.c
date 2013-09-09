#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <signal.h>




void main(int argc, char *argv[]){ // Servidor Proceso Padre.
int puertolocal;
puertolocal = atoi(argv[1]);
char buffer1[256];



printf("Este es el puerto servidor que mandaron desde el main: %d\n",puertolocal); // Para checkear


// 1. Inicializar el Socket.

int idSocket;
struct sockaddr_in DireccionSocketServidor;// Estructura tipo sockaddr_in para el servidor. //
struct sockaddr_in DireccionSocketCliente; // Estructura tipo sockaddr_in para el cliente. //
int idConexionCS; // Crea ID para la conexion Cliente-Servidor
int idread; // id del read


//PARAMETROS
//AF_INET: deja que se conecte entre computadoras distintas.
//SOCK_STREAM: indica que el socket es orientado a conexion.
//3er parametro se pone 0.

idSocket = socket (AF_INET, SOCK_STREAM, 0);

if (idSocket < 0)

{
    fprintf(stderr,"Error creando socket servidor! \n\a");
    exit(1);
} // Manejo de errores. El idSocket da un numero negativo si tuvo algun problema.


 bzero((char *) &DireccionSocketServidor, sizeof(DireccionSocketServidor));



//2. Bind. Enlaza el socket con un puerto.
//Ya el socket esta inicializado y ahora lo vamos a atender.
//Su parametro es una estructura sockaddr_in que contiene lo siguiente:



DireccionSocketServidor.sin_family = AF_INET;
//AF_INET: deja que se conecte entre computadoras distintas.

DireccionSocketServidor.sin_addr.s_addr =INADDR_ANY;
//INADDR_ANY: Enlaza cualquier IP.

DireccionSocketServidor.sin_port = htons(puertolocal); // htons(int) convierte de entero a tipo network.
//Aqui se pone el puerto (servidor)




if(bind(idSocket,(struct sockaddr *)&DireccionSocketServidor,sizeof (DireccionSocketServidor)) == -1) //Enlaza el socket con la direccion
{
fprintf(stderr,"No se pudo unir el socket servidor\n\a");
exit(1); // Manejo de errores devuelve -1 si tuvo algun error en el bind.
}


//3. Listen. Le decimos al servidor que empieze a escuchar solicitudes de clientes.
//PARAMETROS
//-ID del socket
//-Numero maximo de solicitudes que pueda tener en espera en este caso 8.




if(listen(idSocket,8) == -1)
{
fprintf(stderr,"No se escuchar solicitudes servidor\n\a");
exit(1); // Manejo de errores el listen devuelve -1 si da algun error.
}


//4. Accept. El servidor acepta el cliente, el primero en la cola. Se crea un ID de la conexion de ambos. Todas las variables que inicializamos a continuacion son parametros del Accept.



socklen_t largodircliente = sizeof(DireccionSocketCliente); // Largo de estructura del cliente.

idConexionCS = accept (idSocket,(struct sockaddr *) &DireccionSocketCliente, &largodircliente); // Hace un cast de sockaddr_in a sockadrr.

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
