

#include "Manager.h"

Wtx::Eml::Service::Manager::Manager()
: Wt::WObject()
{
}

void Wtx::Eml::Service::Manager::registerAccount( std::unique_ptr< Wtx::Eml::Service::Account > account )
{
  m_accounts.push_back( account.get() );

  addChild( std::move(account) );
}


const std::vector< Wtx::Eml::Service::Account* > & Wtx::Eml::Service::Manager::accounts() const
{
  return m_accounts;
}
