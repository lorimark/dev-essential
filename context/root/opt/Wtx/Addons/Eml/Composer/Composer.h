
#ifndef __COMPOSER_H___
#define __COMPOSER_H___

#include <Wt/WCompositeWidget.h>
#include <Wt/Mail/Mailbox.h>

#include <Wtx/Mail/Message.h>
#include <Wtx/Addons/Eml/Composer/Attachment.h>

namespace Wtx {
  namespace Eml {

class Composer
: public Wt::WCompositeWidget
{
  public:

    Composer();
//    Composer( const Wt::Mail::Message & message );

    const Wtx::Mail::Message & message() const;
    void setMessage( const Wtx::Mail::Message & message );

    Wt::Signal<> & send();
    Wt::Signal<> & discard();

  private:

    Wt::WWidget * m_impl;

};

  } // endnamespace Eml
} // endnamespace Wtx

#endif // __COMPOSER_H___

