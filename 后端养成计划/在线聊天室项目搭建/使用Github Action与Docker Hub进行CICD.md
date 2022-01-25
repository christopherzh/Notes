# 使用Github Action与Docker Hub进行CI/CD
## 建立Github仓库
跟随网站指示建立即可
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
1. 点击Actions，选择自定义，将内容修改为以下内容
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

## 在服务器上拉取构建好的镜像
1. 确保Docker已经在服务器上安装并已启动
2. 拉取镜像：docker pull命令，我的命令：**docker pull christopherzh/docker-test**
3. 启动镜像：docker run命令，我的命令：**docker run -p 8000:8000 --name fastapi -d christopherzh/online-chat-room-backend**
## 在服务器上运行watchtower
watchtower简介：https://www.ioiox.com/archives/84.html

docker run -d --name watchtower -e REPO_USER=xxxx -e REPO_PASS=xxxxx --restart always -v /var/run/docker.sock:/var/run/docker.sock containrrr/watchtower --cleanup --interval 300 //设置watchtower

docker run --rm -e REPO_USER=xxxx -e REPO_PASS=xxxxx  -v /var/run/docker.sock:/var/run/docker.sock containrrr/watchtower --cleanup --run-once //只执行一次，随后就删除自己
## 享受CI/CD带来的便捷吧
