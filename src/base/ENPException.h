/*************************************************************************
 *                                                                       *
 * This file is part of Evolution of Neural Pathways (ENP).              *
 * Copyright (C) 2003-2015 Keyan Ghazi-Zahedi.                           *
 * All rights reserved.                                                  *
 * Email: keyan.zahedi@googlemail.com                                    *
 * Web: https://github.com/kzahedi/ENP                                   *
 *                                                                       *
 * For a list of contributors see the file AUTHORS.                      *
 *                                                                       *
 * YARS is free software; you can redistribute it and/or modify it under *
 * the terms of the GNU General Public License as published by the Free  *
 * Software Foundation; either version 2 of the License, or (at your     *
 * option) any later version.                                            *
 *                                                                       *
 * YARS is distributed in the hope that it will be useful, but WITHOUT   *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or *
 * FITNESS FOR A PARTICULAR PURPOSE.                                     *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with YARS in the file COPYING; if not, write to the Free        *
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor,               *
 * Boston, MA 02110-1301, USA                                            *
 *                                                                       *
 *************************************************************************/



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
