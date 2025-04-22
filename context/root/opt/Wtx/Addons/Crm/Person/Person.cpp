/**************************************************************************
###########################################################################
##
## $SHOWOFFDB_BEGIN_LICENSE$
## Copyright (C) 2011 Lorimark Solutions, LLC and/or its subsidiary(-ies).
##  All rights reserved.
##  Contact: Lorimark Solutions, LLC (info@showoff-db.org)
##
## This file is part of the Showoff Database Application Framework.
##
##  Commercial Usage
##  Licensees holding valid ShowoffDB Commercial licenses may use this file in
##   accordance with the ShowoffDB Commercial License Agreement provided with the
##   Software or, alternatively, in accordance with the terms contained in
##   a written agreement between you and Lorimark Solutions, LLC.
##
## GNU Lesser General Public License Usage
##  Alternatively, this file may be used under the terms of the GNU Lesser
##   General Public License version 2.1 as published by the Free Software
##   Foundation and appearing in the file LICENSE.LGPL included in the
##   packaging of this file.  Please review the following information to
##   ensure the GNU Lesser General Public License version 2.1 requirements
##   will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
##
## In addition, as a special exception, Lorimark Solutions, LLC gives
##  you certain additional rights.  These rights are described in the
##  Lorimark Solutions, LLC ShowoffDB LGPL Exception version 1.0, included in
##  the file LGPL_EXCEPTION.txt in this package.
##
## GNU General Public License Usage
##  Alternatively, this file may be used under the terms of the GNU
##   General Public License version 3.0 as published by the Free Software
##   Foundation and appearing in the file LICENSE.GPL included in the
##   packaging of this file.  Please review the following information to
##   ensure the GNU General Public License version 3.0 requirements will be
##   met: http://www.gnu.org/copyleft/gpl.html.
##
## If you have questions regarding the use of this file, please contact
##   Lorimark Solutions, LLC at info@showoff-db.org.
## $SHOWOFFDB_END_LICENSE$
##
#############################################################################
****************************************************************************/

#include <Wtx/Core/Core.h>
#include <Wtx/Util/Util.h>
#include <Wtx/Dbo/QueryModel.h>

#include "Item.h"
#include "Person.h"

void Wtx::Crm::Person::mapClasses( Wtx::Dbo::Session & session )
{
  Wtx::Crm::Person::Item::MapClass( session );
}

void Wtx::Crm::Person::postCreateTables( Wtx::Dbo::Session & session )
{
  Wtx::Crm::Person::Item::PostCreateTable( session );

}

std::string Wtx::Crm::Person::key( const std::string & lastName, const std::string & firstName )
{
  return
    Wt::WString("{1}, {2}")
    .arg( lastName )
    .arg( firstName )
    .toUTF8()
    ;
}


Wtx::Crm::Person::Item::Ptr Wtx::Crm::Person::load( int id, Wtx::Dbo::Session & session )
{
  Wt::Dbo::Transaction t( session );
  return
    session.load< Wtx::Crm::Person::Item >(id)
    ;
}

Wtx::Crm::Person::Item::Ptr Wtx::Crm::Person::load( const std::string & idstring, Wtx::Dbo::Session & session )
{
  Wtx::Crm::Person::Item::Ptr retVal;

  if( idstring.length() < 0 )
    return retVal;

  if( idstring.at(0) != '[' )
    return retVal;

  auto ids = Wtx::Core::split( idstring, ':' );

  if( ids.size() != 2 )
    return retVal;

  int id = -1;
  try
  {
    id = Wtx::stoi( ids.at(1) );
  }
  catch(...)
  {
    std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;
  }

  if( id > -1 )
    return load( id, session );

  std::cout << __FILE__ << ":" << __LINE__ << " " << ids.size() << std::endl;
  std::cout << __FILE__ << ":" << __LINE__ << " " << ids.at(0)  << std::endl;
  std::cout << __FILE__ << ":" << __LINE__ << " " << ids.at(1)  << std::endl;

//  Wt::Dbo::Transaction t( session );
//  return
//    session.load< Wtx::Crm::Person::Item >(id)
//    ;

  return retVal;

}

Wtx::Crm::Person::Item::Ptr Wtx::Crm::Person::xfind( const std::string & xid, Wtx::Dbo::Session & session )
{
  Wt::Dbo::Transaction t( session );
  return
    session.find< Wtx::Crm::Person::Item >()
    .where( "xid = ? AND xid != ''")
    .bind( xid )
    .resultValue()
    ;
}


Wtx::Crm::Person::Item::Ptr Wtx::Crm::Person::add( const std::string & lastName, const std::string & firstName, Wtx::Dbo::Session & session )
{
  Wt::Dbo::Transaction t( session );
  return
    session.addNew<Wtx::Crm::Person::Item>( Wtx::Crm::Person::key( lastName, firstName ) );
}

std::shared_ptr<Wt::WAbstractItemModel> Wtx::Crm::Person::getComboBoxModel( int sid, int tid, const std::string & where, Wtx::Dbo::Session & session )
{
  auto retVal = std::make_shared< Wtx::Dbo::QueryModel< std::tuple<int,std::string> > >();

  Wt::Dbo::Transaction t( session );

  auto w = where;
  if( tid != -1 )
    w = Wt::WString("WHERE id={1}").arg(tid).toUTF8();

#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << "\n sid:" << sid
    << "\n tid:" << tid
    << "\n where:" << w
    << std::endl
    ;
#endif

  auto sql =
    Wt::WString
    (
     "SELECT id,\"keyField\" || ' ~ ' || \"cfyField\" AS key FROM \"crmPerson\""
     " {1}"
     " UNION "
     "SELECT -1 as id, '' as key"
     " ORDER BY key"
    )
    .arg( w )
    .toUTF8()
    ;


  auto query =
   session.query< std::tuple<int,std::string> >( sql )
   ;

  retVal-> setQuery( query );
  retVal-> addColumn("id");
  retVal-> addColumn("key");

  return retVal;
}



