sysctl net.ipv4.conf.all.forwarding=1
sudo iptables -P FORWARD ACCEPT
# Dzieki tym regulom mozliwa jest komunikacja kontener -> host

docker pull alpine
docker pull ubuntu
docker pull nginx
docker pull tomcat

docker run -itd --name T1 alpine sh

docker network create -d bridge --subnet 10.0.10.0/24 bridge1
docker run -itd --name T2 --net bridge --expose 80 -p 80:80 -p 10.0.10.1:8000:80 nginx sh
docker network connect bridge1 T2

docker exec -itd T2 /bin/bash -c 'service nginx start'
# od teraz mozemy sie polaczyc z nginx na kontenetrze T2 wchodzac na
# `localhost` lub `10.0.10.1:8000` z komputera hosta


docker run -itd --name D1 --net bridge1 alpine sh

docker network create -d bridge bridge2
docker run -itd --net bridge2 --name S1 ubuntu sh

docker run -itd --name D2 --expose 8080 --net bridge2 -p 8081:8080 -p 10.0.10.0:8080:8080 tomcat sh
# Na moim dockerze domyslnie tomcat slucha na 8080
docker network connect bridge1 D2

docker exec D2 /bin/bash -c '/usr/local/tomcat/bin/startup.sh'

docker run -itd --name late --net bridge2 ubuntu bash
# przez podanie --net kontener polaczy się z ta siecia, zamiast z domyslna
docker network connect bridge1 late
# laczymy go do drugiej sieci
