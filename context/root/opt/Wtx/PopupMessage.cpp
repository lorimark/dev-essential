
#include <Wt/WBreak.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WApplication.h>

#include "PopupMessage.h"

Wtx::PopupMessage::PopupMessage( const std::string & message )
: Wt::WDialog("Alert")
{
  contents()-> addNew<Wt::WText>(message,Wt::TextFormat::UnsafeXHTML);
  contents()-> addNew<Wt::WBreak>();
  contents()-> addNew<Wt::WPushButton>("Ok")->
    clicked().connect( [=]()
    {
      accept();
    });

  rejectWhenEscapePressed();

  Wt::WDialog::show();
}


Wtx::PopupMessage * Wtx::PopupMessage::show( const std::string & message )
{
  auto popup = wApp-> addChild( std::make_unique<Wtx::PopupMessage>( message ) );
  popup-> finished().connect( [=](){ wApp-> removeChild(popup); });
  return popup;
}

Wtx::PopupMessage * Wtx::PopupMessage::show( const Wt::WString & message )
{
  return show( message.toUTF8() );
}

Wtx::PopupMessage * Wtx::PopupMessage::show( const char * message )
{
  return show( std::string(message) );
}

Wtx::PopupMessage * Wtx::PopupMessage::ask( const std::string & message )
{
  return show( message );
}

Wt::Signal<std::string> & Wtx::PopupMessage::finished()
{
  return m_finished;
}
