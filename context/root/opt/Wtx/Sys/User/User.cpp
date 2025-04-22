
#include <Wtx/Dbo/QueryModel.h>
#include <Wtx/Core/Core.h>

#include "User.h"


Wtx::Sys::User::Item::Ptr Wtx::Sys::User::load( int userid, Wtx::Dbo::Session & session )
{
  Wtx::Sys::User::Item::Ptr retVal;

  Wt::Dbo::Transaction t(session);
  retVal =
    session.load< Wtx::Sys::User::Item >( userid )
    ;

  return retVal;

}

Wtx::Sys::User::Item::Ptr Wtx::Sys::User::find( const std::string & keyField, Wtx::Dbo::Session & session )
{
  Wtx::Sys::User::Item::Ptr retVal;

  Wt::Dbo::Transaction t(session);
  retVal =
    session.find< Wtx::Sys::User::Item >()
    .where( "UPPER(\"keyField\") = UPPER(?)")
    .bind( keyField )
    .resultValue()
    ;

  return retVal;

}

Wtx::Sys::User::Item::Ptr Wtx::Sys::User::xfind( const std::string & xid, Wtx::Dbo::Session & session )
{
  Wtx::Sys::User::Item::Ptr retVal;

  if( xid != "" )
  {
    Wt::Dbo::Transaction t(session);
    retVal =
      session.find< Wtx::Sys::User::Item >()
      .where( "UPPER(xid) = UPPER(?)")
      .bind( xid )
      .resultValue()
      ;
  }

  return retVal;

}

Wtx::Sys::User::Item::Ptr Wtx::Sys::User::add( const std::string & keyField, const std::string & cfyField, Wtx::Dbo::Session & session )
{
  Wtx::Sys::User::Item::Ptr retVal;

  Wt::Dbo::Transaction t(session);
  retVal =
    session.addNew< Wtx::Sys::User::Item >(keyField,cfyField)
    ;

  return retVal;

}

std::shared_ptr<Wt::WAbstractItemModel> Wtx::Sys::User::getComboBoxModel( int tid, const std::string & group, Wtx::Dbo::Session & session )
{
  auto retVal = std::make_shared< Wtx::Dbo::QueryModel< Wtx::Sys::User::Item::Ptr > >();

  Wt::Dbo::Transaction t(session);

  if( tid == -1 )
  {
    auto query =
      session.find< Wtx::Sys::User::Item >()
      .where("\"isActive\" is true AND (UPPER(\"cfyField\") LIKE UPPER(?) OR \"cfyField\" LIKE '%%*%%')")
      .bind( Wt::WString("%%{1}%%").arg(group) )
      .orderBy("\"keyField\"")
      ;

    retVal-> setQuery( query );
  }

  else
  {
    auto query =
      session.find< Wtx::Sys::User::Item >()
      .where("id = ?")
      .bind( tid )
      ;

    retVal-> setQuery( query );
  }

  retVal-> addColumn("id");
  retVal-> addColumn("keyField");

  return retVal;
}


