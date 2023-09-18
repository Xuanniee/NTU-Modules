// Import Packages
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Random;

public class Rfc865UdpClient {

    public static void main(String[] argv) {
        // static DatagramSocket socket;
        DatagramSocket socket = null;

        try {
            //
            // 1. Open UDP socket for Communication
            //
            socket = new DatagramSocket();
        } 
        catch (SocketException e) {
            e.printStackTrace();
        }

        try {
            //
            // 2. Send UDP request to server
            //

            // Retrieve the Server Address and Server Port

            // IP Address of School
            InetAddress serverAddress = InetAddress.getByName("SWLAB2-C.scse.ntu.edu.sg");

            // LocalHost IP Address
            InetAddress localServerAddress = InetAddress.getByName("127.0.0.1"); // or use "localhost" as the argument
            int serverPort = 17;                                                                // Standard Port for QOTD

            // Create an Empty Request Packet as QOTD have no specific data
            // Remember it is where data is found, size of data, address and port
            DatagramPacket testRequest = new DatagramPacket(new byte[0], 0, serverAddress, serverPort);

            // Create the Request Packet to Server
            String requestData = "Ng Xuan Yi, TCCA, School IPAddress";
            // Convert to Bytes
            byte[] requestDataByBytes = requestData.getBytes();
            DatagramPacket request = new DatagramPacket(requestDataByBytes, requestDataByBytes.length, serverAddress, serverPort);
            
            // Send the Request
            socket.send(request);
            
            //
            // 3. Receive UDP reply from server
            //

            // Create a Buffer to receive the Server's Response
            byte[] receiveData = new byte[1024];
            DatagramPacket reply = new DatagramPacket(receiveData, receiveData.length);

            // Receive the Response
            socket.receive(reply);

            // Convert the Byte Data into a String and Print it
            String quoteOfTheDayString = new String(reply.getData(), 0, reply.getLength());
            System.out.println("Quote of the Day: " + quoteOfTheDayString);
        } catch (IOException e) {
            e.printStackTrace();
        }
        // finally {
        //     // Check if need to close the socket
        //     if (socket != null && !socket.isClosed()) {
        //         socket.close();
        //     }
        // }
    }
}
