
#include <Wt/WStandardItem.h>
#include <Wt/WPushButton.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WFileUpload.h>
#include <Wt/WDialog.h>
#include <Wt/WTemplate.h>
#include <Wt/WProgressBar.h>
#include <Wt/WLineEdit.h>
#include <Wt/WApplication.h>

#include <Wtx/Sys/Log/Log.h>
#include <Wtx/Util/Util.h>
#include <Wtx/PopupMessage.h>
#include <Wtx/PopupYesNo.h>

#include "TableView.h"
#include "Util.h"

namespace {

class SmartString
: public std::string
{
  public:

    SmartString( const std::string & value )
    : std::string( value )
    {
    }

    bool ends( const std::string & value )
    {
      if( length() >= value.length() )
      {
        return ( 0 == compare(length() - value.length(), value.length(), value) );
      }
      else
      {
        return false;
      }
    }

};



class FileResource
: public Wt::WFileResource
{
  public:

    FileResource( const std::string & mimeType, const std::string & fileName )
    : Wt::WFileResource( mimeType, fileName )
    {
    }

    void handleRequest( const Wt::Http::Request & request, Wt::Http::Response & response )
    {
#ifdef NEVER
      std::cout << __FILE__ << ":" << __LINE__
        << " " << request.clientAddress()
        << " " << fileName()
        << std::endl;

      for( auto header : request.headers() )
      {
        std::cout << __FILE__ << ":" << __LINE__
          << " " << header.name() << "=" << header.value()
          << std::endl;
      }

      for( auto element : request.getParameterMap() )
      {
        for( auto second : element.second )
        {
          std::cout << __FILE__ << ":" << __LINE__
            << " " << element.first
            << "=" << second << std::endl;
        }
      }
#endif

      FolderExplorer::log( "download file", fileName() );

      Wt::WFileResource::handleRequest( request, response );
    }
};


} // endnamespace {

FolderExplorer::TableView::TableView()
: AbstractView( "","" )
{
  init();
  setRootFolder( "","" );
}

FolderExplorer::TableView::TableView( const std::string & rootPath, const std::string & alias )
: AbstractView( rootPath, alias )
{
  init();
  setRootFolder( rootPath, alias );
}

void FolderExplorer::TableView::init()
{
//  setOverflow( Wt::Overflow::Scroll );

  m_model = std::make_shared<Wt::WStandardItemModel>();

  auto lw = std::make_unique<Wt::WVBoxLayout>();

  m_title = lw-> addWidget( std::make_unique<Wt::WText>() );

  auto toolbar = lw-> addWidget( std::make_unique<Wt::WContainerWidget>() );

  toolbar-> addNew<Wt::WPushButton>("upload")->
    clicked().connect( this, &FolderExplorer::TableView::on_pbUploadFile_triggered );

  toolbar-> addNew<Wt::WPushButton>("new folder")->
    clicked().connect( this, &FolderExplorer::TableView::on_pbAddFolder_triggered );

  toolbar-> addNew<Wt::WPushButton>("delete")->
    clicked().connect( this, &FolderExplorer::TableView::on_pbDelete_triggered );

#ifdef NEVER
  toolbar-> addNew<Wt::WPushButton>("rename")->
    clicked().connect( this, &FolderExplorer::TableView::on_pbRename_triggered );
#endif

  toolbar-> addNew<Wt::WPushButton>("refresh")->
    clicked().connect( this, &FolderExplorer::TableView::refresh );

  m_pbSign = toolbar-> addNew<Wt::WPushButton>("eSign");
  m_pbSign-> clicked().connect( this, &FolderExplorer::TableView::on_eSign_triggered );
  m_pbSign-> setEnabled( false );

  m_table = lw-> addWidget( std::make_unique<Wt::WTableView>(), 1 );
  table()-> setModel( m_model );
  table()-> setSelectionMode( Wt::SelectionMode::Extended );
  table()-> clicked().connect(       this, &FolderExplorer::TableView::on_clicked_triggered       );
  table()-> doubleClicked().connect( this, &FolderExplorer::TableView::on_doubleClicked_triggered );

  setLayout( std::move(lw) );

} // endvoid FolderExplorer::TableView::init()

