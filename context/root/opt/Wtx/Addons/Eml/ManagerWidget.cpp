
#include <Wt/WText.h>
#include <Wt/WTree.h>
#include <Wt/WTreeNode.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>

#include <Wtx/Util/Util.h>

#include "ManagerWidget.h"

namespace {

class FolderView
: public Wt::WContainerWidget
{
  public:

    class Node
    : public Wt::WTreeNode
    {
      public:

        Node( const std::string & label );

      protected:

      private:

    };

    FolderView( Wtx::Eml::Service::Account * account );

    Wtx::Eml::Service::Account * account();
    Node * rootNode();

    Wtx::Eml::Service::Account * m_account;
    Wt::WTree * m_tree;
    Node * m_rootNode;

};

FolderView::Node::Node( const std::string & lbl )
: Wt::WTreeNode()
{
  auto  folderIcon =
    std::make_unique<Wt::WIconPair>
    (
     "resources/icons/yellow-folder-closed.png",
     "resources/icons/yellow-folder-open.png",
     false
    );

  setLabelIcon( std::move( folderIcon ) );
  label()-> setTextFormat( Wt::TextFormat::Plain );
  label()-> setWordWrap(false);
  label()-> setText( lbl );
  setStyleClass("linkstyle");
  setLoadPolicy( Wt::ContentLoading::NextLevel );

}

FolderView::FolderView( Wtx::Eml::Service::Account * acct )
: m_account(acct)
{
  auto u_hlw = std::make_unique< Wt::WHBoxLayout >();
  auto hlw = u_hlw.get();
  setLayout( std::move( u_hlw ) );
  hlw-> setContentsMargins( 0,0,0,0 );

  auto u_tree = std::make_unique< Wt::WTree >();
  m_tree = u_tree.get();
  hlw-> addWidget( std::move( u_tree ), 1 );

  auto u_rootNode = std::make_unique< FolderView::Node >( account()-> name() );
  m_rootNode = u_rootNode.get();
  m_tree-> setTreeRoot( std::move(u_rootNode) );

  auto inbox = rootNode()-> addChildNode( std::make_unique< FolderView::Node >( "Inbox" ) );

  auto drafts   = inbox-> addChildNode( std::make_unique< FolderView::Node > ( "Drafts"   ) );
  auto sent     = inbox-> addChildNode( std::make_unique< FolderView::Node > ( "Sent"     ) );
  auto archives = inbox-> addChildNode( std::make_unique< FolderView::Node > ( "Archives" ) );
  auto junk     = inbox-> addChildNode( std::make_unique< FolderView::Node > ( "Junk"     ) );
  auto deleted  = inbox-> addChildNode( std::make_unique< FolderView::Node > ( "Deleted"  ) );
  auto scam     = inbox-> addChildNode( std::make_unique< FolderView::Node > ( "Scam"     ) );

  for( int i=2005; i < 2020; i++ )
    archives-> addChildNode( std::make_unique< FolderView::Node >( Wtx::itos(i) ) );

  rootNode()-> expand();

}

Wtx::Eml::Service::Account * FolderView::account()
{
  return m_account;
}

FolderView::Node * FolderView::rootNode()
{
  return m_rootNode;
}





class Widget
: public Wt::WContainerWidget
{
  public:

    Widget( std::unique_ptr< Wtx::Eml::Service::Manager > sm );

    Wtx::Eml::Service::Manager * manager();

    std::unique_ptr< Wtx::Eml::Service::Manager > m_manager;

};

Widget::Widget( std::unique_ptr< Wtx::Eml::Service::Manager > sm )
: Wt::WContainerWidget(),
  m_manager( std::move(sm) )
{
  auto u_lw = std::make_unique< Wt::WVBoxLayout >();
  auto lw = u_lw.get();
  setLayout( std::move( u_lw ) );
  lw-> setContentsMargins( 0,0,0,0 );

  for( auto emlAccount : manager()-> accounts() )
  {
    std::cout << __FILE__ << ":" << __LINE__
      << " " << emlAccount-> name()
      << std::endl
      ;

    auto u_view = std::make_unique< FolderView >( emlAccount );
    lw-> addWidget( std::move( u_view ) );

  }


#ifdef NEVER
  auto u_productView = std::make_unique< Mrp::Product::ManagerWidget >();
  auto productView = u_productView.get();
  hlw-> addWidget( std::move(u_productView) );

  auto u_inventoryView = std::make_unique< Mrp::Inventory::ManagerWidget >();
  auto inventoryView = u_inventoryView.get();
  hlw-> addWidget( std::move(u_inventoryView) );

  auto u_cw = std::make_unique<Wt::WContainerWidget>();
  auto cw = u_cw.get();
  hlw-> addWidget( std::move(u_cw) );

  auto u_vlw = std::make_unique<Wt::WVBoxLayout>();
  auto vlw = u_vlw.get();
  cw-> setLayout( std::move(u_vlw) );

  auto u_inboundView = std::make_unique< Mrp::Inbound::ManagerWidget >();
  auto inboundView = u_inboundView.get();
  vlw-> addWidget( std::move(u_inboundView) );

  auto u_outboundView = std::make_unique< Mrp::Outbound::ManagerWidget >();
  auto outboundView = u_outboundView.get();
  vlw-> addWidget( std::move(u_outboundView) );

  productView-> itemClicked().connect( [=]( Wt::Dbo::ptr<Mrp::Product::Item> item )
  {
    inventoryView-> setFor( item );
  });

  inventoryView-> itemClicked().connect( [=]( Wt::Dbo::ptr<Mrp::Inventory::Item> item )
  {
    inboundView-> setFor( item );
    outboundView-> setFor( item );
  });
#endif

} // endWidget::Widget( std::unique_ptr< Wtx::Eml::Service::Manager > sm )


Wtx::Eml::Service::Manager * Widget::manager()
{
  return m_manager.get();
}

} // endnamespace {










Wtx::Eml::ManagerWidget::ManagerWidget( std::unique_ptr< Wtx::Eml::Service::Manager > sm )
: Wt::WContainerWidget()
{
  auto layout = std::make_unique< Wt::WHBoxLayout >();
  layout-> setContentsMargins( 0,0,0,0 );

  layout-> addWidget( std::make_unique<Widget>( std::move(sm) ) );

  setLayout( std::move( layout ) );
}

