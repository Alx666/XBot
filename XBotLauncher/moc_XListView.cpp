/****************************************************************************
** XListView meta object code from reading C++ file 'XListView.h'
**
** Created: dom 17. ott 15:25:48 2004
**      by: The Qt MOC ($Id: $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "XListView.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.2.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *XListView::className() const
{
    return "XListView";
}

QMetaObject *XListView::metaObj = 0;
static QMetaObjectCleanUp cleanUp_XListView( "XListView", &XListView::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString XListView::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "XListView", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString XListView::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "XListView", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* XListView::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QListView::staticMetaObject();
    static const QUMethod slot_0 = {"slotEditItem", 0, 0 };
    static const QUMethod slot_1 = {"slotDeleteItem", 0, 0 };
    static const QUMethod slot_2 = {"slotAddItem", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotEditItem()", &slot_0, QMetaData::Public },
	{ "slotDeleteItem()", &slot_1, QMetaData::Public },
	{ "slotAddItem()", &slot_2, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"XListView", parentObject,
	slot_tbl, 3,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_XListView.setMetaObject( metaObj );
    return metaObj;
}

void* XListView::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "XListView" ) )
	return this;
    return QListView::qt_cast( clname );
}

bool XListView::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotEditItem(); break;
    case 1: slotDeleteItem(); break;
    case 2: slotAddItem(); break;
    default:
	return QListView::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool XListView::qt_emit( int _id, QUObject* _o )
{
    return QListView::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool XListView::qt_property( int id, int f, QVariant* v)
{
    return QListView::qt_property( id, f, v);
}

bool XListView::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
