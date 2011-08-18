/**
 * \file    TestXMLAttributes.cpp
 * \brief   TestXMLAttributes unit tests
 * \author  Ben Bornstein
 *
 * $Id: TestXMLAttributes.cpp 11633 2010-08-03 03:53:27Z mhucka $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/xml/test/TestXMLAttributes.cpp $
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright (C) 2009-2011 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. EMBL European Bioinformatics Institute (EBML-EBI), Hinxton, UK
 *  
 * Copyright (C) 2006-2008 by the California Institute of Technology,
 *     Pasadena, CA, USA 
 *  
 * Copyright (C) 2002-2005 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. Japan Science and Technology Agency, Japan
 * 
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.  A copy of the license agreement is provided
 * in the file named "LICENSE.txt" included with this software distribution
 * and also available online as http://sbml.org/software/libsbml/license.html
 * ---------------------------------------------------------------------- -->*/


#include <limits>

#include <iostream>
#include <check.h>
#include <XMLAttributes.h>
#include <XMLError.h>
#include <XMLNamespaces.h>
#include <XMLNode.h>
#include <XMLToken.h>
#include <XMLInputStream.h>

#include <string>


/** @cond doxygen-ignored */

using namespace std;
LIBSBML_CPP_NAMESPACE_USE

/** @endcond */
static const string errMsg = "NULL reference in XML constructor";
static const string errMsg1 = "Null argument to copy constructor";
static const string errMsg2 = "Null argument to assignment operator";


CK_CPPSTART

START_TEST ( test_XMLAttributes )
{
  string msg;
  try 
  {
    XMLAttributes * att = new XMLAttributes();
    delete att;
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == "");

  XMLAttributes *att1 = NULL;
  XMLAttributes *att2 = NULL;
  msg = "";
  // copy constructor
  try
  {
    att2=new XMLAttributes(*att1);
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg1);

  msg = "";
  att2 = new XMLAttributes();
  // assignment
  try
  {
    (*att2) = *att1;
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg2);
  delete att2;
}
END_TEST


START_TEST ( test_XMLError )
{
  string msg;
  try 
  {
    XMLError * err = new XMLError(MissingXMLDecl);
    delete err;
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == "");

  XMLError *err1 = NULL;
  XMLError *err2 = NULL;
  msg = "";
  // copy constructor
  try
  {
    err2=new XMLError(*err1);
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg1);

  msg = "";
  err2 = new XMLError(MissingXMLDecl);
  // assignment
  try
  {
    (*err2) = *err1;
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg2);
  delete err2;
}
END_TEST


START_TEST ( test_XMLNamespaces )
{
  string msg;
  try 
  {
    XMLNamespaces * ns = new XMLNamespaces();
    delete ns;
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == "");

  XMLNamespaces *ns1 = NULL;
  XMLNamespaces *ns2 = NULL;
  msg = "";
  // copy constructor
  try
  {
    ns2=new XMLNamespaces(*ns1);
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg1);

  msg = "";
  ns2 = new XMLNamespaces();
  // assignment
  try
  {
    (*ns2) = *ns1;
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg2);
  delete ns2;
}
END_TEST


START_TEST ( test_XMLNode )
{
  string msg;
  try 
  {
    XMLNode * node = new XMLNode();
    delete node;
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == "");

  XMLNode *node1 = NULL;
  XMLNode *node2 = NULL;
  msg = "";
  // copy constructor
  try
  {
    node2=new XMLNode(*node1);
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg1);

  msg = "";
  node2 = new XMLNode();
  // assignment
  try
  {
    (*node2) = *node1;
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg2);
  delete node2;
}
END_TEST


