/****************************************************************************
** Meta object code from reading C++ file 'bedrockserver.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/server/bedrockserver.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bedrockserver.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13BedrockServerE_t {};
} // unnamed namespace

template <> constexpr inline auto BedrockServer::qt_create_metaobjectdata<qt_meta_tag_ZN13BedrockServerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "BedrockServer",
        "serverStateChanged",
        "",
        "BedrockServer::ServerState",
        "newState",
        "serverOutput",
        "BedrockServer::OutputType",
        "type",
        "outputLine",
        "backupStarting",
        "backupStarted",
        "backupInProgres",
        "backupSavingData",
        "backupFinishedOnServer",
        "backupFailed",
        "backupFinished",
        "zipFilePath",
        "backupComplete",
        "playerConnected",
        "name",
        "xuid",
        "playerDisconnected",
        "serverDifficulty",
        "ServerDifficulty",
        "difficulty",
        "serverPermissionList",
        "ops",
        "members",
        "visitors",
        "serverPermissionsChanged",
        "serverWhitelist",
        "serverStatusLine",
        "status",
        "serverConfigurationUpdated",
        "shutdownServerIn",
        "seconds",
        "scheduleBackup",
        "startBackup",
        "completeBackup",
        "startServer",
        "startServerAfter",
        "ms",
        "restartServerAfter",
        "stopServer",
        "stopAndRestartServer",
        "sendCommandToServer",
        "command",
        "setDifficulty",
        "saveConfiguration",
        "handleServerOutput",
        "handleZipComplete"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'serverStateChanged'
        QtMocHelpers::SignalData<void(BedrockServer::ServerState)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'serverOutput'
        QtMocHelpers::SignalData<void(BedrockServer::OutputType, QString)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 }, { QMetaType::QString, 8 },
        }}),
        // Signal 'backupStarting'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'backupStarted'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'backupInProgres'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'backupSavingData'
        QtMocHelpers::SignalData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'backupFinishedOnServer'
        QtMocHelpers::SignalData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'backupFailed'
        QtMocHelpers::SignalData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'backupFinished'
        QtMocHelpers::SignalData<void(QString)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 16 },
        }}),
        // Signal 'backupComplete'
        QtMocHelpers::SignalData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'playerConnected'
        QtMocHelpers::SignalData<void(QString, QString)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 19 }, { QMetaType::QString, 20 },
        }}),
        // Signal 'playerDisconnected'
        QtMocHelpers::SignalData<void(QString, QString)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 19 }, { QMetaType::QString, 20 },
        }}),
        // Signal 'serverDifficulty'
        QtMocHelpers::SignalData<void(enum ServerDifficulty)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 23, 24 },
        }}),
        // Signal 'serverPermissionList'
        QtMocHelpers::SignalData<void(QStringList, QStringList, QStringList)>(25, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QStringList, 26 }, { QMetaType::QStringList, 27 }, { QMetaType::QStringList, 28 },
        }}),
        // Signal 'serverPermissionsChanged'
        QtMocHelpers::SignalData<void()>(29, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'serverWhitelist'
        QtMocHelpers::SignalData<void(QStringList)>(30, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QStringList, 27 },
        }}),
        // Signal 'serverStatusLine'
        QtMocHelpers::SignalData<void(QString)>(31, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 32 },
        }}),
        // Signal 'serverConfigurationUpdated'
        QtMocHelpers::SignalData<void()>(33, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'shutdownServerIn'
        QtMocHelpers::SignalData<void(int)>(34, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 35 },
        }}),
        // Slot 'scheduleBackup'
        QtMocHelpers::SlotData<void()>(36, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'startBackup'
        QtMocHelpers::SlotData<void()>(37, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'completeBackup'
        QtMocHelpers::SlotData<void()>(38, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'startServer'
        QtMocHelpers::SlotData<void()>(39, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'startServerAfter'
        QtMocHelpers::SlotData<void(int)>(40, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 41 },
        }}),
        // Slot 'restartServerAfter'
        QtMocHelpers::SlotData<void(int)>(42, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 41 },
        }}),
        // Slot 'stopServer'
        QtMocHelpers::SlotData<void()>(43, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'stopAndRestartServer'
        QtMocHelpers::SlotData<void()>(44, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'sendCommandToServer'
        QtMocHelpers::SlotData<void(QString)>(45, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 46 },
        }}),
        // Slot 'setDifficulty'
        QtMocHelpers::SlotData<void(int)>(47, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 24 },
        }}),
        // Slot 'saveConfiguration'
        QtMocHelpers::SlotData<void()>(48, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'handleServerOutput'
        QtMocHelpers::SlotData<void()>(49, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleZipComplete'
        QtMocHelpers::SlotData<void()>(50, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<BedrockServer, qt_meta_tag_ZN13BedrockServerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject BedrockServer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13BedrockServerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13BedrockServerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13BedrockServerE_t>.metaTypes,
    nullptr
} };

void BedrockServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<BedrockServer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->serverStateChanged((*reinterpret_cast<std::add_pointer_t<BedrockServer::ServerState>>(_a[1]))); break;
        case 1: _t->serverOutput((*reinterpret_cast<std::add_pointer_t<BedrockServer::OutputType>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->backupStarting(); break;
        case 3: _t->backupStarted(); break;
        case 4: _t->backupInProgres(); break;
        case 5: _t->backupSavingData(); break;
        case 6: _t->backupFinishedOnServer(); break;
        case 7: _t->backupFailed(); break;
        case 8: _t->backupFinished((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->backupComplete(); break;
        case 10: _t->playerConnected((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 11: _t->playerDisconnected((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 12: _t->serverDifficulty((*reinterpret_cast<std::add_pointer_t<enum ServerDifficulty>>(_a[1]))); break;
        case 13: _t->serverPermissionList((*reinterpret_cast<std::add_pointer_t<QStringList>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QStringList>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QStringList>>(_a[3]))); break;
        case 14: _t->serverPermissionsChanged(); break;
        case 15: _t->serverWhitelist((*reinterpret_cast<std::add_pointer_t<QStringList>>(_a[1]))); break;
        case 16: _t->serverStatusLine((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 17: _t->serverConfigurationUpdated(); break;
        case 18: _t->shutdownServerIn((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 19: _t->scheduleBackup(); break;
        case 20: _t->startBackup(); break;
        case 21: _t->completeBackup(); break;
        case 22: _t->startServer(); break;
        case 23: _t->startServerAfter((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 24: _t->restartServerAfter((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 25: _t->stopServer(); break;
        case 26: _t->stopAndRestartServer(); break;
        case 27: _t->sendCommandToServer((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 28: _t->setDifficulty((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 29: _t->saveConfiguration(); break;
        case 30: _t->handleServerOutput(); break;
        case 31: _t->handleZipComplete(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)(BedrockServer::ServerState )>(_a, &BedrockServer::serverStateChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)(BedrockServer::OutputType , QString )>(_a, &BedrockServer::serverOutput, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)()>(_a, &BedrockServer::backupStarting, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)()>(_a, &BedrockServer::backupStarted, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)()>(_a, &BedrockServer::backupInProgres, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)()>(_a, &BedrockServer::backupSavingData, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)()>(_a, &BedrockServer::backupFinishedOnServer, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)()>(_a, &BedrockServer::backupFailed, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)(QString )>(_a, &BedrockServer::backupFinished, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)()>(_a, &BedrockServer::backupComplete, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)(QString , QString )>(_a, &BedrockServer::playerConnected, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)(QString , QString )>(_a, &BedrockServer::playerDisconnected, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)(ServerDifficulty )>(_a, &BedrockServer::serverDifficulty, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)(QStringList , QStringList , QStringList )>(_a, &BedrockServer::serverPermissionList, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)()>(_a, &BedrockServer::serverPermissionsChanged, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)(QStringList )>(_a, &BedrockServer::serverWhitelist, 15))
            return;
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)(QString )>(_a, &BedrockServer::serverStatusLine, 16))
            return;
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)()>(_a, &BedrockServer::serverConfigurationUpdated, 17))
            return;
        if (QtMocHelpers::indexOfMethod<void (BedrockServer::*)(int )>(_a, &BedrockServer::shutdownServerIn, 18))
            return;
    }
}

const QMetaObject *BedrockServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BedrockServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13BedrockServerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BedrockServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 32)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 32;
    }
    return _id;
}

// SIGNAL 0
void BedrockServer::serverStateChanged(BedrockServer::ServerState _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void BedrockServer::serverOutput(BedrockServer::OutputType _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}

// SIGNAL 2
void BedrockServer::backupStarting()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void BedrockServer::backupStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void BedrockServer::backupInProgres()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void BedrockServer::backupSavingData()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void BedrockServer::backupFinishedOnServer()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void BedrockServer::backupFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void BedrockServer::backupFinished(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1);
}

// SIGNAL 9
void BedrockServer::backupComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void BedrockServer::playerConnected(QString _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1, _t2);
}

// SIGNAL 11
void BedrockServer::playerDisconnected(QString _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 11, nullptr, _t1, _t2);
}

// SIGNAL 12
void BedrockServer::serverDifficulty(ServerDifficulty _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 12, nullptr, _t1);
}

// SIGNAL 13
void BedrockServer::serverPermissionList(QStringList _t1, QStringList _t2, QStringList _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 13, nullptr, _t1, _t2, _t3);
}

// SIGNAL 14
void BedrockServer::serverPermissionsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void BedrockServer::serverWhitelist(QStringList _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 15, nullptr, _t1);
}

// SIGNAL 16
void BedrockServer::serverStatusLine(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 16, nullptr, _t1);
}

// SIGNAL 17
void BedrockServer::serverConfigurationUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}

// SIGNAL 18
void BedrockServer::shutdownServerIn(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 18, nullptr, _t1);
}
QT_WARNING_POP
