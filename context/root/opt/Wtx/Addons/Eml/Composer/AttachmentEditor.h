
#ifndef __ATTACHMENTEDITOR_H___
#define __ATTACHMENTEDITOR_H___

#include <Wt/WContainerWidget.h>
#include <Wt/WFileUpload.h>

namespace Wtx {
  namespace Eml {

class AttachmentEditor
: public Wt::WContainerWidget
{
  public:

    AttachmentEditor( int count );
    AttachmentEditor( const std::string & fileName );

    Wt::Signal<> & attached();
    Wt::Signal<> & removed();

  private:

    void do_upload();
    void do_uploaded();
    void do_fileTooLarge();
    void do_removed();

    Wt::WFileUpload * m_fileUpload;

    Wt::Signal<> m_attached;
    Wt::Signal<> m_removed;

}; // endclass AttachmentEditor

  } // endnamespace Eml {
} // endnamespace Wtx {

#endif // __ATTACHMENTEDITOR_H___


