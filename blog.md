## src目录

src目录放的就是库的源代码,我们使用src中的源代码编译出一个so来给其他的程序使用easylog的功能  

src目录中有下面几个文件log\_interface.h，easy\_log.h，easy\_log.cpp，cout\_log\_interface.h，cout\_log\_interface.cpp，Makefile.am。实际上就是除了main.cpp，其他文件都放到了这里来。因为我们提供给别的是一个so库而不是一个可执行程序，所以main.cpp可以不需要编译到目标文件中

.h和.cpp的内容和上一篇[文章](http://blog.islinjw.cn/2017/03/17/automake%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0-helloworld/)的内容是一样的。这里的重点其实是Makefile.am。让我们先来看看它的内容:

```
lib_LTLIBRARIES = libeasylog.la                                                             
libeasylog_la_SOURCES = cout_log_interface.cpp \                                            
                     easy_log.cpp
```

其实它的内容很简单，就是指定了要编译的库的名字和库的源码。但是有一个问题，我们这里需要编译的是so但为什么这里的目标文件却是libeasylog.la呢?

Libtool是一种属于GNU构建系统的GNU程序设计工具,它将静态库和动态库抽象成了一种统一的叫做libtool库的概念。libtool库使用la作为后缀。它可以用来构建静态库也能用来构建动态库，而最终编译出来的到底是哪一种，在最后执行configure命令的时候才能确定。同时它编译的时候产生的文件就不再是.o文件而是.lo文件。  

这里lib\_LTLIBRARIES的的lib前缀表示的就是目标文件是一个库而不是可执行文件(bin前缀表示目标文件是可执行文件)。而LTLIBRARIES的LT指的就是Libtool。还有一点是一般编译库文件的话我们会在文件名钱加上lib前缀，所以我们的目标文件是libeasylog.la。

而下面的libeasylog\_la\_SOURCES就是指定编译libeasylog.la使用的源代码



## examples目录

examples目录里面放了这个库的example代码。因为我们的库是要提供给其他人使用的，所以一般除了文档之外，还会有一些例子去帮助使用者了解应该如何去使用我们的库。这个目录中的example.cpp其实就是上一篇[文章](http://blog.islinjw.cn/2017/03/17/automake%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0-helloworld/)中的main.cpp：

```
#include "easy_log.h"
#include "cout_log_interface.h"


int main()
{
    EasyLog log(std::make_shared<COutLogInterface>());
    log.Debug("test", "testlog");

    return 0;
}
```

这个目录下也有一个Makefile.am，它是用来配置example程序的编译选项的:

```
AM_CPPFLAGS = -I$(top_srcdir)/src

bin_PROGRAMS = example
example_SOURCES = example.cpp

example_LDADD = -L$(top_builddir)/src \
				-leasylog
```

AM\_CPPFLAGS的值在c/c++预处理的时候会当做参数传给预处理器例如我们将源码目录传给预处理器，这样预处理器才能找到easy\_log.h和cout\_log\_interface.h

这里的top\_srcdir变量会在configure是被定义，它的值是工程目录的位置(也就是configure所在目录的位置)，后面的top\_builddir也是类似的，不过它的值是编译目录的位置(也就是执行make命令是所在的目录)

这里编译出来的example就是我们的demo程序




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

