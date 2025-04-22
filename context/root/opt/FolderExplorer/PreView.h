
#ifndef __FOLDEREXPLORER_PREVIEW_H___
#define __FOLDEREXPLORER_PREVIEW_H___

#include "AbstractView.h"


namespace FolderExplorer {

class PreView
: public AbstractView
{
  public:

    PreView( const std::string & rootPath, const std::string & alias = "" );


}; // endclass PreView



} // endnamespace FolderExplorer


#endif


