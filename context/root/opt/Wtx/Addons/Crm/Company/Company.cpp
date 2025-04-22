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

#include <Wtx/Util/Util.h>
#include <Wtx/Dbo/TableView.h>

#include "Item.h"
#include "Company.h"

void Wtx::Crm::Company::mapClasses( Wtx::Dbo::Session & session )
{
  Wtx::Crm::Company::Item::MapClass( session );
}

void Wtx::Crm::Company::postCreateTables( Wtx::Dbo::Session & session )
{
  Wtx::Crm::Company::Item::PostCreateTable( session );

}

std::string Wtx::Crm::Company::key( const std::string & lastName, const std::string & firstName )
{
  return
    Wt::WString("{1}, {2}")
    .arg( lastName )
    .arg( firstName )
    .toUTF8()
    ;
}


Wt::Dbo::ptr< Wtx::Crm::Company::Item > Wtx::Crm::Company::xfind( const std::string & xid, Wtx::Dbo::Session & session )
{
  Wt::Dbo::Transaction t( session );
  return
    session.find<Wtx::Crm::Company::Item>()
    .where( "xid = ?")
    .bind( xid )
    .resultValue()
    ;
}


Wt::Dbo::ptr< Wtx::Crm::Company::Item > Wtx::Crm::Company::add( const std::string & name, Wtx::Dbo::Session & session )
{
  Wt::Dbo::Transaction t( session );
  return
    session.addNew<Wtx::Crm::Company::Item>( name );
}


#ifdef NEVER
std::shared_ptr<Wt::WAbstractItemModel> Wtx::Crm::Company::getCompanyModel( int sid, int tid, const std::string & filter, Wtx::Dbo::Session & session )
{
  auto retVal =
    std::make_shared< Wtx::Dbo::QueryModel< std::tuple<int,std::string> > >();

  Wt::Dbo::Transaction t(session);

  std::string w;

  if( tid != -1 )
    w = Wt::WString("WHERE id={1}").arg(tid).toUTF8();

  else
  {
    w =
      Wt::WString
      (
       "WHERE \"isActive\""
      )
      .toUTF8()
      ;

    if( filter != "" )
    {
      w += Wt::WString
         (
          " AND (UPPER(\"keyField\") LIKE '%{1}%' OR "
          " UPPER(\"cfyField\") LIKE '%{1}%')"
         )
         .arg( Wtx::ucase(filter) )
         .toUTF8()
         ;
    }
  }

  auto sql =
    Wt::WString
    (
      "SELECT "
      "id, "
      "\"keyField\" || ' ~ ' || "
      "\"cfyField\" "
      "AS key "
      "FROM \"crmPerson\" "
      " {1}"
      " ORDER BY key"
    )
    .arg( w )
    .toUTF8()
    ;

#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << "\n sid:" << sid
    << "\n tid:" << tid
    << "\n flt:" << filter
    << "\n sql:" << sql
//    << "\n row:" << retVal-> rowCount()
    << std::endl
    ;
#endif

  auto query =
    session.query< std::tuple<int,std::string> >( sql )
    ;

  retVal-> setQuery( query );
  retVal-> addColumn( "id" );
  retVal-> addColumn( "key" );

  return retVal;

} // endstd::shared_ptr<Wt::WAbstractItemModel> getCompanyModel( int sid, int tid, const std::string & filter, Wtx::Dbo::Session & session )

