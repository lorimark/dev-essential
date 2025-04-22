
#ifndef __WTX_SYS_SESSION_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_SYS_SESSION_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <Wt/Auth/Login.h>
#include <Wt/Auth/Dbo/AuthInfo.h>
#include <Wt/Auth/Dbo/UserDatabase.h>

#include <Wtx/Sys/Auth/Auth.h>
#include <Wtx/Dbo/Session.h>

using UserDatabase = Wt::Auth::Dbo::UserDatabase<Wtx::Sys::Auth::AuthInfo>;

namespace Wtx {
  namespace Sys {

class Session
: public Wtx::Dbo::Session
{
  public:

    Session();
    virtual ~Session();

    Wt::Auth::AbstractUserDatabase & users();
          Wt::Auth::Login & login();
    const Wt::Auth::Login & login() const;

    Wtx::Sys::User::Item::Ptr user() const;
    Wtx::Sys::User::Item::Ptr user( const Wt::Auth::User & authUser );

  private:

    std::unique_ptr<UserDatabase> m_users;
    Wt::Auth::Login m_login;

};

  } // endnamespace Sys
} // endnamespace Wtx

#endif

