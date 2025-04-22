
#include <Wt/WWidget.h>
#include <Wt/WModelIndex.h>
#include <Wt/WItemDelegate.h>
#include <Wt/WText.h>
#include <Wt/WTemplate.h>
#include <Wt/WMenu.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WGridLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WFitLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WMessageBox.h>

#include <Wtx/MessageBox.h>
#include <Wtx/PopupMessage.h>
#include <Wtx/Dbo/TableViewManager.h>
#include <Wtx/Dbo/TemplateFormView.h>
#include <Wtx/Dbo/LookupItemDelegate.h>
#include <Wtx/Dbo/DetailForm.h>

#include <Wtx/Sys/Lookup/ItemDelegate.h>
#include <Wtx/Sys/Lookup/Lookup.h>

#include "Person.h"
#include "ManagerWidget.h"
#include "Item.h"

namespace {

class BaseDesktop
: public Wt::WContainerWidget
{
  public:

    BaseDesktop( Wtx::Dbo::Session * s );

    Wtx::Dbo::Session * session() const { return m_session; }

  private:

    Wtx::Dbo::Session * m_session = nullptr;

}; // endclass BaseDesktop( Wtx::Dbo::Session * s )

BaseDesktop::BaseDesktop( Wtx::Dbo::Session * s )
: Wt::WContainerWidget(),
  m_session(s)
{
}

} // endnamespace

class PersonDetail
: public Wtx::Dbo::DetailForm< Wtx::Crm::Person::Item >
{

  public:

    PersonDetail( Wt::Dbo::ptr< Wtx::Crm::Person::Item > & item )
    : Wtx::Dbo::DetailForm< Wtx::Crm::Person::Item >
      (
        "crmPerson.detailForm",
        item
      )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " Wtx::Dbo::DetailForm< Wtx::Crm::Person::Item >" << std::endl;


//      updateView();

    } // endInboundDetail( Wt::Dbo::ptr< Mrp::Inbound::Item > & item )

}; // endclass PersonDetail

class Wtx::Crm::Person::Desktop
: public BaseDesktop
{
  public:

    Desktop( Wtx::Dbo::Session * s );
    Desktop( Wtx::TableViewDef::ViewDef & viewDef, Wtx::Dbo::Session * s );

    void setFilter( const std::string & value );
    void updateFooter( );

    void init( Wtx::TableViewDef::ViewDef & viewDef );

    void openDetail( Wt::Dbo::ptr<Wtx::Crm::Person::Item> & item );

    void setOpenDetail( bool value );

    Wtx::Dbo::TableViewManager< Wtx::Crm::Person::Item, PersonDetail > * m_view;
};

void Wtx::Crm::Person::Desktop::openDetail( Wt::Dbo::ptr<Wtx::Crm::Person::Item> & item )
{
  m_view-> openDetail( item );
}

void Wtx::Crm::Person::Desktop::setOpenDetail( bool value )
{
  m_view-> m_openDetail = value;
}



void Wtx::Crm::Person::Desktop::init( Wtx::TableViewDef::ViewDef & viewDef )
{
  auto layout = std::make_unique< Wt::WVBoxLayout >();

  auto u_ = std::make_unique< Wtx::Dbo::TableViewManager< Wtx::Crm::Person::Item, PersonDetail > >( viewDef, session() );
  m_view = u_.get();
  layout-> addWidget( std::move( u_ ) );

  setLayout( std::move(layout) );

}

Wtx::Crm::Person::Desktop::Desktop( Wtx::TableViewDef::ViewDef & viewDef, Wtx::Dbo::Session * s )
: BaseDesktop( s )
{
  init( viewDef );
}

