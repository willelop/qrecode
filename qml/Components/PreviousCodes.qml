import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

ListView
{
    signal loadPreviousCode(var codeText,var codeImage)
    property int listMargin: 5
    leftMargin: listMargin
    rightMargin: listMargin
    topMargin: listMargin
    bottomMargin: listMargin
    Component {
        id: delegateComp
        ItemDelegate  {
            padding: listMargin
            leftPadding: 10
            clip: true
            icon.source: model.imageSrc
            icon.height:80
            icon.width: 80
            width: parent ? (parent.width - 2*listMargin):0
            icon.color: "transparent"
            property string codeDate: model.timestamp ? model.timestamp.toLocaleDateString():"nodate"
            text: "<b>"+model.text + "</b>" + "<br/>" + "<i>"+ codeDate + "</i>"

            Rectangle
            {
                color: "#00000000"
                radius: 5
                border.color: "#597b7b7b"
                border.width: 1
                anchors.fill: parent
                z: -10
            }

            onClicked: {
                loadPreviousCode(model.text,model.imageSrc)
            }
        }
    }
    id: previousView
    spacing: 3
    Layout.fillWidth: true
    Layout.fillHeight: true
    clip: true
    delegate: delegateComp
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
