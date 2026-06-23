import QtQuick 2.15
import QtQuick.Controls 2.15
import PnPCompanion
import QtQuick.Layouts
// TODO STYLE
Item {
    width: listView.width
    height: 80
    required property string name
    required property string description
    id: base

    function setNewHeight()
    {
        var titleHeight = Math.max((base.state === "WRITE" ? titleWRITE.height : titleREAD.height), editButton.height);
        base.height = (base.state === "WRITE" ? descWRITE.height : descREAD.height) + titleHeight + column.padding;
    }
    states: [
        State {
            name: "READ"
            PropertyChanges {
                titleREAD.visible: true
                descREAD.visible: true
                //titleREAD.text: name
                //descREAD.text: description

                titleWRITE.visible: false
                descWRITE.visible: false
            }
        },
        State {
            name: "WRITE"
            PropertyChanges {
                titleREAD.visible: false
                descREAD.visible: false

                titleWRITE.visible: true
                descWRITE.visible: true
            }
        }
    ]
    Rectangle {
        anchors.fill: parent
        color: "blue"

        //name: "Test"
        Column {
            anchors.fill: parent
            id: column
            RowLayout {
                width: parent.width
                Text {
                    id: titleREAD
                    text: name
                }
                TextInput {
                    visible: false
                    id: titleWRITE
                    text: name
                    color: "gray"
                    onTextChanged: {
                        name = text;
                    }
                }
                Button {
                    text:"Edit"
                    id: editButton
                    Layout.alignment: Qt.AlignRight
                    onClicked: {
                        if (base.state === "WRITE")
                        {
                            base.state = "READ";
                            base.setNewHeight();
                        }
                        else {
                            base.state = "WRITE";
                            base.setNewHeight()
                        }
                        console.log("i am " + name + ", my state is: " + base.state);
                    }
                }
            }
            Text {
                id: descREAD
                text: description
            }
            TextArea {
                visible: false
                id: descWRITE
                text: description
                color: "gray"
                Component.onCompleted: {
                    setNewHeight();
                }

                onTextChanged: {
                    description = text;
                    setNewHeight();
                }
            }
        }


    }
}