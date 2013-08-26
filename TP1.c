#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]){

// Cliente Proceso Hijo.

// Funcion que agarra el puerto:

// FALTA

//Funcion que agarra el IP del servidor:

// FALTA

// 1. Inicializar el Socket.

int idSocketCliente

idSocketCliente = socket (AF_INET, SOCK_STREAM, 0);

//PARAMETROS
//AF_INET: deja que se conecte entre computadoras distintas.
//SOCK_STREAM: indica que el socket es orientado a conexion.
//3er parametro se pone 0.

//2. Connect 

struct sockaddr_in DireccionSocketServidor;

DireccionSocketServidor.sin_family = AF_INET;
DireccionSocketServidor.sin_addr.s_addr = ; // 	IP DEL SERVIDOR
DireccionSocketServidor.sin_port = ; // # DE PUERTO CLIENTE

connect(idSocketCliente,(struct sockaddr *) &DireccionSocketServidor,sizeof(DireccionSocketServidor));

printf(	"Conexion exitosa!");




//** //



// Servidor Proceso Padre.

// 1. Inicializar el Socket.

int idSocketServidor;

idSocketServidor = socket (AF_INET, SOCK_STREAM, 0); 

//PARAMETROS
//AF_INET: deja que se conecte entre computadoras distintas.
//SOCK_STREAM: indica que el socket es orientado a conexion.
//3er parametro se pone 0.

//2. Bind. Enlaza el socket con un puerto.
//Ya el socket esta inicializado y ahora lo vamos a atender. 
//Su parametro es una estructura sockaddr_in que contiene lo siguiente:

struct sockaddr_in DireccionSocketServidor;

DireccionSocketServidor.sin_family = AF_INET;
//AF_INET: deja que se conecte entre computadoras distintas.

DireccionSocketServidor.sin_port = // agarra el puerto que habilita de su computadora *FALTA*;
// Aqui se pone el puerto  (servidor)

DireccionSocketServidor.sin_addr.s_addr =INADDR_ANY; 
//INADDR_ANY: Enlaza cualquier IP.




bind(idSocketServidor,(struct sockaddr *)&DireccionSocketServidor,sizeof (DireccionSocketServidor));
//Enlaza el socket con la direccion

//3. Listen. Le decimos al servidor que empieze a escuchar solicitudes de clientes.

listen(idSocketServidor,8);
//PARAMETROS
//ID del socket
// Numero maximo de solicitudes que pueda tener en espera en este caso 8.

//4. Accept. El servidor acepta el cliente, el primero en la cola. Se crea un ID de la conexion de ambos. Todas las variables que inicializamos a continuacion son parametros del Accept.

int idConexionCS; // Crea ID para la conexion Cliente-Servidor

struct sockaddr_in DireccionSocketCliente; // Estructura tipo sockaddr_in para el cliente. //***

socklen_t largodircliente = sizeof(DireccionSocketCliente); // Largo de estructura del cliente.

idConexionCS = accept (idSocketServidor,(struct sockaddr *) &DireccionSocketCliente, &largodircliente); // Hace un cast de sockaddr_in a sockadrr.

//5. Ya se tiene conexion Cliente-Servidor. Sigue con el read y write para el intercambio de mensajes. Aca ya va el fork.





} // Final MAIN

