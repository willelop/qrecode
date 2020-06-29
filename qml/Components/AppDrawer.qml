import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12


Drawer {
    id: mainDrawer
    height: parent.height
    edge: Qt.LeftEdge
    //Material.foreground: "white"

    ColumnLayout
    {
        anchors.fill: parent
        RowLayout{
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.fillWidth: true
            Label {
                Layout.fillWidth: true
                text: Definitions.appTitle
                font.weight: Font.Bold
                Layout.leftMargin: 15
                font.bold: false
                font.pointSize: 13
                horizontalAlignment: Text.AlignLeft
            }
            ToolButton {
                icon.source: "qrc:/icons/arrow_back-black-18dp.svg"
                onClicked: mainDrawer.close();
            }
        }
        ListView {
            id:listView
            model: entryModel
            z:0
            property var actions : {
                0: function(){ console.log("No Action Configured")},
                1: function(){ openSettingsAction.trigger() },
                2: function(){ openLicensesAction.trigger() },
                3: function(){Qt.openUrlExternally("https://github.com")}

            }
            Layout.fillWidth: true
            Layout.fillHeight: true

            delegate: DrawerItem {
                model: listView.model
                width: parent.width

            }
        }
    }

    ListModel {
        id: entryModel
        ListElement {
            name: qsTr("Settings")
            actionid: 1
            iconSource: "qrc:/icons/settings-24px.svg"
        }
        ListElement {
            name: qsTr("Github")
            iconSource: "qrc:/icons/code-24px.svg"
            actionid: 3
        }
        ListElement {
            name: qsTr("Licenses")
            iconSource: "qrc:/icons/flag-24px.svg"
            actionid: 2
        }
    }




}
