///  @file    TestModelCreator_newSetters.cs
///  @brief   ModelCreator unit tests
///  @author  Frank Bergmann (Csharp conversion)
///  @author  Akiya Jouraku (Csharp conversion)
///  @author  Sarah Keating 
/// 
///  $Id: TestModelCreator_newSetters.cs 11545 2010-07-23 02:19:10Z mhucka $
///  $HeadURL: http://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/bindings/csharp/test/annotation/TestModelCreator_newSetters.cs $
/// 
///  ====== WARNING ===== WARNING ===== WARNING ===== WARNING ===== WARNING ======
/// 
///  DO NOT EDIT THIS FILE.
/// 
///  This file was generated automatically by converting the file located at
///  src/annotation/test/TestModelCreator_newSetters.c
///  using the conversion program dev/utilities/translateTests/translateTests.pl.
///  Any changes made here will be lost the next time the file is regenerated.
/// 
///  -----------------------------------------------------------------------------
///  This file is part of libSBML.  Please visit http://sbml.org for more
///  information about SBML, and the latest version of libSBML.
/// 
///  Copyright 2005-2010 California Institute of Technology.
///  Copyright 2002-2005 California Institute of Technology and
///                      Japan Science and Technology Corporation.
///  
///  This library is free software; you can redistribute it and/or modify it
///  under the terms of the GNU Lesser General Public License as published by
///  the Free Software Foundation.  A copy of the license agreement is provided
///  in the file named "LICENSE.txt" included with this software distribution
///  and also available online as http://sbml.org/software/libsbml/license.html
///  -----------------------------------------------------------------------------


namespace LibSBMLCSTest {

  using libsbml;

  using System;

  using System.IO;

  public class TestModelCreator_newSetters {
    public class AssertionError : System.Exception 
    {
      public AssertionError() : base()
      {
        
      }
    }


    static void assertTrue(bool condition)
    {
      if (condition == true)
      {
        return;
      }
      throw new AssertionError();
    }

    static void assertEquals(object a, object b)
    {
      if ( (a == null) && (b == null) )
      {
        return;
      }
      else if ( (a == null) || (b == null) )
      {
        throw new AssertionError();
      }
      else if (a.Equals(b))
      {
        return;
      }
  
      throw new AssertionError();
    }

    static void assertNotEquals(object a, object b)
    {
      if ( (a == null) && (b == null) )
      {
        throw new AssertionError();
      }
      else if ( (a == null) || (b == null) )
      {
        return;
      }
      else if (a.Equals(b))
      {
        throw new AssertionError();
      }
    }

    static void assertEquals(bool a, bool b)
    {
      if ( a == b )
      {
        return;
      }
      throw new AssertionError();
    }

    static void assertNotEquals(bool a, bool b)
    {
      if ( a != b )
      {
        return;
      }
      throw new AssertionError();
    }

    static void assertEquals(int a, int b)
    {
      if ( a == b )
      {
        return;
      }
      throw new AssertionError();
    }

    static void assertNotEquals(int a, int b)
    {
      if ( a != b )
      {
        return;
      }
      throw new AssertionError();
    }


    public void test_ModelCreator_setEmail()
    {
      ModelCreator mc = new  ModelCreator();
      assertTrue( mc != null );
      int i = mc.setEmail( "Keating");
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( mc.isSetEmail() == true );
      assertTrue((  "Keating" == mc.getEmail() ));
      i = mc.setEmail( "");
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( mc.isSetEmail() == false );
      i = mc.setEmail( "Keating");
      assertTrue( mc.isSetEmail() == true );
      i = mc.unsetEmail();
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( mc.isSetEmail() == false );
      mc = null;
    }

    public void test_ModelCreator_setFamilyName()
    {
      ModelCreator mc = new  ModelCreator();
      assertTrue( mc != null );
      int i = mc.setFamilyName( "Keating");
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( mc.isSetFamilyName() == true );
      assertTrue((  "Keating" == mc.getFamilyName() ));
      i = mc.setFamilyName( "");
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( mc.isSetFamilyName() == false );
      i = mc.setFamilyName( "Keating");
      assertTrue( mc.isSetFamilyName() == true );
      i = mc.unsetFamilyName();
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( mc.isSetFamilyName() == false );
      mc = null;
    }

    public void test_ModelCreator_setGivenName()
    {
      ModelCreator mc = new  ModelCreator();
      assertTrue( mc != null );
      int i = mc.setGivenName( "Sarah");
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( mc.isSetGivenName() == true );
      assertTrue((  "Sarah" == mc.getGivenName() ));
      i = mc.setGivenName( "");
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( mc.isSetGivenName() == false );
      i = mc.setGivenName( "Sarah");
      assertTrue( mc.isSetGivenName() == true );
      i = mc.unsetGivenName();
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( mc.isSetGivenName() == false );
      mc = null;
    }

    public void test_ModelCreator_setOrganization()
    {
      ModelCreator mc = new  ModelCreator();
      assertTrue( mc != null );
      int i = mc.setOrganization( "Caltech");
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( mc.isSetOrganization() == true );
      assertTrue((  "Caltech" == mc.getOrganization() ));
      i = mc.setOrganization( "");
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( mc.isSetOrganization() == false );
      i = mc.setOrganization( "Caltech");
      assertTrue( mc.isSetOrganization() == true );
      i = mc.unsetOrganization();
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( mc.isSetOrganization() == false );
      mc = null;
    }

  }
}
