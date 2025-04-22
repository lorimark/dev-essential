
#include <Wt/WText.h>
#include <Wt/WHBoxLayout.h>

#include <Wtx/Sys/Session.h>
#include <Wtx/Dbo/TableViewManager.h>
#include <Wtx/Dbo/TemplateFormView.h>
#include <Wtx/Dbo/DetailForm.h>

#include "Item.h"
#include "ManagerWidget.h"

class UserDetail
: public Wtx::Dbo::DetailForm<Wtx::Sys::User::Item>
{
  public:

    UserDetail( Wt::Dbo::ptr<Wtx::Sys::User::Item> & item )
    : Wtx::Dbo::DetailForm<Wtx::Sys::User::Item>
      (
        "sysUser.detailForm",
        item
      )
    {
    }

};



Wtx::Sys::User::ManagerWidget::ManagerWidget( Wtx::Sys::Session * session )
{

  auto layout = std::make_unique<Wt::WHBoxLayout>();

  {
    Wtx::TableViewDef::ViewDef viewDef =
    {
      /* title                */ "Users",
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
      /* allowAdd             */ false,
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
        "id"
      },

      /* search fields        */
      {
      },

      /* column defs          */
      {
        { "id",           "",  50, Wt::AlignmentFlag::Left, "", nullptr  },
        { "isActive",     "",  75, Wt::AlignmentFlag::Left, "", nullptr  },
        { "keyField",     "", 350, Wt::AlignmentFlag::Left, "", nullptr  }
      },

      /* column names         */
      {
        "id",
        "version"
      }
    };

    auto view = layout-> addWidget( std::make_unique< Wtx::Dbo::TableViewManager< Wtx::Sys::User::Item, UserDetail > >( viewDef, session ) );

    view-> tableView()-> clicked().connect( [=]( Wt::WModelIndex index, Wt::WMouseEvent event )
    {
      auto userItem =
        view->
          tableView()->
            model()->
              stableResultRow( index.row() );

      std::cout << __FILE__ << ":" << __LINE__ << " " << userItem.id() << std::endl;

    });

  }

  setLayout( std::move(layout) );

} // endWtx::Sys::User::ManagerWidget::ManagerWidget()





