
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

#include <Wtx/Dbo/TableViewManager.h>
#include <Wtx/Dbo/TemplateFormView.h>
#include <Wtx/Dbo/LookupItemDelegate.h>
#include <Wtx/Dbo/DetailForm.h>

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

class LookupDetail
: public Wtx::Dbo::DetailForm< Wtx::Sys::Lookup::Item >
{
  public:

    LookupDetail( Wt::Dbo::ptr< Wtx::Sys::Lookup::Item > & item )
    : Wtx::Dbo::DetailForm< Wtx::Sys::Lookup::Item >
      (
        "sysLookup.detailForm",
        item
      )
    {
    }

};


class LookupDesktop
: public BaseDesktop
{
  public:

    LookupDesktop( Wtx::Dbo::Session * s );

}; // endclass LookupDesktop( Wtx::Dbo::Session * s )

LookupDesktop::LookupDesktop( Wtx::Dbo::Session * s )
: BaseDesktop( s )
{
  auto layout = std::make_unique< Wt::WHBoxLayout >();
  layout-> setContentsMargins( 0,0,0,0 );

  {
    Wtx::TableViewDef::ViewDef viewDef =
    {
      /* title                */ "Categories",
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
      /* hideSearch           */ true,
      /* allowFilter          */ false,
      /* allowAdd             */ true,
      /* allowChange          */ true,
      /* allowDelete          */ false,
      /* allowExport          */ true,
      /* allowSearch          */ true,
      /* allowPrint           */ false,
      /* allowUnlock          */ false,
      /* additional           */ "",
      /* itemDelegate         */ nullptr,

      /* sortFields           */
      {
        "\"keyField\""
      },

      /* search fields        */
      {
      },

      /* column defs          */
      {
//        { "id",           "",  50, Wt::AlignmentFlag::Left, "", nullptr  },
//        { "isActive",     "",  75, Wt::AlignmentFlag::Left, "", nullptr  },

        { "id",                "",         50,  Wt::AlignmentFlag::Left, "", nullptr  },
        { "keyField",          "",         100, Wt::AlignmentFlag::Left, "", nullptr  },
        { "cfyField",          Wtx::Sys::Lookup::Item::TableDef().CfyFieldDef.label(),         300, Wt::AlignmentFlag::Left, "", nullptr  },
        { "description",       "",         300, Wt::AlignmentFlag::Left, "", nullptr  }

      },

      /* column names         */
      {
        "id",
        "keyField",
        "cfyField",
      }
    };

    layout-> addWidget( std::make_unique< Wtx::Dbo::TableViewManager< Wtx::Sys::Lookup::Item, LookupDetail > >( viewDef, session() ) );

  }

  setLayout( std::move(layout) );

} // endLookupDesktop::LookupDesktop( Wtx::Dbo::Session * s )



Wtx::Sys::Lookup::ManagerWidget::ManagerWidget( Wtx::Dbo::Session * s )
: Wt::WContainerWidget(),
  m_session(s)
{

  auto layout = std::make_unique<Wt::WHBoxLayout>();
  layout-> setContentsMargins( 0,0,0,0 );

  layout-> addWidget( std::make_unique< LookupDesktop >( s ) );

  setLayout( std::move(layout) );

} // endWtx::Sys::Lookup::ManagerWidget::ManagerWidget( Wtx::Dbo::Session * s )


