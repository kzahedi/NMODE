#ifndef __NMODE_EXCEPTION_H__
#define __NMODE_EXCEPTION_H__

#include <iostream>

using namespace std;

class NMODEException : public std::exception
{
  public:
    explicit NMODEException(const std::string& what) : m_what(what) {}  

    virtual ~NMODEException() throw() {}

    virtual const char * what() const throw()
    {   
      return m_what.c_str();
    }   

    virtual void message() const throw()
    {   
      std::cout << "NMODE Exception: " << m_what << std::endl;
    }   


  private:
    std::string m_what;
};

#endif // __NMODE_EXCEPTION_H__
