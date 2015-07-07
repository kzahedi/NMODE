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



#ifndef __MODULES_TEST_H__
#define __MODULES_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

class modulesTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(modulesTest);
  CPPUNIT_TEST(testModules);
  CPPUNIT_TEST(testModuleNeuronEquality);
  CPPUNIT_TEST(testModuleEquality);
  CPPUNIT_TEST(testModuleInequality);
  CPPUNIT_TEST_SUITE_END();

  public:

  void testModules();
  void testModuleNeuronEquality();
  void testModuleEquality();
  void testModuleInequality();
};

#endif // __RNN_H__