START_TEST ( test_XMLToken )
{
  string msg;
  try 
  {
    XMLToken * token = new XMLToken();
    delete token;
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == "");

  msg = "";
  XMLTriple *triple = NULL;
  XMLToken * token3 = NULL;
  // ctor from triple
  try 
  {
    token3 = new XMLToken(*(triple));
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg1);

  msg = "";
  XMLTriple *triple1 = new XMLTriple();
  XMLAttributes *att = NULL;
  // ctor from triple and attributes
  try 
  {
    token3 = new XMLToken(*(triple1), *(att));
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg1);

  msg = "";
  XMLAttributes *att1 = new XMLAttributes();
  XMLNamespaces *ns = NULL;
  // ctor from triple, attributes & namespaces
  try 
  {
    token3 = new XMLToken(*(triple1), *(att1), *(ns));
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg1);

  msg = "";
  std::string *mess = NULL;
  // ctor from string
  try 
  {
    token3 = new XMLToken(*(mess));
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg);

  XMLToken *token1 = NULL;
  XMLToken *token2 = NULL;
  msg = "";
  // copy ctor
  try
  {
    token2=new XMLToken(*token1);
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg1);

  msg = "";
  token2 = new XMLToken();
  // assignment
  try
  {
    (*token2) = *token1;
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg2);
  delete token2;
  delete triple1;
  delete att1;

}
END_TEST


START_TEST ( test_XMLTriple )
{
  string msg;
  try 
  {
    XMLTriple * triple = new XMLTriple();
    delete triple;
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == "");

  XMLTriple *triple1 = NULL;
  XMLTriple *triple2 = NULL;
  msg = "";
  // copy constructor
  try
  {
    triple2=new XMLTriple(*triple1);
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg1);

  msg = "";
  triple2 = new XMLTriple();
  // assignment
  try
  {
    (*triple2) = *triple1;
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg2);

  msg = "";
  // ctor with name/uri/prefix
  try
  {
    std::string *name = NULL;
    std::string uri = "uri";
    std::string prefix = "prefix";
    triple2 = new XMLTriple (*(name), uri, prefix);
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg);

  msg = "";
  // ctor with name/uri/prefix
  try
  {
    std::string name = "name";
    std::string *uri = NULL;
    std::string prefix = "prefix";
    triple2 = new XMLTriple (name, *(uri), prefix);
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg);

  msg = "";
  // ctor with name/uri/prefix

  try
  {
    std::string name = "name";
    std::string uri = "uri";
    std::string *prefix = NULL;
    triple2 = new XMLTriple (name, uri, *(prefix));
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg);

  msg = "";
  // ctor with triplet
  std::string *triplet = NULL;
  try
  {
    triple2 = new XMLTriple (*(triplet));
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg);

  delete triple2;
}
END_TEST


START_TEST ( test_XMLOutputStream )
{
  string msg;
  std::ostream *stream = NULL;
  XMLOutputStream* opstream2 = NULL;
  msg = "";
  // ctor from stream
  try
  {
    opstream2=new XMLOutputStream(*(stream));
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg);
}
END_TEST


START_TEST ( test_XMLInputStream )
{
  string msg;
  const char *stream = NULL;
  msg = "";
  // ctor from content
  try
  {
    XMLInputStream opstream2(stream);
  }
  catch (XMLConstructorException &e)
  {
    msg = e.what();
  }
  fail_unless(msg == errMsg);
}
END_TEST


Suite *
create_suite_XMLExceptions (void)
{
  Suite *suite = suite_create("XMLExceptions");
  TCase *tcase = tcase_create("XMLExceptions");

 
  tcase_add_test( tcase, test_XMLAttributes);
  tcase_add_test( tcase, test_XMLError);
  tcase_add_test( tcase, test_XMLNamespaces);
  tcase_add_test( tcase, test_XMLNode);
  tcase_add_test( tcase, test_XMLToken);
  tcase_add_test( tcase, test_XMLTriple);
  tcase_add_test( tcase, test_XMLOutputStream);
  tcase_add_test( tcase, test_XMLInputStream);

  suite_add_tcase(suite, tcase);

  return suite;
}


CK_CPPEND
