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
        source: "file:///home/spacedviking/Bilder/Wallpaper/wallpaperflare.com_wallpaper.jpg"
        Rules {
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



        MouseArea {
            hoverEnabled:true
            propagateComposedEvents: true
            onPositionChanged: {
                console.log("changed ", mouseX, mouseY);
            }
        }
    }