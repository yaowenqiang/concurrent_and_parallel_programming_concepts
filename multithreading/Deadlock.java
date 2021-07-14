public class Deadlock {
  static Object lock1 = new Object();
  static Object lock2 = new Object();

  public static void main(String argv[])
  {
    Thread thread1 = new Thread() {
      public void run() {
        synchronized(lock1) {
          print("thread1 holds lock1");
          try{
            Thread.sleep(2);
          } catch (Exception e) {}
          print("thread1 waiting for lock2");
          print("\t(thread1 needs lock2 to release lock1...)");
          synchronized(lock2) {
            print("thread1 holds lock1 and lock2");

          }
        }
      }
    };

    Thread thread2 = new Thread() {
      public void run() {
        synchronized(lock2) {
          print("thread1 holds lock2");
          try{
            Thread.sleep(2);
          } catch (Exception e) {}
          print("thread2 waiting for lock1");
          print("\t(thread1 needs lock1 to release lock2...)");
          synchronized(lock1) {
            print("thread2 holds lock2 and lock1");

          }
        }
      }
    };

    thread1.start();
    thread2.start();
  }

  private static void print (Object obj)
  {
    System.out.println(obj);
  }
}
