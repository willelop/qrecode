import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import qr.backend 1.0
import QtQuick.Extras 1.4
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.12
import qrecode.licenses 1.0

Component {

    component LicenseBlock: ColumnLayout {
        property string license_title;
        property string license_text;
        Label {
            Layout.fillWidth: true
            text: license_title;
            font.pointSize: 14
            font.bold: true
        }
        Text {
            text: license_text;
            Layout.fillWidth: true
            wrapMode: Label.WordWrap
            bottomPadding: 20
            font.pointSize: 10
            color: Material.foreground
        }
    }

    Page {
        id: licenses

        LicensesBackend {
            id: licBackend;
        }



        padding: 10
        header: ToolBar {
            id: toolBar
            RowLayout {
                id: rowLayout
                ToolButton {
                    id: menuButton
                    text: qsTr("Back")
                    display: AbstractButton.IconOnly
                    action: closeCurrent
                    icon.source: "qrc:/icons/arrow_back-black-18dp.svg"
                }

                Label {
                    id: label
                    text: qsTr("Licenses")
                    horizontalAlignment: Text.AlignLeft
                    Layout.fillWidth: true
                }
            }
        }

        ScrollView
        {
            contentWidth: licenses.availableWidth
            anchors.fill: parent
            ColumnLayout {
                anchors.fill: parent
                LicenseBlock {
                    license_title: "QR-Code Generation Library";
                    license_text: licBackend.qrCodeLic;
                }
                LicenseBlock {
                    license_title: "Material Icons";
                    license_text: licBackend.materialLic;
                }
                LicenseBlock {
                    license_title: "QRecode";
                    license_text: licBackend.softwareLic;
                }
                Item {
                    Layout.fillHeight: true;
                }
            }
        }
    }

}




/*##^##
Designer {
    D{i:6;anchors_width:0}
}
##^##*/
