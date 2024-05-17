#include "kernel/types.h"
#include "user/user.h"
int main()
{
        char buf = 'P';
        int p[2];//p用于父进程向子进程发送字节,p[0]读取,p[1]写入
        int q[2];//q用于子进程向父进程发送字节,q[0]读取,q[1]写入
        pipe(p);
        pipe(q);
        char b;

        if(fork()==0)
        {
                close(p[1]);
		close(q[0]);
                read(p[0],&b,sizeof(b));
                close(p[0]);
                printf("%d: received ping\n",getpid());
                write(q[1],&buf,sizeof(buf));
		close(q[1]);
                exit(0);
        }
        else{
                close(p[0]);
		close(q[1]);
                write(p[1],&buf,sizeof(buf));
                close(p[1]);
                read(q[0],&b,sizeof(b));
		close(q[0]);
                printf("%d: received pong\n",getpid());
                exit(0);
        }
        exit(1);
}
