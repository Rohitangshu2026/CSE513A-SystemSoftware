/*
============================================================================
Name        : 15.c
Author      : Rohitangshu Bose
Description : Display all environment variables of the current user using `environ`.
Date        : 7th September, 2025
============================================================================
*/

#include <stdio.h>

extern char **environ;
int main() 
{
    char **env = environ;

    printf("Environment variables:\n\n");

    while (*env != NULL) 
    {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}

/*
================================================================================
Output:
________________________________________________________________________________
                                                      
==============================rohit2026~$gcc 15.c    
rohit2026~$./a.out     
Environment variables:

TMPDIR=/var/folders/26/pqp2fbps4d3gngj8fn839bm80000gn/T/
__CFBundleIdentifier=com.apple.Terminal
XPC_FLAGS=0x0
TERM=xterm-256color
SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.u8CR5kERV9/Listeners
XPC_SERVICE_NAME=0
TERM_PROGRAM=Apple_Terminal
TERM_PROGRAM_VERSION=455.1
TERM_SESSION_ID=8F0695A3-463E-4750-B382-7F7B93E29B26
SHELL=/bin/zsh
HOME=/Users/rohit2026
LOGNAME=rohit2026
USER=rohit2026
PATH=/opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin
SHLVL=1
PWD=/Users/rohit2026/Documents/MTech/Term I/Systems Software/HandsOnList1
OLDPWD=/Users/rohit2026
HOMEBREW_PREFIX=/opt/homebrew
HOMEBREW_CELLAR=/opt/homebrew/Cellar
HOMEBREW_REPOSITORY=/opt/homebrew
INFOPATH=/opt/homebrew/share/info:
LANG=en_IN.UTF-8
_=/Users/rohit2026/Documents/MTech/Term I/Systems Software/HandsOnList1/./a.out==================================================
*/