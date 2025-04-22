
#ifndef __WTX_SYS_LOOKUP_MANAGERWIDGET_H___
#define __WTX_SYS_LOOKUP_MANAGERWIDGET_H___

#include <Wt/WContainerWidget.h>
#include <Wtx/Dbo/Session.h>

namespace Wtx {
  namespace Sys {
    namespace Lookup {

class ManagerWidget
: public Wt::WContainerWidget
{
  public:

    ManagerWidget( Wtx::Dbo::Session * s );

    Wtx::Dbo::Session * session() const { return m_session; }

  private:

    Wtx::Dbo::Session * m_session = nullptr;

}; // endclass ManagerWidget

    } // endnamespace Lookup
  } // endnamespace Sys
} // endnamespace Wtx

#endif // #ifndef __WTX_SYS_LOOKUP_MANAGERWIDGET_H___


