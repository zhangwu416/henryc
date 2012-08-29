#ifndef _ENTRY_MGR_H_
#define _ENTRY_MGR_H_

#include <ext/hash_map>

//#include "noncopyable.h"

namespace henrylib
{
    namespace myserver
    {
        //using namespace henrylib::myserver;
        
        template<typename key_type, typename value_type>
        class limit_hash_t //: public noncopyable
        {
            public:
                typedef __gnu_cxx::hash_map<key_type, value_type, __gnu_cxx::hash<key_type>, std::equal_to<key_type> > hash_map_t;
                typedef typename hash_map_t::const_iterator const_it;
                typedef typename hash_map_t::iterator it;
            public:
                limit_hash_t()
                {
                }

                virtual ~limit_hash_t()
                {
                    clear();
                }

                bool insert(const key_type& key_, const value_type& value_)
                {
                    m_elements[key_] = value_;
                    return true;
                }

                bool del(const key_type& key_)
                {
                    if (m_elements.end() == m_elements.find(key_))
                    {
                        return false;
                    }

                    m_elements.erase(key_);
                    return true;
                }
                
                bool find(const key_type& key_, value_type& value_)
                {
                    const_it if_exist = m_elements.find(key_);
                    if (m_elements.end() == if_exist)
                    {
                        return false;
                    }

                    value_ = if_exist->second;
                    return true;
                }
               
                /* 
                value_type find(const key_type& key_)
                {
                    const_it if_exist = m_elements.find(key_);
                    if (m_elements.end() == if_exist)
                    {
                        return value_type();
                    }

                    return if_exist->second;
                }

                value_type first_element()
                {
                    if (!m_elements.empty())
                    {
                        return m_elements.begin().second;
                    }

                    return value_type();
                }
                */

                bool first_element(value_type& value_)
                {
                    if (!m_elements.empty())
                    {
                        value_ = m_elements.begin().second;
                        return true;
                    }

                    return false;
                }
                
                inline void clear()
                {
                    m_elements.clear();
                }
                
                inline uint32_t size() const
                {
                    return m_elements.size();
                }

                inline bool empty() const
                {
                    return m_elements.empyt();
                }
            protected:
                hash_map_t  m_elements;
        };

        class uid_limit_hash_t : public limit_hash_t<uint64_t, entry_t*>
        {
            public:
                bool add(entry_t* entry_)
                {
                    if (entry_)
                    {
                        entry_t* tmp = NULL;
                        if (!limit_hash_t<uint64_t, entry_t*>::find(entry_->m_uid, tmp))
                        {
                            return limit_hash_t<uint64_t, entry_t*>::insert(entry_->m_uid, entry_);
                        }
                    }
                    return false;
                }
                
                void del(entry_t* entry_)
                {
                    if (entry_)
                    {
                        limit_hash_t<uint64_t, entry_t*>::del(entry_->m_uid);
                    }
                }
                entry_t* get_entry_by_uid(uint64_t uid_)
                {
                    entry_t* tmp = NULL;
                    limit_hash_t<uint64_t, entry_t*>::find(uid_, tmp);
                    
                    return tmp;
                }
        };

        template<int i>
        class entry_none
        {
            public:
                inline bool add(entry_t*)
                {
                    return true;
                }

                inline void del(entry_t* entry_)
                {
                }

                inline void clear()
                {
                }
        };

        template<typename e1, typename e2 = entry_none<1>, typename e3 = entry_none<2> >
        class entry_mgr_t : protected e1, protected e2, protected e3
        {
            public:
                virtual ~entry_mgr_t()
                {
                }

                bool add(entry_t* entry_)
                {
                    if (e1.add(entry_))
                    {
                        if (e2.add(entry_))
                        {
                            if (e3.add(entry_))
                            {
                                return true;
                            }
                            else
                            {
                                e1.add(entry_);
                                e2.add(entry_);
                            }
                        }
                        else
                        {
                            e1.del(entry_);
                        }
                    }

                    return false;
                }

                void del(entry_t* entry_)
                {
                    e1.del(entry_);
                    e2.del(entry_);
                    e3.del(entry_);
                }

                inline size_t size() const
                {
                    return e1.size();
                }

                inline bool empty() const
                {
                    return e1.empty();
                }

                inline void clear()
                {
                    e1.clear();
                    e2.clear();
                    e3.clear();
                }
                
                template <typename entry_type>
                inline bool exec_every(entry_callback_t<entry_type>* cb_)
                {
                    typename e1::it it_tmp;
                    for (it_tmp = e1.m_elements.begin(); it_tmp != e1.m_elements.end(); ++it_tmp)
                    {
                        if (!cb->exec((entry_type*)it_tmp.second))
                        {
                            return false;
                        }
                    }

                    return true;
                }
                
                template <typename entry_type>
                inline void remove_entry_if(remove_entry_pre_t<entry_type>* remove_pre_)
                {
                    typename e1::it it_tmp;
                    for (it_tmp = e1.m_elemnts.begin(); it_tmp != e1.elements.end(); ++it_tmp)
                    {
                        if (remove_pre_->is_it((entry_type)it_tmp.second))
                        {
                            remove_pre_->m_vc_entrys.push((entry_type)it_tmp.second);
                        }
                                
                    }

                    for (size_t i = 0; i < remove_pre->m_vc_entrys.size(); ++i)
                    {
                        del(remove_pre_->m_vc_entrys[i]);
                    }
                }
        };
    }
}

#endif
