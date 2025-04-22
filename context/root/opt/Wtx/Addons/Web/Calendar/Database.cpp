
#include <Wt/WStandardItemModel.h>

#include "Database.h"

Wtx::Web::Calendar::Database::Database()
: Wt::WObject()
{
}

void Wtx::Web::Calendar::Database::registerModelProvider( Wtx::Web::Calendar::ModelProvider * modelProvider )
{
  m_modelProviders.push_back( modelProvider );
}

std::vector<Wtx::Web::Calendar::ModelProvider*> & Wtx::Web::Calendar::Database::modelProviders()
{
  return m_modelProviders;
}

