## Lab2

---
## using gdb(easy)
1. > make qemu-geb <br>
<img src="./gdb1.png" height = 100></img>
2. > gdb multiarch (at another window) <br>
<img src="./gdb2.png" height = 100></img>
3. > (gdb) target remote localhost:26000 (which is given by 1)
4. > (gdb) file kernel/kernel <br>
<img src="./gdb3.png" height = 100></img>

---
## System call tracing(moderate)
1. > Modify makefile user/user.h and user/usys.pl to use trace as application
2. > Allocate SYS_trace num at syscall.h <br>
<img src="./syscall_header.png" height = 50></img>
3. > Write sys_trace func <br>
<img src="./sys_trace.png" height = 130></img>
4. > print syscall info at syscall.c <br>
<img src="./syscall_syscall.png" height = 100></img>
5. > Inherit mask to forked process <br>
<img src="./syscall_fork.png" height = 50></img> <br>
<img src="./syscall_trace.png" height = 200></img>


---
## Sysinfo(moderate)
<img src="./sysinfotest.png" height = 100></img>
