#include "Session.h"



Wtx::Sys::Session::Session()
{
  m_users = std::make_unique<UserDatabase>( *this );
}

Wtx::Sys::Session::~Session()
{
}



Wt::Auth::AbstractUserDatabase & Wtx::Sys::Session::users()
{
  return *m_users;
}

Wt::Auth::Login & Wtx::Sys::Session::login()
{
  return m_login;
}

const Wt::Auth::Login & Wtx::Sys::Session::login() const
{
  return m_login;
}

Wtx::Sys::User::Item::Ptr Wtx::Sys::Session::user() const
{
  if( login().loggedIn() )
    return const_cast< Wtx::Sys::Session* >( this )-> user( login().user() );

  return Wt::Dbo::ptr< Wtx::Sys::User::Item>();
}

Wtx::Sys::User::Item::Ptr Wtx::Sys::Session::user( const Wt::Auth::User & authUser )
{
  Wt::Dbo::Transaction t(*this);

  Wt::Dbo::ptr< Wtx::Sys::Auth::AuthInfo > authInfo = m_users-> find( authUser );

  auto user = authInfo-> user();

  if( !user )
  {
    user = addNew<Wtx::Sys::User::Item>();
    authInfo.modify()-> setUser( user );
  }

  return user;
}



