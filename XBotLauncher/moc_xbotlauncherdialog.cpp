/****************************************************************************
** XBotLauncherDialog meta object code from reading C++ file 'xbotlauncherdialog.h'
**
** Created: sab 2. apr 03:09:01 2005
**      by: The Qt MOC ($Id: $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "xbotlauncherdialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *XBotLauncherDialog::className() const
{
    return "XBotLauncherDialog";
}

QMetaObject *XBotLauncherDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_XBotLauncherDialog( "XBotLauncherDialog", &XBotLauncherDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString XBotLauncherDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "XBotLauncherDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString XBotLauncherDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "XBotLauncherDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* XBotLauncherDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = XBotLauncherDialogBase::staticMetaObject();
    static const QUMethod slot_0 = {"slotBuildDefault", 0, 0 };
    static const QUMethod slot_1 = {"slotStart", 0, 0 };
    static const QUMethod slot_2 = {"slotSaveConfig", 0, 0 };
    static const QUMethod slot_3 = {"slotChoosePath", 0, 0 };
    static const QUMethod slot_4 = {"slotQuit", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotBuildDefault()", &slot_0, QMetaData::Public },
	{ "slotStart()", &slot_1, QMetaData::Public },
	{ "slotSaveConfig()", &slot_2, QMetaData::Public },
	{ "slotChoosePath()", &slot_3, QMetaData::Public },
	{ "slotQuit()", &slot_4, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"XBotLauncherDialog", parentObject,
	slot_tbl, 5,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_XBotLauncherDialog.setMetaObject( metaObj );
    return metaObj;
}

void* XBotLauncherDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "XBotLauncherDialog" ) )
	return this;
    return XBotLauncherDialogBase::qt_cast( clname );
}

bool XBotLauncherDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotBuildDefault(); break;
    case 1: slotStart(); break;
    case 2: slotSaveConfig(); break;
    case 3: slotChoosePath(); break;
    case 4: slotQuit(); break;
    default:
	return XBotLauncherDialogBase::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool XBotLauncherDialog::qt_emit( int _id, QUObject* _o )
{
    return XBotLauncherDialogBase::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool XBotLauncherDialog::qt_property( int id, int f, QVariant* v)
{
    return XBotLauncherDialogBase::qt_property( id, f, v);
}

bool XBotLauncherDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
