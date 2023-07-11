/****************************************************************************
** LineEditEx meta object code from reading C++ file 'LineEditEx.h'
**
** Created: dom 10. apr 19:21:35 2005
**      by: The Qt MOC ($Id: $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "LineEditEx.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *LineEditEx::className() const
{
    return "LineEditEx";
}

QMetaObject *LineEditEx::metaObj = 0;
static QMetaObjectCleanUp cleanUp_LineEditEx( "LineEditEx", &LineEditEx::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString LineEditEx::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "LineEditEx", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString LineEditEx::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "LineEditEx", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* LineEditEx::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QLineEdit::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"LineEditEx", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_LineEditEx.setMetaObject( metaObj );
    return metaObj;
}

void* LineEditEx::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "LineEditEx" ) )
	return this;
    return QLineEdit::qt_cast( clname );
}

bool LineEditEx::qt_invoke( int _id, QUObject* _o )
{
    return QLineEdit::qt_invoke(_id,_o);
}

bool LineEditEx::qt_emit( int _id, QUObject* _o )
{
    return QLineEdit::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool LineEditEx::qt_property( int id, int f, QVariant* v)
{
    return QLineEdit::qt_property( id, f, v);
}

bool LineEditEx::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES


const char *XLCDNumber::className() const
{
    return "XLCDNumber";
}

QMetaObject *XLCDNumber::metaObj = 0;
static QMetaObjectCleanUp cleanUp_XLCDNumber( "XLCDNumber", &XLCDNumber::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString XLCDNumber::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "XLCDNumber", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString XLCDNumber::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "XLCDNumber", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* XLCDNumber::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QLCDNumber::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "n", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"display", 1, param_slot_0 };
    static const QMetaData slot_tbl[] = {
	{ "display(int)", &slot_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"XLCDNumber", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_XLCDNumber.setMetaObject( metaObj );
    return metaObj;
}

void* XLCDNumber::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "XLCDNumber" ) )
	return this;
    return QLCDNumber::qt_cast( clname );
}

bool XLCDNumber::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: display((int)static_QUType_int.get(_o+1)); break;
    default:
	return QLCDNumber::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool XLCDNumber::qt_emit( int _id, QUObject* _o )
{
    return QLCDNumber::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool XLCDNumber::qt_property( int id, int f, QVariant* v)
{
    return QLCDNumber::qt_property( id, f, v);
}

bool XLCDNumber::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
