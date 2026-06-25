import QtQuick 2.15
import QtQuick.Controls 2.15
import PnPCompanion
import QtQuick.Layouts

// TODO STYLE
Item {
    id: base
    width: parent.width
    required property string name
    required property string description
    required property string formattedText
    height: 80


    property var fontSize: 20

        function setDesc(newDesc)
        {
            model.setData(model.index(base.index, 0), newDesc, 258);
            updateDesc();
        }
        function setName(newName)
        {
            model.setData(model.index(base.index, 0), newName, 257);
            updateName();
        }

        function updateName()
        {
            titleREAD.text = model.data(model.index(base.index, 0), 257);
            titleWRITE.text = model.data(model.index(base.index, 0), 257);
        }
        function updateDesc()
        {
            descREAD.text = model.data(model.index(base.index, 0), 259);
            descWRITE.text = model.data(model.index(base.index, 0), 258);
        }
        function updateData()
        {
            updateDesc();
            updateName();
        }

        function setNewHeight()
        {
            var titleHeight = Math.max((base.state === "WRITE" ? titleWRITE.height : titleREAD.height), editButton.height) + titleUnderLine.height;
            var descHeight = (base.state === "WRITE" ? descWRITE.height : descREAD.height);

            descBackground.height = descHeight;
            base.height = descHeight + titleHeight + column.padding + 5;/*bottom margin*/
        }

        Component.onCompleted: {
            model.setData(model.index(base.index, 0), "Test", 258); // desc
            //console.log(model.data(model.index(base.index, 0), 258));
            setNewHeight();
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
                id: column
                anchors.fill: parent

                RowLayout {
                    width: parent.width

                    Text {
                        id: titleREAD
                        text: base.name
                        color: "white"
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignBottom
                        Layout.leftMargin: 5
                        font.pointSize: base.fontSize
                        font.bold: true
                    }
                    TextInput {
                        id: titleWRITE
                        visible: false
                        Layout.fillWidth: true
                        color: "white"
                        Layout.alignment: Qt.AlignBottom
                        Layout.leftMargin: 5
                        text: base.name
                        onTextChanged: {
                            base.setName(text);
                        }
                        font.pointSize: base.fontSize
                        font.bold: true
                    }
                    Button {
                        id: editButton
                        text: "Edit"
                        Layout.preferredWidth: 64 // TODO icon for edit button
                        Layout.preferredHeight: 32
                        Layout.alignment: Qt.AlignRight
                        onClicked: {
                            if (base.state === "WRITE")
                            {
                                base.state = "READ";
                                base.description = descWRITE.text;
                                base.setNewHeight();
                            } else {
                            base.state = "WRITE";
                            base.setNewHeight();
                        }
                        //console.log("i am " + base.name + ", my state is: " + base.state);
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
                    textFormat: Text.MarkdownText
                    text: base.formattedText
                    Component.onCompleted: {
                        base.setNewHeight();
                        descBackground.height = height;
                    }
                    font.pointSize: base.fontSize
                }

                TextArea {
                    id: descWRITE
                    visible: false
                    textFormat: Text.PlainText
                    text: base.description
                    color: "black"
                    Component.onCompleted: {
                        base.setNewHeight();
                        descBackground.height = height;
                    }
                    font.pointSize: base.fontSize

                    onTextChanged: {

                        base.setDesc(text);
                        base.setNewHeight();
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
