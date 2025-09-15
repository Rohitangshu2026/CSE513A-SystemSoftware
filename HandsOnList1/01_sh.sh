# 1.a Create a soft (symbolic) link using the symlink system call
ln -s source.txt soft_link.txt

# 1.b Create a hard link using the link system call
ln source.txt hard_link.txt

# 1.c Create a FIFO (named pipe) using mkfifo
mkfifo my_fifo