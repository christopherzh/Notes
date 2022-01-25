# 在 Dockerfile 中使用 ENV 指令设置环境变量
格式有两种：
- ENV key value
- ENV key1=value1 key2=value2
```bash
1、key value
	ENV PYTHON_VERSION 3.5.3
2、key=value
	ENV name1=ping name2=on_ip
3、换行
	ENV VERSION=1.0 DEBUG=on \
	    NAME="Happy Feet"
4、在 Dockerfile 中使用
	$NODE_VERSION
    $PYTHON_VERSION
```
# 在 docker run 命令中设置环境变量
- docker run --env -e
```bash
docker run -e VAR1=value1 --env VAR2=value2 ubuntu
docker run --env VAR1=value1 --env VAR2=value2 ubuntu
```

You can also use variables that you’ve exported to your local environment:
```bash
export VAR1=value1
export VAR2=value2
$ docker run --env VAR1 --env VAR2 ubuntu env | grep VAR
VAR1=value1
VAR2=value2
docker run --env-file
```

使用文件作为环境变量，.env 文件如下：
```bash
# This is a comment
VAR1=value1
VAR2=value2
USER  # which takes the value from the local environment

运行示例：
docker run --env-file .env ubuntu
```
3、查看环境变量
```bash
docker inspect <CONTAINER-NAME> OR <CONTAINER-ID>
```
