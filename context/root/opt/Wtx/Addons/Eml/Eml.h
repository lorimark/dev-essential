/**************************************************************************
###########################################################################
##
## $SHOWOFFDB_BEGIN_LICENSE$
## Copyright (C) 2011 Lorimark Solutions, LLC and/or its subsidiary(-ies).
##  All rights reserved.
##  Contact: Lorimark Solutions, LLC (info@showoff-db.org)
##
## This file is part of the Showoff Database Application Framework.
##
##  Commercial Usage
##  Licensees holding valid ShowoffDB Commercial licenses may use this file in
##   accordance with the ShowoffDB Commercial License Agreement provided with the
##   Software or, alternatively, in accordance with the terms contained in
##   a written agreement between you and Lorimark Solutions, LLC.
##
## GNU Lesser General Public License Usage
##  Alternatively, this file may be used under the terms of the GNU Lesser
##   General Public License version 2.1 as published by the Free Software
##   Foundation and appearing in the file LICENSE.LGPL included in the
##   packaging of this file.  Please review the following information to
##   ensure the GNU Lesser General Public License version 2.1 requirements
##   will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
##
## In addition, as a special exception, Lorimark Solutions, LLC gives
##  you certain additional rights.  These rights are described in the
##  Lorimark Solutions, LLC ShowoffDB LGPL Exception version 1.0, included in
##  the file LGPL_EXCEPTION.txt in this package.
##
## GNU General Public License Usage
##  Alternatively, this file may be used under the terms of the GNU
##   General Public License version 3.0 as published by the Free Software
##   Foundation and appearing in the file LICENSE.GPL included in the
##   packaging of this file.  Please review the following information to
##   ensure the GNU General Public License version 3.0 requirements will be
##   met: http://www.gnu.org/copyleft/gpl.html.
##
## If you have questions regarding the use of this file, please contact
##   Lorimark Solutions, LLC at info@showoff-db.org.
## $SHOWOFFDB_END_LICENSE$
##
#############################################################################
****************************************************************************/

#ifndef __EML_H_76a1f4ca_4458_4c6c_b08a_33eeb94e60d1__
#define __EML_H_76a1f4ca_4458_4c6c_b08a_33eeb94e60d1__

#include <Wt/Dbo/ptr.h>

#include <Wtx/Sys/User/User.h>


namespace Wtx {

  /*!
  ** \brief Email Management
  **
  */
  namespace Eml {

void mapClasses();
void postCreateTables();

/*!
** \brief Current Session
**
** This is a function that needs to be provided by the application.
**  The session object is provided by the application and the
**  exact source of that session is not known by the subsystem
**  itself.
**
*/
Wtx::Dbo::Session * session();

/*!
** \brief Get Current User
**
** This is a function that needs to be provided by the application.
**  The system user object is provided by the application and the
**  exact source of that user is not known by the subsystem
**  itself.
**
** The function should be defined as follows:
** \code
** 2320 namespace Eml {
** 2321 Wt::Dbo::ptr< Wtx::Sys::User::Item > currentUser()
** 2322 {
** 2323   return myApp()-> session()-> user();
** 2324 }
** 2325 } // endnamespace Eml {
** \endcode
**
**
*/
Wt::Dbo::ptr< Wtx::Sys::User::Item > currentUser();

  } // endnamespace Eml
} // endnamespace Wtx

#endif // __EML_H___


