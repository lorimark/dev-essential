
#ifndef __FOLDEREXPLORER_UTIL_H___
#define __FOLDEREXPLORER_UTIL_H___

#include <sys/stat.h>

#include <Wt/WDate.h>
#include <Wt/WTime.h>
#include <Wt/WDateTime.h>
#include <Wt/WLocalDateTime.h>

namespace Wtx {
  namespace Sys {
    namespace Log {
      class Item;
    }
  }
}

namespace FolderExplorer {

std::string getMimeType( const std::string fileName );
std::string fixPath( const std::string path );
void split( const std::string & str, char delim, std::vector< std::string > & elems );
std::vector<std::string> split( const std::string & str, char delim );
std::string upPath( const std::string path );
bool contains( const std::string & inString, const std::string & containString );
bool beginsWith( const std::string & inString, const std::string & beginString );
bool endsWith( const std::string & inString, const std::string & endString );
std::string removeBadFileNameChars( const std::string & fileName );
std::string tooltip( const std::string & path, const std::string & filename );

class FileInfo
{
  public:
    FileInfo( const std::string & name, struct stat stat )
    {
      m_name = name;
      m_stat = stat;
    }

    const std::string & name() const
    {
      return m_name;
    }

    bool isDir() const
    {
      return S_ISDIR(m_stat.st_mode);
    }

    int size() const
    {
      return m_stat.st_size;
    }

    /*!
    ** \note this function requires that Wt::WLocale::setTimeZone be set
    **  in advance of using this function.
    **
    ** \code
    ** 148   #include <chrono>·
    ** 149   #include <Wt/Date/tz.h>·
    ** 150 ·
    ** 151   //·
    ** 152   // set the time-zone to the proper format
    ** 154   //·
    ** 155   auto loc = locale();·
    ** 156 ·
    ** 157   auto tz = date::locate_zone( environment().timeZoneName() );·
    ** 158 ·
    ** 159   loc.setTimeZone( tz );·
    ** 160 ·
    ** 161   std::cout << __FILE__ << ":" << __LINE__·
    ** 162     << " tzn:" << environment().timeZoneName()·
    ** 163     << " tzo:" << environment().timeZoneOffset().count()·
    ** 164     << " tz:" << tz·
    ** 165     << " loc:" << loc.name()·
    ** 166     << " ltz:" << loc.timeZone()-> name()·
    ** 167     << std::endl;·
    ** 168 ·
    ** 151   //·
    ** 152   // set the date format to regular american·
    ** 154   //·
    ** 169   loc.setDateFormat( "MM/dd/yyyy" );·
    ** 170   setLocale( loc );·
    ** 171 ·
    ** 172 } // endvoid Project::AppBase::init( )·
    ** \endcode
    **
    */
    Wt::WDateTime mTime() const
    {
      auto dateTime  = Wt::WDateTime::fromTime_t( m_stat.st_mtime );

      auto localTime = dateTime.toLocalTime();

      return Wt::WDateTime( localTime.date(), localTime.time() );
    }

    std::string m_name;
    struct stat m_stat;
};

/*
** This function produces a case-insensitive sort of
**  the files and folders in a directory.  The file
**  items are converted to upper-case so that case
**  becomes ignored, and then the function uses the
**  strverscmp function which causes jan-1, jan-2,
**  jan-10 to be sorted in that order, which can
**  make a little more logical sense when looking at
**  folder names.
**
** https://linux.die.net/man/3/scandir
**
*/
int ialphasort( const struct dirent **a, const struct dirent **b );

std::vector<FileInfo> getFileInfo( const std::string & folder );

/*!
** \brief Log Activity
**
** This function should be provided by the user
**
*/
Wt::Dbo::ptr<Wtx::Sys::Log::Item> log( const std::string & title, const std::string & message );

} // endnamespace



#endif // #ifndef __FOLDEREXPLORER_UTIL_H___


