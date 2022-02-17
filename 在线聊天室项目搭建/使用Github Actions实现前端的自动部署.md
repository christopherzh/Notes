## 本地建立项目
## 上传至Github仓库
## 编辑Github Actions
## 编辑nginx服务器配置
## 在服务器上启动nginx docker
```
docker run -p 80:80 --name nginx -d christopherzh/online-chat-room-frontend
docker run --name nginx  -d --net="host"  -v /app/blog:/usr/share/nginx/blog -v /app/chat:/usr/share/nginx/chat -v /root/nginx/default.conf:/etc/nginx/conf.d/default.conf nginx:latest

FROM nginx
COPY /app/blog /usr/share/nginx/blog/
COPY /app/chat /usr/share/nginx/chat/
COPY ./nginx/default.conf /etc/nginx/conf.d/default.conf
EXPOSE 80 443
```