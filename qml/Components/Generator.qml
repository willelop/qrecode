import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import qr.backend 1.0
import saver.backend 1.0
import QtQuick.Extras 1.4
import QtGraphicalEffects 1.0
import Qt.labs.settings 1.0
import QtQuick.Controls.Material 2.12
import Definitions 1.0

Page {
    id: page
    QrBackend {
        id: backend
    }
    SaverBackend {
        id: saverBackend
        imageSrc: image.source;
        onRequestFolder :fileDialog.visible = true
    }


    function syncSettings() {
        backend.regenerate();
    }

    header: ToolBar {
        Material.elevation: 0
        id: toolBar
        RowLayout {
            id: rowLayout
            anchors.fill: parent
            ToolButton {
                id: menuButton
                text: "Menu"
                display: AbstractButton.IconOnly

                icon.source: "qrc:/icons/menu-black-18dp.svg"
                action: openAppDrawer
            }
        }
    }




    Settings {
        id: settings
        //property alias includeText
        property alias lastString : textField.text;
    }

    padding: 10

    ScrollView
    {
        anchors.fill: parent
        width: parent.width
        height : parent.height
        contentWidth: column.width    // The important part
        Column {
            id: column
            width: page.width -2*page.padding
            height: page.height-2*page.padding

            RowLayout {
                id: inputRow
                width: parent.width
                Layout.fillWidth: true

                TextField {
                    id: textField
                    text: settings.lastString
                    selectByMouse: true
                    Layout.fillWidth: true
                    onTextChanged: backend.inputText = text
                }

                Button {
                    id: button
                    text: qsTr("Create")

                    Connections {
                        target: button
                        function onClicked() {backend.generate()}
                    }
                }

            }

            Image {
                id: image
                width: parent.width
                fillMode: Image.PreserveAspectFit
                cache: false
                enabled: false
                source: backend.imageSrc
            }

            RowLayout {
                id: saveRow
                width: column.width
                Button {
                    id: saveButton
                    text: qsTr("Save to Device")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true
                    visible: false
                    checked: false
                    checkable: false
                    Connections {
                        target: saveButton
                        function onClicked() {saverBackend.saveToDisk()}
                    }
                }
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a folder"
        folder: shortcuts.home
        selectExisting: true
        selectFolder: true
        selectMultiple: false
        onFileUrlChanged: {
            console.log("You chose: " + fileDialog.fileUrls)
            saverBackend.saveInFolder(decodeURIComponent(fileDialog.fileUrl))
        }

        onRejected: {
            console.log("Canceled")
        }
    }


    Connections {
        target: backend
        function onImageUpdated() { page.state = "qr_exists_state" }
    }
    states: [
        State {
            name: "qr_exists_state"

            PropertyChanges {
                target: saveButton
                visible: true
            }
        }
    ]
}






/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
