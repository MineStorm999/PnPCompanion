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


    Image {
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "qrc:/wallpapers/ninja.jpg"

        TreeView {
            id: treeView
            anchors.left: parent.left
            width: 400
            height: parent.height
            model: RuleNodeTreeModel {
                id: treeModel
            }

            rowSpacing: 5
            ScrollBar.vertical: ScrollBar {}
            //flickingHorizontally : false
            delegate: Item {
                required property string name

                required property TreeView treeView
                required property bool isTreeNode
                required property bool expanded
                required property bool hasChildren
                required property int depth
                required property int row
                required property int column
                required property bool current

                implicitWidth: treeView.width - (depth * 20)
                implicitHeight: txt.contentHeight
                x: (depth * 20) + treeView.x
                Rectangle {
                    Component.onCompleted: {
                        console.log("DEPTH: " + depth);
                    }
                    width: treeView.width - (depth * 40)
                    implicitHeight: parent.height

                    color: "#6d05082e"
                    border.width: 2
                    border.color: "black"
                    x: (depth * 40) + treeView.x

                    Text {
                        id: txt
                        text: name

                        width: parent.width
                        wrapMode: Text.Wrap
                        font.pointSize: 24
                        //anchors.rightMargin: (depth * 20) + treeView.x;
                    }
                    MouseArea {
                        propagateComposedEvents: true
                        anchors.fill: parent
                        /*Rectangle {
                        anchors.fill: parent
                        color: "black"
                    }*/
                    onClicked: mouse => {
                    treeView.toggleExpanded(row);
                }
                onDoubleClicked: mouse => { // TODO Handle tree item expanding / scroll to better
                rules.scrollToNode(name);
                treeView.toggleExpanded(row);
                mouse.accepted = false;
            }
        }
    }
}
}

Rules {
    id: rules
    anchors.right: parent.right
    width: parent.width - 400
    height: parent.height
}
}
Button {
    id: addNode
    text: "AddNode"
    x: 100
    property int i: 0
        onClicked: {
            ruleCreateDlg.open();
            //rules.addNode("NewNode" + (i++).toString(), "This a new node {Root}");           // Create a new RuleNode and add it to the model;
        }
    }
    Button {
        id: saveButton
        text: "Save"
        x: 200
        property int i: 0
            onClicked: {
                treeModel.save();           // Create a new RuleNode and add it to the model;
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
        RuleCreationDialog {
            id : ruleCreateDlg
        }
    }

