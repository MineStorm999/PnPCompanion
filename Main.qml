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

    Image {
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "qrc:/wallpapers/ninja.jpg"


        TreeView {
            anchors.left: parent.left
            id: treeView
            width: 200
            height: parent.height
            model: RuleNodeTreeModel {id: treeModel}
            delegate: Item {
                implicitWidth: treeView.width
                implicitHeight: 20
                required property string name

                required property TreeView treeView
                required property bool isTreeNode
                required property bool expanded
                required property bool hasChildren
                required property int depth
                required property int row
                required property int column
                required property bool current

                Text {
                    text: name
                }
                Component.onCompleted: {
                    console.log("HEEEEEEEEEEEEEEEEEEEEELLLLLLLLLLLLLOOOOOOOOOOOO");
                }
            }
        }

        Rules {
            anchors.right: parent.right
            width: parent.width - 200
            height: parent.height
            id: rules
        }

    }
    Button {
        id: addNode
        text: "AddNode"
        x: 100
        property int i: 0
            onClicked: {
                rules.addNode("NewNode" + (i++).toString(), "This a new node {Root}");           // Create a new RuleNode and add it to the model;
            }
        }


        /*
        MouseArea {
            hoverEnabled:true
            propagateComposedEvents: true
            onPositionChanged: {
                console.log("changed ", mouseX, mouseY);
            }
        }*/
    }