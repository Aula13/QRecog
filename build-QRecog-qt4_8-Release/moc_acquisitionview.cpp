/****************************************************************************
** Meta object code from reading C++ file 'acquisitionview.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../project/acquisitionview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'acquisitionview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AcquisitionView[] = {

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
      17,   16,   16,   16, 0x08,
      46,   41,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AcquisitionView[] = {
    "AcquisitionView\0\0on_btnCapture_clicked()\0"
    "arg1\0on_checkBox_stateChanged(int)\0"
};

void AcquisitionView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AcquisitionView *_t = static_cast<AcquisitionView *>(_o);
        switch (_id) {
        case 0: _t->on_btnCapture_clicked(); break;
        case 1: _t->on_checkBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AcquisitionView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AcquisitionView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AcquisitionView,
      qt_meta_data_AcquisitionView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AcquisitionView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AcquisitionView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AcquisitionView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AcquisitionView))
        return static_cast<void*>(const_cast< AcquisitionView*>(this));
    return QWidget::qt_metacast(_clname);
}

int AcquisitionView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