const Wt::WText * FolderExplorer::TableView::title() const
{
  return m_title;
}

Wt::WTableView * FolderExplorer::TableView::table()
{
  return m_table;
}

void FolderExplorer::TableView::setRootFolder( const std::string & rootPath, const std::string & alias )
{
  m_rootFolder = rootPath;

  if( alias == "" )
    m_title-> setText( rootPath );
  else
    m_title-> setText( alias );

#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << "\nrootPath:" << rootPath
    << "\nalias:"    << alias
    << std::endl
    ;
#endif

  setCurrentFolder( rootPath );

}

const std::string & FolderExplorer::TableView::rootFolder() const
{
  return m_rootFolder;
}

const std::string & FolderExplorer::TableView::currentFolder() const
{
  return m_currentFolder;
}

void FolderExplorer::TableView::setCurrentFolder( const std::string & value )
{
  m_currentFolder = value;
  refresh();

}

const std::vector< std::string > & FolderExplorer::TableView::hiddenFiles() const
{
  return m_hiddenFiles;
}

void FolderExplorer::TableView::setHiddenFiles( const std::vector< std::string > & value )
{
  m_hiddenFiles = value;
}


void FolderExplorer::TableView::refresh()
{

  /*
  ** Clear any resource objects.
  **
  */
  m_fileResources.clear();

  m_model-> clear();
  m_model-> insertColumns( 0, 3 );
  m_model-> setHeaderData( 0, Wt::Orientation::Horizontal, std::string("name")     );
  m_model-> setHeaderData( 1, Wt::Orientation::Horizontal, std::string("size")     );
  m_model-> setHeaderData( 2, Wt::Orientation::Horizontal, std::string("modified") );

  /*
  ** a folder must be specified, even if its the
  **  root folder
  **
  */
  if( currentFolder() == "" )
    return;

  /*
  ** if the new path ends with the .. back sequence,
  **  then move back a full directory
  **
  */
//  if( endsWith(   currentFolder(), "../" )
//  ||  beginsWith( currentFolder(), ".."  )
//  ||  contains(   currentFolder(), ".."  ) )
  if( contains( currentFolder(), ".." ) )
  {
    setCurrentFolder( upPath( currentFolder() ) );
    return;
  }

  /*
  ** get all the file items out of the folder.  This
  **  will include directories as well as regular files.
  **
  */
//  std::cout << __FILE__ << ":" << __LINE__ << " " << currentFolder() << std::endl;

  auto fileInfos = getFileInfo( currentFolder() );

  /*
  ** This is a little lambda function that will return
  **  .true. if this fileName is listed in the hiddenFiles
  **  list.  Hidden files are ignored and do not appear
  **  in the table view.
  **
  */
  auto _isHidden = [this]( const std::string & fileName )
  {
    for( auto hiddenFile : hiddenFiles() )
      if( fileName == hiddenFile )
        return true;

    return false;
  };

  /*
  ** Loop through each item to get the directories.
  **
  */
  for( auto fileInfo : fileInfos )
  {
    /*
    ** the double '..' dot items are 'up' folder items.
    **  we keep these when we are not at the root
    **  folder so the user can navigate up one folder.
    **
    */
#ifdef NEVER
    std::cout << __FILE__ << ":" << __LINE__
      << " '" << fileInfo.name() << "'"
      << " '" << rootFolder()    << "'"
      << " '" << currentFolder() << "'"
      << std::endl
      ;
#endif

    if( fileInfo.name() == ".." )
    {
#ifdef NEVER
      std::cout << __FILE__ << ":" << __LINE__
        << " root:" << rootFolder()
        << " curr:" << currentFolder()
        << std::endl;
#endif

      /*
      ** this is a crappy test for equality
      **
      */
      if( currentFolder() == rootFolder() + "/"
      ||  currentFolder() == rootFolder()  )
        continue;
    }

    /*
    ** if the fileInfo item is ~not~ a directory item
    **  then we ignore it.
    **
    */
    if( !fileInfo.isDir() )
      continue;

    /*
    ** If this file is among the list of files that are hidden
    **  then don't show it.
    **
    */
    if( _isHidden(fileInfo.name()) )
      continue;

    /*
    ** produce a table item that ~is~ the filename column
    **
    */
    auto fn = fileInfo.name();
    if( fn == ".." )
      fn += " (up folder)";

    auto fileNameItem = std::make_unique<Wt::WStandardItem>( Wt::WString( fn, Wt::CharEncoding::UTF8 ).toUTF8() );
//    auto fileNameItem = std::make_unique<Node>( Wt::WString( fn, Wt::CharEncoding::UTF8 ).toUTF8() );
    fileNameItem-> setIcon( "/resources/icons/yellow-folder-closed.png" );
    fileNameItem-> setStyleClass("linkstyle");
    fileNameItem-> setToolTip( fn );
    fileNameItem-> setData( "dir", Wt::ItemDataRole::User );

    auto fileSizeItem =
      std::make_unique<Wt::WStandardItem>
      (
       Wt::WString("{1}")
       .arg( fileInfo.size() )
       .toUTF8()
      );

    auto fileModifiedItem =
      std::make_unique<Wt::WStandardItem>
      (
       Wt::WString("{1}")
       .arg( fileInfo.mTime().toString("yyyy-MM-dd hh:mm:ss") )
       .toUTF8()
      );

    std::vector< std::unique_ptr<Wt::WStandardItem> > items;
    items.push_back( std::move(fileNameItem) );
    items.push_back( std::move(fileSizeItem) );
    items.push_back( std::move(fileModifiedItem) );

    m_model-> insertRow( m_model-> rowCount(), std::move(items) );

  } // endfor( auto fileInfo : fileInfos ) ** Loop through each item to get the directories.

  /*
  ** Loop through each item to get the FILE info.
  **
  */
  for( auto fileInfo : fileInfos )
  {
    /*
    ** if the fileInfo item is a directory item
    **  then we ignore it.
    **
    */
    if( fileInfo.isDir() )
      continue;

    /*
    ** If this file is among the list of files that are hidden
    **  then don't show it.
    **
    */
    if( _isHidden(fileInfo.name()) )
      continue;

    /*
    ** produce a table item that ~is~ the filename column
    **
    */
    auto fileNameItem = std::make_unique<Wt::WStandardItem>( Wt::WString( fileInfo.name(), Wt::CharEncoding::UTF8 ) );
    fileNameItem-> setToolTip( FolderExplorer::tooltip( currentFolder(), fileInfo.name() ) );
    fileNameItem-> setData( "file", Wt::ItemDataRole::User );

    /*
    ** file items have different icons depending on the
    **  content that they are and also have other attributes
    **  based on the fileName extension
    **
    */
    if( fileInfo.name().find(".png") != std::string::npos
    ||  fileInfo.name().find(".PNG") != std::string::npos
    ||  fileInfo.name().find(".jpg") != std::string::npos
    ||  fileInfo.name().find(".JPG") != std::string::npos  )
    {
      fileNameItem-> setIcon( "resources/icons/image2.png" );
    }
    else
    {
      if( fileInfo.name().find(".obj") != std::string::npos
      ||  fileInfo.name().find(".dsk") != std::string::npos
      ||  fileInfo.name().find(".exe") != std::string::npos  )
      {
        fileNameItem-> setIcon( "resources/icons/binary.png" );
      }
      else
      {
        fileNameItem-> setIcon( wApp-> bookmarkUrl() + "/resources/icons/generic.png" );
      }
    }

    /*
    ** make something that represents the full file path
    **
    */
    std::string filePath( currentFolder() + "/" + fileInfo.name() );

    /*
    ** By creating a WFileResource on the file name, we will be
    **  allowing a user to click on the file and 'download' it
    **  or view it in their browser.  These WFileResource items
    **  must be deleted later when the user changes folders
    **  so we push them back in to our vector so we can recall
    **  the pointer and properly delete it.  As long as the
    **  resources live in memory they can be called from any
    **  browser session, logged in or not.  The resource link
    **  address ends up looking something like this;
    **
    **  http://.../vault/Cell%20Snap%20at%20Night.jpg?wtd=SMTIqEnEfaoE3wQ5&request=resource&resource=o13nzs7&rand=19
    **
    ** This means that as long as a user keeps their browser open
    **  and logged in to the site, and also keeps this folder open,
    **  then the URL like the one shown above will be available
    **  and functional for anyone who navigates to it, but as soon
    **  as the browser is refreshed or the folder is changed and
    **  the resource is deleted, then the URL like the one shown
    **  above will no longer function and will produce the following
    **  message in the browser;
    **
    **  "Nothing to say about that."
    **
    */
    auto imgFile = std::make_shared<FileResource>("application/pdf", filePath );
    m_fileResources.push_back(imgFile);
    imgFile-> suggestFileName( fileInfo.name() );
    imgFile-> setMimeType( getMimeType(fileInfo.name()) );
    imgFile-> setDispositionType( Wt::ContentDisposition::Inline );
    auto link = Wt::WLink( imgFile );
    link.setTarget( Wt::LinkTarget::NewWindow );
    fileNameItem-> setLink( link );

    auto fileSizeItem =
      std::make_unique<Wt::WStandardItem>
      (
       Wt::WString("{1}")
       .arg( fileInfo.size() )
       .toUTF8()
      );

    auto fileModifiedItem =
      std::make_unique<Wt::WStandardItem>
      (
       Wt::WString("{1}")
       .arg( fileInfo.mTime().toString("yyyy-MM-dd hh:mm:ss") )
       .toUTF8()
      );

    std::vector< std::unique_ptr<Wt::WStandardItem> > items;
    items.push_back( std::move(fileNameItem) );
    items.push_back( std::move(fileSizeItem) );
    items.push_back( std::move(fileModifiedItem) );

    m_model-> insertRow( m_model-> rowCount(), std::move(items) );

  } // endfor( auto fileInfo : fileInfos ) ** Loop through each item to get the FILE info.


#ifdef NEVER
  td::string fn = "test";
  auto fileNameItem = std::make_unique<Wt::WStandardItem>( Wt::WString( fn, Wt::CharEncoding::UTF8 ) );
  fileNameItem-> setIcon( "resources/icons/small/folder.png" );
  fileNameItem-> setStyleClass("linkstyle");
  fileNameItem-> setToolTip( fn );

  auto fileSizeItem =
    std::make_unique<Wt::WStandardItem>
    (
     Wt::WString("{1}")
     .arg( 123 )
     .toUTF8()
    );

  auto fileModifiedItem =
    std::make_unique<Wt::WStandardItem>
    (
     Wt::WString("{1}")
     .arg( "yyyy-MM-dd hh:mm:ss" )
     .toUTF8()
    );

  std::vector< std::unique_ptr<Wt::WStandardItem> > items;
  items.push_back( std::move(fileNameItem) );
  items.push_back( std::move(fileSizeItem) );
  items.push_back( std::move(fileModifiedItem) );

  m_model-> insertRow( m_model-> rowCount(), std::move(items) );
#endif

  m_table-> setRowHeight( 30 );
  m_table-> setColumnWidth( 0, 300 );
  m_table-> setColumnWidth( 1,  75 );
  m_table-> setColumnWidth( 2, 150 );

} // endvoid FolderExplorer::TableView::refresh()



