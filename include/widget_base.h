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
#include <QWidget>
#include <QMap>
#include <QString>
#include <QVariant>
#include <QMessageBox>
#include <memory>

namespace mrigtlbridge {

class SignalManager;
class ListenerBase;

class WidgetBase : public QObject {
    Q_OBJECT

public:
    explicit WidgetBase(QObject* parent = nullptr);
    virtual ~WidgetBase();

    // Build the GUI on the provided parent widget
    virtual void buildGUI(QWidget* parent);

    // Update the GUI based on the state
    virtual void updateGUI(const QString& state);

    // Set the signal manager
    virtual void setSignalManager(SignalManager* sm);

    // Start the listener
    virtual void startListener();

    // Stop the listener
    virtual void stopListener();

signals:
    void messageBoxSignal(const QString& message);

private slots:
    void onListenerConnected(const QString& className);
    void onListenerDisconnected(const QString& className);
    void onListenerTerminated(const QString& className);

protected:
    SignalManager* signalManager;
    ListenerBase* listener;
    
    // Class name and module for the listener
    QStringList listener_class;
    
    // Parameters for the listener
    QVariantMap listenerParameter;
    
    // Signal list
    QStringList signalList;
};

} // namespace mrigtlbridge