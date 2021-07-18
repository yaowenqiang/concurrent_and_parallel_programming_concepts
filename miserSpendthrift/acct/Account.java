package acct;

class Miser extends Thread {
  Miser(int howMany) {
    this.howMany = howMany;
  }

  public void run() {
    for (int i = 0; i < howMany; i++) {
      Account.balance++;
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
      Account.balance--;
    }
  }
  private int howMany;
}

public class Account {
  public static int balance = 0;
}
