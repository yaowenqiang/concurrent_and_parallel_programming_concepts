> sleep 5 | echo "Hello, World"

> man 2 fork

> nginx

user www-data;
worker_process 4;
pid /var/run/nginx.pid;
> events {
  worker_connections 1024;
}


key data strcture of process context

+ process table - tracks information per process, in particular information that allows a pre-empted process to restart later
+ page table - translate virtual into physical addresses. Each process has its own, which effectively partitions virtual address space among processes.
+ file table - tracks , per process, files that a process has opened.

Process level context switch
Thread  level context switch

> Nginx and Unicorn  communicate via local socket

Multithreading overview

+ A process consists of one or more threads of execution
+ A thread-level context switch has a near-zero cost for threads in the same process
+ A process-level contest switch is significently more expensive, in the multithread range.

The chief disadvantage is that threads in the same process share the same address space:

+ the programmer, rather then the OS, must ensure that two threads in the same process don't inaprpropriately access the same memory location(i.e, by trying to update the location)
+ The programmer must coordinate threads in the same process to avoid 'race conditions', 
  + if the coordination is overdone, 'deadlock' may result.
+ Thread coordination must be just right
  + Too little brings the threat of race condition that happend to share an address space, results
  + too much hurts efficiency and may result in deadlock

Some system(e.g, Linux_implement standard threads as processes that happen to share an address space; other system(e.g, windows) have distinct kernel-level support for threads

  under any implementation, the standard behavior is that distinct processes have distinct address spaces, whereas threads in thes same process share an address space.
  )

> javac Racec.java
> java Main

Various locking mechanisms:

+ A "semphore" restricts the number of threads allowed to access a shared resource(e.g, a shared function), For example, "semaphore"  might allow two threads to access a chunk of code simultaneously, but no more than two, A semaphore is thus a set of permission tickets, which enable a thread to access a resource.

Semaphores as 'tickets' : a semaphore is like a ticket that grants access to a resource.
a semaphore  with a value of three would grant access to three threads at most at a time.

+ A 'mutex' is a semaphore with a value of 1: whichever thread holds the mutex has access to the protected resource, whereas all others are excluded.

+ A 'monitor'(which the Java 'symchronized' block provdes) is a mechanism that enforces mutual exclusion. supports progress, and has addition mechanisms for thread cooperation: in java's case, the 'wait' mechanism supports quiet waiting for a lock to be released, and the 'notify' mechanism notifies waiters that a lock has been released.

<<<<<<< HEAD

native versus green thread, and the Global interpreter lock(GIL)

+ A 'native thread' is under kernel OS control when it comes to scheduling.
  + since roughly 2000, Java Thread instances map to 'native' thread (Same for C#)   
  + C's 'pthreads' (the 'p' for POSIX API standardization) are 'native' threads
+ A 'green thread' (aka 'microthread', 'tasklet') is under a particular langeuage's runtime control
  + In effect, 'green thread' emulate native thread, and may provide better performance for operations such as thread creation and synchronization
  + Prior to version 1.9, for example, Ruby's standard implementtaion(CRuby) had only green threads
  + A GIL is a mechanism(in implementation, a mutex) that a runtime uses to allow only one thread to execute at a time, even in a multithread environment: no thread-level parallelism
  + the standard implementation of Ruby(CRuby) and Python(CPython) have a GIL.


> valgrind --tool=helgrind -v --log-file=hg.log ./noddy
> https://accu.org/journals/overload/21/114/floyd_1867/


> javac accc/*.java
> java acc.RaceCondition
