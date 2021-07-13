public class RaceC {
  static int n;
  static void race() {
    n = 0;
    long limit = Integer.MAX_VALUE * 21;
    Thread t1 = new Thread() {
      public void run() {
        for(long i = 0; i < limit; i++) {
          n = n + 1;
        }
      }
    };
    Thread t2 = new Thread() {
      public void run() {
        for(long i = 0; i < limit; i++) {
          n = n - 1;
        }
      }
    };
    t1.start();
    t2.start();

    try {
      t1.join();
      t2.join();
    } catch(Exception e) {

    }

    System.out.println("n's value is : "+ n);
  }

}

class Main {
  public static void main(String[] args) {
    for (int i = 0; i < 8; i++) {
      RaceC.race();
    }
  }
}
