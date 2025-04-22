
#include "Config.h"



Wtx::Sys::Config::Item::Ptr Wtx::Sys::Config::xfind( const std::string & xid, Wtx::Dbo::Session & session )
{
  Wt::Dbo::Transaction t(session);
  return session.find< Wtx::Sys::Config::Item >()
    .where( "\"xid\" = ?" )
    .bind( xid )
    .resultValue()
    ;

}

Wtx::Sys::Config::Item::Ptr Wtx::Sys::Config::load( int id, Wtx::Dbo::Session & session )
{
  Wt::Dbo::Transaction t(session);
  return session.load< Wtx::Sys::Config::Item >( id );

}

Wtx::Sys::Config::Item::Ptr Wtx::Sys::Config::find( const std::string & key, Wtx::Dbo::Session & session )
{
  Wt::Dbo::Transaction t(session);
  return session.find< Wtx::Sys::Config::Item >()
    .where( "\"keyField\" = ?" )
    .bind( key )
    .resultValue()
    ;

}


Wtx::Sys::Config::Item::Ptr Wtx::Sys::Config::add( const std::string & key, Wtx::Dbo::Session & session )
{
  Wt::Dbo::Transaction t( session );
  return
    session.addNew< Wtx::Sys::Config::Item >( key );

}

Wtx::Sys::Config::Item::Ptr Wtx::Sys::Config::add( const std::string & key, const std::string & cfy, Wtx::Dbo::Session & session )
{
  Wt::Dbo::Transaction t( session );
  return
    session.addNew< Wtx::Sys::Config::Item >( key, cfy );

}

Wtx::Sys::Config::Item::Ptr Wtx::Sys::Config::fadd( const std::string & key, Wtx::Dbo::Session & session )
{
  auto retVal = find( key, session );

  if( !retVal )
       retVal = add( key, session );

  return retVal;

}

Wtx::Sys::Config::Item::Ptr Wtx::Sys::Config::fadd( const std::string & key, const std::string & cfy, Wtx::Dbo::Session & session )
{
  auto retVal = find( key, session );

  if( !retVal )
       retVal = add( key, cfy, session );

  return retVal;

}


bool Wtx::Sys::Config::del( const std::string & key, Wtx::Dbo::Session & session )
{
  find( key, session ).remove();

  return true;
}


