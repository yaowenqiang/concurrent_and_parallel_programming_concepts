import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;
import java.util.Iterator;
import java.util.Set;

public class NonBlockingServer {
  public static void main(String[] args) {
    new NonBlockingServer().runServer();
  }
  private void runServer() {
    try {
      final int port = 9876;

      ServerSocketChannel serverSocket = ServerSocketChannel.open();
      serverSocket.configureBlocking(false);
      serverSocket.socket().bind(new InetSocketAddress(InetAddress.getByName("localhost"), port));

      System.out.println("Server accepting connection on port " + port);

      Selector selector = Selector.open();
      serverSocket.register(selector, SelectionKey.OP_ACCEPT);
      while (true) {
        if (selector.select() <= 0) {
          continue;
        }

        acceptConnection(selector.selectedKeys());
      }

    } catch (Exception e) {

    }
  }

  private void acceptConnection(Set keys) {
    try {
      Iterator it = keys.iterator();
      while (it.hasNext()) {
        SelectionKey key = (SelectionKey) it.next();
        it.remove();

      if (key.isAcceptable()) {
        ServerSocketChannel serverSocket = (ServerSocketChannel) key.channel();
        SocketChannel rwChannel = (SocketChannel) serverSocket.accept();
        rwChannel.register(key.selector(), SelectionKey.OP_READ);
      }

      if (key.isReadable()) {
        String request = handleRead(key);
        if (request.length() > 0) {
          SocketChannel rwChannel = (SocketChannel) key.channel();
          request = "Echoing: " + request;
          ByteBuffer buffer = ByteBuffer.wrap(request.getBytes());
          rwChannel.write(buffer);
          System.out.println(new String(buffer.array()));
        }
      }
    }
  } catch (Exception e) {
  }
  }

  private String handleRead(SelectionKey key) {
    try {
      SocketChannel rwChannel = (SocketChannel) key.channel();
      ByteBuffer buffer = ByteBuffer.allocate(1024);
      int bytesCount = rwChannel.read(buffer);
      if (bytesCount > 0) {
        buffer.flip();
        return new String(buffer.array());
      }
    } catch (Exception e) {
    }
    return "No request";
  }

}
