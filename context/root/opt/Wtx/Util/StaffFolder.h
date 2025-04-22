
    /*
    ** \brief Client ID Part
    **
    ** This function constructs a string that appears as the id
    **  element that contains the name we are looking for.  The
    **  id element is a value that begins with " ~ C" (for customer)
    **  and then a leading-zero-padded numeric string.  This is
    **  usually enough to be able to track down a potentially
    **  lost client folder in event that someone renamed it.
    **
    ** \par Examples include:
    ** \code
    **   " ~ C012320"
    **   " ~ C045939"
    **   " ~ C020034"
    **   " ~ C200443"
    **   " ~ C520344"
    **    \v/v\--v-/
    **     | |   |
    **     | |   +---- clientId()
    **     | +-------- clientIdPrefix()
    **     +---------- separator
    ** \endcode
    **
    */

    /*
    ** \brief Client Folder Name
    **
    ** This function calculates what the client folder name
    **  should be.
    **
    ** \par Examples include:
    ** \code
    **  AAA (AAA VACUUM) ~ C006585
    **  ADVANCE (ADVANCE MFG INC) ~ C006767
    **  ALB (ALBERT J ANGEL) ~ C000005
    **  ALF (AMPAK COMPANY INC) ~ C002885
    **  DATA (DATA OPTICS CABLE INC) ~ C002247
    **  DEIROSSI (DEIROSSI-TRAVELOCITY) ~ C005227
    **  DEKO (DEKO INTERNATIONAL CO) ~ C001319
    **  DSI (DTI DIRECT) ~ C006488
    **  DYNE (DYNE INDUSTRIES) ~ C006166
    **  DYNE IND (DYNE INDUSTRIES) ~ C005418
    **  SOLO (SOLO CUP) ~ C002094
    **  SOP (SOPREMA INC) ~ C000030
    **  STAY (STAY WELL INC) ~ C002876
    **  \-v-/ \-----v-----/  \----v---/
    **    |         |             |
    **    |         |             +------------ clientIdPart()
    **    |         +-------------------------- name()
    **    +------------------------------------ key()
    ** \endcode
    **
    */

    /*
    ** \brief Folder Path
    **
    ** The folder is more-or-less an absolute path
    **  of the hard-drive.
    **
    ** \par Examples include:
    ** \code
    **  approot/customer/A/AAA (AAA VACUUM) ~ C006585
    **  approot/customer/A/ADVANCE (ADVANCE MFG INC) ~ C006767
    **  approot/customer/A/ALB (ALBERT J ANGEL) ~ C000005
    **  approot/customer/A/ALF (AMPAK COMPANY INC) ~ C002885
    **  approot/customer/D/DATA (DATA OPTICS CABLE INC) ~ C002247
    **  approot/customer/D/DEIROSSI (DEIROSSI-TRAVELOCITY) ~ C005227
    **  approot/customer/D/DEKO (DEKO INTERNATIONAL CO) ~ C001319
    **  approot/customer/D/DSI (DTI DIRECT) ~ C006488
    **  approot/customer/D/DYNE (DYNE INDUSTRIES) ~ C006166
    **  approot/customer/D/DYNE IND (DYNE INDUSTRIES) ~ C005418
    **  approot/customer/S/SOLO (SOLO CUP) ~ C002094
    **  approot/customer/S/SOP (SOPREMA INC) ~ C000030
    **  approot/customer/S/STAY (STAY WELL INC) ~ C002876
    **  \-------v------/ v \-v-/ \-----v-----/  \----v---/
    **          |        |   |         |             |
    **          |        |   |         |             +------------ clientIdPart()
    **          |        |   |         +-------------------------- name()
    **          |        |   +------------------------------------ key()
    **          |        +---------------------------------------- fileCode()
    **          +------------------------------------------------- rootPath()
    ** \endcode
    **
    */

#ifndef __WTX_CLIENTFOLDER_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_CLIENTFOLDER_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <string>
#include <vector>

