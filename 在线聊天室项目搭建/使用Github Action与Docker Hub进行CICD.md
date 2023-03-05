# 使用Github Action与Docker Hub进行CI/CD
## 建立Github仓库
跟随网站指示建立即可
## 在仓库根目录下创建Dockerfile
## 建立Docker Hub账户并获取Token
1. 跟随网站指示建立账户
2. 建立完成后在 Account Settings-Security-Access Tokens中选择New Access Token
3. Token名称随意，点击创建即可
4. 重点：**在随后出现的窗口中复制生成的Token并保存下来** （因为关闭窗口后就再也看不到Token了）
## 配置Github secret
1. 进入之前创建的仓库
2. 点击Settings-Secrets，选择新建，建立两个secrets
   1. Name: **DOCKER_HUB_USERNAME** ; Value: **Docker Hub的用户名**
   2. Name：**DOCKER_HUB_ACCESS_TOKEN** ; Value: **之前保存的Token**
## 使用Github Action并编写yml文件
1. 点击Actions，选择docker image，将内容修改为以下内容
```yml
name: Docker Image CI

on:
  push:
    branches: [ master ]
    tags:
      - 'v*'
  pull_request:
    branches: [ master ]

jobs:

  build:

    runs-on: ubuntu-latest

    steps:
      -
        name: Checkout 
        uses: actions/checkout@v2
      -
        name: Login to Docker Hub
        uses: docker/login-action@v1
        with:
          username: ${{ secrets.DOCKER_HUB_USERNAME }}
          password: ${{ secrets.DOCKER_HUB_ACCESS_TOKEN }}
      -
        name: Set up Docker Buildx
        uses: docker/setup-buildx-action@v1
      -
        name: Build and push
        uses: docker/build-push-action@v2
        with:
          context: .
          file: ./Dockerfile
          push: true
          tags: ${{ secrets.DOCKER_HUB_USERNAME }}/your-image-name:latest
```

## (选做)配置创建容器所需的环境变量文件
因为我们的fastapi后端需要访问Redis等数据库，需要数据库的配置，但由于后端代码是开源的，直接将config文件上传到github有很大风险，故使用环境变量+后端启动时读取环境变量的方式来进行数据库的配置。

如不需要访问数据库或不在意安全性问题的可以跳过该步骤。

1. 在 bash shell运行目录下建立 *.redis_env*
2. 内容为
```
REDIS_PWD=Redis登陆密码
REDIS_USR=root
REDIS_IP=xxx
```
## 在服务器上拉取构建好的镜像并启动
1. 确保Docker已经在服务器上安装并已启动
2. 拉取镜像：docker pull命令，我的命令：
```docker
docker pull christopherzh/online-chat-room-backend
```
3. 启动镜像：docker run命令，我的命令：
```docker
docker run -p 8000:8000 -p 50051:50051 --name fastapi -d --env-file .redis_env  christopherzh/online-chat-room-backend:latest
```
## 在服务器上运行watchtower
### watchtower简介
https://www.ioiox.com/archives/84.html

### 配置环境变量文件
1. 在bash shell当前所在目录建立 *.watchtower_env*
2. 内容为
```txt
REPO_USER=dockerhub账户名称
REPO_PASS=dockerhub账户密码
```
### 命令
```docker
docker run -d --name watchtower --env-file .watchtower_env   --restart always -v /var/run/docker.sock:/var/run/docker.sock containrrr/watchtower --cleanup --interval 90 nginx fastapi

docker run --rm --env-file .watchtower_env  -v /var/run/docker.sock:/var/run/docker.sock containrrr/watchtower --cleanup --run-once nginx //只执行一次，随后就删除自己，watchtower 将在名为“nginx”的容器上执行一次尝试升级。程序将在前台运行，执行更新后，容器将退出并删除（因为这里加入了 --rm参数）
```
## 提交代码，并享受CI/CD带来的便捷吧
