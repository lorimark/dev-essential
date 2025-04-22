
#include <Wt/WBreak.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WApplication.h>
#include <Wt/WLineEdit.h>

#include "PopupQuestion.h"

Wtx::PopupQuestion::PopupQuestion( const std::string & question, const std::string & answer, const std::string & placeholder )
: Wt::WDialog("Alert")
{
  contents()-> addNew<Wt::WText>(question);
  contents()-> addNew<Wt::WBreak>();
  auto textEdit = contents()-> addNew<Wt::WLineEdit>(answer);
  textEdit-> setPlaceholderText( placeholder );
  contents()-> addNew<Wt::WBreak>();
  contents()-> addNew<Wt::WPushButton>("Ok")->
    clicked().connect( [=]()
    {
      m_answered.emit( textEdit-> valueText().toUTF8() );
      accept();
    });

  contents()-> addNew<Wt::WPushButton>("Cancel")->
    clicked().connect( this, &Wt::WDialog::reject );

  rejectWhenEscapePressed();

  Wt::WDialog::show();
}


Wtx::PopupQuestion * Wtx::PopupQuestion::ask( const std::string & question, const std::string & answer, const std::string & placeholder )
{
  auto popup = wApp-> addChild( std::make_unique<Wtx::PopupQuestion>( question, answer, placeholder ) );
  popup-> finished().connect( [=](){ wApp-> removeChild(popup); });
  return popup;
}

Wt::Signal<std::string> & Wtx::PopupQuestion::answered()
{
  return m_answered;
}
