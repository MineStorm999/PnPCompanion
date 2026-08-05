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


    property string ruleName: ""
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

        function opn(rlName)
        {
            ruleName = rlName;
            updateNodeList();
            open();
        }

        onAccepted: {
            console.log("New Parent: " + cmboBx.model[cmboBx.currentIndex]);
            ruleNodeManagerInterface.changeParent(ruleNodeManagerInterface.getRule(ruleName), ruleNodeManagerInterface.getRule(cmboBx.model[cmboBx.currentIndex]));
        }
    }