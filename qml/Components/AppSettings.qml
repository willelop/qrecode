import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import qr.backend 1.0
import QtQuick.Extras 1.4
import QtGraphicalEffects 1.0
import Qt.labs.settings 1.0
import QtQuick.Controls.Material 2.12


Page {
    id: settingsDrawer
    //edge: Qt.RightEdge
    Settings {
        id: settings
        property alias imageFormatId: imageFormatCombo.currentIndex
        property alias imageFormatText: imageFormatCombo.currentText
        property alias includeText: includeTextSwitch.checked
        property alias imageSize: sizeSlider.value
    }

    header: ToolBar {
        Material.elevation: 0
        id: toolBar
        RowLayout {
            id: rowLayout
            anchors.fill: parent
            ToolButton {
                id: menuButton
                text: qsTr("Back")
                display: AbstractButton.IconOnly
                action: closeCurrent
                icon.source: "qrc:/icons/arrow_back-black-18dp.svg"
            }

            Label {
                id: label
                text: qsTr("Settings")
                horizontalAlignment: Text.AlignLeft
                Layout.fillWidth: true
            }
        }
    }
    GridLayout {
        columns: 2
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        Label {
            id: label1
            text: qsTr("Include Text Below Image")
        }
        Switch {
            id: includeTextSwitch
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.columnSpan: 1
            checked: settings.includeText
        }
        Label {
            id: imageFormatLabel
            text: qsTr("Image Format")
        }
        ComboBox {
            id: imageFormatCombo
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            currentIndex: settings.imageFormatId

            model: ListModel {
                id: model
                ListElement { text: "PNG"; }
                ListElement { text: "BMP"; }
                ListElement { text: "JPG"; }
            }
        }
        RowLayout {
            id: imageSize
            Layout.columnSpan: 2
            Label {
                id: sizeDesc
                text: qsTr("Image Size")
            }
            Slider {
                id: sizeSlider
                Layout.fillWidth: true
                stepSize: 40
                to: 1280
                from: 320
                value: settings.imageSize
            }
            Label {
                id: sizeLabel
                text: sizeSlider.value.toString() + "px"
                horizontalAlignment: Text.AlignRight
            }
        }
        Label {
            id: darkModeLabel
            text: qsTr("Night Mode")
        }
        Switch {
            id: darkMode
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            checked: applicationWindow.darkTheme
            onCheckedChanged: applicationWindow.darkTheme = checked
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
