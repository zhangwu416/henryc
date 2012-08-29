#ifndef _SINGLETON_H_
#define _SINGLETON_H_

namespace henrylib
{
    namespace myutility
    {
        template<typename type>
        class singleton_t
        {
            public:
                static type& instance()
                {
                    if (NULL == m_instance)
                    {
                       m_instance =  new type();
                       atexit(&destory);
                    }

                    return *m_instance;

                }
            private:
                static void destory()
                {
                    if (m_instance)
                    {
                        delete m_instance;
                        m_instance = NULL;
                    }
                }
            private:
                static type*   m_instance;
        }
    }
}


#endif
