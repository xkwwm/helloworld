FROM docker.oa.com:8080/public/golang:latest
RUN mkdir -p /data/helloworld
COPY . /data/helloworld/ 
RUN cd /data/helloworld \
    && chmod +x ./start.sh
CMD ["sh","/data/helloworld/start.sh"]

