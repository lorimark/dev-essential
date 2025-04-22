
#include <Wt/WApplication.h>
#include <Wt/WPushButton.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WLineEdit.h>
#include <Wt/WComboBox.h>
#include <Wt/WImage.h>
#include <Wt/WFileUpload.h>
#include <Wt/WTextArea.h>
#include <Wt/WTextEdit.h>

#include "Composer.h"
#include "AttachmentEditor.h"

class DetailForm
: public Wt::WContainerWidget
{
  public:

    DetailForm();

    void do_send();
    void do_save();
    void do_discard();
    void do_attach();

    void setMessage( const Wtx::Mail::Message & message );

    Wt::WLineEdit * m_fromEdit;
    Wt::WLineEdit * m_subjectEdit;

    struct RecipientEditor
    {
      Wt::WComboBox * recipientType;
      Wt::WLineEdit * emailAddress;
      int row;
    };

    RecipientEditor & addRecipientEditor();
    std::vector< RecipientEditor > m_recipientEditors;

    struct AttachmentEditor
    {
      Wtx::Eml::AttachmentEditor * editor;
      int row;
    };

    void addAttachmentEditor();
    std::vector< AttachmentEditor > m_attachmentEditors;

    void loadMessage();

    Wtx::Mail::Message m_message;
    Wt::WTable    * m_table;
    Wt::WTextArea * m_body;
    Wt::Signal<>    m_send;
    Wt::Signal<>       m_discard;

}; // endclass DetailForm

DetailForm::DetailForm()
: Wt::WContainerWidget()
{
  setStyleClass( "darker" );
  setOverflow( Wt::Overflow::Auto );

  auto _controlButtons = [=]()
  {
    auto cw = addNew< Wt::WContainerWidget >();

    cw-> setPadding( 5 );
    auto pbSend = cw-> addNew< Wt::WPushButton >( Wt::WString::tr( "wtx.eml.composer.send" ) );
    pbSend-> setStyleClass( "default btn-xs" );
    pbSend-> clicked().connect( [=](){ m_send.emit(); } );

    auto pbSave = cw-> addNew< Wt::WPushButton >( Wt::WString::tr( "wtx.eml.composer.savenow" ) );
    pbSave-> setStyleClass( "btn-xs" );
    pbSave-> clicked().connect( this, &DetailForm::do_save );

    auto pbDiscard = cw-> addNew< Wt::WPushButton >( Wt::WString::tr( "wtx.eml.composer.discard" ) );
    pbDiscard-> setStyleClass( "btn-xs" );
    pbDiscard-> clicked().connect( [=](){ m_discard.emit(); } );

    return cw;
  };

  _controlButtons();

  m_table = addNew< Wt::WTable >();

  m_body = addNew< Wt::WTextEdit >();
//  m_body-> setHeight( "375px" );
  m_body-> setHeight( "200px" );

  _controlButtons();

  loadMessage();

} // endDetailForm::DetailForm()

void DetailForm::loadMessage()
{
  m_table-> clear();
  m_recipientEditors.clear();

  int row = 0;

  m_table-> setStyleClass( "lighter" );
  m_table-> resize( Wt::WLength( 100, Wt::LengthUnit::Percentage ), Wt::WLength::Auto );
  m_table-> elementAt( row, 0 )-> resize( Wt::WLength( 1, Wt::LengthUnit::Percentage ), Wt::WLength::Auto );

  m_table-> elementAt( row, 0 )-> addNew< Wt::WText >( Wt::WString::tr( "wtx.eml.composer.from" ) );
  m_fromEdit = m_table-> elementAt( row, 1 )-> addNew< Wt::WLineEdit >();
  m_fromEdit-> setText( m_message.from().displayName() + " <" + m_message.from().address() + ">" );
  m_fromEdit-> setReadOnly( true );

  for( auto recipient : m_message.recipients() )
  {
    auto recipientEditor = addRecipientEditor();
    recipientEditor.emailAddress-> setValueText( recipient.mailbox.address() );
  }

  addRecipientEditor();

  row = m_table-> rowCount();
  m_table-> elementAt( row, 0 )-> addNew< Wt::WText >( Wt::WString::tr( "wtx.eml.composer.subject" ) );
  m_subjectEdit = m_table-> elementAt( row, 1 )-> addNew< Wt::WLineEdit >();
  m_subjectEdit-> setValueText( m_message.subject() );

  for( auto attachment : m_message.attachments() )
  {
    int row = m_table-> rowCount();
    m_table-> elementAt( row, 0 )-> addNew< Wt::WImage >( "resources/icons/paperclip.png" );
    m_table-> elementAt( row, 0 )-> setContentAlignment( Wt::AlignmentFlag::Right | Wt::AlignmentFlag::Top );
    m_table-> elementAt( row, 0 )-> setPadding( 3 );
//    auto pb = m_table-> elementAt( row, 1 )-> addNew< Wt::WPushButton >( "O" );
//    pb-> setStyleClass( "btn-xs" );
    m_table-> elementAt( row, 1 )-> addNew< Wt::WText >( attachment.fileName );
  }

  addAttachmentEditor();

} // endvoid DetailForm::loadMessage()

