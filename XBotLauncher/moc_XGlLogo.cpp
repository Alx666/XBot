/****************************************************************************
** XGlLogo meta object code from reading C++ file 'XGlLogo.h'
**
** Created: sab 2. apr 03:09:01 2005
**      by: The Qt MOC ($Id: $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "XGlLogo.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *XGlLogo::className() const
{
    return "XGlLogo";
}

QMetaObject *XGlLogo::metaObj = 0;
static QMetaObjectCleanUp cleanUp_XGlLogo( "XGlLogo", &XGlLogo::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString XGlLogo::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "XGlLogo", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString XGlLogo::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "XGlLogo", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* XGlLogo::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QGLWidget::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"XGlLogo", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_XGlLogo.setMetaObject( metaObj );
    return metaObj;
}

void* XGlLogo::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "XGlLogo" ) )
	return this;
    return QGLWidget::qt_cast( clname );
}

bool XGlLogo::qt_invoke( int _id, QUObject* _o )
{
    return QGLWidget::qt_invoke(_id,_o);
}

bool XGlLogo::qt_emit( int _id, QUObject* _o )
{
    return QGLWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool XGlLogo::qt_property( int id, int f, QVariant* v)
{
    return QGLWidget::qt_property( id, f, v);
}

bool XGlLogo::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
