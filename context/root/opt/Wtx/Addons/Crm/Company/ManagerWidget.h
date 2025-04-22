
#ifndef __WTX_CRM_COMPANY_MANAGERWIDGET_H___
#define __WTX_CRM_COMPANY_MANAGERWIDGET_H___

#include <Wt/WContainerWidget.h>
#include <Wtx/Dbo/Session.h>

namespace Wtx {
  namespace Crm {
    namespace Company {

class ManagerWidget
: public Wt::WContainerWidget
{
  public:

    ManagerWidget( Wtx::Dbo::Session * s );

    Wtx::Dbo::Session * session() const { return m_session; }

  private:

    Wtx::Dbo::Session * m_session = nullptr;

}; // endclass ManagerWidget

    } // endnamespace Company
  } // endnamespace Crm
} // endnamespace Wtx

#endif


