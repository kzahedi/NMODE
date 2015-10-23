/*************************************************************************
 *                                                                       *
 * This file is part of Yet Another Robot Simulator (YARS).              *
 * Copyright (C) 2003-2015 Keyan Ghazi-Zahedi.                           *
 * All rights reserved.                                                  *
 * Email: keyan.zahedi@googlemail.com                                    *
 * Web: https://github.com/kzahedi/YARS                                  *
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



#include "StringTokeniser.h"

using namespace std;

// taken from http://www.digitalpeer.com/id/simple
std::vector<string> StringTokeniser::tokenise(const string& str, const string& delimiters)
{
  std::vector<string> tokens;
  string::size_type delimPos = 0, tokenPos = 0, pos = 0;

  if(str.length()<1)  return tokens;
  while(1){
    delimPos = str.find_first_of(delimiters, pos);
    tokenPos = str.find_first_not_of(delimiters, pos);

    if(string::npos != delimPos){
      if(string::npos != tokenPos){
        if(tokenPos<delimPos){
          tokens.push_back(str.substr(pos,delimPos-pos));
        }else{
          tokens.push_back("");
        }
      }else{
        tokens.push_back("");
      }
      pos = delimPos+1;
    } else {
      if(string::npos != tokenPos){
        tokens.push_back(str.substr(pos));
      } else {
        tokens.push_back("");
      }
      break;
    }
  }
  return tokens;
}

