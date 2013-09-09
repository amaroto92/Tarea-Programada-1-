// Cliente Proceso Hijo.
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <signal.h>



void main(int argc, char *argv[]){

int puertoc;
puertoc = atoi(argv[2]);

// 1. Inicializar el Socket.

struct sockaddr_in DireccionSocketServidor;

struct hostent *ip; // estructura que recibirá información sobre el nodo remoto //

int idSocket;
int idwrite; // Identificador para el write

char buffer1[256];// Mensaje a enviar

int hayconexion; // variable para salirse del while infinito cuando hay alguna conexion.


printf("Este es el puerto cliente que mandaron desde el main: %d\n",puertoc); // Checkeo
printf("Este es el ip cliente que mandaron desde el main: %s\n",argv[1]); // Checkeo




idSocket = socket (AF_INET, SOCK_STREAM, 0);
//PARAMETROS
//AF_INET: deja que se conecte entre computadoras distintas.
//SOCK_STREAM: indica que el socket es orientado a conexion.
//3er parametro se pone 0.


if (idSocket == -1){
    fprintf(stderr,"Error creando socket cliente! \n\a");
     // Manejo de errores el idSocketCliente devuelve -1 si no se pudo inicializar.
}


ip = gethostbyname(argv[1]); // Agarra la direccion ip en el formato deseado.

if (ip == NULL) {
fprintf(stderr,"Error con la direccion ip. \a\n");
// Manejo de errores con la direccion ip.
}

//2. Connect




bzero((char *) &DireccionSocketServidor, sizeof(DireccionSocketServidor));

DireccionSocketServidor.sin_family = AF_INET;

bcopy((char *)ip->h_addr,(char*)&DireccionSocketServidor.sin_addr.s_addr,ip->h_length); // Direccion IP del cliente

  
DireccionSocketServidor.sin_port = htons(puertoc);// Puerto del cliente


while(1){ //while infinito para espera de conexion con el cliente.

if (hayconexion >= 0){ // Si hay una conexion: salgase del while infinito.

puts("HAY CONEXION \n");



break;
}

else	{


if(hayconexion=connect(idSocket,(struct sockaddr *) &DireccionSocketServidor,sizeof(DireccionSocketServidor))==-1)
{
fprintf(stderr,"No se pudo conectar cliente\n\a");

} // Manejo de errores con el connect.
}// fin del else.
} // Fin del while.


//3. Write

while(1){



puts("Escriba su mensaje: \n");

bzero(buffer1,256); // Limpia el buffer

fgets(buffer1,255,stdin); // Agarra datos del stdin



idwrite = write(idSocket,buffer1,strlen(buffer1)); // escribe
  if (idwrite < 0){
    fprintf(stderr,"No se pudo escribir, cliente \n\a");
     // Manejo de errores.
}

printf("\033[A\033[2K\033[01;31m""Mensaje Enviado: \033[31m %s ",buffer1); // \033[31m color rojo


}
} // Final cliente
