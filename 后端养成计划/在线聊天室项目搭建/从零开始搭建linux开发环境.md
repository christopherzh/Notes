# SSH 远程连接
## 命令行操作
1. *ssh root@123.123.123.123* (root代表用户名,123代表IP地址)
2. 输入密码
3. *cd .ssh*
4. *touch authorized_keys* (为了免密登录,所以要添加远程访问电脑的公钥)
5. *vim authorized_keys*
6. 将公钥复制到文件内

大功告成!

# 升级Git
1、查看git版本
```bash
git --version
```
查看当前git版本，看git版本是否过旧。

2、安装依赖
源代码安装和编译git，需要安装依赖，具体命令如下：
```bash
yum install curl-devel expat-devel gettext-devel openssl-devel zlib-devel asciidoc
yum install gcc perl-ExtUtils-MakeMaker
```
出现Complete!则代表安装成功

3、卸载git（旧版本）
```bash
yum remove git
```
 4、打开文件夹
用于存放下载的git包
```bash
cd /usr/local/src/
```
 5、下载git压缩包
使用国内指定下载最新版本，目前最新版是v2.34.1
```bash
wget https://mirrors.edge.kernel.org/pub/software/scm/git/git-2.34.1.tar.xz
```
 6、解压
```bash
tar -xvf git-2.34.1.tar.xz
```

 7、打开解压好的git文件夹
```bash
 cd git-2.34.1
```
8、编译
```bash
make prefix=/usr/local/git all
```
 9、安装git
```bash
make prefix=/usr/local/git install
```
10、配置环境变量
写到环境变量中
```bash
echo "export PATH=$PATH:/usr/local/git/bin" >> /etc/profile && source /etc/profile
```
11、验证git版本
再次查看当前版本，验证是否已更新

# Docker
## 安装docker
https://www.runoob.com/docker/centos-docker-install.html
```bash
curl -fsSL https://get.docker.com | bash -s docker --mirror Aliyun
```
## 启动Docker并设置开机自启
systemctl start docker
systemctl enable docker

## 启动相关容器