DetailForm::RecipientEditor & DetailForm::addRecipientEditor()
{
  auto _tcb = [=]()
  {
    auto retVal = std::make_unique< Wt::WComboBox >();

    retVal-> addItem( Wt::WString::tr( "wtx.eml.composer.to"  ) );
    retVal-> addItem( Wt::WString::tr( "wtx.eml.composer.cc"  ) );
    retVal-> addItem( Wt::WString::tr( "wtx.eml.composer.bcc" ) );

    return retVal;
  };

  int row = 0;
  for( auto recipientEditor : m_recipientEditors )
    if( row < recipientEditor.row )
      row = recipientEditor.row;
  row++;

  m_table-> insertRow( row );

  RecipientEditor editor;
  editor.recipientType = m_table-> elementAt( row, 0 )-> addWidget( _tcb() );
  editor.emailAddress  = m_table-> elementAt( row, 1 )-> addNew< Wt::WLineEdit >();
  editor.row = row;

  m_recipientEditors.push_back( editor );

  return m_recipientEditors.at( m_recipientEditors.size()-1 );

} // endDetailForm::RecipientEditor & DetailForm::addRecipientEditor()

void DetailForm::addAttachmentEditor()
{
  int row = m_table-> rowCount();
  m_table-> elementAt( row, 0 )-> addNew< Wt::WImage >( "resources/icons/paperclip.png" );
  m_table-> elementAt( row, 0 )-> setContentAlignment( Wt::AlignmentFlag::Right | Wt::AlignmentFlag::Top );
  m_table-> elementAt( row, 0 )-> setPadding( 3 );
  auto editor = m_table-> elementAt( row, 1 )-> addNew< Wtx::Eml::AttachmentEditor >( m_attachmentEditors.size() );

  AttachmentEditor attachmentEditor;
  attachmentEditor.editor = editor;
  attachmentEditor.row = row;
  m_attachmentEditors.push_back( attachmentEditor );

  editor-> attached().connect( [=]()
  {
    std::cout << __FILE__ << ":" << __LINE__ << " " << row << std::endl;

    addAttachmentEditor();
  });

  editor-> removed().connect( [=]()
  {
    std::cout << __FILE__ << ":" << __LINE__ << " " << row << std::endl;

  });

}

void DetailForm::setMessage( const Wtx::Mail::Message & message )
{
  m_message = message;

  loadMessage();

} // endvoid DetailForm::setMessage( const Wt::Mail::Message & message )

void DetailForm::do_save()
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

}

void DetailForm::do_attach()
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

}


/***************************************************************************/
/***************************************************************************/
/***************************************************************************/

Wtx::Eml::Composer::Composer()
{
  m_impl = setImplementation( std::make_unique< DetailForm >() );
}

#ifdef DONT_USE_THIS_IT_DOESNT_WORK
Wtx::Eml::Composer::Composer( const Wt::Mail::Message & message )
{
  auto u_impl = std::make_unique< DetailForm >();
       u_impl-> setMessage( message );

  wApp-> processEvents();

  m_impl = setImplementation( std::move( u_impl ) );

}
#endif


const Wtx::Mail::Message & Wtx::Eml::Composer::message() const
{
  return dynamic_cast< DetailForm* >( m_impl )-> m_message;
}

void Wtx::Eml::Composer::setMessage( const Wtx::Mail::Message & message )
{
  dynamic_cast< DetailForm* >( m_impl )-> setMessage( message );
}

Wt::Signal<> & Wtx::Eml::Composer::send()
{
  return dynamic_cast< DetailForm* >( m_impl )-> m_send;
}

Wt::Signal<> & Wtx::Eml::Composer::discard()
{
  return dynamic_cast< DetailForm* >( m_impl )-> m_discard;
}


