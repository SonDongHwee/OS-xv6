#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void find(char* path, char* filename){
    char buf[512], *p;
    int fd;
    struct stat st;
    struct dirent de;

    if((fd = open(path, 0)) < 0){
        fprintf(2, "find: cannot open %s\n", path);
        return;
    } 

    if(fstat(fd, &st) < 0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch(st.type){
        case T_FILE:
        //printf("%s, %s, %d\n",fmtname(path),filename,strcmp(fmtname(path),filename));
        if(strcmp(fmtname(path),filename) == 32){
            printf("%s\n",path);
        }break;

        case T_DIR:
        if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
          printf("find: path too long\n");
          break;
        }
        strcpy(buf,path);
        p = buf + strlen(buf);
        *p++ = '/';
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            if(de.inum == 0)
                continue;
            if(strcmp(".", de.name) == 0  || strcmp("..", de.name) == 0)
				        continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            find(buf, filename);
        }break;
    }

    close(fd);
}

int main(int argc, char ** argv){
    if(argc < 2){
        fprintf(2, "Usage: find path filename ...\n");
        exit(1);
    }
    if(argc == 2){
        find(".", argv[1]);
        exit(0);
    }
    find(argv[1],argv[2]);
    exit(0);
}