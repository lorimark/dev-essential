
#include <Wt/WText.h>
#include <Wt/WHBoxLayout.h>

#include <Wtx/Sys/Session.h>
#include <Wtx/Dbo/TableViewManager.h>
#include <Wtx/Dbo/TemplateFormView.h>
#include <Wtx/Dbo/DetailForm.h>
#include <Wtx/Sys/User/ItemDelegate.h>

#include "Item.h"
#include "ManagerWidget.h"

namespace Wtx {
  namespace Sys {
    namespace Log {

class Detail
: public Wtx::Dbo::DetailForm<Wtx::Sys::Log::Item>
{
  public:

    Detail( Wt::Dbo::ptr<Wtx::Sys::Log::Item> & item )
    : Wtx::Dbo::DetailForm<Wtx::Sys::Log::Item>
      (
        "sysLog.detailForm",
        item
      )
    {
    }

};

class View
: public Wt::WContainerWidget
{
  public:

    View( Wtx::Sys::Session * session );

    void setFilter( const std::string & filter );

    Wtx::Dbo::TableViewManager< Wtx::Sys::Log::Item, Detail > * m_view = nullptr;

};

View::View(  Wtx::Sys::Session * session )
: Wt::WContainerWidget()
{
  auto lw = std::make_unique< Wt::WVBoxLayout >();

  Wtx::TableViewDef::ViewDef viewDef =
  {
    /* title                */ "Log",
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
    /* showHeader           */ false,
    /* showFooter           */ true,
    /* showPrevNext         */ false,
    /* hideSearch           */ true,
    /* allowFilter          */ false,
    /* allowAdd             */ false,
    /* allowChange          */ false,
    /* allowDelete          */ false,
    /* allowExport          */ false,
    /* allowSearch          */ false,
    /* allowPrint           */ false,
    /* allowUnlock          */ false,
    /* additional           */ "",
    /* itemDelegate         */ nullptr,


    /* sortFields           */
    {
      "id DESC"
    },

    /* search fields        */
    {
    },

    /* column defs          */
    {
      { "id",           "",  75, Wt::AlignmentFlag::Left, "", nullptr  },
      { "createdOn",    "", 150, Wt::AlignmentFlag::Left, "", nullptr  },
      { "clip",         "", 125, Wt::AlignmentFlag::Left, "", nullptr  },
      { "sysUser_id",   "", 125, Wt::AlignmentFlag::Left, "", &Wtx::Sys::User::ItemDelegate::create  },
      { "keyField",     "", 150, Wt::AlignmentFlag::Left, "", nullptr  },
      { "cfyField",     "", 450, Wt::AlignmentFlag::Left, "", nullptr  },
    },

    /* column names         */
    {
      "id",
      "version"
    }
  };

  m_view = lw-> addWidget( std::make_unique< Wtx::Dbo::TableViewManager< Wtx::Sys::Log::Item, Detail > >( viewDef, session ) );

  setLayout( std::move(lw) );

}

void View::setFilter( const std::string & filter )
{
  m_view-> tableView()-> setFilter( filter );
}

    } // endnamespace Log
  } // endnamespace Sys
} // endnamespace Wtx

Wtx::Sys::Log::ManagerWidget::ManagerWidget( Wtx::Sys::Session * session )
{
  auto layout = std::make_unique<Wt::WHBoxLayout>();

  m_view = layout-> addWidget( std::make_unique< View >( session ) );

  setLayout( std::move(layout) );

} // endWtx::Sys::Log::ManagerWidget::ManagerWidget()


void Wtx::Sys::Log::ManagerWidget::setFilter( const std::string & filter )
{
  m_view-> setFilter( filter );

}

