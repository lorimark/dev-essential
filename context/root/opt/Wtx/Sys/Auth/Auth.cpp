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

#include <Wt/Auth/Dbo/UserDatabase.h>
#include <Wt/Auth/AuthService.h>
#include <Wt/Auth/HashFunction.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/Auth/PasswordStrengthValidator.h>
#include <Wt/Auth/PasswordVerifier.h>
#include <Wt/Auth/GoogleService.h>
#include <Wt/Auth/FacebookService.h>
#include <Wt/Auth/Dbo/AuthInfo.h>

#include "Auth.h"

void Wtx::Sys::Auth::mapClasses( Wtx::Dbo::Session & session )
{
  session.mapClass<AuthInfo>( "sysAuthInfo" );
  session.mapClass<AuthInfo::AuthIdentityType>( "sysAuthIdentity" );
  session.mapClass<AuthInfo::AuthTokenType>( "sysAuthToken" );
}

void Wtx::Sys::Auth::postCreateTables( Wtx::Dbo::Session & session )
{
#ifdef NEVER
  /*
  ** we will create a single default 'admin' user in the system
  **  that can be used to log in to the interface.
  **
  */
  typedef Wt::Auth::Dbo::UserDatabase<AuthInfo> UserDatabase;

  Wt::Dbo::Transaction t(session);
  UserDatabase users( session, &Wtx::Sys::Auth::service() );

  auto authUser = users.registerNew();
  authUser.addIdentity( Wt::Auth::Identity::LoginName, "admin" );
  authUser.setEmail( "mark@lorimarksolutions.com" );
  passwordService().updatePassword( authUser, "ABC123!!!" );
#endif
}

namespace {
  Wt::Auth::AuthService myAuthService;
  Wt::Auth::PasswordService myPasswordService( myAuthService );
  std::vector<std::unique_ptr<Wt::Auth::OAuthService>> myOAuthServices;
}

void Wtx::Sys::Auth::configure()
{
  myAuthService.setAuthTokensEnabled( true, "logincookie" );
  myAuthService.setEmailVerificationEnabled( true );
  myAuthService.setEmailVerificationRequired( true );
  myAuthService.setIdentityPolicy( Wt::Auth::IdentityPolicy::EmailAddress );

  auto verifier
    = std::make_unique<Wt::Auth::PasswordVerifier>();
  verifier->addHashFunction( std::make_unique<Wt::Auth::BCryptHashFunction>(7) );
  myPasswordService.setVerifier( std::move(verifier) );
  myPasswordService.setAttemptThrottlingEnabled( true );
  myPasswordService.setStrengthValidator( std::make_unique<Wt::Auth::PasswordStrengthValidator>() );

  if( Wt::Auth::GoogleService::configured() )
    myOAuthServices.push_back( std::make_unique<Wt::Auth::GoogleService>( myAuthService ) );

  if( Wt::Auth::FacebookService::configured() )
    myOAuthServices.push_back( std::make_unique<Wt::Auth::FacebookService>( myAuthService ) );

  for( unsigned i = 0; i < myOAuthServices.size(); ++i )
    myOAuthServices[i]-> generateRedirectEndpoint();

} // endvoid Wtx::Sys::configureAuth()

const Wt::Auth::AuthService & Wtx::Sys::Auth::service()
{
  return myAuthService;
}

const Wt::Auth::PasswordService& Wtx::Sys::Auth::passwordService()
{
  return myPasswordService;
}

const std::vector<const Wt::Auth::OAuthService *> Wtx::Sys::Auth::oService()
{
  std::vector<const Wt::Auth::OAuthService *> result;

  for( auto & auth : myOAuthServices )
    result.push_back( auth.get() );

  return result;
}


