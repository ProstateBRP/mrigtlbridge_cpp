/*=========================================================================

  Program:   mrigtlbridge
  Language:  C++
  Web page:  https://github.com/ProstateBRP/mrigtlbridge_cpp

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#pragma once

#include <QObject>
#include <QString>
#include <QVariant>
#include <QVariantMap>

namespace mrigtlbridge {

// Base class for signal wrappers
class SignalWrap : public QObject {
public:
    virtual bool emitSignal(const QVariant& param = QVariant()) = 0;
    QString paramType;
};

// Wrapper for signals with no parameters
class SignalWrapVoid : public SignalWrap {
    Q_OBJECT
public:
    SignalWrapVoid() { paramType = ""; }
    bool emitSignal(const QVariant& param = QVariant()) override {
        Q_UNUSED(param);
        emit signal();
        return true;
    }
signals:
    void signal();
};

// Wrapper for signals with string parameter
class SignalWrapStr : public SignalWrap {
    Q_OBJECT
public:
    SignalWrapStr() { paramType = "str"; }
    bool emitSignal(const QVariant& param = QVariant()) override {
        emit signal(param.toString());
        return true;
    }
signals:
    void signal(const QString& param);
};

// Wrapper for signals with dictionary parameter
class SignalWrapDict : public SignalWrap {
    Q_OBJECT
public:
    SignalWrapDict() { paramType = "dict"; }
    bool emitSignal(const QVariant& param = QVariant()) override {
        emit signal(param.toMap());
        return true;
    }
signals:
    void signal(const QVariantMap& param);
};

} // namespace mrigtlbridge