/****************************************************************************
** Meta object code from reading C++ file 'backupmanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/backup/backupmanager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backupmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN13BackupManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto BackupManager::qt_create_metaobjectdata<qt_meta_tag_ZN13BackupManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "BackupManager",
        "backupSavedToFile",
        "",
        "filename",
        "backupFailed",
        "FailReason",
        "reason",
        "backupTimerChanged",
        "backupStarting",
        "storageFolderItemsChanged",
        "backupFileDeleted",
        "setLimitStorageFolderSize",
        "state",
        "setLimitStorageFolderItemAge",
        "setLimitStorageFolderItemCount",
        "setMaximumStorageFolderSize",
        "qsizetype",
        "maxSizeInMib",
        "setMaximumStorageFolderItemCount",
        "count",
        "setMaximumStorageFolderItemAgeInDays",
        "days",
        "scheduleBackup",
        "setBackupStorageFolder",
        "folder",
        "setEnableTimedBackups",
        "setBackupTimerIgnoresOtherEvents"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'backupSavedToFile'
        QtMocHelpers::SignalData<void(QString)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'backupFailed'
        QtMocHelpers::SignalData<void(enum FailReason)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Signal 'backupTimerChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'backupStarting'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'storageFolderItemsChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'backupFileDeleted'
        QtMocHelpers::SignalData<void(QString)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Slot 'setLimitStorageFolderSize'
        QtMocHelpers::SlotData<void(bool)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 12 },
        }}),
        // Slot 'setLimitStorageFolderItemAge'
        QtMocHelpers::SlotData<void(bool)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 12 },
        }}),
        // Slot 'setLimitStorageFolderItemCount'
        QtMocHelpers::SlotData<void(bool)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 12 },
        }}),
        // Slot 'setMaximumStorageFolderSize'
        QtMocHelpers::SlotData<void(qsizetype)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 16, 17 },
        }}),
        // Slot 'setMaximumStorageFolderItemCount'
        QtMocHelpers::SlotData<void(int)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 19 },
        }}),
        // Slot 'setMaximumStorageFolderItemAgeInDays'
        QtMocHelpers::SlotData<void(int)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 21 },
        }}),
        // Slot 'scheduleBackup'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setBackupStorageFolder'
        QtMocHelpers::SlotData<void(QString)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 24 },
        }}),
        // Slot 'setEnableTimedBackups'
        QtMocHelpers::SlotData<void(bool)>(25, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 12 },
        }}),
        // Slot 'setBackupTimerIgnoresOtherEvents'
        QtMocHelpers::SlotData<void(bool)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 12 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<BackupManager, qt_meta_tag_ZN13BackupManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject BackupManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13BackupManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13BackupManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13BackupManagerE_t>.metaTypes,
    nullptr
} };

void BackupManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<BackupManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->backupSavedToFile((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->backupFailed((*reinterpret_cast<std::add_pointer_t<enum FailReason>>(_a[1]))); break;
        case 2: _t->backupTimerChanged(); break;
        case 3: _t->backupStarting(); break;
        case 4: _t->storageFolderItemsChanged(); break;
        case 5: _t->backupFileDeleted((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->setLimitStorageFolderSize((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->setLimitStorageFolderItemAge((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: _t->setLimitStorageFolderItemCount((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 9: _t->setMaximumStorageFolderSize((*reinterpret_cast<std::add_pointer_t<qsizetype>>(_a[1]))); break;
        case 10: _t->setMaximumStorageFolderItemCount((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->setMaximumStorageFolderItemAgeInDays((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->scheduleBackup(); break;
        case 13: _t->setBackupStorageFolder((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->setEnableTimedBackups((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 15: _t->setBackupTimerIgnoresOtherEvents((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (BackupManager::*)(QString )>(_a, &BackupManager::backupSavedToFile, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (BackupManager::*)(FailReason )>(_a, &BackupManager::backupFailed, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (BackupManager::*)()>(_a, &BackupManager::backupTimerChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (BackupManager::*)()>(_a, &BackupManager::backupStarting, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (BackupManager::*)()>(_a, &BackupManager::storageFolderItemsChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (BackupManager::*)(QString )>(_a, &BackupManager::backupFileDeleted, 5))
            return;
    }
}

const QMetaObject *BackupManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BackupManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13BackupManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BackupManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void BackupManager::backupSavedToFile(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void BackupManager::backupFailed(FailReason _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void BackupManager::backupTimerChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void BackupManager::backupStarting()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void BackupManager::storageFolderItemsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void BackupManager::backupFileDeleted(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}
QT_WARNING_POP
