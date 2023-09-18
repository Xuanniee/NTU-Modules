// Import Packages
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Random;

public class Rfc865UdpServer {
    public static void main(String[] argv) {
        //
        // 1. Open UDP socket at well-known port
        //
        DatagramSocket socket = null;
        try {
            // Quote of the Day uses Port 17. Open to listen for requests
            socket = new DatagramSocket(17);
            System.out.println("UDP Quote of the Day Socket is running...");
        } 
        catch (SocketException e) {
            // Error with Socket Creation
            e.printStackTrace();
        }


        while (true) {
            try {
                //
                // 2. Listen for UDP request from client
                //
                // Create a Byte Array to store the data from Client
                byte[] receiveData = new byte[1024];
                // Encapsulate the Data received from the Client, with the location and max data that can be stored
                DatagramPacket request = new DatagramPacket(receiveData, receiveData.length);
                // Receive the Data from the Client and store it in the request packet.
                socket.receive(request);
                
                //
                // 3. Send UDP response to client after we receive a request
                //

                // Retrieve the Client's IP Address & Port Number from the Request
                InetAddress clientAddress = request.getAddress();
                int clientPort = request.getPort();

                // Generate a Random Quote to return to the Client
                String randomQuoteResponse = getRandomQuote();

                // Convert the Quotes into Bytes so that we can send the data over
                byte[] sendData = randomQuoteResponse.getBytes();

                // Encapsulate the Data into another Datagram Packet to be sent back to the client
                // Place the Data, Size of Data, Address and Port Number
                DatagramPacket responseToClient = new DatagramPacket(sendData, sendData.length, clientAddress, clientPort);

                // Send the response
                socket.send(responseToClient);
                System.out.println("Sending a QOTD Response to " + clientAddress + ":" + clientPort + ": " + randomQuoteResponse);
            } 
            catch (IOException e) {
                // IO Error
                e.printStackTrace();
            }
        }
    }
    // Helper function to get a random quote
    private static String getRandomQuote() {
        String[] quotes = {
            "The only way to do great work is to love what you do. - Steve Jobs",
            "In three words I can sum up everything I've learned about life: it goes on. - Robert Frost",
            "The future belongs to those who believe in the beauty of their dreams. - Eleanor Roosevelt",
            "To be yourself in a world that is constantly trying to make you something else is the greatest accomplishment. - Ralph Waldo Emerson",
            "Life is what happens when you're busy making other plans. - John Lennon"
        };

        Random random = new Random();
        int randomIndex = random.nextInt(quotes.length);
        return quotes[randomIndex];
    }
}