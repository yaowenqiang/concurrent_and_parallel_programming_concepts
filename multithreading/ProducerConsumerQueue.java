/**
 * javac ProducerConsumerQueue.java
 * java ProducerConsumerQueue
 */

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.SynchronousQueue;
import java.util.Random;

public class ProducerConsumerQueue {
  public static void main(String[] args) {
    BlockingQueue<String> dropbox = new SynchronousQueue<String>();
    new Thread(new Producer(dropbox)).start();
    new Thread(new Consumer(dropbox, 12)).start();
    new Thread(new Producer(dropbox)).start();

  }
}

class Producer implements Runnable {
  private BlockingQueue<String> dropbox;
  Producer(BlockingQueue<String> dropbox) {
    this.dropbox = dropbox;
  }

  @Override
  public void run() {
    String importantInfo[] = {
      "a",
      "b",
      "c",
      "d",
      "e",
      "f",
      "g",
      "h",
    };

    try {
      for (String info : importantInfo) dropbox.put(info);
    } catch (InterruptedException e) {}
  }
}

class Consumer implements Runnable {
  private BlockingQueue<String> dropbox;
  private int maxTakes;
  Consumer(BlockingQueue<String> dropbox, int maxTakes) {
    this.dropbox = dropbox;
    this.maxTakes = maxTakes;
  }

  @Override

  public void run() {
    Random random = new Random();
    try {
      for (int i = 0; i < this.maxTakes; i++) {
        String message = dropbox.take();
        System.out.format("Message received: %s\n", message);
        Thread.sleep(random.nextInt(3000));
      }
    } catch (InterruptedException e) {}
  }
}
