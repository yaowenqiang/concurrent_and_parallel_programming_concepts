> sleep 5 | echo "Hello, World"

> man 2 fork

> nginx

user www-data;
worker_process 4;
pid /var/run/nginx.pid;
> events {
  worker_connections 1024;
}
