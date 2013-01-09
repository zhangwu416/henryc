#include "thread_tools.h"

namespace henrylib
{
    namespace myutility
    {

        int thread_tools_t::set_thread_detach()
        {
            pthread_attr_t attr;
            ::pthread_attr_init(&attr);
            if (0 != ::pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED))
            {
                return errno;
            }
            ::pthread_attr_destroy(&attr);

            return 0;
        }

        int thread_tools_t::set_thread_all_sigs()
        {
            sigset_t sig;
            ::sigfillset(&sig);
            if (0 != ::pthread_sigmask(SIG_SETMASK, &sig, NULL))
            {
                return errno;
            }

            return 0;
        }
        
#define KEY_INVALID 0xffffffff
        pthread_key_t    thread_specific_t::m_key = KEY_INVALID;
        pthread_once_t   thread_specific_t::m_once = PTHREAD_ONCE_INIT;

        void thread_specific_t::pthread_atexit_destructor(void* arg_)
        {
            list_atexit_data_t* atexit_datas = (list_atexit_data_t*)(arg_);
            thread_atexit_t* tmp;
            for (list_atexit_data_it_t it = atexit_datas->begin(); it != atexit_datas->end(); ++it)
            {
                tmp = *it;
                if (tmp && tmp->m_fn)
                {
                    tmp->m_fn(tmp->m_arg);
                }

                delete tmp;
            }

            atexit_datas->clear();
            delete atexit_datas;
        }

        void thread_specific_t::pthread_atexit_init()
        {
            pthread_key_create(&m_key, pthread_atexit_destructor);
        }

        int thread_specific_t::pthread_atexit_add(void (*exit_fn_)(void*), void* arg_)
        {
            //!
            static char* func_name = "pthread_atexit_add";

            //! the function may need arg value is NULL
            if (/*arg_ == NULL || */exit_fn_ == NULL)
            {
                return -1;
            }

            pthread_once(&m_once, pthread_atexit_init);
            if (m_key == (pthread_key_t)KEY_INVALID)
            {
                //sprintf(stderr, "%s:key(%d) thread id (%ld) invalid\n", func_name, __LINE__, m_key, pthread_self());
                return -1;
            }

            thread_atexit_t* data = new thread_atexit_t;
            if (data == NULL)
            {
                //sprintf(stderr, "%s:key(%d) thread id (%ld) new thread atexit data error\n", func_name, __LINE__, m_key, pthread_self());
                return -1;
            }
            data->m_arg = arg_;
            data->m_fn = exit_fn_;

            list_atexit_data_t* atexit_datas = (list_atexit_data_t*)pthread_getspecific(m_key);
            if (atexit_datas == NULL)
            {
                atexit_datas = new list_atexit_data_t;
                if (pthread_setspecific(m_key, (void*)atexit_datas) != 0)
                {
                    //sprintf(stderr, "%s(%d):key(%d) thread id (%ld) new setspecific data error\n", func_name, __LINE__, m_key, pthread_self());
                    return -1;
                }
            }

            atexit_datas->push_back(data);
            return 0;
        }

        int thread_specific_t::pthread_atexit_remove(void (*exit_fn_)(void*), void* arg_)
        {
            //!
            static char* func_name = "pthread_atexit_remove";
            
            //! the function may need arg value is NULL
            if (/*arg_ == NULL || */exit_fn_ == NULL)
            {
                return -1;
            }

            if (m_key == (pthread_key_t)KEY_INVALID)
            {
                //sprintf(stderr, "%s:key(%d) thread id (%ld) invalid\n", func_name, __LINE__, m_key, pthread_self());
                return -1;
            }

            list_atexit_data_t* atexit_datas = (list_atexit_data_t*)pthread_getspecific(m_key);
            if (atexit_datas == NULL)
            {
                //sprintf(stderr, "%s(%d):key(%d) thread id (%ld) new setspecific data error\n", func_name, __LINE__, m_key, pthread_self());
                return -1;
            }
  
            thread_atexit_t* tmp;
            for (list_atexit_data_it_t it = atexit_datas->begin(); it != atexit_datas->end(); ++it)
            {
                tmp = *it;
                if (tmp && tmp->m_fn == exit_fn_ && tmp->m_arg == arg_)
                {
                    atexit_datas->erase(it);
                    delete tmp;
                    return 0;
                }
            }

            return 0;
        }


    }
}
