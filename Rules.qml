import QtQuick
import QtQuick.Controls
import PnPCompanion

ListView {
    id: listView
    RuleNodeListModel {
        id: listModel
    }
    anchors.fill: parent
    model: listModel
    spacing: 5

    ScrollBar.vertical: ScrollBar {}

    delegate: RuleNodeDel {}

    function addNode(name, description)
    {
        listModel.addNode(name, description);
    }
}
