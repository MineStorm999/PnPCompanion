import QtQuick 2.15
import QtQuick.Controls 2.15
import PnPCompanion
import QtQuick.Layouts

Item {
    id: base
    anchors.right: parent.right
    required property string name
    required property string description
    required property string formattedText
    required property string depth
    required property int index
    property int children: 0 // TODO Query from model

        width: parent.width * (1 - ((depth) * 0.03))
        height: 40

        property var fontSize: 20

            function setDesc(newDesc)
            {
                //base.description = newDesc;
                model.setData(model.index(base.index, 0), newDesc, 258);
                updateDesc();
            }
            function setName(newName)
            {
                //base.name = newName;
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
                depth = model.data(model.index(base.index, 0), 260);
                //base.width = base.parent.width * (1 - ((depth) * 0.03));

                console.log(depth);
                console.log("updating: " +index);
                setNewHeight();
            }

            function setNewHeight()
            {
                var titleHeight = Math.max((base.state === "WRITE" ? titleWRITE.contentHeight : titleREAD.contentHeight), editButton.height * (editButton.visible ? 1 : 0)) + titleUnderLine.height;
                descBackground.height = (base.state === "WRITE" ? descWRITE.height : descREAD.height);

                base.height = descBackground.height + titleHeight + column.padding + 5;/*bottom margin*/
                bG.height = base.height;
            }

            Component.onCompleted: {
                updateData();
                setNewHeight();
                console.log("depth: " + base.depth);
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
                },
                State {
                    name: "PLAYER"
                    PropertyChanges {
                        titleREAD.visible: true
                        descREAD.visible: true

                        titleWRITE.visible: false
                        descWRITE.visible: false

                        editButton.visible: false
                    }
                }
            ]
            Rectangle {
                height: parent.height
                width: parent.width
                color: "transparent"
                id: bG

                //name: "Test"
                Column {
                    id: column
                    anchors.fill: parent

                    RowLayout {
                        width: parent.width

                        Text {
                            id: titleREAD
                            text: base.name

                            wrapMode: Text.Wrap
                            color: "white"
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignBottom
                            Layout.leftMargin: 5
                            font.pointSize: 32//base.fontSize;
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
                            font.pointSize: 32//base.fontSize
                            font.bold: true
                        }
                        Button {
                            id: addChildButton
                            text: "Add Child Rule"
                            onClicked: {
                                base.children+=1;
                                model.addChildNode(base.children + "th_NewChildNode_of_" + titleREAD.text, "This is a child of {" + titleREAD.text + "} rule", base.index);
                            }
                        }
                        Button {
                            id: editButton
                            //text: "Edit"
                            //icon.color: "transparent"

                            Layout.preferredWidth: 64 // TODO icon for edit button
                            Layout.preferredHeight: 64

                            icon.source: "qrc:/icons/edit.png"
                            icon.height: Layout.preferredHeight
                            icon.width: Layout.preferredWidth

                            Layout.alignment: Qt.AlignRight

                            background: Rectangle {
                                color: "transparent"
                                border.color: "black"
                                border.width: 3
                                radius: 5

                            }


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
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "#6d05082e"
                    Text {
                        id: descREAD
                        textFormat: Text.MarkdownText
                        text: base.formattedText
                        width: parent.width
                        wrapMode: Text.Wrap
                        color: "white"

                        onWidthChanged: {
                            base.setNewHeight();
                        }
                        Component.onCompleted: {
                            base.setNewHeight();
                        }
                        font.pointSize: base.fontSize

                        RuleNodeHint {
                            id: tT
                            x: 100;
                            y: 200;
                            delay: 200
                            function show()
                            {
                                visible = true;
                            }
                            function hide()
                            {
                                visible = false
                            }
                        }

                        onLinkHovered: (link)=>{
                        if (link === "")
                        {
                            tT.visible = false;
                        }else {
                        tT.showHint(link);
                    }
                }

                onLinkActivated: (link)=>{
                if (link != "")
                {
                    listView.scrollToNode(link);
                    console.log("Scrolling");
                }
            }
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.NoButton
                hoverEnabled: true
                onPositionChanged: {
                    tT.y = mouseY + 20;
                    tT.x = mouseX;
                }

            }
        }

        TextArea {
            id: descWRITE
            visible: false
            textFormat: Text.PlainText
            text: base.description
            color: "white"
            Component.onCompleted: {
                base.setNewHeight();
            }
            font.pointSize: base.fontSize
            wrapMode: Text.WordWrap
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
