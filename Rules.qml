import QtQuick 2.15
import QtQuick.Controls 2.15
import PnPCompanion

ListView {
    id: listView
    anchors.fill: parent
    required model

    ScrollBar.vertical: ScrollBar {}
    delegate: Rectangle {
        width: listView.width
        height: 100
        color: "blue"
        required property string name
        required property string description
        Column {
            Text {
                text: parent.name
            }
            Text {
                text: parent.description
            }
        }
    }
}
