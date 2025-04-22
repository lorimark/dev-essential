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


#include "Item.h"



Wtx::Web::BlogEntry::Definition::Definition()
: Wtx::Dbo::PermissionTableDef("webBlogEntry"),
  ParentMenuFieldDef(  *this, "parentMenux"   ),
  IsPageFieldDef(      *this, "isPage"       ),
  UrlFieldDef(         *this, "url"          ),
  DatePostedFieldDef(  *this, "datePosted"   ),
  SummaryFieldDef(     *this, "summary"      ),
  ThumbnailFieldDef(   *this, "thumbnail"    ),
  BodyFieldDef(        *this, "body"         )
{
  KeyFieldDef.setLabel( "Article Title" );
  CfyFieldDef.setLabel( "Categories"    );

}

static Wtx::Web::BlogEntry::Definition s_definition;

DBO_INSTANTIATE_TEMPLATES(Wtx::Web::BlogEntry::Item);

Wtx::Web::BlogEntry::Definition & Wtx::Web::BlogEntry::Item::s_tableDef = s_definition;


