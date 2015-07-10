#ifndef __ENP_EXCEPTION_H__
#define __ENP_EXCEPTION_H__

#include <iostream>

using namespace std;

class ENPException : public std::exception
{
  public:
    explicit ENPException(const std::string& what) : m_what(what) {}  

    virtual ~ENPException() throw() {}

    virtual const char * what() const throw()
    {   
      return m_what.c_str();
    }   

    virtual void message() const throw()
    {   
      std::cout << "ENP Exception: " << m_what << std::endl;
    }   


  private:
    std::string m_what;
};

#endif // __ENP_EXCEPTION_H__
