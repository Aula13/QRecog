/****************************************************************************
** Meta object code from reading C++ file 'cameractrlview.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../project/cameractrlview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cameractrlview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CameraCtrlView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      44,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CameraCtrlView[] = {
    "CameraCtrlView\0\0on_btnStartCamera_clicked()\0"
    "on_btnStopCamera_clicked()\0"
};

void CameraCtrlView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CameraCtrlView *_t = static_cast<CameraCtrlView *>(_o);
        switch (_id) {
        case 0: _t->on_btnStartCamera_clicked(); break;
        case 1: _t->on_btnStopCamera_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CameraCtrlView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CameraCtrlView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CameraCtrlView,
      qt_meta_data_CameraCtrlView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CameraCtrlView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CameraCtrlView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CameraCtrlView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CameraCtrlView))
        return static_cast<void*>(const_cast< CameraCtrlView*>(this));
    return QWidget::qt_metacast(_clname);
}

int CameraCtrlView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
