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

    delegate: RuleNodeDel {}

    function addNode(name, description)
    {
        listModel.addNode(name, description);
    }
}
