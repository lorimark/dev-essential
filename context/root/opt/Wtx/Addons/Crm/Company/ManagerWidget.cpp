
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
#include <Wtx/Dbo/DetailForm.h>

#include "Item.h"
#include "ManagerWidget.h"

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

class CompanyDetail
: public Wtx::Dbo::DetailForm< Wtx::Crm::Company::Item >
{
  public:

    CompanyDetail( Wt::Dbo::ptr< Wtx::Crm::Company::Item > & item )
    : Wtx::Dbo::DetailForm< Wtx::Crm::Company::Item >
      (
        "crmCompany.detailForm",
        item
      )
    {
    }

};

class CompanyDesktop
: public BaseDesktop
{
  public:

    CompanyDesktop( Wtx::Dbo::Session * s );

}; // endclass CustomerDesktop( Wtx::Dbo::Session * s )

CompanyDesktop::CompanyDesktop( Wtx::Dbo::Session * s )
: BaseDesktop( s )
{
  auto layout = std::make_unique< Wt::WHBoxLayout >();

#ifndef NEVER
  {
    Wtx::TableViewDef::ViewDef viewDef =
    {
      /* title                */ "Customers",
      /* tip                  */ "",
      /* headerCount          */ 0,
      /* selectionMode        */ Wt::SelectionMode::Single,
      /* columnResizeEnabled  */ true,
      /* alternatingRowColors */ true,
      /* sql                  */ "",
      /* filter               */ "\"isActive\"",
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
      /* allowDelete          */ true,
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
        "city",
        "state",
        "zip",
        "phone",
        "buyer",
        "buyerPhone",
        "email",
        "contact",
        "contactPhone"
      },

      /* column defs          */
      {
//        { "id",           "",  50, Wt::AlignmentFlag::Left, "", nullptr  },
//        { "isActive",     "",  75, Wt::AlignmentFlag::Left, "", nullptr  },

        { "custType",     "type",     50, Wt::AlignmentFlag::Left, "", nullptr  },
        { "keyField",     "",        100, Wt::AlignmentFlag::Left, "", nullptr  },
        { "cfyField",     "",        300, Wt::AlignmentFlag::Left, "", nullptr  },
        { "addr",         "",        150, Wt::AlignmentFlag::Left, "", nullptr  },
        { "city",         "",        100, Wt::AlignmentFlag::Left, "", nullptr  },
        { "state",        "",        100, Wt::AlignmentFlag::Left, "", nullptr  },
        { "zip",          "",        100, Wt::AlignmentFlag::Left, "", nullptr  },
        { "contact",      "",        100, Wt::AlignmentFlag::Left, "", nullptr  },
        { "contactPhone", "",        100, Wt::AlignmentFlag::Left, "", nullptr  }

      },

      /* column names         */
      {
        "id",
        "keyField",
        "cfyField",
        "phone"
      }
    };

    layout-> addWidget( std::make_unique< Wtx::Dbo::TableViewManager< Wtx::Crm::Company::Item, CompanyDetail > >( viewDef, session() ) );

  }
#endif

#ifdef NEVER
  auto vlw = std::make_unique<Wt::WVBoxLayout>();

  {
    Wtx::TableViewDef::ViewDef viewDef =
    {
      /* title                */ "Invoices for Account",
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
      /* hideSearch           */ true,
      /* allowFilter          */ false,
      /* allowAdd             */ false,
      /* allowChange          */ false,
      /* allowDelete          */ false,
      /* allowExport          */ true,
      /* allowSearch          */ true,
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
        { "id",           "",  50, Wt::AlignmentFlag::Left, "", nullptr  },
        { "keyField",     "", 350, Wt::AlignmentFlag::Left, "", nullptr  }
      },

      /* column names         */
      {
        "id",
        "version",
        "versionSync",
        "isActive",
        "isVisible",
        "isDeleted",
        "keyField",
        "cfyField",
        "varField",
        "uidField",
        "pMode",
        "createdOn",
        "changedOn",
        "pUser",
        "pGroup",
        "sessionLock",
        "datePosted",
        "summary",
        "thumbnail",
        "body"
      }
    };

    vlw-> addWidget( std::make_unique< Wtx::Dbo::TableViewManager< Wtx::Fms::Invoice::Item, InvoiceDetail > >( viewDef, session() ) );

  }

  {
    Wtx::TableViewDef::ViewDef viewDef =
    {
      /* title                */ "Activity for Account",
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
      /* hideSearch           */ true,
      /* allowFilter          */ false,
      /* allowAdd             */ false,
      /* allowChange          */ false,
      /* allowDelete          */ false,
      /* allowExport          */ true,
      /* allowSearch          */ true,
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
        { "id",           "",  50, Wt::AlignmentFlag::Left, "", nullptr  },
        { "keyField",     "", 350, Wt::AlignmentFlag::Left, "", nullptr  }
      },

      /* column names         */
      {
        "id",
        "version",
        "versionSync",
        "isActive",
        "isVisible",
        "isDeleted",
        "keyField",
        "cfyField",
        "varField",
        "uidField",
        "pMode",
        "createdOn",
        "changedOn",
        "pUser",
        "pGroup",
        "sessionLock",
        "datePosted",
        "summary",
        "thumbnail",
        "body"
      }
    };

    vlw-> addWidget( std::make_unique< Wtx::Dbo::TableViewManager< Wtx::Fms::Activity::Item, ActivityDetail > >( viewDef, session() ) );
  }

  {
    Wtx::TableViewDef::ViewDef viewDef =
    {
      /* title                */ "Transactions for Activity",
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
      /* hideSearch           */ true,
      /* allowFilter          */ false,
      /* allowAdd             */ false,
      /* allowChange          */ false,
      /* allowDelete          */ false,
      /* allowExport          */ true,
      /* allowSearch          */ true,
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
        { "id",           "",  50, Wt::AlignmentFlag::Left, "", nullptr  },
        { "keyField",     "", 350, Wt::AlignmentFlag::Left, "", nullptr  }
      },

      /* column names         */
      {
        "id",
        "version",
        "versionSync",
        "isActive",
        "isVisible",
        "isDeleted",
        "keyField",
        "cfyField",
        "varField",
        "uidField",
        "pMode",
        "createdOn",
        "changedOn",
        "pUser",
        "pGroup",
        "sessionLock",
        "datePosted",
        "summary",
        "thumbnail",
        "body"
      }
    };

    vlw-> addWidget( std::make_unique< Wtx::Dbo::TableViewManager< Wtx::Fms::Transaction::Item, TransactionDetail > >( viewDef, session() ) );
  }

  vlw-> setResizable( 0 );
  vlw-> setResizable( 1 );

  layout-> addLayout( std::move(vlw) );
  layout-> setResizable( 0 );
#endif

  setLayout( std::move(layout) );

} // endCompanyDesktop::CompanyDesktop( Wtx::Dbo::Session * s )



Wtx::Crm::Company::ManagerWidget::ManagerWidget( Wtx::Dbo::Session * s )
: Wt::WContainerWidget(),
  m_session(s)
{

  auto lw_u = std::make_unique<Wt::WHBoxLayout>();
  auto lw = lw_u.get();
  setLayout( std::move(lw_u) );

  lw-> addWidget( std::make_unique< CompanyDesktop >( s ) );

} // endWarehouse::Customer::ManagerWidget::ManagerWidget( Wtx::Dbo::Session * s )


