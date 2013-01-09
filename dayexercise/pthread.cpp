//! g++ pthread.cpp -lpthread

#include <iostream>
#include <pthread.h>
using namespace std;


/*!*********************************************************
 * 线程本地化的通用方法,用到的函数主要有:
 * pthread_key_create
 * pthread_once
 * pthread_getspecific
 * pthread_setspecific
 * 这种方法用起来相对繁杂
 ***********************************************************/

pthread_key_t key;
pthread_once_t once = PTHREAD_ONCE_INIT;

static void destructor(void* ptr)
{
    printf("des..%p.\n", ptr);
    free(ptr);
}

static void init_once(void)
{
     printf("create...\n");
    pthread_key_create(&key, destructor);
}

static void* get_buff(void)
{
    pthread_once(&once, init_once);

    void* ptr = NULL;
    if ((ptr = pthread_getspecific(key)) == NULL)
    {
        ptr = malloc(1024);
        printf("new..%p.\n", &key);
        pthread_setspecific(key, ptr);
    }
    
    return ptr;
}

static void* thread_fn1(void* arg_)
{
    char* ptr = (char*) get_buff();
    printf(">>%s..%pbegin\n", ptr, ptr);
    sprintf(ptr, "hell world:%ld", pthread_self());
    printf(">>%s..end\n\n\n", ptr);
    /*
    if (test == NULL)
    {
        test = new test_t();
        printf("new %p..\n", test);
    }
    printf("data:%p..%ld\n", test, pthread_self());
    */

    return NULL;
}

int method1()
{
    pthread_t threads[10];

    for (size_t i = 0; i < 10; ++i)
    {
        pthread_create(&threads[i], NULL, thread_fn1, NULL);
    {
        sleep(2);
    }
    }

    for (size_t i = 0; i < 10; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    return 0;
}

/*!*********************************************************
 * 线程本地化的简单方法，但这种方法容易造成内存泄露：
 * 主要通过__thread关键字来字义本地化变量,下面我们先做一个测试
 * 当用__thread修饰的本地变量是堆上存放时,改动thread_fn1，如下
 * 那么，当没有加DUS_TLS宏定义项时,在线程函数退出时就会不释放所申请的内存
 * 而且，要特别说明的是:
 * 基本类型(如(unsigned) int,long, char,指针，c类型的结构体等 )可以采用用 __thread修饰符来定义线程局部变量.
 * 但是像string等类不能直接用__thread修饰，只能用其指针类型.
 * 那么为了解决以上内存泄露的问题，我们可以借助于
 * pthread_xx系列函数在线程退出时进行内存回收.代码见henrylib/myutility目录下
 * 为方便，我们直接把thread_tools.h和thread_tools.cpp 拷贝到当前目录，然后
 * g++ pthread.cpp thread_tools.cpp -lpthread -DUSE_TLS. 然后运行明显可以看到有相应析构函数执行
 **********************************************************/
#ifdef USE_TLS
#include "thread_tools.h"
using namespace henrylib::myutility;
#endif

class test_t
{
    public:
        test_t()
        {
            printf("test_t\n");
        }
        ~test_t()
        {
            printf("~test_t\n");
        }
};

__thread test_t* test;

static void destructor2(void* ptr)
{
    printf("des..%p.\n", ptr);
    test_t* tmp = (test_t*)ptr;
    delete tmp;
}

static void* thread_fn2(void* arg_)
{
    if (test == NULL)
    {
        test = new test_t();
        printf("new %p..\n", test);
#ifdef USE_TLS
        thread_specific_t::pthread_atexit_add(destructor2, (void*)test);
#endif
    }
    printf("data:%p..%ld\n", test, pthread_self());
    return NULL;
}

int method2()
{
    pthread_t threads[10];

    for (size_t i = 0; i < 10; ++i)
    {
        pthread_create(&threads[i], NULL, thread_fn2, NULL);
    {
        sleep(1);
    }
    }

    for (size_t i = 0; i < 10; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
int main()
{
    //method1();
    method2();
    return 0;
}
