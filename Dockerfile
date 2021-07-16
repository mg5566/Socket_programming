FROM ubuntu
#FROM debian:buster

RUN apt-get update
RUN apt-get upgrade
RUN apt-get install -y nginx nginx-full
RUN apt-get install -y vim
RUN mkdir /var/www/html/dav
RUN mkdir /usr/share/nginx/html/dav

#COPY default /etc/nginx/sites-available/
COPY nginx.conf /etc/nginx/
COPY test.html /var/www/html/dav/
COPY test.html /usr/share/nginx/html/dav/

#RUN chmod a+w /var/www/html/dav
#RUN chmod a+w /var/www/html/dav/test.html

RUN chown www-data:www-data /usr/share/nginx/html/dav 
RUN chown www-data:www-data /usr/share/nginx/html/dav/test.html

#RUN service nginx start

#EXPOSE 80 8080 443