namespace Wtx {

/*!
** \brief Client Folder
**
** This object encapsulates a handful of functions that can be used
**  to manipulate and interact with client folders that are stored
**  on disk somewhere.
**
** What this object does is take some of the elements of the client
**  file and construct some disk-compatible file-name strings.  The
**  reason we want these to be disk-compatible is we are going to make
**  a client folder out of these values, and we don't want any funky
**  characters in them.
**
** This object also contains disk-folder manipulation functions for
**  creating and maintaining client folders.  Where this can be very
**  useful is on a file-system where users have access to changing
**  the folder names (they shouldn't, but sometimes they do) and
**  these functions will locate client folders that have been renamed
**  for some reason and will help in getting the names set back to
**  what they should be.
**
** The overall objective is to provide for a common disk-compatible
**  client file naming system, that organizes disk-files in a similar
**  manner to the database itself.
**
** \image html WtxClientFolderSample.png
**
**
** \par Usage Example:
** \code
**   #include <Wtx/Util/ClientFolder.h>
**   Wtx::ClientFolder clientFolder
**   (
**    (int)customerItem.id(),               // customerItem ID
**    m_customerItem-> keyField().value(),  // keyField (abbreviation)
**    m_customerItem-> cfyField().value()   // cfyField (full name)
**   );
**
** \endcode
**
** The result of constructing this object with the values above facilitates
**  extracting the various folder properties, such as the root portion of
**  the file path, and the various elements that make it all up.
**
** \code
**           +-------------------------------------------------: fileParent()       // includes the 'S' of the folder
**           |                        +------------------------: filePath()         // just the part beginning with 'S'
**  /--------^-------\                |
**  |                /----------------^------------------\
**  |                |                +------------------------: fileFolder()       // just the folder part after the 'S'
**  |                |                |           +------------: fileCode()         // the ID/Code with Prefix and Suffix
**  |                |                |           |
**  |                |                |    /------^------\
**  |                ^ /--------------^------------------\
**  approot/customer/S/STAY (STAY WELL INC) ~~ C0002876 ~~  <--: fileAbsolutePath() // the whole path
**  \-------v------/ v \-v-/ \-----v-----/ \-v-/\--v--/\v/
**          |        |   |         |         |     |    |
**          |        |   |         |         |     |    +------: idSuffix()         // thing to put after the ID
**          |        |   |         |         |     +-----------: fileId()           // just the ID with the prefix and prepend
**          |        |   |         |         +-----------------: idPrefix()         // prefix-separator
**          |        |   |         +---------------------------: fileName()         // the 'full-client-name' of the file
**          |        |   +-------------------------------------: fileKey()          // the 'abbreviated-client-name' of the file
**          |        +-----------------------------------------: fileChar()         // the first letter of the abbreviation
**          +--------------------------------------------------: fileRoot()         // the root path
** \endcode
**
**
** \par A Practical Example
** \code
**   322       Wtx::ClientFolder clientFolder
**   323       (
**   324        (int)m_customerItem.id(),             // customerItem ID
**   325        m_customerItem-> keyField().value(),  // keyField (abbreviation)
**   326        m_customerItem-> cfyField().value()   // cfyField (full name)
**   327       );
**   328
**   329       std::cout << __FILE__ << ":" << __LINE__ << " "
**   330         << "\n rootPath:"         << clientFolder.rootPath()
**   331         << "\n idPrefix:"         << clientFolder.idPrefix()
**   332         << "\n idLength:"         << clientFolder.idLength()
**   333         << "\n idSuffix:"         << clientFolder.idSuffix()
**   334         << "\n idPadding:"        << clientFolder.idPadding()
**   335         << "\n isValid:"          << clientFolder.isValid()
**   336         << "\n uid:"              << clientFolder.uid()
**   337         << "\n key:"              << clientFolder.key()
**   338         << "\n name:"             << clientFolder.name()
**   339         << "\n fileParent:"       << clientFolder.fileParent()
**   340         << "\n filePath:"         << clientFolder.filePath()
**   341         << "\n fileFolder:"       << clientFolder.fileFolder()
**   342         << "\n fileAbsolutePath:" << clientFolder.fileAbsolutePath()
**   343         << "\n fileAbsolutePath:" << clientFolder.fileAbsolutePath("invoices")
**   344         << "\n fileId:"           << clientFolder.fileId()
**   345         << "\n fileCode:"         << clientFolder.fileCode()
**   346         << "\n fileKey:"          << clientFolder.fileKey()
**   347         << "\n fileChar:"         << clientFolder.fileChar()
**   348         << "\n fileRoot:"         << clientFolder.fileRoot()
**   349         << std::endl;
**
**   Produces the following output:
**
**   /home/mark/projects/clients/ABC/warehouse/src/Company/ManagerWidget.cpp:329
**     rootPath:approot/clients
**     idPrefix: ~~ C
**     idLength:6
**     idSuffix: ~~
**     idPadding:0
**     isValid:1
**     uid:5
**     key:AIC
**     name:AMERICAN INTERNATIONAL CHEMICAL
**     fileParent:approot/clients/A
**     filePath:A/AIC (AMERICAN INTERNATIONAL CHEMICAL) ~~ C000005 ~~
**     fileFolder:AIC (AMERICAN INTERNATIONAL CHEMICAL) ~~ C000005 ~~
**     fileAbsolutePath:approot/clients/A/AIC (AMERICAN INTERNATIONAL CHEMICAL) ~~ C000005 ~~
**     fileAbsolutePath:approot/clients/A/AIC (AMERICAN INTERNATIONAL CHEMICAL) ~~ C000005 ~~/invoices
**     fileId:000005
**     fileCode: ~~ C000005 ~~
**     fileKey:AIC
**     fileChar:A
**     fileRoot:approot/clients
**
** \endcode
**
** \note This object employs real simple (aka; dumb) string manipulation
**  to generate path strings.  Pay attention to NOT sending extra '/'
**  characters as part of the object initialization.
**
*/
class ClientFolder
: public Wt::WObject
{
  public:

    ClientFolder();

    ClientFolder
    (
     int uid,
     const std::string & key,
     const std::string & name
    );

    ClientFolder
    (
     const std::string & uid,
     const std::string & key,
     const std::string & name
    );

    ClientFolder( const ClientFolder & copy );

    /*!
    ** \brief Setup Global Static
    **
    ** This functions sets up the global settings for this object.
    **  This function should be called at the start of program launch,
    **  perhaps in the main() function.  Once set, these values will be
    **  used by all instances of the object.
    **
    ** \par Initialization example - tests for folder availability
    ** \code
    ** 36 //
    ** 37 // This is the location of the client file folders.  This location is intended to
    ** 38 //  be a smb:mount to the remote server where the files are being stored.  If
    ** 39 //  at any time this mount becomes disconnected, the application should
    ** 40 //  detect this condition and warn the user.
    ** 41 //
    ** 43 #define CLIENT_FOLDERS "/mnt/client/warehouse/remoteserver/ClientFiles"
    ** 44 #define CLIENT_FOLDERS_FALLBACK "approot/clients"
    ** 45
    **
    ** 3965   if( Wtx::fileExists( CLIENT_FOLDERS ) )
    ** 3966   {
    ** 3967     Wtx::ClientFolder::setup
    ** 3968     (
    ** 3969      CLIENT_FOLDERS,                   // set value
    ** 3970      Wtx::ClientFolder::idPrefix(),    // keep default
    ** 3971      Wtx::ClientFolder::idLength(),    // keep default
    ** 3972      Wtx::ClientFolder::idPadding(),   // keep default
    ** 3973      Wtx::ClientFolder::idSuffix()     // keep default
    ** 3974     );
    ** 3975   }
    ** 3976   else
    ** 3977   {
    ** 3978     layout-> addWidget
    ** 3979     (
    ** 3980      std::make_unique<Wt::WText>
    ** 3981      (
    ** 3982       Wt::WString::tr("Warehouse.client-folders-do-not-exist")
    ** 3983       .arg(CLIENT_FOLDERS)
    ** 3984      )
    ** 3985     );
    ** 3986
    ** 3987     Wtx::ClientFolder::setup
    ** 3988     (
    ** 3989      CLIENT_FOLDERS_FALLBACK,
    ** 3990      Wtx::ClientFolder::idPrefix(),
    ** 3991      Wtx::ClientFolder::idLength(),
    ** 3992      Wtx::ClientFolder::idPadding(),
    ** 3993      Wtx::ClientFolder::idSuffix()
    ** 3994     );
    ** 3995   }
    ** 3996
    ** \endcode
    **
    **
    */
    static void setup
    (

     /*!
     ** Base Path to the point where client char folders will
     **  be created.  This path should ~not~ end with a '/' (forward
     **  slash) character... the folder separator '/' gets added as
     **  needed as the object is called upon.  Remember that this
     **  object uses real simple string manipulation, and does not
     **  search for things like '//' in the middle of the string,
     **  so pay attention to what's being sent to the rootPath.
     **
     */
     const std::string & rootPath,

     /*!
     ** String of characters that are prepended to the client 'ID'
     **  value.  This setting helps force a fixed-known set of
     **  characters that appear immediately in front of the ID value
     **  such that in the event that the folder is accidently renamed
     **  that it can be relocated.  The flip side of this issue is
     **  if the client itself is renamed, then any client folders
     **  that were previously created need to be renamed to match.
     **  By providing an ID-Prefix to the file name, it becomes
     **  possible to scan the client folders for the encoded ID
     **  value, and rename the folder to properly match what's in
     **  the database.
     **
     */
     const std::string & idPrefix,

     /*!
     ** It is possible to control the overall length of the client
     **  ID that is represented on the disk folder.  This value,
     **  used in conjunction with the 'padding' value causes the
     **  ID to be padded and filled to match this length.
     **
     */
     int idLength,

     /*!
     ** This is a single padding character that is used to fill ID
     **  numbers.
     **
     */
     char idPadding,

     /*!
     ** This value follows the ID value.  The combination of idPrefix()
     **  and the idSuffix() improves the ability to identify disconnected
     **  and misnamed file folders.
     **
     */
     const std::string & idSuffix

    ); // endstatic void setup

    /*!
    ** \brief Root Path
    **
    ** This returns the static value to the root path of the file system.
    **
    ** \note This value should ~not~ end with the forward slash '/'
    **
    */
    static std::string & rootPath();

    /*!
    ** \brief ID Prefix
    **
    ** This string value is placed in the front of the ID string.
    **
    */
    static std::string & idPrefix();

    /*!
    ** \brief ID Length
    **
    ** This determines how many characters the ID value should occupy.  When
    **  the resulting ID value is short, it is padded to reach this length.
    **
    */
    static int idLength();

    /*!
    ** \brief ID Suffix
    **
    ** This string value is placed immediately after the ID string.
    **
    */
    static std::string & idSuffix();

    /*!
    ** \brief ID Padding
    **
    ** This is the single-character that is used to pad the ID value
    **  when it is shorted than the idLength().
    **
    */
    static char idPadding();

    /*!
    ** \brief Is Valid
    **
    ** This indicates .true. when the object has been properly initialized
    **  by the proper constructor.
    **
    */
    bool isValid() const;

    /*!
    ** \brief Unique ID
    **
    ** This is a string representation of the ID value that was provided
    **  by the constructor.
    **
    */
    const std::string & uid() const;

    /*!
    ** \brief Key Value
    **
    ** This is the original KEY value that was provided by the caller.
    **
    */
    const std::string & key() const;

    /*!
    ** \brief Name Value
    **
    ** This is the orignial NAME value that was provided by the caller.
    **
    */
    const std::string & name() const;

    /*!
    ** \brief File Parent
    **
    ** This is the parent portion of the folder path.  This value includes
    **  the single-letter value that identifies the root element to where
    **  the client folder is going to exist.  It is possible to provide
    **  a sub-folder element to this call and it will be appended to the
    **  return value as a convenience feature.
    **
    */
    std::string fileParent( const std::string & subFolder = "" ) const;

    /*!
    ** \brief File Path
    **
    ** This is the client sub folder element of the client folder.  This
    **  value also includes the single-character group folder.
    **
    */
    std::string filePath( const std::string & subFolder = "" ) const;

    /*!
    ** \brief File Folder
    **
    ** This is the portion of the folder that is ~only~ the elements that
    **  include only the client info.  This does not include the
    **  single-character group folder.
    **
    */
    std::string fileFolder( const std::string & subFolder = "" ) const;

    /*!
    ** \brief File Absolute Path
    **
    ** This is the client folder absolute path.  This includes everything
    **  up to the end of the folder (without the appended '/' forward
    **  slash.  As a matter of convenience a subFolder parameter can be
    **  provided, and it will be appended with a '/' slash-separator
    **
    */
    std::string fileAbsolutePath( const std::string & subFolder = "" ) const;

    /*!
    ** \brief Field ID
    **
    ** The Formatted File ID
    **
    */
    std::string fileId() const;

    /*!
    ** \brief File Code
    **
    ** This is the portion of the client folder that contains the prefix
    **  formatted ID and suffix.
    **
    */
    std::string fileCode() const;

    /*!
    ** \brief File Name
    **
    ** This is the reformatted File Name.
    **
    */
    std::string fileName() const;

    /*!
    ** \brief File Key
    **
    ** This is the reformatted File Key.
    **
    */
    std::string fileKey() const;

    /*!
    ** \brief File Character
    **
    ** This is the File single-letter character
    **
    */
    std::string fileChar() const;

    /*!
    ** \brief File Root
    **
    ** This is the root folder.  This allows for a sub-folder to be passed in,
    **  and this function will insure it is appended properly.
    **
    */
    std::string fileRoot( const std::string & subFolder = "" ) const;

    /*!
    ** \brief Folder
    **
    ** This is an internal function that is used to append one string to
    **  another with the '/' delimiter.
    **
    */
    static std::string folder( const std::string & base, const std::string & sub );

  private:

    static std::string s_rootPath;
    static std::string s_idPrefix;
    static int         s_idLength;
    static char        s_idPadding;
    static std::string s_idSuffix;

    bool m_isValid;
    std::string m_uid;
    std::string m_key;
    std::string m_name;

}; // endclass ClientFolder

} // endnamespace Wtx

#endif // #ifndef __WTX_CLIENTFOLDER_H___


