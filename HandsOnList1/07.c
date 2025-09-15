/*
============================================================================
Name : 07.c
Author     : Rohitangshu Bose
Description : Write a program to copy file1 into file2 ($cp file1 file2).
Date:       1st September, 2025.
============================================================================
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) 
{
    if(argc < 3) 
    {
        printf("File name needed in arguement\nUsage: %s source_file destination_file\n", argv[0]);
        return 1;
    }

    char buffer[1024];  
    ssize_t readByte, writeByte;

    int sourceFD = open(argv[1], O_RDONLY);
    if(sourceFD == -1) 
    {
        perror("Error opening source file");
        return 1;
    }

    int destinationFD = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if(destinationFD == -1) 
    {
        perror("Error opening/creating destination file");
        close(sourceFD);
        return 1;
    }

    while((readByte = read(sourceFD, buffer, sizeof(buffer))) > 0) 
    {
        writeByte = write(destinationFD, buffer, readByte);
        if(writeByte == -1) 
        {
            perror("Error writing to destination file");
            close(sourceFD);
            close(destinationFD);
            return 1;
        }
    }

    if(readByte == -1) {
        perror("Error reading from source file");
    } else {
        printf("File copied sucessfully!!\n");
    }

    close(sourceFD);
    close(destinationFD);
    return 0;
}
/*
===============================================
Output:
_______________________________________________
rohit2026~$gcc 07.c -o 07.out       
rohit2026~$./07.out 02.c newFile.txt
File copied sucessfully!!
rohit2026~$cat newFile.txt

============================================================================
Name        : 2.c
Author      : Rohitangshu Bose
Description : Program to execute in an infinite loop at the background.
              Once running, go to /proc/<pid>/ directory to inspect
              process-related information such as status, fd, maps, etc.
Date        : 1st September, 2025
============================================================================

int main()
{
    for( ; ; );
    return 0;
}

======================================================================================================================================================
Output(on macOS, since macOS doesn't have /proc using ps and lsof):
______________________________________________________________________________________________________________________________________________________
rohit2026~$gcc 02.c -o 02.out                       
rohit2026~$./02.out &
[2] 2280
rohit2026~$ps -p 2280 -o pid,ppid,state,user,uid,gid,%cpu,%mem,etime,command
  PID  PPID STAT USER        UID   GID  %CPU %MEM ELAPSED COMMAND
 2280  1652 RN   rohit2026   501    20  99.3  0.0   02:01 ./02.out
rohit2026~$lsof -p 2280
COMMAND  PID      USER   FD   TYPE DEVICE SIZE/OFF                NODE NAME
02.out  2280 rohit2026  cwd    DIR   1,16      448             2735475 /Users/rohit2026/Documents/MTech/Term I/Systems Software/HandsOnList1
02.out  2280 rohit2026  txt    REG   1,16    16840             3054268 /Users/rohit2026/Documents/MTech/Term I/Systems Software/HandsOnList1/02.out
02.out  2280 rohit2026  txt    REG   1,16  2289328 1152921500312524573 /usr/lib/dyld
02.out  2280 rohit2026    0u   CHR   16,0  0t15605                 707 /dev/ttys000
02.out  2280 rohit2026    1u   CHR   16,0  0t15605                 707 /dev/ttys000
02.out  2280 rohit2026    2u   CHR   16,0  0t15605                 707 /dev/ttys000

======================================================================================================================================================
Output(on WSL):
______________________________________________________________________________________________________________________________________________________
ayushi@Entropy:~/HandsOnList1$ gcc 02.c -o 02.out
ayushi@Entropy:~/HandsOnList1$ ./02.out &
[3] 1813
ayushi@Entropy:~/HandsOnList1$ ls /proc
1     209  268   buddyinfo  diskstats      iomem        kpagecount     mpt           slabinfo       tty
1042  210  269   bus        dma            ioports      kpageflags     mtrr          softirqs       uptime
142   211  493   cgroups    driver         irq          latency_stats  net           stat           version
156   212  539   cmdline    dynamic_debug  kallsyms     loadavg        pagetypeinfo  swaps          vmallocinfo
157   214  540   config.gz  execdomains    kcore        locks          partitions    sys            vmstat
1667  224  552   consoles   fb             key-users    meminfo        pressure      sysrq-trigger  zoneinfo
1813  228  7     cpuinfo    filesystems    keys         misc           schedstat     sysvipc
1814  241  83    crypto     fs             kmsg         modules        scsi          thread-self
2     246  acpi  devices    interrupts     kpagecgroup  mounts         self          timer_list
ayushi@Entropy:~/HandsOnList1$ ls /proc/1813
arch_status  coredump_filter  gid_map            map_files   ns             personality  smaps         task
attr         cpuset           io                 maps        numa_maps      projid_map   smaps_rollup  timens_offsets
auxv         cwd              ksm_merging_pages  mem         oom_adj        root         stack         timers
cgroup       environ          ksm_stat           mountinfo   oom_score      sched        stat          timerslack_ns
clear_refs   exe              latency            mounts      oom_score_adj  schedstat    statm         uid_map
cmdline      fd               limits             mountstats  pagemap        sessionid    status        wchan
comm         fdinfo           loginuid           net         patch_state    setgroups    syscall
======================================================================================================================================================
%                       
===============================================
*/