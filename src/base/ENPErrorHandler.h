/*************************************************************************
 *                                                                       *
 * This file is part of Yet Another Robot Simulator (ENP).              *
 * Copyright (C) 2003-2015 Keyan Ghazi-Zahedi.                           *
 * All rights reserved.                                                  *
 * Email: keyan.zahedi@googlemail.com                                    *
 * Web: https://github.com/kzahedi/ENP                                  *
 *                                                                       *
 * For a list of contributors see the file AUTHORS.                      *
 *                                                                       *
 * ENP is free software; you can redistribute it and/or modify it under *
 * the terms of the GNU General Public License as published by the Free  *
 * Software Foundation; either version 2 of the License, or (at your     *
 * option) any later version.                                            *
 *                                                                       *
 * ENP is distributed in the hope that it will be useful, but WITHOUT   *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or *
 * FITNESS FOR A PARTICULAR PURPOSE.                                     *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with ENP in the file COPYING; if not, write to the Free        *
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor,               *
 * Boston, MA 02110-1301, USA                                            *
 *                                                                       *
 *************************************************************************/



#ifndef __ENP_ERROR_HANDLER_H__
#define __ENP_ERROR_HANDLER_H__

#include <string>
#include <sstream>

using namespace std;

class ENPErrorHandler : public stringstream
{
  public:
    static ENPErrorHandler* instance();

    static void push();
    static void push(const char *string, ...);
    static void push(string message);

    string message();

  private:
    ENPErrorHandler();

    static ENPErrorHandler *_me;

};
#endif // __ENP_ERROR_HANDLER_H__
