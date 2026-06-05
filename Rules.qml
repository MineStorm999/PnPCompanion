import QtQuick 2.15
import QtQuick.Controls 2.15
import PnPCompanion

Rectangle{
    id: root
    anchors.fill: parent
    ListView {
        id: listView
        anchors.fill: parent
        required model

        delegate: Rectangle {
           width: listView.width
           height: 100
           required property string name
           required property string description
           Column{
            
           }
        }
    }
}