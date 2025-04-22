
#include <vmime/vmime.hpp>

#include <Wt/WString.h>

#include "Account.h"

Wtx::Eml::Service::Account::Account
(
  const std::string & name,
  const std::string & protocol,
  const std::string & hostname,
  const std::string & username,
  const std::string & password
)
: Wt::WObject(),
  m_name( name )
{

  m_urlString =
    Wt::WString("{1}://{2}:{3}@{4}")
    .arg( protocol )
    .arg( username )
    .arg( password )
    .arg( hostname )
    .toUTF8()
    ;

#ifdef NEVER
  auto url = vmime::utility::url( urlString );

  auto sess = vmime::net::session::create();
  auto store = sess-> getStore(url);
  store-> connect();
  auto defaultFolder = store-> getDefaultFolder();
  defaultFolder-> open( vmime::net::folder::Modes::MODE_READ_ONLY );
  auto messages =
    defaultFolder-> getAndFetchMessages
    (
     vmime::net::messageSet::byNumber(1,-1),
     vmime::net::fetchAttributes::FLAGS |
     vmime::net::fetchAttributes::ENVELOPE
    );

  auto folders =
    defaultFolder-> getFolders();

  std::cout << __FILE__ << ":" << __LINE__
    << " " << messages.size()
    << " " << defaultFolder-> getName().generate()
    << " " << folders.size()
    << std::endl
    ;

  for( auto folder : folders )
  {
    std::cout << __FILE__ << ":" << __LINE__
      << " " << folder-> getName().generate()
      << std::endl
      ;
  }
#endif


#ifdef NEVER
616 ·
583   for( auto message : messages )·
584   {·
585     auto flags = message-> getFlags();·
586 ·
587     auto header = message-> getHeader();·
588 ·
589     std::cout << __FILE__ << ":" << __LINE__·
590       << " " << header-> Date()-> generate()·
591       << " " << header-> From()-> generate()·
592       << std::endl·
593       ;·
594 ·
595 ·
596   }·
#endif


} // endWtx::Eml::Service::Account::Account

const std::string & Wtx::Eml::Service::Account::name() const
{
  return m_name;
}



