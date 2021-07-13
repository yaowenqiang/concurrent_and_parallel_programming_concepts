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
