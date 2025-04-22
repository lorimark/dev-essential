
#ifndef __FOLDEREXPLORER_SPLITVIEW_H___
#define __FOLDEREXPLORER_SPLITVIEW_H___

#include <Wt/WText.h>

#include "PreView.h"
#include "TableView.h"
#include "TreeView.h"

namespace FolderExplorer {

class SplitView
: public Wt::WContainerWidget
{
  public:

    SplitView();
    SplitView( const std::string & rootPath, const std::string & alias = "" );

    void setFolder( const std::string & rootPath, const std::string & alias = "" );

    FolderExplorer::TreeView  * treeView();
    FolderExplorer::TableView * tableView();

  private:

    void init();
    void on_folderSelected( FolderExplorer::TreeView::Node * node );

    std::string m_rootPath;
    std::string m_alias;
    Wt::WText * m_path;
    FolderExplorer::TreeView  * m_treeView = nullptr;
    FolderExplorer::TableView * m_tableView = nullptr;

}; // endclass SplitView



} // endnamespace FolderExplorer


#endif


