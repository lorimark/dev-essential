
#ifndef __FOLDEREXPLORER_ABSTRACTVIEW_H___
#define __FOLDEREXPLORER_ABSTRACTVIEW_H___

#include <Wt/WContainerWidget.h>

namespace FolderExplorer {

class AbstractView
: public Wt::WContainerWidget
{
  public:

    AbstractView( const std::string & rootPath, const std::string & alias = "" );

    const std::string & currentPath() const;
    const std::string & rootPath() const;
    const std::string & alias() const;

  private:

    std::string m_currentPath;
    std::string m_rootPath;
    std::string m_alias;

}; // endclass AbstractView



} // endnamespace FolderExplorer


#endif


