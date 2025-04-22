
#include <Wt/WText.h>
#include <Wt/WTree.h>
#include <Wt/WDateTime.h>
#include <Wt/WFitLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WApplication.h>

#include "TreeView.h"
#include "Util.h"

FolderExplorer::TreeView::Node::Node( const std::string & labelText, const std::string & alias )
: Wt::WTreeNode()
{

  if( alias != "" )
    m_labelText = labelText;

//      std::cout << __FILE__ << ":" << __LINE__
//        << " labelText:" << labelText
//        << " alias:"     << alias
//        << " m_alias:"   << m_alias
//        << std::endl
//        ;

//      auto splt = split( folderName, '/' );
//      if( splt.size() > 1 )
//      {
//        label()-> setText( splt.back() );
//        m_isRoot = true;
//      }

#ifndef NEVER

  auto  folderIcon =
    std::make_unique<Wt::WIconPair>
    (
     "/resources/icons/yellow-folder-closed.png",
     "resources/icons/yellow-folder-open.png",
     false
    );

#else

  auto  folderIcon =
    std::make_unique<Wt::WIconPair>
    (
     wApp-> bookmarkUrl() + "/resources/icons/yellow-folder-closed.png",
     wApp-> bookmarkUrl() + "/resources/icons/yellow-folder-open.png",
     false
    );

#endif

  setLabelIcon( std::move(folderIcon) );
  label()-> setTextFormat( Wt::TextFormat::Plain );
  label()-> setWordWrap(false);
  label()-> setText( alias == ""? (labelText == ""? "nak":labelText) :alias );
  setStyleClass("linkstyle");
  setLoadPolicy( Wt::ContentLoading::NextLevel );

} // endFolderExplorer::TreeView::Node::Node( const std::string & labelText, const std::string & alias )

const std::string & FolderExplorer::TreeView::Node::realLabel() const
{
  return m_labelText;
}

std::string FolderExplorer::TreeView::Node::getFolderPath( const std::string & rootAlias ) const
{
  return getFolderPath( this, rootAlias );
}

std::string FolderExplorer::TreeView::Node::getFolderPath( const Node * node, const std::string & rootAlias ) const
{
  if( !node )
    return "";

//std::cout << __FILE__ << ":" << __LINE__
//  << " node: " << node << " "
//  << " label: " << node-> label()-> text()
//  << " alias: " << node-> alias()
//  << std::endl
//  ;

  std::string retVal =
    getFolderPath( dynamic_cast<FolderExplorer::TreeView::Node*>( node-> parentNode() ), rootAlias ) +
    (node-> realLabel() == ""?
     node-> label()-> text().toUTF8()
     :rootAlias == ""?
     node-> realLabel()
     :rootAlias
    )
     ;

  if( retVal.back() != '/' )
    retVal += "/";

  return retVal;

} // endstd::string FolderExplorer::TreeView::Node::getFolderPath( const Node * node, const std::string & rootAlias ) const

void FolderExplorer::TreeView::Node::populate()
{

  auto currentFolder = getFolderPath(this);

  if( currentFolder == "" )
    return;

  /*
  ** get all the file items out of the folder.  This
  **  will include directories as well as regular files.
  **
  */
  auto fileInfos = FolderExplorer::getFileInfo( currentFolder );

  /*
  ** Loop through each item to get the directories.
  **
  */
  for( auto i = fileInfos.begin(); i != fileInfos.end(); i++ )
  {
    auto fileInfo = *i;

    /*
    ** the double '..' dot items are 'up' folder items.
    **  we keep these when we are not at the root
    **  folder so the user can navigate up one folder.
    **
    */
    if( fileInfo.name() == ".." )
      continue;

    /*
    ** if the fileInfo item is ~not~ a directory item
    **  then we ignore it.
    **
    */
    if( !fileInfo.isDir() )
      continue;

    /*
    ** produce a table item that ~is~ the filename column
    **
    */
    auto fn = fileInfo.name();

    auto newTreeNode = std::make_unique<FolderExplorer::TreeView::Node>( fn );
    addChildNode( std::move( newTreeNode ) );

  } // endfor( auto i = fileInfos.begin(); i != fileInfos.end(); i++ )

} // endvoid FolderExplorer::TreeView::Node::populate()


FolderExplorer::TreeView::TreeView( const std::string & rp, const std::string & al )
: AbstractView( rp, al )
{
  setOverflow( Wt::Overflow::Auto );

  auto lw = std::make_unique<Wt::WVBoxLayout>();

  auto u_tree = std::make_unique<Wt::WTree>();
  m_tree = u_tree.get();
  lw-> addWidget( std::move( u_tree ), 1 );
  tree()-> setSelectionMode( Wt::SelectionMode::Single );
  tree()-> itemSelectionChanged().connect( this, &FolderExplorer::TreeView::do_itemSelectionChanged );

//std::cout << __FILE__ << ":" << __LINE__
//  << " setting up: " << rootPath
//  << " alias: " << alias
//  << std::endl
//  ;

  auto rootNode = std::make_unique<FolderExplorer::TreeView::Node>( rootPath(), alias() );
  rootNode-> expand();
  tree()-> setTreeRoot( std::move( rootNode ) );

  setLayout( std::move(lw) );

} // endFolderExplorer::TreeView::TreeView( const std::string & rp, const std::string & al )

Wt::WTree * FolderExplorer::TreeView::tree()
{
  return m_tree;
}

Wt::Signal<FolderExplorer::TreeView::Node*> & FolderExplorer::TreeView::itemSelectionChanged()
{
  return m_itemSelectionChanged;
}

void FolderExplorer::TreeView::do_itemSelectionChanged()
{
  if( tree()-> selectedNodes().size() != 1 )
    return;

  auto node =
    dynamic_cast<FolderExplorer::TreeView::Node*>
    (
     *(tree()-> selectedNodes().begin())
    );

  m_currentSelection = node;

//std::cout << __FILE__ << ":" << __LINE__ << " "
//  << "\nroot:  "  << m_rootPath << " "
//  << "\nalias: " << m_alias << " "
//  << "\nlabel: " << node-> label()-> text() << " "
//  << "\npath:  "  << node-> getFolderPath("/") << " "
//  << std::endl
//  ;

  m_itemSelectionChanged.emit( node );

} // endvoid FolderExplorer::TreeView::do_itemSelectionChanged()


FolderExplorer::TreeView::Node * FolderExplorer::TreeView::currentSelection() const
{
  return m_currentSelection;
}

std::string FolderExplorer::TreeView::currentPath() const
{
  if( currentSelection() )
  {
    return currentSelection()-> getFolderPath();
  }

  return rootPath();
}




