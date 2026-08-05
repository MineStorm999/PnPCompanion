import QtQuick 2.15
import QtQuick.Controls 2.15
import PnPCompanion

Dialog {

    anchors.centerIn: parent

    title: "Create new Rule"
    id: base
    width: parent.width * 0.9
    height: 150
    modal: true

    property int parentID: -1

        function setNewHeight()
        {
            base.height = ruleDesc.contentHeight + ruleName.contentHeight + 150
        }

        Component.onCompleted: {
            setNewHeight();
        }

        Column {
            TextInput {
                id: ruleName
                text: "New_Node"
                color: "white"
                font.pointSize: 24
            }

            TextArea {
                id: ruleDesc
                textFormat: Text.PlainText
                text: "Description of the new Rule."
                font.pointSize: 24
                color: "white"

                wrapMode: Text.WordWrap
                onTextChanged: {
                    base.setNewHeight();
                }
                background: Rectangle {
                    color: "transparent"
                    border.color: "transparent"
                }
            }
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