void FolderExplorer::TableView::on_pbNext_triggered()
{
  std::cout << __FILE__ << ":" << __LINE__ << std::endl;
}

void FolderExplorer::TableView::on_pbPrev_triggered()
{
  std::cout << __FILE__ << ":" << __LINE__ << std::endl;
}

void FolderExplorer::TableView::on_pbUploadFile_triggered()
{
  auto dialog = addChild( std::make_unique<Wt::WDialog>("Upload File") );

  dialog-> rejectWhenEscapePressed();
  dialog-> setTitleBarEnabled( true );
  dialog-> setClosable( true );
//  dialog-> setLayoutSizeAware( true );
  dialog-> setModal( true );
  dialog-> setResizable( true );
//  resize("50%", Wt::WLength::Auto);
  dialog-> setMaximumSize( Wt::WLength::Auto, "600px" );
//  setMinimumSize("310", Wt::WLength::Auto);

  auto templt = dialog-> contents()-> addNew<Wt::WTemplate>
  (
    "<div class=\"col-xs-12\">"
    "  <p>${upload}</p>"
    "  <p>${message}</p>"
    "  <div class=\"col-xs-12\">"
    "    <center>"
    "      ${dismiss}"
    "    </center>"
    "  </div>"
    "  <div class=\"clear\" />"
    "</div>"
  );

  templt-> bindNew<Wt::WPushButton>( "dismiss", "Dismiss" )-> clicked().connect( [=]()
  {
    removeChild( dialog );
  });

  templt-> bindNew<Wt::WText>( "message", "Choose your file to upload" );

  auto uploadWidget = templt-> bindNew<Wt::WFileUpload>( "upload" );
//  uploadWidget-> setFilters( ".bmp,.jpeg,.jpg,.xls,.xlsx,.doc,.docx,.odt,.txt,.pdf,.png,.rtf" );
  uploadWidget-> setMultiple( true );

  uploadWidget-> changed().connect( [=]()
  {
    auto progressBar = templt-> bindNew<Wt::WProgressBar>( "message" );
    progressBar-> setFormat( Wt::WString::Empty );
    progressBar-> setVerticalAlignment( Wt::AlignmentFlag::Middle );
    uploadWidget-> setProgressBar( progressBar );

    uploadWidget-> upload();
  });

  uploadWidget-> uploaded().connect( [=]()
  {
    for( auto uploadedFile : uploadWidget-> uploadedFiles() )
    {
      auto srcFile = uploadedFile.spoolFileName();
      auto dstFile = uploadedFile.clientFileName();

      if( srcFile == "" || dstFile == "" )
      {
        templt-> bindNew<Wt::WText>( "message", "oh oh, there was a problem with\n<br /> the upload.  Please try again." );
        return;
      }

#ifdef NEVER
      std::cout << __FILE__ << ":" << __LINE__
        << "\n rootPath:       " << rootPath()
        << "\n currentFolder:  " << currentFolder()
        << "\n spoolFileName:  " << uploadedFile.spoolFileName()
        << "\n clientFileName: " << uploadedFile.clientFileName()
        << "\n contentType:    " << uploadedFile.contentType()
        << std::endl;
#endif

      auto destination = currentFolder() + "/" + dstFile;
      {
        std::string cmd = "mv \"" + srcFile + "\" \"" + destination + "\"";
        Wtx::system_command( cmd );
      }

      {
        std::string cmd = "chmod 777 \"" + destination + "\"";
        Wtx::system_command( cmd );
      }

      log( "upload file", destination );

    } // endfor( auto uploadedFile : uploadWidget-> uploadedFiles() )

    refresh();

    templt-> bindNew<Wt::WText>( "message", Wt::WString("{1} Files Uploaded").arg( uploadWidget-> uploadedFiles().size() ) );
    templt-> bindEmpty( "upload" );

  });

  uploadWidget-> fileTooLarge() .connect( [=]()
  {
   templt-> bindNew<Wt::WText>( "message", "Oops, Your upload is too large." );

  });

  dialog-> show();

} // endvoid FolderExplorer::TableView::on_pbUploadFile_triggered()

