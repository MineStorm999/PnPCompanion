import QtQuick 2.15
import QtQuick.Controls 2.15
import PnPCompanion

Dialog {

    anchors.centerIn: parent

    title: "Create new Rule"
    id: base
    width: 150
    height: parent.height * 0.9
    modal: true


    property string parentName: ""
        standardButtons: Dialog.Ok | Dialog.Cancel

        ComboBox {
            height: 45
            width: parent.width
            id: cmboBx
            model: []
        }

        Component.onCompleted: {
            updateNodeList();
        }

        function updateNodeList()
        {
            cmboBx.model = ruleNodeManagerInterface.getRulesNames();
        }

        function opn(curParentName)
        {
            parentName = curParentName;
            updateNodeList();
            cmboBx.currentIndex = cmboBx.find(parentName)
            open();
        }

        onAccepted: {
            console.log("New Parent: " + cmboBx.model[cmboBx.currentIndex]);
            /*if (parentID < 0)
        {
            rules.addNode(ruleName.text, ruleDesc.text);
        }else {
        rules.addChildNode(ruleName.text, ruleDesc.text, parentID);*/
    }
}