std::unique_ptr<Wt::WTableView> Wtx::Crm::Company::getCompanyTableView( int sid, int tid, const std::string & filter, Wtx::Dbo::Session & session )
{
  Wtx::TableViewDef::ViewDef viewDef =
  {
    /* title                */ "",
    /* tip                  */ "",
    /* headerCount          */ 0,
    /* selectionMode        */ Wt::SelectionMode::Single,
    /* columnResizeEnabled  */ true,
    /* alternatingRowColors */ true,
    /* sql                  */ "",
    /* filter               */ "",
    /* subFilter            */ "",
    /* idin                 */ {},
    /* doubleClick          */ 0,
    /* showHeader           */ true,
    /* showFooter           */ true,
    /* showPrevNext         */ false,
    /* hideSearch           */ true,
    /* allowFilter          */ false,
    /* allowAdd             */ true,
    /* allowChange          */ false,
    /* allowDelete          */ false,
    /* allowExport          */ true,
    /* allowSearch          */ true,
    /* allowPrint           */ false,
    /* allowUnlock          */ false,
    /* additional           */ "",
    /* itemDelegate         */ nullptr,

    /* sortFields           */
    {
       "\"keyField\", id"
    },

    /* search fields        */
    {
    },

    /* column defs          */
    {
      { "id",           "",       50, Wt::AlignmentFlag::Left, "", nullptr  },
      { "keyField",     "",      150, Wt::AlignmentFlag::Left, "", nullptr  },
      { "cfyField",     "",      350, Wt::AlignmentFlag::Left, "", nullptr  },

    },

    /* column names         */
    {
       "id",
       "keyField",
       "cfyField",
    }
  };

  Wt::Dbo::Transaction t(session);

  auto retVal = std::make_unique< Wtx::Dbo::TableView< Wtx::Crm::Company::Item > >( viewDef, &session );
  //  retVal-> setModel( getProductModel( sid, tid, "", session ) );
  retVal-> setMaximumSize( Wt::WLength::Auto, 300 );
  retVal-> setColumnHidden( 0,true );
  if( filter.length() > 2 )
  {
    auto f =
      Wt::WString
      (
       "(UPPER(\"keyField\") LIKE UPPER('%{1}%')) OR "
       "(UPPER(\"cfyField\") LIKE UPPER('%{1}%'))"
      )
      .arg(filter)
      .toUTF8()
      ;

    retVal-> setFilter( f );

  }

  return retVal;

} // endstd::unique_ptr<Wt::WTableView> getCompanyTableView( int sid, int tid, const std::string & filter, Wtx::Dbo::Session & session )


int Wtx::Crm::Company::CompanyProvider::find_id( const std::string & value )
{
  auto v = "%" + Wtx::ucase(value) + "%";

  Wt::Dbo::Transaction t( *session() );
  auto items =
    session()-> find< Wtx::Crm::Person::Item >()
    .where
    (
     "   (UPPER( \"keyField\"        ) LIKE ?"
     " OR UPPER( \"cfyField\"        ) LIKE ?)"
    )
    .bind( v )
    .bind( v )
    .resultList()
    ;

  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "():"
     << " value=" << value
     << " size:"  << items.size()
     << std::endl
    ;

   if( items.size() != 1 )
    return -1;

  return items.begin()-> id();

} // endint CompanyProvider::find_id( const std::string & value )

std::string Wtx::Crm::Company::CompanyProvider::get_string( int id )
{
  Wt::Dbo::Transaction t( *session() );

  auto companyItem = session()-> load< Wtx::Crm::Company::Item >( id );

  return
    Wt::WString("{1} ~ {2}")
     .arg( companyItem-> cfyField().value() )
     .arg( companyItem-> keyField().value() )
     .toUTF8()
    ;

} // endstd::string CompanyProvider::get_string( int id )