void FolderExplorer::TableView::on_pbAddFolder_triggered()
{
  auto dialog = addChild( std::make_unique<Wt::WDialog>("New Folder") );

  dialog-> rejectWhenEscapePressed();
  dialog-> setTitleBarEnabled( true );
  dialog-> setClosable( true );
//  dialog-> setLayoutSizeAware( true );
  dialog-> setModal( true );
  dialog-> setResizable( true );
//  resize("50%", Wt::WLength::Auto);
  dialog-> setMaximumSize( Wt::WLength::Auto, "600px" );
//  setMinimumSize("310", Wt::WLength::Auto);

  auto templt = dialog-> contents()-> addNew<Wt::WTemplate>
  (
    "<div class=\"col-xs-12\">"
    "  <div>"
    "  <p>Create a folder</p>"
    "  ${input}"
    "  </div>"
    "  ${ok} ${cancel}"
    "  <div class=\"clear\" />"
    "</div>"
  );

  auto input = templt-> bindNew<Wt::WLineEdit>( "input" );

  templt-> bindNew<Wt::WPushButton>( "ok", "Ok" )->
    clicked().connect( [=]()
    {
      auto fileName = Wtx::makeFileName( input-> valueText().toUTF8() );

      if( fileName == "" )
      {
        dialog-> reject();
        return;
      }

      Wtx::system_command( Wt::WString("mkdir -p -m777 \"{1}\"").arg( currentFolder() + "/" + fileName ).toUTF8() );

      log( "add folder", currentFolder() + "/" + fileName );

      refresh();

      dialog-> reject();

    });

  templt-> bindNew<Wt::WPushButton>( "cancel", "Cancel" )->
    clicked().connect( dialog, &Wt::WDialog::reject );

  dialog-> show();
  dialog-> finished().connect( [=](){ removeChild( dialog ); });

} // endvoid FolderExplorer::TableView::on_pbAddFolder_triggered()

