# C++
1. const用于修饰它左侧的内容（类型 int、指针 *），当const处于最左端时，它修饰右边的内容
# Linux
1. - 硬链接： 与普通文件没什么不同，inode都指向同一个文件在硬盘中的区块
   - 软链接： 保存了其代表的文件的绝对路径，是另外一种文件，在硬盘上有独立的区块，访问时替换自身路径。
2. 查看端口占用情况  lsof -i:端口号 
   
# Docker
## 安装vim
cat >/etc/apt/sources.list <<EOF
deb http://deb.debian.org/debian buster main
deb http://security.debian.org/debian-security buster/updates main
deb http://deb.debian.org/debian buster-updates main
EOF

执行成功后，再运行下面的命令即可

apt-get update
apt-get install -y vim

# LeetCode
## 并查集代码


