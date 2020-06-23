import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import qr.backend 1.0
import QtQuick.Extras 1.4
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.12
import Qt.labs.settings 1.0
import qrecode.utils 1.0


import "qrc:/qml/Components" as Components



ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 360
    height: 640
    color: "#5d6377"
    title: qsTr("QRecode")
    property int darkTheme: -1;
    Material.primary: Material.backgroundColor

    onDarkThemeChanged:
    {
        Material.theme = darkTheme == -1 ? Material.System : (darkTheme == 1 ? Material.Dark : Material.Light)
        utils.changeTheme(Material.backgroundColor,darkTheme)
    }

    QRecodeUtils {
        id: utils
    }

    Settings {
        id: settings
        property alias darkTheme: applicationWindow.darkTheme
    }

    Action {
        id: openSettingsAction
        icon.name: "menu"
        onTriggered: stackView.push(settingsPanelComponent)
    }
    Action {
        id: openLicensesAction
        icon.name: "menu"
        onTriggered: stackView.push(licensesPageComponent)
    }
    Action {
        id: openAppDrawer
        icon.name: "menu"
        onTriggered: applicationDrawer.open()
    }
    Action {
        id: closeCurrent
        icon.name: "menu"
        onTriggered: stackView.pop()
    }

    StackView
    {
        id: stackView
        initialItem:generatorComponent
        anchors.fill: parent
    }

    Component {
        id: generatorComponent
        Components.Generator {
            id: generator
            StackView.onActivated:  syncSettings()
        }
    }
    Component {
        id: settingsPanelComponent
        Components.AppSettings {
            id: settingsPanel

        }
    }
    Component {
        id: licensesPageComponent
        Components.Licenses {
            id: licensesPage

        }
    }
    Components.AppDrawer {
        id: applicationDrawer
    }

}










