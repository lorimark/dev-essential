
#include "AbstractView.h"

FolderExplorer::AbstractView::AbstractView( const std::string & rootPath, const std::string & alias )
: m_rootPath(rootPath),
  m_alias(alias)
{
}

const std::string & FolderExplorer::AbstractView::rootPath() const
{
  return m_rootPath;
}

const std::string & FolderExplorer::AbstractView::alias() const
{
  return m_alias;
}


