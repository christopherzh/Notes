# 安装Git
## Linux系统
### Debian/Ubuntu
```shell
$ sudo apt-get install git
```
## Windows系统

# 使用Git
## 基本语法

## tips
revert和reset的区别:

revert是放弃指定提交的修改，但是会生成一次新的提交，需要填写提交注释，以前的历史记录都在，而reset是指将HEAD指针指到指定提交，历史记录中不会出现放弃的提交记录。

# 与Github建立连接

## 使用SSH连接到Github
[Github官方指南-使用SSH连接到Github](https://docs.github.com/en/github/authenticating-to-github/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent)

1. 打开 Git Bash
2. 运行 ssh-keygen -t rsa -b 4096 -C "邮箱地址"，随后按回车三次
3. 打开本地用户目录里的 .ssh 文件夹
4. 在文件夹中，会有 id_rsa.pub 与 id_rsa 文件，其中前者是公钥，可以提供给Gihub；后者是私钥，自己保存，不得泄露
5. 在Github网站中找到添加SSH的界面，添加自己的公钥
6. 在本机使用 ssh -T git@github.com 命令验证是否已添加成功，随后输入yes
7. 如果看到 Permission denied (publickey). 就说明失败；如果看到 Hi XXXX! You've successfully authenticated, but GitHub does not provide shell access
   
## 本地仓库关联远程仓库 
1. git remote add origin xxxx
2. git pull origin master
如果遇到 *fatal: refusing to merge unrelated histories*，使用下面的命令来拉取
git pull origin master --allow-unrelated-histories
3. git push
# 一些资源
- [官方网站](https://www.git-scm.com/)
- [廖雪峰的教程](https://www.liaoxuefeng.com/wiki/896043488029600) 
- 

