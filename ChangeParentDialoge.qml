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

        Component.onCompleted: {
            setNewHeight();
        }


        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: {
            console.log("New Rule: " + ruleName.text + " " + ruleDesc.text);
            if (parentID < 0)
            {
                rules.addNode(ruleName.text, ruleDesc.text);
            }else {
            rules.addChildNode(ruleName.text, ruleDesc.text, parentID);
        }
    }
    onRejected: console.log("Cancel clicked")
}