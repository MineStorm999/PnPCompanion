import QtQuick
import QtQuick.VirtualKeyboard
import PnPCompanion
import QtQuick.Controls

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    InputPanel {
        id: inputPanel
        z: 99
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                inputPanel.y: window.height //- inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            NumberAnimation {
                properties: "y"
                easing.type: Easing.InOutQuad
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color:"#292b33"
        Rules {
            id: rules
        }
    }
    Button {
        id: addNode
        text: "AddNode"
        property int i: 0
            onClicked: {
                rules.addNode("NewNode" + (i++).toString(), "This a new node");           // Create a new RuleNode and add it to the model;
            }
        }
    }
