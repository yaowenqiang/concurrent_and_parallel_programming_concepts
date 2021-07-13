class Test {
  static int n;
  static Object lock = new Object();
  void incremtN() {
    synchronized(lock) {
      n = n + 1;
    }
  }
}
