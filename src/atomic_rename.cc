/* This file is (c) 2008-2011 Konstantin Isakov <ikm@users.berlios.de>
 * Part of GoldenDict. Licensed under GPLv3 or later, see the LICENSE file */

#include "atomic_rename.hh"
#include <QtGlobal>
#include <QVector>
#include <QFile>
#include <QDir>

#include <string> // for wchar_t
#ifdef Q_OS_WIN32
#include <windows.h>
#endif


bool renameAtomically( QString const & oldName, QString const & newName )
{
#ifdef Q_OS_WIN32

  QString srcFile( QDir::toNativeSeparators( oldName ) );
  QVector< wchar_t > srcFileW( srcFile.size() + 1 );
  srcFileW[ srcFile.toWCharArray( srcFileW.data() ) ] = 0;

  QString destFile( QDir::toNativeSeparators( newName ) );
  QVector< wchar_t > destFileW( destFile.size() + 1 );
  destFileW[ destFile.toWCharArray( destFileW.data() ) ] = 0;

  if ( !MoveFileExW( srcFileW.data(), destFileW.data(),  MOVEFILE_REPLACE_EXISTING ) )
    return false;

#else

  if ( rename( QFile::encodeName( QDir::toNativeSeparators( oldName ) ).data(),
               QFile::encodeName( QDir::toNativeSeparators( newName ) ).data() ) )
    return false;

#endif

  return true;
}
