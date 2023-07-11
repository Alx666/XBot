/****************************************************************************
** XBotLauncherDialogBase meta object code from reading C++ file 'xbotlauncherdialogbase.h'
**
** Created: sab 2. apr 03:09:01 2005
**      by: The Qt MOC ($Id: $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "xbotlauncherdialogbase.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *XBotLauncherDialogBase::className() const
{
    return "XBotLauncherDialogBase";
}

QMetaObject *XBotLauncherDialogBase::metaObj = 0;
static QMetaObjectCleanUp cleanUp_XBotLauncherDialogBase( "XBotLauncherDialogBase", &XBotLauncherDialogBase::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString XBotLauncherDialogBase::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "XBotLauncherDialogBase", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString XBotLauncherDialogBase::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "XBotLauncherDialogBase", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* XBotLauncherDialogBase::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"XBotLauncherDialogBase", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_XBotLauncherDialogBase.setMetaObject( metaObj );
    return metaObj;
}

void* XBotLauncherDialogBase::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "XBotLauncherDialogBase" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool XBotLauncherDialogBase::qt_invoke( int _id, QUObject* _o )
{
    return QDialog::qt_invoke(_id,_o);
}

bool XBotLauncherDialogBase::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool XBotLauncherDialogBase::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool XBotLauncherDialogBase::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
