#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int socket_desc, new_socket;
    struct sockaddr_in servidor, cliente;
    socklen_t c;
    int numeroRecibido, numeroModificado;

    // Crear el socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("No se pudo crear el socket\n");
        return 1;
    }

    // Configurar la estructura del servidor
    servidor.sin_family = AF_INET;
    servidor.sin_addr.s_addr = INADDR_ANY;
    servidor.sin_port = htons(5000);

    // Enlazar el socket
    if (bind(socket_desc, (struct sockaddr *)&servidor, sizeof(servidor)) < 0) {
        printf("Error al enlazar el socket\n");
        return 1;
    }

    // Escuchar por conexiones
    listen(socket_desc, 3);
    printf("Esperando conexiones...\n");

    // Aceptar conexiones entrantes
    c = sizeof(struct sockaddr_in);
    new_socket = accept(socket_desc, (struct sockaddr *)&cliente, &c);
    if (new_socket < 0) {
        printf("Error al aceptar la conexión\n");
        return 1;
    }
    printf("Conexión aceptada.\n");

    // Intercambio de números enteros
    while (1) {
        // Recibir un número del cliente
        if (recv(new_socket, &numeroRecibido, sizeof(int), 0) < 0) {
            printf("Error al recibir número\n");
            return 1;
        }

        // Si el cliente envía un 0, se termina la conexión
        if (numeroRecibido == 0) {
            printf("El cliente envió un 0. Terminando...\n");
            break;
        }

        // Incrementar el número recibido
        numeroModificado = numeroRecibido + 1;
        printf("Número recibido: %d, número modificado: %d\n", numeroRecibido, numeroModificado);

        // Enviar el número modificado al cliente
        if (send(new_socket, &numeroModificado, sizeof(int), 0) < 0) {
            printf("Error al enviar número\n");
            return 1;
        }
    }

    // Cerrar el socket
    close(new_socket);
    close(socket_desc);

    return 0;
}
