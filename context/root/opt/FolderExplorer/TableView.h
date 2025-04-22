
#ifndef __FOLDEREXPLORER_TABLEVIEW_H___
#define __FOLDEREXPLORER_TABLEVIEW_H___

#include <Wt/WText.h>
#include <Wt/WTableView.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WStandardItem.h>
#include <Wt/WFileResource.h>

#include "AbstractView.h"
#include "Util.h"

namespace FolderExplorer {

class TableView
: public AbstractView
{
  public:

#ifdef NEVER
    class Node
    : public Wt::WStandardItem
    {
      public:

        Node( FileInfo & fileInfo );
        Node( const std::string & labelText, const std::string & alias = "" );
        const std::string & realLabel();
        const std::string & realLabel() const;
        std::string getFolderPath( const std::string & rootAlias = "" ) const;

      private:

        std::string m_labelText;
        FileInfo m_fileInfo;

    }; // endclass Node
#endif

    TableView();
    TableView( const std::string & rootPath, const std::string & alias = "" );

    const std::string & rootFolder() const;
    void setRootFolder( const std::string & rootPath, const std::string & alias = "" );

    const Wt::WText * title() const;
    Wt::WTableView * table();

    const std::vector< std::string > & hiddenFiles() const;
    void setHiddenFiles( const std::vector< std::string > & hiddenFiles );

    const std::string & currentFolder() const;
    void setCurrentFolder( const std::string & value );

    Wt::Signal< std::string > & rowClicked();
    Wt::Signal< std::string > & fileClicked();
    Wt::Signal< std::string > & folderClicked();
    Wt::Signal< std::string > & folderDoubleClicked();
    Wt::Signal< std::string, std::string > & eSignClicked();

    void refresh();

  private:

    void init();

    void on_pbNext_triggered();
    void on_pbPrev_triggered();
    void on_pbUploadFile_triggered();
    void on_pbAddFolder_triggered();
    void on_pbDelete_triggered();
    void on_pbRename_triggered();
    void on_pbProperties_triggered();
    void on_clicked_triggered( Wt::WModelIndex index, Wt::WMouseEvent event );
    void on_doubleClicked_triggered( Wt::WModelIndex index, Wt::WMouseEvent event );
    void on_eSign_triggered();

    void activate_esign();

    std::string m_rootFolder;
    std::string m_currentFolder;
    Wt::WText * m_title = nullptr;
    Wt::WTableView * m_table = nullptr;

    std::vector< std::string > m_hiddenFiles;
    std::vector< std::shared_ptr<Wt::WFileResource> > m_fileResources;
    std::shared_ptr<Wt::WStandardItemModel> m_model;

    Wt::WPushButton * m_pbSign = nullptr;

    Wt::Signal< std::string > m_rowClicked;
    Wt::Signal< std::string > m_fileClicked;
    Wt::Signal< std::string > m_folderClicked;
    Wt::Signal< std::string > m_folderDoubleClicked;
    Wt::Signal< std::string, std::string > m_eSignClicked;

}; // endclass TableView

} // endnamespace FolderExplorer


#endif // #ifndef __FOLDEREXPLORER_TABLEVIEW_H___


