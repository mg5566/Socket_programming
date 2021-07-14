FROM ubuntu

RUN apt-get update
RUN apt-get upgrade
RUN apt-get install -y nginx
RUN apt-get install -y vim

EXPOSE 8080
EXPOSE 80
EXPOSE 443
