/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 4.8.7
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtCore/qglobal.h>

static const unsigned char qt_resource_data[] = {
  // /home/users/work/tmp_suluyanove/SpotRecognition/config.txt
  0x0,0x0,0x0,0x27,
  0x2f,
  0x68,0x6f,0x6d,0x65,0x2f,0x75,0x73,0x65,0x72,0x73,0x2f,0x77,0x6f,0x72,0x6b,0x2f,
  0x73,0x75,0x6c,0x75,0x79,0x61,0x6e,0x6f,0x76,0x65,0x2f,0x76,0x69,0x64,0x65,0x6f,
  0x2e,0x6d,0x70,0x34,0xd,0xa,
  
};

static const unsigned char qt_resource_name[] = {
  // new
  0x0,0x3,
  0x0,0x0,0x74,0xc7,
  0x0,0x6e,
  0x0,0x65,0x0,0x77,
    // prefix1
  0x0,0x7,
  0x7,0x8b,0xd0,0x51,
  0x0,0x70,
  0x0,0x72,0x0,0x65,0x0,0x66,0x0,0x69,0x0,0x78,0x0,0x31,
    // config.txt
  0x0,0xa,
  0xc,0xf7,0x17,0x74,
  0x0,0x63,
  0x0,0x6f,0x0,0x6e,0x0,0x66,0x0,0x69,0x0,0x67,0x0,0x2e,0x0,0x74,0x0,0x78,0x0,0x74,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,
  // :/new
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x2,
  // :/new/prefix1
  0x0,0x0,0x0,0xc,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x3,
  // :/new/prefix1/config.txt
  0x0,0x0,0x0,0x20,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,

};

QT_BEGIN_NAMESPACE

extern Q_CORE_EXPORT bool qRegisterResourceData
    (int, const unsigned char *, const unsigned char *, const unsigned char *);

extern Q_CORE_EXPORT bool qUnregisterResourceData
    (int, const unsigned char *, const unsigned char *, const unsigned char *);

QT_END_NAMESPACE


int QT_MANGLE_NAMESPACE(qInitResources_path)()
{
    QT_PREPEND_NAMESPACE(qRegisterResourceData)
        (0x01, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_path))

int QT_MANGLE_NAMESPACE(qCleanupResources_path)()
{
    QT_PREPEND_NAMESPACE(qUnregisterResourceData)
       (0x01, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

Q_DESTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qCleanupResources_path))

