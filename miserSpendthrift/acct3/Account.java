package acct3;

import java.util.concurrent.atomic.AtomicInteger;

class Miser extends Thread {
  Miser(int howMany) {
    this.howMany = howMany;
  }

  public void run() {
    for (int i = 0; i < howMany; i++) {
        Account.balance.incrementAndGet();
    }
  }

  private int howMany;
}

class Spendthrift extends Thread {
  Spendthrift(int howMany) {
    this.howMany = howMany;
  }

  public void run() {
    for (int i = 0; i < howMany; i++) {
      Account.balance.decrementAndGet();
    }
  }
  private int howMany;
}

public class Account {
  public static AtomicInteger balance = new AtomicInteger();
}