Wtx::Crm::Person::Desktop::Desktop( Wtx::Dbo::Session * s )
: BaseDesktop( s )
{
  Wtx::TableViewDef::ViewDef viewDef =
  {
    /* title                */ "Person",
    /* tip                  */ "",
    /* headerCount          */ 0,
    /* selectionMode        */ Wt::SelectionMode::Single,
    /* columnResizeEnabled  */ true,
    /* alternatingRowColors */ true,
    /* sql                  */ "",
    /* filter               */ "",
    /* subFilter            */ "",
    /* idin                 */ {},
    /* doubleClick          */ 0,
    /* showHeader           */ true,
    /* showFooter           */ true,
    /* showPrevNext         */ false,
    /* hideSearch           */ false,
    /* allowFilter          */ false,
    /* allowAdd             */ true,
    /* allowChange          */ true,
    /* allowDelete          */ true,
    /* allowExport          */ true,
    /* allowSearch          */ true,
    /* allowPrint           */ false,
    /* allowUnlock          */ false,
    /* additional           */ "",
    /* itemDelegate         */ nullptr,


    /* sortFields           */
    {
      "\"keyField\", \"cfyField\""
    },

    /* search fields        */
    {
      "phone",
      "cell",
      "email",
      "street1",
      "street2",
      "city",
      "state",
      "zip",

    },

    /* column defs          */
    {
      { "keyField", "", 190, Wt::AlignmentFlag::Left, "", nullptr },
      { "cfyField", "", 190, Wt::AlignmentFlag::Left, "", nullptr },
      { "phone",    "", 120, Wt::AlignmentFlag::Left, "", nullptr },
      { "cell",     "", 120, Wt::AlignmentFlag::Left, "", nullptr },
      { "email",    "", 170, Wt::AlignmentFlag::Left, "", nullptr },
      { "street1",    "", 170, Wt::AlignmentFlag::Left, "", nullptr },
      { "street2",    "", 170, Wt::AlignmentFlag::Left, "", nullptr },
      { "city",    "", 170, Wt::AlignmentFlag::Left, "", nullptr },
      { "state",    "", 170, Wt::AlignmentFlag::Left, "", nullptr },
      { "zip",    "", 170, Wt::AlignmentFlag::Left, "", nullptr },
    },

    /* column names         */
    {
      "id",
      "keyField",
      "cfyField",
    }
  };

  init( viewDef );

} // endWtx::Crm::Person::Desktop::Desktop( Wtx::Dbo::Session * s )


Wtx::Crm::Person::ManagerWidget::ManagerWidget( Wtx::Dbo::Session * session )
: Wt::WCompositeWidget()
{
  m_desktop = setImplementation( std::make_unique<Wtx::Crm::Person::Desktop>( session ) );

} // endWarehouse::Order::ManagerWidget::ManagerWidget()


Wtx::Crm::Person::ManagerWidget::ManagerWidget( Wtx::TableViewDef::ViewDef & viewDef, Wtx::Dbo::Session * session )
: Wt::WCompositeWidget()
{
  m_desktop = setImplementation( std::make_unique< Wtx::Crm::Person::Desktop >( viewDef, session ) );

} // endWarehouse::Order::ManagerWidget::ManagerWidget()

Wt::Signal< Wtx::Crm::Person::Item::Ptr > & Wtx::Crm::Person::ManagerWidget::clicked()
{
  return m_desktop-> m_view-> itemClicked();
}

Wt::Signal< Wtx::Crm::Person::Item::Ptr > & Wtx::Crm::Person::ManagerWidget::doubleClicked()
{
  return m_desktop-> m_view-> doubleClicked();
}

Wt::Signal< Wtx::Crm::Person::Item::Ptr > & Wtx::Crm::Person::ManagerWidget::addClicked()
{
  return m_desktop-> m_view-> addClicked();
}

Wt::Signal< std::string > &  Wtx::Crm::Person::ManagerWidget::additionalClicked()
{
  return m_desktop-> m_view-> additionalClicked();
}

void Wtx::Crm::Person::ManagerWidget::setFilter( const std::string & value )
{
  m_desktop-> m_view-> tableView()-> setFilter( value );
}

void Wtx::Crm::Person::ManagerWidget::clearFilter()
{
  m_desktop-> m_view-> tableView()-> setFilter( "true" );
}

void Wtx::Crm::Person::ManagerWidget::openDetail( Wt::Dbo::ptr<Wtx::Crm::Person::Item> & item )
{
  m_desktop-> openDetail( item );
}

void Wtx::Crm::Person::ManagerWidget::setOpenDetail( bool value )
{
  m_desktop-> setOpenDetail( value );
}

Wtx::Dbo::TableView< Wtx::Crm::Person::Item > * Wtx::Crm::Person::ManagerWidget::tableView()
{
  return m_desktop-> m_view-> tableView();
}

