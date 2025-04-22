
#include <iostream>
#include <fstream>

#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>

#include "Log.h"

Wtx::Sys::Log::Item::Ptr Wtx::Sys::Log::add( const std::string & key, const std::string & cfy, bool sendEmail, Wtx::Dbo::Session & session )
{
  Wt::Dbo::Transaction t( session );

  auto retVal =
    session.addNew<Wtx::Sys::Log::Item>( key );

  retVal.modify()-> cfyField().setValue( cfy );

  auto value =
    Wt::WString
    (
      "----------------------------------------------\n"
      "{1}\n"
      "key:{2}\n"
      "cfy:{3}\n"
      "clip:{4}"
     )
    .arg( Wt::WDateTime::currentDateTime().toString() )
    .arg( key )
    .arg( cfy )
    .arg( wApp-> instance()-> environment().headerValue("X-Forwarded-For") )
    .toUTF8()
    ;

  std::cout << __FILE__ << ":" << __LINE__
    << "\n" << value
    << "\n----------------------------------------------"
    << std::endl;

  if( sendEmail )
  {
  }

  auto fileName =
    Wt::WString("sysLog-{1}.txt")
    .arg( Wt::WDateTime::currentDateTime().toString("yyyyMMdd") )
    .toUTF8()
    ;

  std::ofstream myfile;
  myfile.open( fileName.c_str(), std::ios::out | std::ios::app );
  myfile << value << "\n";
  myfile.close();


  return retVal;

} // endWt::Dbo::ptr< Wtx::Sys::Log::Item > Wtx::Sys::Log::add( const std::string & key, const std::string & cfy, bool sendEmail, Wtx::Dbo::Session & session )

Wtx::Sys::Log::Item::Ptr Wtx::Sys::Log::add( const std::string & key, const std::string & cfy, Wtx::Dbo::Session & session )
{
  return add( key, cfy, false, session );
}

