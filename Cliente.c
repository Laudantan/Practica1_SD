#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int socket_desc;
    struct sockaddr_in servidor;
    char *mensaje;
    char respuestaServidor[2000];

    // Crear el socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("No se pudo crear el socket\n");
        return 1;
    }

    // Configurar la dirección del servidor
    servidor.sin_addr.s_addr = inet_addr("127.0.0.1"); // Dirección IP del servidor
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(5000); // Puerto del servidor

    // Conectar al servidor
    if (connect(socket_desc, (struct sockaddr *)&servidor, sizeof(servidor)) < 0) {
        printf("Error al conectar\n");
        return 1;
    }
    printf("Conectado al servidor\n");

    // Enviar un mensaje al servidor
    mensaje = "Hola";
    if (send(socket_desc, mensaje, strlen(mensaje), 0) < 0) {
        printf("Error al enviar mensaje\n");
        return 1;
    }
    printf("Mensaje enviado: %s\n", mensaje);

    // Recibir la respuesta del servidor
    if (recv(socket_desc, respuestaServidor, 2000, 0) < 0) {
        printf("Error al recibir respuesta\n");
        return 1;
    }
    printf("Respuesta del servidor: %s\n", respuestaServidor);

    // Cerrar el socket
    close(socket_desc);

    return 0;
}
