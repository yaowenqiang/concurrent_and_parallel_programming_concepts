package acct;
public class RaceCondition {
  public static void main(String[] args) {
    if (args.length < 1) {
      System.err.println("RunCondition <time to iterate>");
    }

    int n = Integer.parseInt(args[0]);
    Miser miser = new Miser(n);
    Spendthrift spendthrift = new Spendthrift(n);
    miser.start();
    spendthrift.start();
    try {
      miser.join();
      spendthrift.join();
    } catch (Exception e)  {
      System.err.println(e);
    }
    System.out.println("Finaly balance: " + Account.balance);
  }
}
