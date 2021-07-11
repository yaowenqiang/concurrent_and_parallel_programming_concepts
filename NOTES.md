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


