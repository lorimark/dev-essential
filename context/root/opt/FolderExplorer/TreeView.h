
#ifndef __FOLDEREXPLORER_TREEVIEW_H___
#define __FOLDEREXPLORER_TREEVIEW_H___

#include <Wt/WTreeNode.h>

#include "AbstractView.h"

namespace FolderExplorer {

class TreeView
: public AbstractView
{
  public:

    class Node
    : public Wt::WTreeNode
    {
      public:

        Node( const std::string & labelText, const std::string & alias = "" );
        const std::string & realLabel();

        const std::string & realLabel() const;
        std::string getFolderPath( const std::string & rootAlias = "" ) const;

      protected:

        std::string getFolderPath( const Node * node, const std::string & rootAlias = "" ) const;
        void populate();

      private:

        std::string m_labelText;

    }; // endclass Node

    TreeView( const std::string & rootPath, const std::string & alias = "" );

    Node * currentSelection() const;
    Wt::Signal<Node*> & itemSelectionChanged();

    std::string currentPath() const;

    Wt::WTree * tree();

  private:

    void do_itemSelectionChanged();

//    std::string m_rootPath;
//    std::string m_alias;
    Wt::WTree * m_tree = nullptr;
    Wt::Signal<Node*> m_itemSelectionChanged;
    Node * m_currentSelection = nullptr;

}; // endclass TreeView

} // endnamespace FolderExplorer


#endif // #ifndef __FOLDEREXPLORER_TREEVIEW_H___


