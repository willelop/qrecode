import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import qrecode.previous 1.0
import QtQuick.Controls.Material 2.12

Component {



Page {
    id: page
    property  alias previousCodes: previousModel
    signal loadCode(var text,var image)
    title: "Recent QR Codes"

    Component.onCompleted:  loadCode.connect(function(text,image){
        stackView.push(generatorComponent,{state:"view_state",viewCodeText: text, viewCodeSrc: image});
    })


    header: ToolBar {
        //Material.elevation: 0
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
            Label {
                text: page.title
                font.pointSize: 13
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }
    ColumnLayout
    {
        anchors.fill: parent


        PreviousCodes{
            onLoadPreviousCode:  {
                loadCode(codeText,codeImage)
            }

            model: PreviousCodesModel{
                id: previousModel
            }
        }
    }

    RoundButton {
        x: 0
        y: 0
        width: 80
        height: 80
        text: qsTr("+")
        display: AbstractButton.TextOnly
        font.pointSize: 30
        z: 10.326
        anchors.right: parent.right
        anchors.rightMargin: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        action: openGenerator
        highlighted: true

        Material.accent: Material.primary
    }
}
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
