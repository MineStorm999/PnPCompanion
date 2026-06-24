import QtQuick 2.15
import QtQuick.Controls 2.15
import PnPCompanion
import QtQuick.Layouts
// TODO STYLE
Item {
    width: listView.width
    required property string name
    required property string description
    id: base
    height: 80


    property var fontSize: 20

        function setNewHeight()
        {
            var titleHeight = Math.max((base.state === "WRITE" ? titleWRITE.height : titleREAD.height), editButton.height) + titleUnderLine.height;
            var descHeight = (base.state === "WRITE" ? descWRITE.height : descREAD.height)

            descBackground.height = descHeight
            base.height = descHeight + titleHeight + column.padding + 5/*bottom margin*/;
        }

        Component.onCompleted: {
            setNewHeight()
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
            color: "black"

            //name: "Test"
            Column {
                anchors.fill: parent
                id: column

                RowLayout {
                    width: parent.width

                    Text {
                        id: titleREAD
                        text: name
                        color:"white"
                        Layout.fillWidth : true
                        Layout.alignment: Qt.AlignBottom
                        Layout.leftMargin: 5
                        font.pointSize: base.fontSize
                        font.bold: true
                    }
                    TextInput {
                        visible: false
                        Layout.fillWidth : true
                        color:"white"
                        Layout.alignment: Qt.AlignBottom
                        Layout.leftMargin: 5
                        id: titleWRITE
                        text: name
                        onTextChanged: {
                            name = text;
                        }
                        font.pointSize: base.fontSize
                        font.bold: true
                    }
                    Button {
                        text:"Edit"
                        id: editButton
                        Layout.preferredWidth : 64 // TODO icon for edit button
                        Layout.preferredHeight : 32
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

                Rectangle {
                    id: titleUnderLine
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 2
                    width: parent.width - 10

                    color: "yellow"
                }
                Rectangle {
                    id: descBackground
                    anchors.topMargin: 5
                    width: parent.width - 10
                    height: 50
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "gray"
                    Text {
                        id: descREAD
                        text: description
                        Component.onCompleted: {
                            setNewHeight();
                            descBackground.height = height
                        }
                        font.pointSize: base.fontSize
                    }

                    TextArea {
                        visible: false
                        id: descWRITE
                        text: description
                        text: '<html><style type="text/css"></style><a href="http://google.com">google</a></html>'
                        color: "black"
                        Component.onCompleted: {
                            setNewHeight();
                            descBackground.height = height
                        }
                        font.pointSize: base.fontSize

                        onTextChanged: {
                            description = text;
                            setNewHeight();
                        }
                        background: Rectangle {
                            color: "transparent"
                            border.color: "transparent"
                        }
                    }
                }
            }


        }
    }