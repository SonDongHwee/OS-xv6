## Lab2

---
## using gdb(easy)
1. > make qemu-geb 
<img src="./gdb1.png" height = 100></img>
2. > gdb multiarch (at another window)
<img src="./gdb2.png" height = 100></img>
3. > (gdb) target remote localhost:26000 (which is given by 1)
4. > (gdb) file kernel/kernel
<img src="./gdb3.png" height = 100></img>

---
## System call tracing(moderate)
1. > Modify makefile user/user.h and user/usys.pl to use trace as application
2. > Allocate SYS_trace num at syscall.h
<img src="./syscall_header.png" height = 100></img>
3. > Write sys_trace func
<img src="./sys_trace.png" height = 100></img>
4. > print syscall info at syscall.c
<img src="./syscall_syscall.png" height = 100></img>
5. > Inherit mask to forked process
<img src="./syscall_fork.png" height = 100></img>
<img src="./syscall_trace.png" height = 200></img>


---
## Sysinfo(moderate)