std::string Wtx::Crm::Company::CompanyProvider::get_toolTip( int id )
{
  Wt::Dbo::Transaction t( *session() );
  auto companyItem = session()-> load< Wtx::Crm::Company::Item >( id );

  auto companyKey   = companyItem-> keyField().value();
  auto companyCfy   = companyItem-> cfyField().value();
  auto companyPhone = companyItem-> phone().value();
  auto companyEmail = companyItem-> email().value();

  return "Wtx::Crm::Company::CompanyProvider::get_toolTip";

#ifdef NEVER
  std::string companyInfo;
  if( auto companyItem = personItem-> contactForCompany().value() )
  {
     companyInfo =
      Wt::WString
       (
       "\n~~~ COMPANY INFO:"
        "\n{1} ~ {2}"
       "\nphone:{3}"
        "\n{4}"
       "\n{5}"
        "\n{6} {7}"
      )
      .arg( companyItem-> keyField  ().value() )
      .arg( companyItem-> cfyField  ().value() )
      .arg( companyItem-> mainPhone ().value() )
      .arg( companyItem-> addr      ().value() )
      .arg( companyItem-> addr2     ().value() )
      .arg( companyItem-> city      ().value() )
      .arg( companyItem-> zip       ().value() )
      .toUTF8()
      ;

   }

   return
    Wt::WString
     (
     "~~~ CONTACT INFO:"
      "\n{1} ~ {2}"
     "\nphone:{3}"
      "\nemail:{4}"
     "\n{5}"
     )
    .arg( personCfy   )
    .arg( personKey   )
    .arg( personPhone )
    .arg( personEmail )
    .arg( companyInfo )
    .toUTF8()
    ;
#endif

} // endstd::string ProductProvider::get_string( int id )

std::shared_ptr< Wt::WAbstractItemModel > Wtx::Crm::Company::CompanyProvider::model( int sid, int tid, const std::string & filter )
{
#ifdef NEVER
   std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "():"
     << " sid:"     << sid    << "("   << m_sid  << ")"
     << " tid:"     << tid    << "("   << m_tid  << ")"
     << " filter:'" << filter << "' (" << filter << ")"
     << std::endl
     ;
 #endif

  /*
  ** If nothing has changed, then just return the model.
  **
  */
  if( m_sid    == sid
  &&  m_tid    == tid
  &&  m_filter == filter )
  {
    return m_model;
  }

  /*
  ** Remember things.
  **
  */
  m_sid    = sid;
  m_tid    = tid;
  m_filter = filter;

  /*
  ** build the query as the return value.
  **
  */
  m_model = std::make_shared< Model >();

  /*
  ** Grab things from the system
  **
  */
  Wt::Dbo::Transaction t( *session() );

  std::string w;

  if( tid != -1 )
    w = Wt::WString("WHERE id={1}").arg(tid).toUTF8();

  else
  {
    if( filter != "" )
    {
      w += Wt::WString
         (
         " AND"
          " (UPPER(\"keyField\") LIKE '%{1}%' OR "
         "  UPPER(\"cfyField\") LIKE '%{1}%')"
         )
         .arg( Wtx::ucase(filter) )
         .toUTF8()
        ;
    }
  }

  auto sql =
    Wt::WString
     (
     " {1}"
      " {2}"
     " ORDER BY \"keyField\""
     )
    .arg( "SELECT id,\"keyField\" as key FROM \"crmPerson\"" )
     .arg( w )
    .toUTF8()
     ;

  auto query =
    session()-> query< std::tuple<int,std::string> >( sql )
    ;

   m_model-> setQuery( query );
   m_model-> addColumn( "id" );
   m_model-> addColumn( "key" );

#ifdef NEVER
   std::cout << __FILE__ << ":" << __LINE__
     << "\n sid:" << sid
     << "\n tid:" << tid
     << "\n flt:" << filter
     << "\n row:" << m_model-> rowCount()
     << "\n sql:" << sql
     << std::endl
    ;
#endif

  return m_model;

} // endstd::shared_ptr< Wt::WAbstractItemModel > CompanyProvider::model( int sid, int tid, const std::string & filter )

std::unique_ptr<Wt::WTableView> Wtx::Crm::Company::CompanyProvider::getTableView( int sid, int tid, const std::string & filter )
{
  return std::make_unique< Wt::WTableView >();
}

std::unique_ptr< Wtx::Crm::Company::CompanyProvider > Rtm::Dbo::Person::makeCompanyProvider()
{
  return std::make_unique< Wtx::Crm::Company::CompanyProvider >();
}

#endif
