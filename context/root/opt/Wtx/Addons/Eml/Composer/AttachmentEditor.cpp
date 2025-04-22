
#include <Wt/WText.h>
#include <Wt/WPushButton.h>

#include "AttachmentEditor.h"

Wtx::Eml::AttachmentEditor::AttachmentEditor( int count )
: Wt::WContainerWidget()
{
  Wt::WText * text;

  if( count == 0 )
    text = addNew< Wt::WText >( Wt::WString::tr("wtx.eml.composer.attachfile") );
  else
    text = addNew< Wt::WText >( Wt::WString::tr("wtx.eml.composer.attachanother") );

  text-> setAttributeValue( "style", "text-decoration: underline" );
  text-> clicked().connect( this, &Wtx::Eml::AttachmentEditor::do_upload );

}

Wtx::Eml::AttachmentEditor::AttachmentEditor( const std::string & fileName )
{
}

Wt::Signal<> & Wtx::Eml::AttachmentEditor::attached()
{
  return m_attached;
}

Wt::Signal<> & Wtx::Eml::AttachmentEditor::removed()
{
  return m_removed;
}

void Wtx::Eml::AttachmentEditor::do_upload()
{
  clear();

  m_fileUpload = addNew< Wt::WFileUpload >();

  /*
   * React to events.
   */

  // Try to catch the fileupload change signal to trigger an upload.
  // We could do like google and at a delay with a WTimer as well...
  m_fileUpload-> changed().connect( m_fileUpload, &Wt::WFileUpload::upload );

  // React to a succesfull upload.
  m_fileUpload-> uploaded().connect( this, &Wtx::Eml::AttachmentEditor::do_uploaded );

  // React to a fileupload problem.
  m_fileUpload-> fileTooLarge().connect( this, &Wtx::Eml::AttachmentEditor::do_fileTooLarge );

  /*
   * Connect the uploadDone signal to the Composer's attachmentDone,
   * so that the Composer can keep track of attachment upload progress,
   * if it wishes.
   */
//  uploadDone_.connect(composer, &Composer::attachmentDone);

} // endvoid Wtx::Eml::AttachmentEditor::do_upload()

void Wtx::Eml::AttachmentEditor::do_uploaded()
{

  std::vector< std::string > files;

  for( auto uploadedFile : m_fileUpload-> uploadedFiles() )
  {
    std::cout << __FILE__ << ":" << __LINE__
      << " " << uploadedFile.spoolFileName()
      << " " << uploadedFile.clientFileName()
      << std::endl;

    files.push_back( uploadedFile.clientFileName() );

  }

  clear();

  for( auto file : files )
  {
    auto pbRemove = addNew< Wt::WPushButton >( "X" );
    addNew< Wt::WText >( file );

    pbRemove-> setStyleClass( "btn-xs" );
    pbRemove-> clicked().connect( this, &Wtx::Eml::AttachmentEditor::do_removed );

  }

  m_attached.emit();

} // endvoid Wtx::Eml::AttachmentEditor::do_uploaded()

void Wtx::Eml::AttachmentEditor::do_fileTooLarge()
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

}

void Wtx::Eml::AttachmentEditor::do_removed()
{
  m_removed.emit();
}

