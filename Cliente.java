import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Cliente {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        try {
            // Conectar al servidor en localhost (127.0.0.1) en el puerto 5000
            Socket socket = new Socket("127.0.0.1", 5000);
            System.out.println("Conectado al servidor.");

            // Crear flujos para enviar y recibir datos
            DataOutputStream salida = new DataOutputStream(socket.getOutputStream());
            DataInputStream entrada = new DataInputStream(socket.getInputStream());

            int numeroEnviado;
            do {
                // Pedir al usuario un número entero
                System.out.print("Introduce un número entero (0 para terminar): ");
                numeroEnviado = scanner.nextInt();

                // Enviar el número al servidor
                salida.writeInt(numeroEnviado);

                if (numeroEnviado != 0) {
                    // Recibir el número modificado del servidor
                    int numeroRecibido = entrada.readInt();
                    System.out.println("Número recibido del servidor: " + numeroRecibido);
                }

            } while (numeroEnviado != 0);

            // Cerrar la conexión
            entrada.close();
            salida.close();
            socket.close();
            System.out.println("Conexión cerrada.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}