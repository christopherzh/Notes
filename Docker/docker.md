# docker
## 安装
```bash
yum install docker
docker version
```
## 服务启动与检查
```bash
systemctl start docker //启动docker
systemctl status docker // 检查运行状态
system enable docker.service //设置为开机启动
```
# 镜像
## 设置加速源
https://cloud.tencent.com/document/product/1207/45596
## 下载镜像
```bash
docker pull 镜像名(e.g. nginx, tomcat)
```

## 查看
```bash
docker images //查看已下载的镜像
```
## 删除
```
docker image rm [image]
```

# 容器
## 查看容器
```bash
docker ps //查看当前运行的容器
docker ps -a //查看所有容器
```

## 启动容器
```bash
```
## 停止与删除
```bash

docker stop 容器名(container name) 
docker rm 容器名
```

# 容器内配置
## 安装vim
cat >/etc/apt/sources.list <<EOF
deb http://deb.debian.org/debian buster main
deb http://security.debian.org/debian-security buster/updates main
deb http://deb.debian.org/debian buster-updates main
EOF

执行成功后，再运行下面的命令即可

apt-get update
apt-get install -y vim
