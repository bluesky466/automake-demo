修改好这些之后执行autoreconf --install命令得到了下面的错误日志:

```
src/Makefile.am:1: error: Libtool library used but 'LIBTOOL' is undefined
src/Makefile.am:1:   The usual way to define 'LIBTOOL' is to add 'LT_INIT'
src/Makefile.am:1:   to 'configure.ac' and run 'aclocal' and 'autoconf' again.
src/Makefile.am:1:   If 'LT_INIT' is in 'configure.ac', make sure
src/Makefile.am:1:   its definition is in aclocal's search path.
automake: warnings are treated as errors
/usr/share/automake-1.15/am/ltlibrary.am: warning: 'libeasylog.la': linking libtool libraries using a non-POSIX
/usr/share/automake-1.15/am/ltlibrary.am: archiver requires 'AM_PROG_AR' in 'configure.ac'
src/Makefile.am:1:   while processing Libtool library 'libeasylog.la'
autoreconf: automake failed with exit status: 1
```

根据提示在configure.ac中加入 LT\_INIT 和 AM\_PROG\_AR,注意AM\_PROG\_AR 要放在 LT\_INIT 之前,要不然 autoreconf --install 的时候会报warn

```
#                                               -*- Autoconf -*-                    
# Process this file with autoconf to produce a configure script.                    
                                                                                 
AC_PREREQ([2.69])                                                                
AC_INIT([easylog], [0.0.2], [466474482@qq.com])                                     
AM_INIT_AUTOMAKE([-Wall -Werror foreign])                                        
AC_CONFIG_SRCDIR([src/log_interface.h])
AC_CONFIG_HEADERS([config.h])                                                    
                                                                                 
AM_PROG_AR                                                                       
LT_INIT                                                                          
                                                                                 
# Checks for programs.                                                           
AC_PROG_CXX                                                                      
AC_PROG_CC                                                                       
AX_CXX_COMPILE_STDCXX_11                                                         
                                                                                 
# Checks for libraries.                                                          
                                                                                 
# Checks for header files.                                                       
                                                                                 
# Checks for typedefs, structures, and compiler characteristics.                    
                                                                                 
# Checks for library functions.                                                  
                                                                                 
AC_CONFIG_FILES([Makefile                                                        
                 examples/Makefile                                               
                 src/Makefile])                                                  
                                                                                 
AC_OUTPUT  
```

