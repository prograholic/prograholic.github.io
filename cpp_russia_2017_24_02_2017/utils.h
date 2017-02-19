#pragma once

#include <type_traits>
#include <new>


struct exception_support : 
#if defined (_CPPUNWIND)
    std::true_type
#else
    std::false_type
#endif
{
};

#if 0
namespace detail
{

template<typename T, typename MemberPtrGetter>
struct has_member_impl
{
private:
    template<typename U> static char Test(typename MemberPtrGetter::template type<U>*);
    template<typename U> static int Test(...);

public:
    static constexpr bool value = sizeof(Test<T>(0)) == sizeof(char);
};


struct check_has_assign_copy
{
    template <typename T, int (T::*)(const T&) = &T::assign_copy>
    struct type
    {
    };
};


} // namespace detail



template <typename T, typename MemberPtrGetter>
struct has_member : public std::integral_constant<bool, detail::has_member_impl<T, MemberPtrGetter>::value>
{
};


template <typename T>
struct has_assign_copy : public has_member<T, detail::check_has_assign_copy>
{
};


#endif //

template <bool condition, typename T, typename Y>
struct or_
{
    typedef T type;
};

template <typename T, typename Y>
struct or_<false, T, Y>
{
    typedef Y type;
};


template <typename T>
struct allocator
{
    template <typename ...Args>
    static bool assign_copy(T& src, Args&& ... args) noexcept
    {
        return src.assign_copy(std::forward<Args>(args)...);
    }
    
    template <typename ...Args>
    static T* construct_copy(Args&& ... args) noexcept
    {
        void* location = allocate_nx(1);
        if (!location)
        {
            return nullptr;
        }
        
        T* obj = new(static_cast<void*>(location))T(); // should be noexcept
        if (!obj->assign_copy(std::forward<Args>(args)...))
        {
            destroy(obj);
            deallocate(obj);
            
            return nullptr;
        }

        return obj;
    }
    
    static void* allocate_nx(size_t count) noexcept
    {
        return operator new(count * sizeof(T), std::nothrow);
    }
    
    static void destroy(T* obj) noexcept
    {
        obj->~T();
    }
    
    static void deallocate(T* location) noexcept
    {
        delete location;
    }
};

template <typename T>
class vector_base
{
public:
    vector_base() noexcept
        : m_value(nullptr)
    {
    }
    
    ~vector_base() noexcept
    {
        delete m_value;
    }
    
    vector_base(vector_base&& other) noexcept
        : m_value(other.m_value)
    {
        other.m_value = nullptr;
    }
    
    vector_base(const vector_base& ) = delete;
    
public:
    T* m_value; 
};

template <typename T>
class vector_nx : public vector_base<T>
{
public:
    
    vector_nx() = default;
    vector_nx(vector_nx&& ) = default;
    vector_nx(const vector_nx& ) = delete;

    bool assign_copy(const vector_base<T>& other) noexcept
    {
        if (!other.m_value)
        {
            return true;
        }
        
        m_value = allocator<T>::construct_copy(*other.m_value);
        if (!m_value)
        {
            return false;
        }
        
        return true;
    }
    
    bool push_back_nothrow(const T& val) noexcept
    {
        if (m_value)
        {
            return false;
        }
        
        m_value = allocator<T>::construct_copy(val);
        if (!m_value)
        {
            return false;
        }
        
        return true;
    }
};

template <typename T>
class vector_x : public vector_nx<T>
{
public:

    vector_x() = default;
    vector_x(vector_x&& ) = default;
    
    vector_x(const vector_x& other)
    {
        if (!other.m_value)
        {
            m_value = nullptr;
        }
        
        m_value = new T(*other.m_value);
    }

    vector_x& operator=(const vector_x& other)
    {
        if (!other.m_value)
        {
            return *this;
        }
        
        T* val = new T(*other.m_value);
        
        vector_base tmp(std::move(*this));
        m_value = val;
        
        return *this;
    }

    void push_back(const T& val)
    {
        if (m_value)
        {
            throw std::exception("full");
        }
        
        m_value = new T(val);
    }
};

template <typename T>
using vector = typename or_<exception_support::value, vector_x<T>, vector_nx<T> >::type;

struct Foo
{
    Foo()
        : x(0)
    {
    }
    
    Foo(int i)
        : x(i)
    {
    }
    
    bool assign_copy(const Foo& other)
    {
        x = other.x;
        return true;
    }
    
    int x;
};
