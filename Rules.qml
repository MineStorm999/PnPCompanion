import QtQuick 2.15
import QtQuick.Controls 2.15
import PnPCompanion

ListView {
    id: listView
    RuleNodeListModel {
        id: listModel
    }
    anchors.fill: parent
    model: listModel

    ScrollBar.vertical: ScrollBar {}

    delegate: Rectangle {
        width: listView.width
        height: 50
        color: "blue"

        required property string name
        required property string description
        Column {
            anchors.fill: parent
            Text {
                text: name
            }
            Text {
                text: description
            }
        }
    }

    function addNode(name, description) {
        listModel.addNode(name, description);
    }
}
