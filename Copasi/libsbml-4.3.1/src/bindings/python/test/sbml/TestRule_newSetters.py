#
# @file    TestRule_newSetters.py
# @brief   Rule unit tests for new set function API
#
# @author  Akiya Jouraku (Python conversion)
# @author  Sarah Keating 
#
# $Id: TestRule_newSetters.py 11402 2010-07-07 01:43:53Z mhucka $
# $HeadURL: http://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/bindings/python/test/sbml/TestRule_newSetters.py $
#
# ====== WARNING ===== WARNING ===== WARNING ===== WARNING ===== WARNING ======
#
# DO NOT EDIT THIS FILE.
#
# This file was generated automatically by converting the file located at
# src/sbml/test/TestRule_newSetters.c
# using the conversion program dev/utilities/translateTests/translateTests.pl.
# Any changes made here will be lost the next time the file is regenerated.
#
# -----------------------------------------------------------------------------
# This file is part of libSBML.  Please visit http://sbml.org for more
# information about SBML, and the latest version of libSBML.
#
# Copyright 2005-2010 California Institute of Technology.
# Copyright 2002-2005 California Institute of Technology and
#                     Japan Science and Technology Corporation.
# 
# This library is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation.  A copy of the license agreement is provided
# in the file named "LICENSE.txt" included with this software distribution
# and also available online as http://sbml.org/software/libsbml/license.html
# -----------------------------------------------------------------------------

import sys
import unittest
import libsbml


class TestRule_newSetters(unittest.TestCase):

  global R
  R = None

  def setUp(self):
    self.R = libsbml.AssignmentRule(2,4)
    if (self.R == None):
      pass    
    pass  

  def tearDown(self):
    _dummyList = [ self.R ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Rule_setFormula1(self):
    formula =  "k1*X0";
    i = self.R.setFormula(formula)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_(( formula == self.R.getFormula() ))
    self.assertEqual( True, self.R.isSetFormula() )
    pass  

  def test_Rule_setFormula2(self):
    i = self.R.setFormula("")
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( False, self.R.isSetFormula() )
    pass  

  def test_Rule_setFormula3(self):
    formula =  "k1 X0";
    i = self.R.setFormula(formula)
    self.assert_( i == libsbml.LIBSBML_INVALID_OBJECT )
    self.assertEqual( False, self.R.isSetFormula() )
    pass  

  def test_Rule_setMath1(self):
    math = libsbml.ASTNode(libsbml.AST_TIMES)
    a = libsbml.ASTNode()
    b = libsbml.ASTNode()
    a.setName( "a")
    b.setName( "b")
    math.addChild(a)
    math.addChild(b)
    i = self.R.setMath(math)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( True, self.R.isSetMath() )
    math1 = self.R.getMath()
    self.assert_( math1 != None )
    formula = libsbml.formulaToString(math1)
    self.assert_( formula != None )
    self.assert_((  "a * b" == formula ))
    _dummyList = [ math ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Rule_setMath2(self):
    math = libsbml.ASTNode(libsbml.AST_TIMES)
    a = libsbml.ASTNode()
    a.setName( "a")
    math.addChild(a)
    i = self.R.setMath(math)
    self.assert_( i == libsbml.LIBSBML_INVALID_OBJECT )
    self.assertEqual( False, self.R.isSetMath() )
    _dummyList = [ math ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Rule_setMath3(self):
    i = self.R.setMath(None)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( False, self.R.isSetMath() )
    pass  

  def test_Rule_setUnits1(self):
    i = self.R.setUnits( "second")
    self.assert_( i == libsbml.LIBSBML_UNEXPECTED_ATTRIBUTE )
    self.assertEqual( False, self.R.isSetUnits() )
    pass  

  def test_Rule_setUnits2(self):
    R1 = libsbml.AssignmentRule(1,2)
    R1.setL1TypeCode(libsbml.SBML_PARAMETER_RULE)
    i = R1.setUnits( "second")
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( True, R1.isSetUnits() )
    i = R1.unsetUnits()
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( False, R1.isSetUnits() )
    _dummyList = [ R1 ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Rule_setUnits3(self):
    R1 = libsbml.AssignmentRule(1,2)
    R1.setL1TypeCode(libsbml.SBML_PARAMETER_RULE)
    i = R1.setUnits( "1second")
    self.assert_( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE )
    self.assertEqual( False, R1.isSetUnits() )
    i = R1.unsetUnits()
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( False, R1.isSetUnits() )
    _dummyList = [ R1 ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Rule_setUnits4(self):
    R1 = libsbml.AssignmentRule(1,2)
    R1.setL1TypeCode(libsbml.SBML_PARAMETER_RULE)
    i = R1.setUnits( "second")
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( True, R1.isSetUnits() )
    i = R1.setUnits("")
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( False, R1.isSetUnits() )
    _dummyList = [ R1 ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Rule_setVariable1(self):
    i = self.R.setVariable( "1mole")
    self.assert_( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE )
    self.assertEqual( False, self.R.isSetVariable() )
    pass  

  def test_Rule_setVariable2(self):
    i = self.R.setVariable( "mole")
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( True, self.R.isSetVariable() )
    i = self.R.setVariable( "")
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( False, self.R.isSetVariable() )
    pass  

  def test_Rule_setVariable3(self):
    R1 = libsbml.AlgebraicRule(1,2)
    i = R1.setVariable( "r")
    self.assert_( i == libsbml.LIBSBML_UNEXPECTED_ATTRIBUTE )
    self.assertEqual( False, R1.isSetVariable() )
    _dummyList = [ R1 ]; _dummyList[:] = []; del _dummyList
    pass  

def suite():
  suite = unittest.TestSuite()
  suite.addTest(unittest.makeSuite(TestRule_newSetters))

  return suite

if __name__ == "__main__":
  if unittest.TextTestRunner(verbosity=1).run(suite()).wasSuccessful() :
    sys.exit(0)
  else:
    sys.exit(1)
