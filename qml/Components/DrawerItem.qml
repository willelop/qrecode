import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

ItemDelegate {
    property ListModel model
            function itemText (index)
            {
                return model.get(index).name;
            }
            function getSource (index)
            {
                return model.get(index).iconSource
            }
            onClicked: {
                listView.actions[model.get(index).actionid]()
                mainDrawer.close()
            }
            icon.source: getSource (index)
            text: itemText (index)
        }