void FolderExplorer::TableView::on_pbDelete_triggered()
{
  if( table()-> selectedIndexes().size() == 0 )
  {
    Wtx::PopupMessage::show( "You must highlight a file before deleting" );
    return;
  }

  auto _doDelete = [=]()
  {
    for( auto selectedIndex : table()-> selectedIndexes() )
    {
      auto itemText =
        Wt::asString( selectedIndex.data() )
        .toUTF8()
        ;

      auto fileName = currentFolder() + "/" + itemText;

      if( Wt::asString( selectedIndex.data( Wt::ItemDataRole::User ) ) == "file" )
      {
//      std::cout << __FILE__ << ":" << __LINE__
//        << " currentFolder: " << currentFolder()
//        << " file:" << itemText
//        << std::endl;

        Wtx::system_command( "rm \"" + fileName + "\"" );

        log( "delete file", fileName );

      }

      if( Wt::asString( selectedIndex.data( Wt::ItemDataRole::User ) ) == "dir" )
      {

        Wtx::system_command( "rmdir \"" + fileName + "\"" );

        log( "delete folder", fileName );
      }

    } // endfor( auto selectedIndex : table()-> selectedIndexes() )

    refresh();

  };

  Wtx::PopupYesNo::ask( Wt::WString("Delete {1} selected items?").arg( table()-> selectedIndexes().size() ).toUTF8() )->
    answered().connect( [=]( Wt::StandardButton answer )
    {
      if( answer == Wt::StandardButton::Yes )
      {
        _doDelete();
      }

    });

} // endvoid FolderExplorer::TableView::on_pbDelete_triggered()

