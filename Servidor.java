import java.io.*;
import java.net.*;

public class Servidor {
    public static void main(String[] args) {
        try {
            // Crear el socket del servidor en el puerto 5000
            ServerSocket servidor = new ServerSocket(5000);
            System.out.println("Servidor escuchando en el puerto 5000...");

            // Aceptar conexiones de clientes
            Socket socket = servidor.accept();
            System.out.println("Cliente conectado.");

            // Crear flujos para recibir y enviar mensajes
            BufferedReader entrada = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter salida = new PrintWriter(socket.getOutputStream(), true);

            // Leer el mensaje enviado por el cliente
            String mensajeCliente = entrada.readLine();
            System.out.println("Mensaje recibido del cliente: " + mensajeCliente);

            // Responder al cliente
            salida.println("Hola, que tal");

            // Cerrar la conexión
            entrada.close();
            salida.close();
            socket.close();
            servidor.close();
            System.out.println("Conexión cerrada.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}