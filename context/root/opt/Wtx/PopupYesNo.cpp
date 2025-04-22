
#include <Wt/WBreak.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WApplication.h>
#include <Wt/WLineEdit.h>

#include "PopupYesNo.h"

Wtx::PopupYesNo::PopupYesNo( const std::string & question )
: Wt::WDialog("Yes/No")
{
  contents()-> addNew<Wt::WText>(question);
  contents()-> addNew<Wt::WBreak>();
  contents()-> addNew<Wt::WPushButton>("Yes")->
    clicked().connect( [=]()
    {
      m_answered.emit( Wt::StandardButton::Yes );
      accept();
    });

  contents()-> addNew<Wt::WPushButton>("No")->
    clicked().connect( [=]()
    {
      m_answered.emit( Wt::StandardButton::No );
      accept();
    });

  rejectWhenEscapePressed();

  Wt::WDialog::show();
}


Wtx::PopupYesNo * Wtx::PopupYesNo::ask( const std::string & question )
{
  auto popup = wApp-> addChild( std::make_unique<Wtx::PopupYesNo>( question ) );
  popup-> finished().connect( [=](){ wApp-> removeChild(popup); });
  return popup;
}

Wt::Signal<Wt::StandardButton> & Wtx::PopupYesNo::answered()
{
  return m_answered;
}