void FolderExplorer::TableView::on_pbRename_triggered()
{
  std::cout << __FILE__ << ":" << __LINE__ << std::endl;
}

void FolderExplorer::TableView::on_pbProperties_triggered()
{
  std::cout << __FILE__ << ":" << __LINE__ << std::endl;
}

void FolderExplorer::TableView::on_clicked_triggered( Wt::WModelIndex index, Wt::WMouseEvent event )
{
  if( table()-> selectedIndexes().size() != 1 )
    return;

  /*
  ** clicking on the file or folder
  **  name itself (the first column) does something.  But, also,
  **  clicking on one of the other columns signals the eSign
  **  module to engage.
  **
  */
  if( index.column() != 0 )
  {
    activate_esign();
    return;
  }

  auto selectedIndex =
    *(table()-> selectedIndexes().begin());

  auto itemtext =
    Wt::asString( selectedIndex.data() )
    .toUTF8()
    ;

#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << "\n rootFolder:" << rootFolder()
    << "\n currFolder:" << currentFolder()
    << "\n selectSize:" << table()-> selectedIndexes().size()
    << "\n selected:  " << itemtext
    << "\n type:      " << Wt::asString( selectedIndex.data( Wt::ItemDataRole::User ) )
    << std::endl;
#endif

  if( Wt::asString( selectedIndex.data( Wt::ItemDataRole::User ) ) == "file" )
  {
    m_fileClicked.emit( itemtext );
  }

  if( Wt::asString( selectedIndex.data( Wt::ItemDataRole::User ) ) == "dir" )
  {
    m_folderClicked.emit( itemtext );
  }

} // endvoid FolderExplorer::TableView::on_clicked_triggered()

