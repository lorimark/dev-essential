
#include <Wt/WBreak.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include "MessageBox.h"

Wtx::MessageBox::MessageBox( const std::string & message )
: Wt::WDialog("Question")
{
  contents()-> addNew<Wt::WText>(message);
  contents()-> addNew<Wt::WBreak>();
  contents()-> addNew<Wt::WPushButton>("Yes")->
    clicked().connect( [=]()
    {
      accept();
      m_yes.emit();
    });

  contents()-> addNew<Wt::WPushButton>("No")->
    clicked().connect( [=]()
    {
      accept();
      m_no.emit();
    });

  rejectWhenEscapePressed();

  show();
}

Wt::Signal<> & Wtx::MessageBox::yes()
{
  return m_yes;
}

Wt::Signal<> & Wtx::MessageBox::no()
{
  return m_no;
}
