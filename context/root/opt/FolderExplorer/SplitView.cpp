
#include <Wt/Utils.h>
#include <Wt/WApplication.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>

#include <Wtx/Util/Util.h>

#include "SplitView.h"

FolderExplorer::SplitView::SplitView()
{
//  m_rootPath = ".";
  init();
}

FolderExplorer::SplitView::SplitView( const std::string & rootPath, const std::string & alias )
: m_rootPath(rootPath),
  m_alias(alias)
{
  init();
}

void FolderExplorer::SplitView::setFolder( const std::string & rp, const std::string & ali )
{
  m_rootPath = rp;
  m_alias = ali;
  init();
}

FolderExplorer::TreeView  * FolderExplorer::SplitView::treeView()
{
  return m_treeView;
}

FolderExplorer::TableView * FolderExplorer::SplitView::tableView()
{
  return m_tableView;
}


void FolderExplorer::SplitView::on_folderSelected( FolderExplorer::TreeView::Node * node )
{
#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
    << "\nlabel: " << node-> label()-> text()   << " "
    << "\npath:  " << node-> getFolderPath()    << " "
    << "\npath:  " << node-> getFolderPath("/") << " "
    << std::endl
    ;
#endif

  m_path-> setText( node-> getFolderPath("/") );
  m_tableView-> setCurrentFolder( node-> getFolderPath() /*, node-> label()-> text().toUTF8() */ );

//  Wt::WApplication::instance()-> setInternalPath( Wt::Utils::urlEncode( node-> getFolderPath("/") ) );
//  Wt::WApplication::instance()-> setInternalPath( node-> getFolderPath("/") );
}

void FolderExplorer::SplitView::init()
{
  auto vl = std::make_unique<Wt::WVBoxLayout>();

  auto u_path = std::make_unique< Wt::WText >("/");
  m_path = u_path.get();
  vl-> addWidget( std::move( u_path ) );

  auto hl = std::make_unique<Wt::WHBoxLayout>();

  auto ev = std::make_unique< FolderExplorer::TreeView  >( m_rootPath, m_alias );
  m_treeView = ev.get();
  ev-> itemSelectionChanged().connect( this, &FolderExplorer::SplitView::on_folderSelected );
  hl-> addWidget( std::move(ev) );

  auto av = std::make_unique< FolderExplorer::TableView >( m_rootPath, m_alias );
  m_tableView = av.get();
  hl-> addWidget( std::move(av) );
  m_tableView-> folderClicked().connect( [=]( const std::string & itemname )
  {
    auto newpath = Wtx::append( m_tableView-> currentFolder(), itemname, "/" );

#ifndef NEVER
    std::cout << __FILE__ << ":" << __LINE__ << " SplitView::init()"
      << " current: '" << m_tableView-> currentFolder() << "'"
      << " item: '"    << itemname << "'"
      << " newpath: '" << newpath << "'"
      << std::endl
      ;
#endif

    m_tableView-> setCurrentFolder( newpath );
    m_path-> setText( m_tableView-> currentFolder() );

  });

  m_tableView-> folderDoubleClicked().connect( [=]( const std::string & itemname )
  {
    std::cout << __FILE__ << ":" << __LINE__ << " " << itemname << std::endl;

  });

  hl-> setResizable( 0, true, "25%" );

  vl-> addLayout( std::move(hl), 1 );
  setLayout( std::move(vl) );
}