void FolderExplorer::TableView::activate_esign( )
{
  auto selectedIndex =
    *(table()-> selectedIndexes().begin());

  SmartString fileName =
    Wt::asString( selectedIndex.data() )
    .toUTF8()
    ;

  std::cout << __FILE__ << ":" << __LINE__
    << " folder:'" << currentFolder() << "'"
    << " col:" << selectedIndex.column()
    << " text:'" << fileName << "'"
    << std::endl;

  bool enabled = false;

  /*
  ** The fileName must have both '2848' and
  **  and '.pdf' in it to enable the signature
  **  button.
  **
  */
  if( fileName.find( "2848" ) != std::string::npos
  &&  fileName.ends( ".pdf" )
    )
  {
    enabled = true;

    /*
    ** The fileName must _not_ have any other
    **  indicators that show the file is already
    **  signed (to prevent double-sigs)
    **
    */
    if( fileName.find( "IRS"    ) != std::string::npos
    ||  fileName.find( "ack"    ) != std::string::npos
    ||  fileName.find( "as of"  ) != std::string::npos
    ||  fileName.find( "signed" ) != std::string::npos
      )
    {
      enabled = false;
    }

  }

  m_pbSign-> setEnabled( enabled );
  m_pbSign-> setAttributeValue( "style", enabled? "background-color:aquamarine;color:red;":"" );


}

void FolderExplorer::TableView::on_doubleClicked_triggered( Wt::WModelIndex index, Wt::WMouseEvent event )
{
  if( table()-> selectedIndexes().size() != 1 )
    return;

  auto itemtext =
    Wt::asString
    (
      (*(table()-> selectedIndexes().begin())).data()
    )
    .toUTF8()
    ;

#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << "\n rootFolder:" << rootFolder()
    << "\n currFolder:" << currentFolder()
    << "\n selectSize:" << table()-> selectedIndexes().size()
    << "\n selected:  " << itemtext
    << std::endl;
#endif

  m_folderDoubleClicked.emit( itemtext );

  setCurrentFolder( currentFolder() + "/" + itemtext );
  refresh();

} // endvoid FolderExplorer::TableView::on_doubleClicked_triggered()

void FolderExplorer::TableView::on_eSign_triggered()
{
  if( table()-> selectedIndexes().size() != 1 )
    return;

  auto index = *(table()-> selectedIndexes().begin() );

  auto fileName = Wt::asString( index.data() ).toUTF8();

  m_eSignClicked.emit( currentFolder(), fileName );

}

Wt::Signal< std::string > & FolderExplorer::TableView::fileClicked()
{
  return m_fileClicked;
}

Wt::Signal< std::string > & FolderExplorer::TableView::folderClicked()
{
  return m_folderClicked;
}

Wt::Signal< std::string > & FolderExplorer::TableView::folderDoubleClicked()
{
  return m_folderDoubleClicked;
}

Wt::Signal< std::string, std::string > & FolderExplorer::TableView::eSignClicked()
{
  return m_eSignClicked;
}


