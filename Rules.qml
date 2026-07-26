import QtQuick
import QtQuick.Controls
import PnPCompanion
import QtQuick.Layouts

ListView {
    id: listView
    RuleNodeListModel {
        id: listModel
    }
    model: listModel
    spacing: 5

    ScrollBar.vertical: ScrollBar {}

    delegate: RuleNodeDel {

    }

    function scrollToNode(nodeName)
    {
        listView.positionViewAtIndex(listModel.getIndex(nodeName), ListView.Beginning);
        var index = treeModel.getRuleIndex(nodeName);
        listModel.setNewChapter(nodeName);
        treeView.expandToIndex(index)
        treeView.forceLayout()
        treeView.positionViewAtIndex((index), Qt.AlignVCenter)

    }

    function addNode(name, description)
    {
        listModel.addNode(name, description);
    }


    function addChildNode(name, description, parentID)
    {
        listModel.addChildNode(name, description, parentID);
    }

    function isNameTaken(name)
    {
        return listModel.isNameTaken(name);
    }
}
